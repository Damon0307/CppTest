#include <iostream>
#include <functional> 
#include <string>   
#include <memory>
#include <thread>
#include <chrono>

#include "SerialPortClass.h"

using namespace std;    

//一个简单的test 类，用来测试，拥有两个成员函数，和一个成员变量
class Test
{
public:
    Test(int i):m_i(i){};
    void GetMsg(char* data, int len)
    {
        std::thread::id this_id = std::this_thread::get_id();
        std::hash<std::thread::id> hasher;
        long long int hashed_id = hasher(this_id);
        std::cout << "Thread ID: " << hashed_id << std::endl;

        cout<<"in GetMsg "<<endl;
        //打印接收到的数据
        for(int i = 0; i < len; i++)
        {
            cout<<data[i];
        }
        cout<<endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  
static void print_static(int i)
{
  cout<<"in static print2 "<<i<<endl;
}

void onRecv(int i)
{
    cout<<"in onRecv "<<i<<endl;
}
void send_data(int i)
{
    cout<<"in send_data "<<i<<endl;
}

private:
    int m_i;
};
 

int main() {
    // 标准的C++ main函数模版
    std::cout << "道阻且长，行之将至。" << std::endl;

    std::cout<<"执行回调时候除了普通的thread,我们还可以使用更好地方法  async"<<std::endl;

    auto sp = make_shared<SerialPortClass>();
    
    
    auto t = make_shared<Test>(1);
    //将成员函数GetMsg绑定到onRecv上

    //sp->onRecv = std::bind(&Test::GetMsg, t.get(), std::placeholders::_1, std::placeholders::_2);

    sp->onRecv = [&t](char* data, int len){  
        t->GetMsg(data, len);
    };

    sp->StartRecv();


    return 0;
}

//