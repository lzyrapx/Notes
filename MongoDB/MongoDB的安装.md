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
[https://blog.csdn.net/weixin_40612082/article/details/81568915?utm_source=blogxgwz1]( connection attempt failed )
```
