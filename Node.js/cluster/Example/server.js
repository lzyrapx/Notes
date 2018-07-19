var cluster = require('cluster')

// 如果是主线程
if(cluster.isMaster) {
    require('./process.js');
    return;
}

var express = require('express');
var http = require('http');
var app = express();

app.get('/',function (req,res) {
   res.end('how cruel the world!');
});

http.createServer(app).listen(8080,function () {
   console.log('http://localhost:8080');
});
