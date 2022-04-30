# tingServer
该并发服务器框架模仿 陈硕的Muduo库来实现，采用reactor + threadpool的模式，是一个能适应密集计算的并发服务器框架。该项目主要分为两个部分：reactor+ threadpool。reactor负责将TCP连接进行封装，并采用Event-Loop模式结合epoll多路复用进行监听，然后注册相应的回调函数，并且将IO线程与计算线程分离。

目录结构:
```txt
├─Acceptor.cpp 
├─Acceptor.h 
├─Condition.h 
├─EventLoop.cpp 
├─EventLoop.h 
├─InetAddress.cpp 
├─InetAddress.h 
├─makefile 
├─MutexLock.h 
├─Noncopyable.h 
├─server.cpp 
├─Socket.cpp 
├─Socket.h 
├─SocketIO.cpp 
├─SocketIO.h 
├─TaskQueue.cpp 
├─TaskQueue.h 
├─TcpConnection.cpp 
├─TcpConnection.h 
├─TcpServer.cpp 
├─TcpServer.h 
├─Thread.cpp 
├─Thread.h 
├─Threadpool.cpp 
└─Threadpool.h 
```
webbench服务器压力测试：
![image](https://user-images.githubusercontent.com/43102456/165943088-2339f4b7-c368-41da-86f0-fe8f4a0a5ef9.png)
