#### 1.Redis 脚本使用 Lua 解释器来执行脚本。
```
1. eval： 执行 Lua 脚本。
2. evalsha : 执行 Lua 脚本。
3. script exists: 令用于校验指定的脚本是否已经被保存在缓存当中。
4. script flush: 从脚本缓存中移除所有脚本。
5. script kill: 杀死当前正在运行的 Lua 脚本。
6. script: load：将脚本 script 添加到脚本缓存中，但并不立即执行这个脚本。
```
#### 2.Redis 2.6 版本通过内嵌支持 Lua 环境。执行脚本的常用命令为 `EVAL`。
#### 3.Redis Eval 命令使用 Lua 解释器执行脚本。


