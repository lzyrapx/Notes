var cluster= require('cluster')
console.log('start master with ' + process.pid)

//新建一个worker线程
cluster.fork();

/*
主进程监听SIGHUP事件，如果发生该事件就关闭其他所有worker进程。
之所以是SIGHUP事件，是因为nginx服务器监听到这个信号，会创造一个新的worker进程，重新加载配置文件。
另外，关闭worker进程时，主进程发送SIGTERM信号，这是因为Node允许多个worker进程监听同一个端口。
 */
process.on('SIGHUP',function () {
    console.log("reloadding......");
    var new_worker = cluster.fork();

    new_worker.once("listening",function() {
        // 关闭所有其他worker的进程
        for(var id in cluster.workers) {
            if(id === new_worker.id.toString()) continue;
            cluster.workers[id].kill('SIGTERM')
        }
    });
});
