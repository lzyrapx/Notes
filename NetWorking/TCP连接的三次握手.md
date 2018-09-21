## TCP协议建立连接的三次握手过程：
假设此时，我们客户机需要与服务器建立连接。那么A就会向B发出连接请求报文段，其首部中的同步位 SYN = 1，并选择序号 seq = x，
表明传送数据时的第一个数据字节的序号是 x。这就是第一次握手：
![xxx](https://github.com/LzyRapx/Notes/blob/master/NetWorking/img/1.png)
![xxx](https://github.com/LzyRapx/Notes/blob/master/NetWorking/img/2.png)
![xxx](https://github.com/LzyRapx/Notes/blob/master/NetWorking/img/3.png)
![xxx](https://github.com/LzyRapx/Notes/blob/master/NetWorking/img/4.png)
