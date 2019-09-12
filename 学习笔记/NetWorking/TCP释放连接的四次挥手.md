## TCP释放连接的四次挥手过程

### 数据传输结束后，通信的双方都可释放连接。假设现在 A 的应用进程先向其 TCP 发出连接释放报文段，并停止再发送数据，主动关闭 TCP连接。A 把连接释放报文段首部的 FIN = 1，其序号seq = u，等待 B 的确认。这是第一次挥手：
![xxx](https://github.com/LzyRapx/Notes/blob/master/NetWorking/img/5.png)

### B 发出确认，确认号 ack = u+1，而这个报文段自己的序号 seq = v。TCP 服务器进程通知高层应用进程。从 A 到 B 这个方向的连接就释放了，TCP 连接处于半关闭状态。B 若发送数据，A 仍要接收（此段Tips中有详细解释）。这是第二次挥手：
![xxx](https://github.com/LzyRapx/Notes/blob/master/NetWorking/img/6.png)

### 假设到某一时刻B 已经没有要向 A 发送的数据，其应用进程就通知 TCP 释放连接。携带位FIN = 1, ACK = 1, seq = w, ack= u+1。这是第三次挥手：
![xxx](https://github.com/LzyRapx/Notes/blob/master/NetWorking/img/7.png)

### A 收到连接释放报文段后，必须发出确认。ACK = 1, seq = u + 1, ack = w+1。这是第四次挥手：
![xxx](https://github.com/LzyRapx/Notes/blob/master/NetWorking/img/8.png)

## Tips:
### 客户机与服务器之间，谁有关闭连接的需求，谁就要发送带FIN位的报文段 
### 半关闭状态：数据的传输方向将变为单向，只能由被动关闭方向主动关闭方传输数据 
### TCP连接的真正关闭并不是在第四次挥手之后马上进行，而是要等待时间 2MSL（最大报文段生存周期） 后才真正释放掉。这种机制是为了： 
### 一，为了保证 A 发送的最后一个 ACK 报文段能够到达 B。 
### 二，防止 “已失效的连接请求报文段”出现在本连接中。A 在发送完最后一个 ACK 报文段后，再经过时间 2MSL，就可以使本连接持续的时间内所产生的所有报文段，都从网络中消失。这样就可以使下一个新的连接中不会出现这种旧的连接请求报文段。
