## Kubelet

kubelet组件是K8S集群工作节点中最重要的组件，它负责管理和维护在这台主机上运行着的所有容器(使得pod的运行状态与它的期望值spec一致)

### kubelet与cAdvisor交互

`cAdvisor`是谷歌开发的用于分析运行中容器的资源占用和性能指标的开源工具，它是一个运行时的守护进程，负责收集、聚合、处理和输出运行中容器的信息，通过暴露一个TCP端口对外提供一套REST API

- **容器信息**

  URL:`/api/{api version}/containers/绝对容器名`

  如`/api/v1.0/containers/docker/2c4dee605.`

- **宿主机信息**

  URL:`/api/{api version}/machine`

### kubelet的垃圾回收机制

kubelet的垃圾回收机制分为`容器回收`与`镜像回收`

#### 容器回收

docker容器回收策略主要涉及3个因素

|         名称         |           含义            |   备注    |
| :----------------: | :---------------------: | :-----: |
|       MinAge       |      回收前距离创建时间的最小值      | =0：没有限制 |
| MaxPerPodContainer | 每个pod最多留有的停止的相同容器名的容器数目 | <0：没有限制 |
|   MaxContainers    |    每个工作节点上最多拥有的容器数目     | <0：没有限制 |

**回收步骤**

1. 获取所有可以被kubelet垃圾回收的容器(过滤、排序)
2. 根据垃圾回收策略回收镜像(上面列表的参数)

#### 镜像回收

docker镜像回收策略主要涉及3个因素

|          名称           |       含义       |
| :-------------------: | :------------: |
| HighThreshouldPercent | 触发镜像回收的磁盘使用率上限 |
|  LowThresholdPercent  | 触发镜像回收的磁盘使用率下限 |
|        MinAge         | 触发镜像回收时至少存在的时间 |

**回收步骤**

1. 调用`cAdvisor`客户端API获取工作节点的文件系统信息(磁盘设备、挂载点、总容量、使用量等)
2. 根据垃圾回收策略删除镜像来释放空间

### kubelet对工作节点的同步

首先，kubelet调用APIServer API向etcd获取包含当前工作节点状态信息的node对象；

然后调用`cAdvisor`客户端API获取当前工作节点的宿主机信息(IP、机器信息、磁盘信息、工作节点状态、是否可被调度)，更新获取到的node对象；

最后kubelet再次调用APIServer API将上述更新持久化到etcd中
