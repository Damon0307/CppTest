#ifndef __WTIMER_H__
#define __WTIMER_H__

//一个定时器,执行一次性任务，或者周期性任务

#include <functional>
#include <string>
#include <memory>
#include <thread>
#include <chrono>
#include <atomic>
#include <iostream>

using namespace std;

 
class WTimer
{

public:
    WTimer(/* args */)
    {
        m_bRunning = true;
    }
    ~WTimer()
    {
        m_bRunning = false;
    }


template <typename CB,typename... Args>
 void SetTimeout(int ms, CB&& cb, Args&&... args)
    {
         std::thread([this](int ms,CB&& cb,Args&&... args)
         {
             std::chrono::milliseconds dura(ms);
             std::this_thread::sleep_for(dura);
             if (m_bRunning)
             {
                 cb(std::forward<Args>(args)...);
             }
          },ms,std::forward<CB>(cb),std::forward<Args>(args)...).detach();   

    }
    
template <typename CB,typename... Args>
void SetTimerInterval(int ms,CB&& cb,Args&&... args)
    {
        std::thread([this](int ms,CB&& cb,Args&&... args)
        {
            while (m_bRunning)
            {
                std::chrono::milliseconds dura(ms);
                std::this_thread::sleep_for(dura);
            
                    if (m_bRunning)
                            {
                                cb(std::forward<Args>(args)...);
                            }
            }
        },ms,std::forward<CB>(cb),std::forward<Args>(args)...).detach();
    }

    void Stop()
    {
        m_bRunning = false;
    }

    private:
    //原子变量
    std::atomic<bool> m_bRunning;
};
/**note 
 * 首先要搞清楚，timer 是定时器，不是eventloop 。timer 的功能只需要周期性执行某个任务就可以了
 * 
 * 想把不同的事件都加进去的，是eventloop 的功能，eventloop 需要一个事件列表，当有新的事件加进去的时候，
 * eventloop 应该能够检测到，然后执行相应的任务。
 * 
 * eventloop 借用 linux 的 epoll 来实现，这样就可以实现一个高效的事件循环。epoll不仅能监听普通IO
 * 事件，还能监听定时器事件，这样就可以实现一个高效的事件循环。
 * 
 * 使用了epoll就避免了使用轮询的方式来检测事件，这样就可以避免浪费CPU资源。
 *  
 * 
 */

#endif // __WTIMER_H__