
var cluster = require('cluster');
var http = require('http'); // 加载http模块


http.createServer(function (request,response) { // 调用http模块的createServer方法，创造一个服务器实例
   response.writeHead(200,{'Content-Type':'text/plain'});
   response.write("How cruel the  world!!!");
   response.end();
}).listen(8080,'127.0.0.1');

console.log("server running on port 8080");

// http://127.0.0.1:8080/，网页显示"How cruel the  world!!!"
