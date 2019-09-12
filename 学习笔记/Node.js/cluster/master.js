
var cluster = require('cluster');
var http = require('http')
if(cluster.isMaster) { // 判断当前进程是否为主进程
    // 如果是，就按照CPU的核数，新建若干个worker进程
    var numWorkers = require('os').cpus().length;
    console.log('Master cluster setting up ' + numWorkers + ' workers...');

    for(var i = 0; i < numWorkers; i++) {
        cluster.fork();
    }
    // 在主进程部署online事件和exit事件的监听函数
    cluster.on('online', function(worker) {
        console.log('Worker ' + worker.process.pid + ' is online');
    });
    // 主进程一旦监听到worker进程的exit事件，就会重启一个worker进程。
    // worker进程一旦启动成功，可以正常运行了，就会发出online事件
    cluster.on('exit', function(worker, code, signal) {
        console.log('Worker ' + worker.process.pid + ' died with code: ' + code + ', and signal: ' + signal);
        console.log('Starting a new worker');
        cluster.fork();
    });
}
else {
    // do something
    // 如果不是，说明当前进程是worker进程，则在该进程启动一个服务器程序
    http.createServer(function (req,res) {
        res.writeHead(200);
        res.end('Hello World!!!');
    }).listen(8000);
}
// process.exit(0);

