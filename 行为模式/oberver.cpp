/**
 * @file oberver.cpp
 * @author https://github.com/mingo-wu1/gof_design_pattern_23
 * @brief 核心解释:无穷多个观察者观察同一个目标, 当目标发生变化, 无穷多个观察者就会收到通知
 *        1、行为模式-研究如何分离-分离核心点(如果自己设计,从分离核心点出发):观察者与目标分离
 *        2、怎么做到无穷多个观察者收到通知: 目标有注册进来的所有的观察者指针,
 *           然后调用观察者的函数(也叫更新函数等)就获得通知
 * @version 0.1
 * @date 2022-01-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <list>
#include <string>

class Subject;
/**
 * @brief 观察者。
 *        1、核心设计思路：扣住设计思路，观察者与目标分离，给出一个接口用于目标的调用，
 *           当这个接口被调用，观察者就知道数据更新了
 */
class Observer{
public:
    ~Observer(){} // 虚基类必须有析构
    virtual void Update() = 0; // 被目标调用的接口,参照核心设计1，被动
    
    virtual void Update(Subject *) = 0; // 多增加一个接口，用于观察者主动访问目标数据,最简设计非必须，看业务，主动
};

/**
 * @brief 目标。
 *        1、核心设计思路：扣住设计思路，观察者与目标分离,目标有所有观察者指针，
 *           通过遍历所有观察者的更新函数，观察者就收到通知
 *        1、核心设计思路：目标怎么才有观察者指针(以及怎么删掉它)？通过增删的接口 attach detach
 *        2、核心设计思路：目标怎么通知所有观察者？通过遍历所有观察者指针，notify需要实现遍历
 *        3、核心设计思路：怎么遍历？用容器装住所有观察者，for循环就可以
 */
class Subject{
public:
    ~Subject(){} // 虚基类必须有析构
    virtual void Attach(Observer *) = 0; // 增加一个观察者，参照核心设计1
    virtual void Detach(Observer *) = 0; // 删掉一个观察者，参照核心设计1
    virtual void Notify() = 0; // notify需要实现遍历,参照核心设计2

    virtual std::string GetState() = 0; // 用于观察者调用，观察者主动查询信息，非必须
protected:
    std::list<Observer *> observerList; // 使用合适的容器（没规定只要合适），参照核心设计3
};

// 实现接口，扣住核心设计思路就行，不做说明
class ConcreteSubject : public Subject{
public:
    void Attach(Observer *observer) override{
        observerList.push_back(observer);
    }

    void Detach(Observer *observer) override{
        observerList.remove(observer);
    }

    void Notify() override{
        for(auto o : observerList){
            o->Update();
        }
    }

    std::string GetState() override{
        return "今日大事件：力宏橱柜，真拉跨";
    }
};

// 实现接口，扣住核心设计思路就行，不做说明
class ConcreteObserver : public Observer{
public:
    void Update() override{
        std::cout<<"has been changed."<<std::endl;        
    }

    /**
     * @brief 用于观察者主动去问，对于最精简的设计来说不必要
     * 
     * @param subject 
     */
    void Update(Subject *subject) override{
        std::string str = subject->GetState();
        std::cout<<str<<std::endl;
    }
};

/**
 * @brief 测试
 * 
 * @return int 
 */
int main(){
    Observer *o1 = new ConcreteObserver;
    Observer *o2 = new ConcreteObserver;
    Subject *target = new ConcreteSubject;
    target->Attach(o1);
    target->Attach(o2);
    target->Notify();
    target->Detach(o1);
    target->Notify();

    o1->Update(target); // 我主动向目标请求更新一下

    delete target;
    delete o2;
    delete o1;
    return 0;
}