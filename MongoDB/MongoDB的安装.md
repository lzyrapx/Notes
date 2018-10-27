#### 参考文档：https://docs.mongodb.com/master/tutorial/install-mongodb-on-ubuntu/
***
### 虽然Ubuntu本身也提供MongoDB安装包，但往往官网的安装包版本更新。
```
hupeng@hupeng-vm:~$ apt-cache show mongodb-clients
Package: mongodb-clients
Priority: optional
Section: universe/database
Installed-Size: 160066
Maintainer: Ubuntu Developers <ubuntu-devel-discuss@lists.ubuntu.com>
Original-Maintainer: Laszlo Boszormenyi (GCS) <gcs@debian.org>
Architecture: amd64
Source: mongodb
Version: 1:2.6.10-0ubuntu1   # 版本号
```
## 安装步骤:

#### 1.导入包管理系统使用的公钥
```
sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv 0C49F3730359A14518585931BC711F9BA15703C6
```
#### 2.为MongoDB创建一个列表文件
根据版本创建`/etc/apt/sources.list.d/mongodb-org-3.4.list `列表文件

Ubuntu 14.04
```
echo "deb [ arch=amd64 ] http://repo.mongodb.org/apt/ubuntu trusty/mongodb-org/3.4 multiverse" | sudo tee /etc/apt/sources.list.d/mongodb-org-3.4.list
```
Ubuntu 16.04
```
echo "deb [ arch=amd64,arm64 ] http://repo.mongodb.org/apt/ubuntu xenial/mongodb-org/3.4 multiverse" | sudo tee /etc/apt/sources.list.d/mongodb-org-3.4.list
```
#### 3.更新本地包数据库
```
sudo apt-get update
```
#### 4.安装最新版本的MongoDB
```
sudo apt-get install -y mongodb-org
```
然后`mongo`启动MongoDB.
如果发生以下报错：
```
connect@src/mongo/shell/mongo.js:240:13
@(connect):1:6
exception: connect failed
```
解决方案：
```
[connection attempt failed ](https://blog.csdn.net/weixin_40612082/article/details/81568915?utm_source=blogxgwz1)
```
#### 5.查看配置文件

配置文件`mongod.conf`所在路径: 
```
/etc/mongod.conf
```
内容:
```
# mongod.conf

# for documentation of all options, see:
#   http://docs.mongodb.org/manual/reference/configuration-options/

# Where and how to store data.
storage:
  dbPath: /var/lib/mongodb   #数据库存储路径
  journal:
    enabled: true
#  engine:
#  mmapv1:
#  wiredTiger:


# where to write logging data.
systemLog:
  destination: file
  logAppend: true     #以追加的方式写入日志
  path: /var/log/mongodb/mongod.log   #日志文件路径

# network interfaces
net:
  port: 27017
  bindIp: 127.0.0.1   #绑定监听的ip 127.0.0.1只能监听本地的连接，可以改为0.0.0.0


#processManagement:

#security:

#operationProfiling:

#replication:

#sharding:

## Enterprise-Only Options:

#auditLog:

#snmp:
```
#### 6.启动和关闭MongoDB
```
sudo service mongod start  # 启动
sudo service mongod stop   # 关闭


ps aux | grep mongod   # 查看守护进程mongod的运行状态
root      5997  0.0  0.0  14656  2100 tty1     T    15:45   0:00 sudo mongod
root      5998  1.7  0.2 946052 19916 tty1     Tl   15:45   0:36 mongod
root      6044  0.0  0.0  12892  1112 tty1     S    16:20   0:00 grep --color=auto mongod
```
#### 7.卸载

1. 关闭守护进程 mongod
```
sudo service mongod stop
```
2.卸载安装的软件包
```
sudo apt-get purge mongodb-org*
```
3.移除数据库和日志文件（数据库和日志文件的路径取决于`/etc/mongod.conf`文件中的配置)
```
sudo rm -r /var/log/mongodb
sudo rm -r /var/lib/mongodb
```
