#ifndef __WTIMER_H__
#define __WTIMER_H__

//一个定时器,执行一次性任务，或者周期性任务

#include <functional>
#include <string>
#include <memory>
#include <thread>
#include <chrono>
#include <iostream>

using namespace std;

class WTimer
{

public:
    WTimer(/* args */);


template <typename CB,typename... Args>
 void SetTimeout(int ms, CB&& cb, Args&&... args)
    {
        cout<<" you have set a timeout function will be called after "<<ms<<" ms"<<endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
        std::thread t(cb,std::forward<Args>(args)...);
        t.detach();
    }

    ~WTimer();

    private:
    /* data */

};

WTimer::WTimer(/* args */)
{
}

WTimer::~WTimer()
{
}





#endif // __WTIMER_H__