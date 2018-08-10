1.下载`lua`包并解压
```
wget -c http://www.lua.org/ftp/lua-5.3.0.tar.gz 
tar zxvf lua-5.3.0.tar.gz 
```
2、下载`libreadline`相关支持
```
sudo apt-get install libreadline5
sudo apt-get install libreadline-gplv2-dev
```
3、编译以及安装
```
cd lua-5.3.0
make linux
sudo make install
```
4、测试
```
$ lua
Lua 5.1.2 Copyright (C) 1994-2007 Lua.org, PUC-Rio
>print("Hello World!")
```
按下`Ctrl+D`退出。
