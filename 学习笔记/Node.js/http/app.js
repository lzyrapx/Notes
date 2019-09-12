
var cluster = require('cluster');
var http = require('http'); // 加载http模块


http.createServer(function (request,response) { // 调用http模块的createServer方法，创造一个服务器实例
   response.writeHead(200,{'Content-Type':'text/plain'});
   response.write("How cruel the  world!!!");
   response.end();
}).listen(8080,'127.0.0.1');
/*
ceateServer方法接受一个函数作为参数，该函数的request参数是一个对象，表示客户端的HTTP请求；
response参数也是一个对象，表示服务器端的HTTP回应。
response.writeHead方法用来写入HTTP回应的头信息；
response.end方法用来写入HTTP回应的具体内容，以及回应完成后关闭本次对话。
最后的listen(8080)表示启动服务器实例，监听本机的8080端口。
 */
console.log("server running on port 8080");

// http://127.0.0.1:8080/，网页显示"How cruel the  world!!!"
