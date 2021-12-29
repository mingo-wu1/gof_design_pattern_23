#include <iostream>

/**
 * @brief 接口，核心点在 构造函数 和 HandleRequest()
 *        1、一般设计模式有一个省代码妙招在于巧妙设计构造函数
 *        2、使用多态，这个是所有设计模式的顶层思路
 */
class IHandler{
public:
    IHandler(IHandler *handler = nullptr) : _handler(handler){};
    
    virtual void HandleRequest(int event = -1) = 0;

protected:
    IHandler *_handler;
};

/**
 * @brief 头链/中间链，继承IHandle，实现自己的HandleRequest()
 *        头链/中间链，构造函数必须有基类指针
 *        头链/中间链可以有一个或者很多个
 */
class ConcreteHandler1 : public IHandler{
public:
    ConcreteHandler1(IHandler *handler = nullptr):IHandler(handler){
    }
    
    void HandleRequest(int event = -1) override{
        if(1 == event)
            std::cout<<"drink it."<<std::endl;
        else
            _handler->HandleRequest(event);
    }
};

/**
 * @brief 最终链，继承IHandle，实现自己的HandleRequest()
 *        最终链比较特殊，构造函数一定没有基类指针
 */
class ConcreteHandler2 : public IHandler{
public:
    ConcreteHandler2(){
        
    }

    void HandleRequest(int event = -1) override{
        std::cout<<"cannot do it."<<std::endl;
    }
};

/**
 * @brief 自定义的测试事件变量，非必须
 * 
 */
const int shadow_eat = 0;
const int shadow_drink = 1;
const int shadow_run = 2;

int main(){
    IHandler *concreteHandle2 = new ConcreteHandler2(); // 先构造最终链
    IHandler *concreteHandle1 = new ConcreteHandler1(concreteHandle2); // 再构造头链或中间链
    concreteHandle1 ->HandleRequest(shadow_eat); // res: cannot do it.
    concreteHandle1 ->HandleRequest(shadow_drink); // res: drink it.
    concreteHandle1 ->HandleRequest(shadow_run); // res: cannot do it.
    return 0;
}