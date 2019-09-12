## kubectl Command

### Get

以下命令以Pod举例，Service、ReplicaSet、Deployment、...都一样，命令中的pod换为service、replicaset、deployments即可.

- 查询所有Pod

  ```shell
  > kubectl get pods
  NAME                              READY     STATUS    RESTARTS   AGE
  eureka-58886df557-txwl9           1/1       Running   0          13d
  > kubectl get pods -o wide
  NAME                              READY     STATUS    RESTARTS   AGE       IP              NODE
  eureka-58886df557-txwl9           1/1       Running   0          13d       10.42.88.73     eureka1
  ```

- 查询某个Pod

  ```shell
  > kubectl get pod/eureka-58886df557-txwl9
  ```

- 根据label查询

  ```shell
  > kubectl get pod -l app=eureka
  ```

- 根据namespace查询

  ```shell
  > kubectl get namespaces
  NAME           STATUS    AGE
  default        Active    17d
  istio-system   Active    9d
  kube-dev       Active    9d
  kube-public    Active    17d
  kube-system    Active    17d
  > kubectl get pod --namespace=default
  NAME                              READY     STATUS    RESTARTS   AGE
  eureka-58886df557-txwl9           1/1       Running   0          13d
  ```

- 以JSON格式输出

  ```shell
  > kubectl get -o json pod eureka-58886df557-txwl9
  {
      "apiVersion": "v1",
      "kind": "Pod",
      "metadata": {
          "creationTimestamp": "2018-06-08T07:01:18Z",
          "generateName": "eureka-58886df557-",
          "labels": {
              "app": "eureka",
              "pod-template-hash": "1444289113"
          },
          "name": "eureka-58886df557-txwl9",
          "namespace": "default",
          ...
  ```

- 查询value值

  ```shell
  > kubectl get -o template pod/eureka-58886df557-txwl9 --template={{.status.phase}}
  Running
  > kubectl get -o template pod/eureka-58886df557-txwl9 --template={{.metadata.name}}
  eureka-58886df557-txwl9
  > kubectl get -o template pod/eureka-58886df557-txwl9 --template={{.status.podIP}}
  10.42.88.73
  ```

### Create

创建kubernetes对象

```shell
> kubectl create -f xxx.json
```

参数-f

```shell
-f, --filename=[]: Filename, directory, or URL to files to use to create the resource
```

### Apply

在原有资源基础上进行更新

```shell
> kubectl apply -f new-xxx.yaml
```

### Edit

与Apply一样都是更新，Edit在执行如下命令后会让你更新对应的yaml文件，相当于修改完yaml文件然后执行replace

```shell
> kubectl edit pod/eureka-58886df557-txwl9
```

### Logs

查看日志

```shell
> kubectl logs pod/eureka-58886df557-txwl9
```

### Delete

删除

```shell
# 根据xxx.json指定的name删除
> kubectl delete -f xxx.json
# 删除指定pod(service、replicaset)
> kubectl delete pod/xxx
# 根据labels删除pods(services、replicasets)
> kubectl delete pods -l app=eureka
```

### Rollout

对deployment失败的资源进行回滚操作

```shell
> kubectl rollout --help
Available Commands:
  history     展示历史版本
  pause       将资源标记为暂停
  resume      恢复一个暂停的资源
  status      显示rollout的状态
  undo        回滚到指定的版本
```
---

`docker`容器管理的要求：

|要求|含义|
|---|---|
|调度|我的容器该在哪里运行|
|生命周期管理和健康检查|如何保证容器可以在不同环境下都正常运行|
|服务发现|我的容器现在正在哪里运行？提供哪些服务|
|监控|我的容器发生了什么|
|认证授权|谁可以对我的容器做哪些事情|
|聚合|如何管理由多个容器组成的服务|
|扩展性|动态的调整容器的规模|

> kubernets提供的功能  

调度、容器健康、服务发现、监控、认证授权、自动扩展、自愈、持久化接口
