#include "Socket.h"
#include "InetAddress.h"
#include "Acceptor.h"
#include "SocketIO.h"
#include "TcpConnection.h"
#include "EventLoop.h"
#include "TcpServer.h"
#include "Threadpool.h"
#include <iostream>
#include <string.h>
#include <string>
#include <thread>
using namespace std;
using namespace wd;

/*
网路库Version4.0: 
新增基于对象的线程池，利用子线程帮助服务器处理信息
对于一般的命令，主线程自己就可以解决；对于由复杂的逻辑操作的命令，交给子线程完成（实际过程就是像任务队列插入新的任务）

*/
Threadpool *pthreadpool = NULL; //定义全局变量：线程池

class MyTask
{
private:
    string _msg;
    TcpConnectionPtr _ptr;
public:
    MyTask(const string& msg, const TcpConnectionPtr& ptr)
    :_msg(msg)
    ,_ptr(ptr)
    {
    }
    void process(){
        _ptr->sendInEventLoop(_msg);
    }
};

void ConnectionCallBack(const TcpConnectionPtr& ptr)
{
    cout << ">>client has connected " << ptr->Address() << endl;
    ptr->send("welcome to server");
}

void MessageCallBack(const TcpConnectionPtr& ptr)
{
    cout << ">>from client:" << ptr->Address() << endl;
    string s = ptr->recv();
    cout << s;
    //send消息的工作交给子线程
    MyTask task(s, ptr);
    pthreadpool->addTask(std::bind(&MyTask::process, task));
    // ptr->send(s);
}

void CloseCallBack(const TcpConnectionPtr& ptr)
{
    cout << "client has broken up " << ptr->Address() << endl;
}

int main()
{
    unsigned int in = std::thread::hardware_concurrency();
    Threadpool threadpool(in, 10);//线程数 任务队列容量
    pthreadpool = &threadpool;
    pthreadpool->start();
    TcpServer server("127.0.0.1",20080);
    server.setConnectionCallBack(ConnectionCallBack);
    server.setMessageCallBack(MessageCallBack);
    server.setCloseCallBack(CloseCallBack);
    server.start();
    return 0;
}