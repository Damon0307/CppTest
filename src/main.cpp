#include <iostream>
#include <functional> 
#include <string>   
#include <memory>
#include <thread>
#include <chrono>

#include "WTimer.h"


using namespace std;    

//模板分为两类，函数模板和类模板

//函数模板

template <typename T>

T add(T a,T b)
{
    std::cout<<"函数模板"<<std::endl;
    std::cout<<" a+b="<<a+b<<std::endl;
    return a+b;
}
//不定参数模板

template<typename... Args>
void PowerPrint(Args... args)
{
    std::cout<<"不定参数模板"<<std::endl;
    
    (std::cout<<...<<args)<<std::endl;
//挨个处理参数
    ((std::cout<<"->"<<args<<std::endl),...);
    //感觉上面的代码有点像 for_each

}
//函数模板+不定参数
 template <typename CB,typename... Args>

 void RunyourCB(CB&& cb,Args&&... args)
 {
        std::cout<<"函数模板+不定参数 Run your cb"<<std::endl;
        cb(std::forward<Args>(args)...);//这里使用完美转发来确保参数的类型不变
 }

 

int main() {
    // 标准的C++ main函数模版
    std::cout << "道阻且长，行之将至。" << std::endl;

    // //调用函数模板
    // add(1,2); //可以自己推导类型
    // add<int>(2,2); //也可以指定类型
    // add<double>(2.1,2.2);
    // add<float>(2.1,2); //类型不一样，会自动转换
    // add<string>("hello","world");//字符串也可以相加，因为重载了+运算符
    // //调用不定参数模板
    // PowerPrint(1,"hello",2.1,"world");
    // //调用函数模板+不定参数
    // int tmp_a=1;
    // int tmp_b=2;
    // RunyourCB([tmp_a,tmp_b](){
    //     std::cout<<"回调函数"<<std::endl;
    //     std::cout<<"tmp_a+tmp_b="<<tmp_a+tmp_b<<std::endl;
    // });
    
    
    WTimer wtimer;
    wtimer.SetTimeout(1000, [](int a,int b) { std::cout << "Hello a + b --> "<<a+b<< std::endl;
        fflush(stdout);
    },3,3);


    // wtimer.SetTimerInterval(3000, [](int a,int b) { std::cout << "Hello a - b --> "<<a-b<< std::endl;
    //     fflush(stdout);
    // },3,3);

    cout<<"main end"<<endl;
 
    while (1)
    {
        this_thread::sleep_for(chrono::seconds(1));
    }
 
    // TestCB testCB;
    // testCB.run([](int a, int b) { std::cout << a + b << std::endl; }, 1, 2);
  
    // std::function<void(int, int)> func = [](int a, int b) { std::cout <<"魔法师："<<a + b << std::endl; };

    // testCB.run(func, 4, 2);


    return 0;
}
//! 从链接中找找原因
//!在类的内部使用lambda表达式，需要使用this指针，否则会报错, 目的是为了访问类的成员变量，采用值拷贝的方式，防止在成员函数中启动的
//!线程访问成员变量时，成员变量已经被析构的情况 ,不能无脑的试用 & 符号，因为可能会导致线程访问的时候，成员变量已经被析构的情况
/*
 
*/


