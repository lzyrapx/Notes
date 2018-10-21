1.首先让自己本地的`ssh`私钥和`github`上的私钥一致：
本地没有私钥就通过：`ssh-keygen`命令生成`ssh`私钥
然后需要你`Enter passphrase`，直接不断按【Enter】就可以了。
然后会显示：
```
The key's randomart image is:
+---[RSA 2048]----+
| x...         |
| o..o .          |
|oo.    . .       |
|ooo     o.o..    |
|xx  . S+==     |
|xx   |
|xx    |
|oxx     |
|  . .o   .*+     |
+----[SHA256]-----+
```
这样就成功了。

2.然后执行 ：`cat ~/.ssh/id_rsa.pub` 命令，查看`ssh`私钥，复制粘贴到`github`的`ssh-key`设置里就行了。

3.然后在本地：`git clone`【项目ssh地址】

4.进入刚`clone`下来的项目里, 然后你更新项目后。。。想也更新上`github`.

5.在项目里面执行以下命令：

(1)`git config --global user.name "github用户名"`

(2) `git config --global user.email "注册邮箱"`

(3) `git init`

(4) `git add 文件名 或者 git add -A`

(5) `git status (查看状态)`

(6) `git commit -m "改动评论"`

(6) `git remote add origin 项目ssh地址`

  (如果出现`fatal: remote origin already exists.`就执行 `git remote rm origin`, 再重新执行(6))

(7) `git push -u orgin master`
 (报错
fatal: 'orgin' does not appear to be a git repository
fatal: Could not read from remote repository.

Please make sure you have the correct access rights
and the repository exists.
就直接执行：`git push` 或者 ` git push --set-upstream origin master`)




