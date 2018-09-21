## TCP协议建立连接的三次握手过程：
### 假设此时，我们客户机需要与服务器建立连接。那么A就会向B发出连接请求报文段，其首部中的同步位 SYN = 1，并选择序号 seq = x，表明传送数据时的第一个数据字节的序号是 x。这就是第一次握手：
![xxx](https://github.com/LzyRapx/Notes/blob/master/NetWorking/img/1.png)

### 接下来，服务器需要对客户机的连接请求报文段做出回应，这里我们假设服务器同意客户机的连接请求，则B 在确认报文段中应使 SYN = 1，使 ACK = 1，其确认号ack = x + 1，自己选择的序号 seq = y。这就是第二次握手：
![xxx](https://github.com/LzyRapx/Notes/blob/master/NetWorking/img/2.png)

### A 收到此报文段后向 B 给出确认，其 ACK = 1，确认号 ack = y+1。与此同时，A的TCP告诉向上层应用进程，连接已经建立。这就是第三次握手：
![xxx](https://github.com/LzyRapx/Notes/blob/master/NetWorking/img/3.png)

### 而当B收到A的确认报文后，也将向上层应用报告，连接已经建立，此时客户机与服务器之间就可以传输数据了。
![xxx](https://github.com/LzyRapx/Notes/blob/master/NetWorking/img/4.png)
