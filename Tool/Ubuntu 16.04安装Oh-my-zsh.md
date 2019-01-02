一、安装zsh
```
sudo apt-get update
sudo apt-get install zsh
```
二、修改默认shell
```
sudo chsh -s /bin/zsh
```
修改配置文件
```
sudo gedit /etc/passwd/
```
将文件中最后一行
```
ubuntu:x:500:500:ubuntu,,,:/home/ubuntu:bin/bash
```
修改为
```
ubuntu:x:500:500:ubuntu,,,:/home/ubuntu:bin/zsh
```
三、安装Oh-my-zsh 
安装之前，确认安装curl或者wget，可以使用curl –version或者wget –version查看
`
sudo apt-get install curl
sudo apt-get install wget
`
之后，使用以下命令安装Oh-my-zsh
`
//via curl
sh -c "$(curl -fsSL https://raw.githubusercontent.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"
`
`
//via wget
sh -c "$(wget https://raw.githubusercontent.com/robbyrussell/oh-my-zsh/master/tools/install.sh -O -)"
`
重启之后生效

四、安装插件 
1.autojump
```
sudo apt-get update
sudo apt-get install autojump
```
说明文件路径在目录
```
/usr/share/doc/autojump/README.Debian
```
打开.zshrc文件
```
sudo gedit ~/.zshrc
```
在文件最后加上以下
```
. /usr/share/autojump/autojump.sh
```
使配置文件生效
```
source ~/.zshrc
```
