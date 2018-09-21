## TCP协议建立连接的三次握手过程：
### 假设此时，我们客户机需要与服务器建立连接。那么A就会向B发出连接请求报文段，其首部中的同步位 SYN = 1，并选择序号 seq = x，表明传送数据时的第一个数据字节的序号是 x。这就是第一次握手：
![xxx](https://github.com/LzyRapx/Notes/blob/master/NetWorking/img/1.png)

### 接下来，服务器需要对客户机的连接请求报文段做出回应，这里我们假设服务器同意客户机的连接请求，则B 在确认报文段中应使 SYN = 1，使 ACK = 1，其确认号ack = x + 1，自己选择的序号 seq = y。这就是第二次握手：
![xxx](https://github.com/LzyRapx/Notes/blob/master/NetWorking/img/2.png)

### A 收到此报文段后向 B 给出确认，其 ACK = 1，确认号 ack = y+1。与此同时，A的TCP告诉向上层应用进程，连接已经建立。这就是第三次握手：
![xxx](https://github.com/LzyRapx/Notes/blob/master/NetWorking/img/3.png)

### 而当B收到A的确认报文后，也将向上层应用报告，连接已经建立，此时客户机与服务器之间就可以传输数据了。
![xxx](https://github.com/LzyRapx/Notes/blob/master/NetWorking/img/4.png)

## Tips:
### 对于客户机和服务器的定义并不是绝对的，我们将主动发起连接的一方叫做客户机，将能够应答的一方称为服务器， 如果TCP连接同时打开，那么双方将既是客户机又是服务器。 
### ACK位和ack位的意义是不一样的，前者只有0/1两个值，1表示这是一个确认报文，后者则表示在此序号之前的数据都已经收到，现在期望收到序号为此值得数据。
### ack是对对方发来数据的确认号，而seq则是自己发送的数据的序号。 
### SYN（同步位）仅在建立连接的前两个报文段中使用。
### SYN置1的报文段虽然不携带数据，但也要消耗掉一个序号。
