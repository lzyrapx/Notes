### 指定容器cpu个数，--cpus=2 表示容器最多可以使用主机上两个 CPU:
```
 docker run -it --rm --cpus=2 ubuntu:latest /bin/bash
```

### 指定容器cpu个数和编号:
```
 docker run -it --rm --cpuset-cpus="1,3" ubuntu:latest /bin/bash
```
