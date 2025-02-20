#include <iostream>
#include <functional>
#include <string>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>
#include <atomic>
#include <future>

#include "SerialPortClass.h"

using namespace std;

int thread_func(int *i)
{
    cout << "result: will be send in 2 seconds" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    *i += 100;

    std::thread::id this_id = std::this_thread::get_id();
    std::hash<std::thread::id> hasher;
    long long int hashed_id = hasher(this_id);
    std::cout << " thread_func thread ID: " << static_cast<unsigned long long>(hashed_id) << std::endl;
    return *i;
}

int main()
{
    // 标准的C++ main函数模版
    std::cout << "道阻且长，行之将至。" << std::endl;

    std::cout << "执行异步操作时候除了普通的thread,我们还可以使用更好地方法  async" << std::endl;

    int i = 0;
    std::future<int> result = std::async(std::launch::async, thread_func, &i);

    while (1)
    {

        auto status = result.wait_for(std::chrono::milliseconds(100));
        if (status == std::future_status::ready)
        {
            cout << "result is ready" << endl;
            int res = result.get();
            cout << "result: " << res << endl;
            break;
        }
        else
        {
            cout << "result is not ready" << endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    if (result.valid())
    {
        cout << "result is valid" << endl;
    }
    else
    { // 上面已经get过了，这里再次get()会有异常
        cout << "result is invalid" << endl;
    }

    return 0;
}

#if 0

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
        std::cout << "Thread ID: " << static_cast<unsigned long long>(hashed_id) << std::endl;

        cout<<"in GetMsg with len: "<<len<<endl;
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

    //!更推荐使用lambda表达式，效率高且能实现更多的功能
    //sp->onRecv = std::bind(&Test::GetMsg, t.get(), std::placeholders::_1, std::placeholders::_2);

    //! t是一个shared_ptr, 不应该按引用传递，应该按值传递这样就能正确的增加引用计数，不然会出现引用计数错误导致悬空指针
    // sp->onRecv = [&t](char* data, int len){  
    //     t->GetMsg(data, len);
    // };
    sp->onRecv =[t](char* data, int len){  
        t->GetMsg(data, len);
    };


    sp->StartRecv();


    return 0;
}
#endif
//