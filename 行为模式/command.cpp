#include <iostream>

/**
 * @brief 接受者，它是真正执行动作的类
 *        1、比如将 Receiver 视作 office 文档程序里的 word 文档
 *        2、动作 Action1 就可以视作打开 doc file open
 *        3、动作 Action2 就可以视作关闭 doc file close
 */
class Receiver1
{
public:
    void Action1(){
        std::cout<<"doc file open."<<std::endl;
    }

    void Action2(){
        std::cout<<"doc file close."<<std::endl;
    }
};

/**
 * @brief 接受者，它是真正执行动作的类
 *        1、比如将 Receiver 视作 text 文档
 *        2、动作 Action1 就可以视作复制 text 文字复制
 *        3、动作 Action2 就可以视作粘贴 text 文字粘贴
 */
class Receiver2
{
public:
    void Action1(){
        std::cout<<"text copy."<<std::endl;
    }

    void Action2(){
        std::cout<<"text paste."<<std::endl;
    }
};

/**
 * @brief 命令模式的核心点，可以被继承并扩展成千上万中命令
 *        有且仅有的关键函数是 Execute()，其他的非关键
 */
class Command
{
public:
    ~Command(){}

    virtual void Execute() = 0; // 有且仅有的关键函数
};

/**
 * @brief 继承Command，并使用泛型使得可以传入千万种 Receiver
 * 
 * @tparam Receiver 
 */
template<class Receiver>
class ConcreteCommand : public Command
{
public:

    typedef void (Receiver::*pAction)(); // 高端操作，别名函数指针，指针名为pAction

    // 高端操作，形参实现可传入千万种不同的receiver调用任意的receiver的action功能
    ConcreteCommand(Receiver *receiver, pAction action){
        _receiver = receiver;
        _action = action;
    }

    void Execute() override{
        (_receiver->*_action)(); // 高端操作，实现可传入千万种不同的receiver调用任意的receiver的action功能
    }

private:
    Receiver *_receiver;
    pAction _action;
};

/**
 * @brief 这个类非必须存在，只是构建一个调用者（也可以理解为执行者），那么就不做详细说明了
 * 
 */
class Invoker
{
public:
     Invoker(Command *command) : _command(command){}
     void Invoke()
     {
          _command->Execute();
     }
private:
     Command *_command;
};

/**
 * @brief 测试
 * 
 * @return int 
 */
int main(){
    Receiver1 docFile; // 构建接受者，它是真正执行动作的类
    // 构建命令，用于给执行者执行的命令，相当于给 Receiver1 做了接口隔离开来,传入需要执行的 Action
    Command *cmd = new ConcreteCommand<Receiver1>(&docFile, &Receiver1::Action1);
    cmd->Execute(); // res: doc file open.
    delete cmd;

    // 构建命令，用于给执行者执行的命令，类似于给 Receiver1 做了接口隔离开来,传入需要执行的 Action
    cmd = new ConcreteCommand<Receiver1>(&docFile, &Receiver1::Action2);
    cmd->Execute(); // res: doc file close.
    delete cmd;

    Receiver2 textFile; // 构建接受者，它是真正执行动作的类
    // 构建命令，用于给执行者执行的命令，相当于给 Receiver2 做了接口隔离开来,传入需要执行的 Action
    cmd = new ConcreteCommand<Receiver2>(&textFile, &Receiver2::Action1);
    cmd->Execute(); // res: text copy.
    delete cmd;

    // 构建命令，用于给执行者执行的命令，相当于给 Receiver2 做了接口隔离开来,传入需要执行的 Action
    cmd = new ConcreteCommand<Receiver2>(&textFile, &Receiver2::Action2);
    cmd->Execute(); // res: text paste.
    delete cmd;

    // 构建命令，用于给执行者执行的命令，相当于给 Receiver2 做了接口隔离开来,传入需要执行的 Action
    cmd = new ConcreteCommand<Receiver2>(&textFile, &Receiver2::Action2);
    // Invoker 非必须存在，这相当于又多做了一层隔离。是可以使得调用的扩展性更强
    Invoker *invoker = new Invoker(cmd);
    invoker->Invoke(); // Invoker调用者也可以叫执行者
    delete invoker; // 因为压栈所以先析构
    delete cmd;
    return 0;
}