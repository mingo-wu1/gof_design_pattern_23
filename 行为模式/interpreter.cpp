#include <iostream>

/**
 * @brief 内容，举例：句子的字符
 * 
 */
class Context
{
public:
    char GetChar()
    {
        return letter;
    }

    char letter;
};

/**
 * @brief 核心点：Interpret(Context *),获取字符用于判断
 * 
 */
class AbstractExpression
{
public:
    virtual void Interpret(Context *context) = 0;
};

/**
 * @brief 重点：Interpret(Context *),获取字符用于判断
 * 
 */
class TerminalExpression : public AbstractExpression
{
public:
    void Interpret(Context *context) override
    {
        std::cout<<"not small letter."<<std::endl;
    }
};

/**
 * @brief 重点：Interpret(Context *),获取字符用于判断
 * 
 */
class NonterminalExpression : public AbstractExpression
{
public:
    NonterminalExpression(AbstractExpression *abstractExpression){
        _abstractExpression = abstractExpression;
    }

    /**
     * @brief 全场唯一核心点：Interpret(Context *), 语法树的递归核心点
     * 
     */
    void Interpret(Context *context) override
    {
        if(context->GetChar() >= 0x61 && context->GetChar() <= 0x7A)
            std::cout<<"small letter."<<std::endl;
        else
            _abstractExpression->Interpret(context);
    }

private:
    AbstractExpression *_abstractExpression;
};

/**
 * @brief 测试
 * 
 * @return int 
 */
int main(){
    // 就三个构建对象的过程
    Context *context = new Context;
    AbstractExpression *tExp = new TerminalExpression;
    AbstractExpression *nontExp = new NonterminalExpression(tExp);

    // 测试
    char letters[] = "what the fck?\0";
    for(int i = 0; context->letter = letters[i], letters[i] != '\0'; ++i)
        nontExp->Interpret(context);

    // 析构
    delete(nontExp);
    delete(tExp);
    delete(context);
    return 0;
}