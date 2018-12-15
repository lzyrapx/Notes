### 文档:
#### http://docs.kubernetes.org.cn/
##3# https://www.kubernetes.org.cn/docs

### Kubernetes集群中移除Node:
在master节点上执行：
```
kubectl drain xxx --delete-local-data --force --ignore-daemonsets
kubectl delete node xxx
```
