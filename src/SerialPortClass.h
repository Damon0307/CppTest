#ifndef __SERIALPORTCLASS_H__
#define __SERIALPORTCLASS_H__
#include <iostream>
#include <functional>
#include <string>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>
#include <future>
#include <vector>
#include <algorithm>
 
using namespace std;

//模拟串口类
class SerialPortClass
{
public:
    SerialPortClass()
    {

    }
    ~SerialPortClass()
    {

    }

//接收数据
void ReceiveData(char* data, int length)
{
    //将接收到的数据传递给onRecv函数
    if(onRecv)
    {
        onRecv(data, length);
    }
}

//将onRecv直接放在public中，方便外部直接赋值调用，因为onRecv是一个回调函数
std::function<void(char*, int)> onRecv;
 
    bool SendData(const char* data, int length)
    {
        //模拟串口发送数据
        cout<<"send data:"<<data<<endl;
        return true;
    }
    
 
    //模拟串口接收数据
    void StartRecv()
    {
        while(1)
        {
            //模拟串口接收数据随机发送6个长度以内的ascii码
            char data[6] = {0};
            int length = rand()%6;
            for(int i = 0; i < length; i++)
            {
                data[i] = rand()%128;
            }
            //模拟串口接收数据
            ReceiveData(data, length);
          
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    }

  
};

#endif // __SERIALPORTCLASS_H__