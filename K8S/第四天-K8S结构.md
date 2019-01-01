## K8S 架构

K8S由两种节点组成：`master节点`(管理节点)和`工作节点`(容器运行的节点)

### master节点

master节点主要有3个重要的组件，分别是`APIServer`、`Scheduler`、`Controller Manager`

#### APIServer

K8S APIServer负责对外提供Kubernetes API服务，任何对资源增删改查的操作都要交给APIServer处理后才能提交给etcd

- 对外提供基于RESTFul的管理接口
- 配置K8S的资源对象
- 提供可定制的功能插件
- 系统日志收集功能
- 可视化API

#### Scheduler

K8S Scheduler是一个典型的单体调度器，它的作用是根据特定的调度算法将pod调度到指定的工作节点上，这一过程通常称为绑定(bind)

![](http://qiniu.itliusir.com/scheduler.png)

- **数据采集模型**

  K8S没有消息系统帮助用户实现各组件间的高效通信，所以Scheduler专门对感兴趣的资源和数据设置了本地缓存机制(简单的无序cache对象:可用的podLister NodeLister ServiceLister等 、有序数据的先进先出队列:podQueue)

- **调度算法**

  - default
  - 自定义

- **启动与运行**

  1. 收集scheduler产生的事件信息并构建事件对象，然后向APIServer发送这些对象，最终由APIServer调用etcd客户端接口将这些事件进行持久化
  2. 创建一个http server，默认绑定到IP地址(default:0.0.0.0)上并监听端口(default:10251)
  3. 根据配置信息创建调度器并启动SchedulerServer
  4. 注册metrics规则，用于检测调度工作的性能

- **multi-scheduler**

#### Controller Manager

K8S Controller Manager是基于Pod API上的一个独立服务，它管理着K8S集群中的各种控制器，如大家熟知的Replication Controller、Node Controller等

- **启动过程**

  1. 根据用户传入的参数以及默认参数创建kubeconfig(包含了Controller Manager在工作中需要使用的配置信息)和kubeClient(与APIServer进行交互的客户端)
  2. 创建一个http server，对外暴露`/debug/pprof/`、`/debug/pprof/profile`、`/debug/pprof/symbol`和`/metrics`用于辅助debug和收集metric数据
  3. 按照顺序创建各种控制管理器

  > 其控制pod、工作节点等资源正常运行的本质就是靠各种controller定时对pod、工作节点等资源进行检查，然后判断实际运行状态与期望是否一致，若不一致则通知APIServer进行增删改操作

- **服务端点控制器(endpoint controller)**

  **当用户在K8S中创建一个包含label selector的service对象时，系统会随之创建一个对应的endpoint对象，该对象即保存了所有匹配service的label selector后端pod的IP地址和端口**

  endpoint controller维护了两个缓存池，其中serviceStore用于存储service，podStore用于存储pod，并且使用controller的reflector机制实现两个缓存与etcd内数据的同步

  endpoint通过多个goroutine来同时处理service队列中的状态更新，goroutine的数量由controller manager的ConcurrentEndpointSyncs参数来指定，默认为5个，不同goroutine相互之间互不干扰

  **goroutine的工作步骤：**

  1. 从service队列中取出当前处理的service名，在serviceStore中查找该service对象，若该对象不存在，则删除其所对应的所有endpoint
  2. 构建service对应的endpoint的期望状态。根据service.Spec.Selector从podStore中获取该service对应的后端pod对象列表。对于每一个pod将pod.Status.PodIP、pod.Spec.Hostname和service.spec中定义的端口号，版本号这些组成一个EndpointSubset对象，然后将这些对象组成一个slice subset，这就是期望的endpoint状态
  3. 使用service名作为检索键值，调用APIServer的API获取当前系统中存在的endpoint对象列表currentEndpoints(当前实际状态)，如果找不到对应的endpoint则将新建一个新的endpoint对象给currentEndpoints，此时ResourceVersion为0，ResourceVersion也是用来判断endpoint是创建还是更新

  > 通过上述分析可以看出，controller的一般处理逻辑是先获取某种资源对象的期望状态，期望状态可能是存储在etcd里的spec字段下的数据，也可能是类似endpoint这种动态构造。然后将之与实际状态对比，最后向APIServer发请求弥补两者之间可能存在的差别

- **副本管理控制器(replication controller，rm)**

  负责保证rc管理的pod的**期望副本数**与**实际运行的pod数量**匹配

  与endpoint controller类似，rm本地也维护了两个缓存池rcStore和podStore，分别同步rc与pod在etcd的数据，同样使用reflector机制实现两个缓存与etcd内数据的同步，rcStore更新时候会将该rc对象加入待更新队列queue中

  rc启用了多个goroutine对其进行同步工作

  **goroutine的工作步骤：**

  1. 从rc队列中取出当前处理的rc名，通过rcStore获得该rc对象，如果rc不存在则从`expectations`中将该rc删除；如果查询时返回的是其他错误，则重新将该rc入队
  2. 检查该rc的`expectations`是否被满足或者TTL超时，如果是则需要同步
  3. 调整rc中的副本数，将从APIServer获取的pod列表与rc的.spec.replicas字段相减得到diff，如果diff小于0表示还需要更多的副本，设置`expectations`中的add值为|diff|，并且调用APIServer的API发起pod的创建请求，创建完毕add-1。同理如果diff大于0就需要清除一些pod
  4. 最后，调用APISever的API更新rc的status.replicas

  > expectations是rm用于记住每个rc期望看到的pod数的TTL cache，为每个rc维护了原子技术器(add/del)，对于创建的会add-1，删除的会del-1，当add或者del小于等于0就代表rc的期望已经被满足啦

  > 本节的rc指的是副本控制器 rm(也叫replication controller)指的是副本管理控制器

- **垃圾回收控制器(gc controller)**

  gc controller维护了一个缓存池podStore，用于存储终止状态的pod(podPhase非Pending/Running/Unknow三者的pod)，使用reflector机制监听APIServer对podStore进行更新

- **节点控制器(node  controller)**

  node controller主要用于检查K8S的工作节点是否可用，它会定期检查所有在运行的工作节点上的kubelet进程来获取这些工作节点的信息，若kubelet在规定时间内没有推送该节点状态则将其NodeCondition为Ready的状态置成Unknow，并写入etcd中

### 工作节点

#### 描述方式

K8S将工作节点也看作是资源对象的一种，用户可以像创建pod那样，通过资源配置文件或kubectl命令行工具来创建一个node资源对象。创建node资源对象只是为了抽象并维护工作节点的相关信息(spec、status)，并对工作节点是否可用进行持续的追踪

K8S主要维护工作节点的spec和status属性，分别用来描述期望状态和当前状态，期望状态是由一个json资源配置文件构成，描述了一个工作节点的具体信息，当前状态包含如下相关信息：

- Node Address——工作节点的主机地址信息
- Node Phase——工作节点的生命周期，分为Pending、Running和Terminated
- Node Condition——描述Running状态下工作节点的细分情况
- Node Capacity与Node Allocatable——工作节点上的资源总量和当前可供调度的资源等
- Node Info——如内核信息、runtime版本(docker)、kubelet版本等，这些信息由kubelet收集
- Images——工作节点上存在的容器镜像列表
- Daemon Endpoint——工作节点上运行的kubelet监听的端口

#### 管理机制

工作节点的动态维护过程是依靠node controller来完成的，通过循环来不断检测当前K8S已知的每台工作节点是否正常工作，如果是正常则将其添加为工作节点的一员，反之则会删除

> node controller主要职责是负责监控有kubelet发送过来的工作节点运行状态，监控间隔是5秒钟，node controller与其他controller不同之处是其实际上的工作节点是由IAAS平台来做，etcd里存放的node资源只是一种说明它是否正常的描述性资源，其信息由kubelet提供
