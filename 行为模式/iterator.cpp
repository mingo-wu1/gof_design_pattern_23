/**
 * @file iterator.cpp
 * @author your name (you@domain.com)
 * @brief 迭代器模式全篇设计的核心点是 容器 和 迭代器 各自负责 的内容分离
 *        代码编写的核心点在于 容器的父类（很多必须设计的点） 和 迭代器的父类
 *
 *        迭代器责任：使用容器的指针 并负责访问容器元素，也就是访问容器元素 get
 *        迭代器父类：给出接口
 *        迭代器子类：实现接口        
 *              
 *        容器责任：装配具体类型，比如int，并进行 push， pop 等操作
 *        容器的父类：负责分配内存
 *        容器子类：负责构造对象
 * 
 * @date 2022-01-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <cstdlib>
#include <iostream>
#include <memory>

template<class Item>
class IAggregate;

/**
 * @brief 迭代器，因为迭代的是别的容器所以必须有别的容器指针，所以构造函数添加别的容器指针
 *        迭代器的功能肯定是遍历别的容器内容，所以就有了访问相关的函数
 * @tparam T 
 */
template<class Item>
class Iterator
{
public:
    Iterator(IAggregate<Item> *aggregate) // 迭代别的容器，所以有容器IAggregate指针
    {
        _aggregate = aggregate;
    }
    ~Iterator(){}
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone() = 0;
    virtual Item& CurrentItem() = 0;

protected:
    IAggregate<Item> *_aggregate{nullptr};
};

/**
 * @brief 继承 Iterator 并实现，没有什么特别的实现
 * 
 * @tparam Item 
 */
template<class Item>
class ConcreteIterator : public Iterator<Item>
{
public:
    ConcreteIterator(IAggregate<Item> *aggregate):Iterator<Item>(aggregate){
    }

    void First() override
    {
        _iter = 0;
    }

    void Next() override
    {
        _iter++;
    }

    bool IsDone() override
    {
        return _iter >= Iterator<Item>::_aggregate->GetCurrent();
    }

    Item& CurrentItem() override
    {
        return Iterator<Item>::_aggregate->GetItem(_iter);
    }

private:
    int _iter{0};
};

/**
 * @brief 容器，模板类，赋予容器类型，包装具体的类型
 * 
 */
const int DEFAULT_CAPACITY=100;
template<class Item>
class IAggregate
{
public:
    IAggregate(int size = DEFAULT_CAPACITY):_size(size),_current(0)
    {
        /**
         * @brief 必须这样，这里比较特殊，使用了 allocate，目的是内存分配和对象构造分离
         *        也可以用 new 实现，但没那么好
         *        try catch 是为了处理可能的内存分配失败
         */
        try{
            _item = alloc.allocate(_size); 
        } catch (std::bad_alloc &b) {
            std::cout<<b.what()<<std::endl;
            abort();
        }
    }

    ~IAggregate()
    {   
        /**
         * @brief 必须这样，析构掉分配的内存
         * 
         */
        alloc.deallocate(_item, _size);
    }

    /**
     * @brief 必须有的接口
     * 
     * @return Iterator<Item>* 
     */
    virtual Iterator<Item>* CreateIterator() = 0;

    /**
     * @brief 用于迭代器访问的接口
     * 
     */
public:
    int GetCurrent(){return _current;}
    Item& GetItem(int index){return _item[index];}

    /**
     * @brief 给子类调用的数据成员
     * 
     */
protected:
    Item *_item{nullptr}; // 必须有 item， 是具体类型
    int _size; // 必须有 size
    int _current; // 必须有 current 给出当前的下标
    std::allocator<Item> alloc; // 必须有，用于内存分配
};


#include <mutex>
#include <condition_variable>
/**
 * @brief 继承容器，具体实现
 * 
 * @tparam Item 
 */
template <class Item>
class ConcreteAggregate : public IAggregate<Item>
{
public:
    ConcreteAggregate(int size = DEFAULT_CAPACITY):IAggregate<Item>(size){}

    Iterator<Item>* CreateIterator() override
    {   
        return new ConcreteIterator<Item>(this);
    }
    
    /**
     * @brief 使用了 allocator 的对象构造接口，将内存分配交给父类，构造对象给子类
     *        加了锁，push 更安全，如果从可运行角度看，不是必须
     * @param item 
     */
    void Push_Back(Item item){
        std::lock_guard<std::mutex> lock(_m);
        IAggregate<Item>::alloc.construct(
            IAggregate<Item>::_item + IAggregate<Item>::_current, item);
        IAggregate<Item>::_current++;
        _cond.notify_one();
    }

    /**
     * @brief 使用了 allocator 的对象析构接口，将内存分配交给父类，析构对象给子类 
     *        加了锁，pop 更安全, 如果从可运行角度看，不是必须
     * @param item 
     * @param item 
     */
    void Pop_Back(){
        std::lock_guard<std::mutex> lock(_m);
        IAggregate<Item>::alloc.destroy(
            IAggregate<Item>::_item + IAggregate<Item>::_current);
        IAggregate<Item>::_current--;
        _cond.notify_one();
    }

    /**
     * @brief 加锁，更安全, 如果从可运行角度看，不是必须
     * 
     */
private:
    std::mutex _m;
    std::condition_variable _cond;
};

/**
 * @brief 测试
 * 
 * @return int 
 */
int main()
{
    ConcreteAggregate<int> vector; // 构造int类型的容器
    vector.Push_Back(10); // 执行尾部插入
    vector.Push_Back(20); // 执行尾部插入
    vector.Pop_Back(); // 执行尾部弹出
    Iterator<int> *iter = vector.CreateIterator(); // 执行了new
    for(iter->First(); !iter->IsDone(); iter->Next()) // 遍历所有元素
        std::cout<<iter->CurrentItem()<<std::endl;
    delete iter; // 析构掉迭代器，也可以放到类里面实现
    return 0;
}
