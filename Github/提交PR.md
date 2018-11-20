- fork 到自己的仓库

`git clone 到本地(克隆自己fork的)`

- 上游建立连接
 `git remote add upstream 开源项目地址`

- 创建开发分支 (非必须)
 `git checkout -b dev`

- 修改提交代码
`git status `
`git add . `
`git commit -m  “xxx”`
`git push origin branch`

- 同步代码三部曲
`git fetch upstream`
`git rebase upstream/master`
`git push origin master`

- 提交pr
`去自己github仓库对应fork的项目下 new pull request`
 
 ---
 https://blog.csdn.net/vim_wj/article/details/78300239
