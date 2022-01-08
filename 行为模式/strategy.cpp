#include <iostream>
/**
 * @brief 向前声明，必须是非虚基类
 * 
 */
class Context;

/**
 * @brief 策略类（也叫算法类）基类，也就是算法类接口，策略模式比较简单，给出算法的公共接口，实际就是单纯封装好算法就行
 *        Context通过最简单的方式就是通过Strategy的一个接口去调用算法
 */
class Strategy {
public:
  ~Strategy() {}
  /**
   * @brief 必须定义的接口
   * 
   */
  virtual void AlgorithmInterface() = 0;

  /**
   * @brief 非必须，扩展了一下，用于实现回调功能
   * 
   * @param c 
   */
  virtual void ContextCallback(Context *c) = 0;
};

/**
 * @brief 上下文，也就是调用类，用于调用具体策略，也就是调用算法
 * 
 */
class Context {
public:
  /**
   * @brief Context的构造函数
   * 
   * @param s 必须传入Strategy的指针
   */
  Context(Strategy *s) { _s = s; }
  ~Context() {}

  /**
   * @brief 必须有，context对策略（算法）的具体策略（算法）调用在这里
   * 
   */
  void ContextInterface() { _s->AlgorithmInterface(); };

  /**
   * @brief 非必须，扩展了一下，用于实现Callback回调
   * 
   */
  void Callback() {
    std::cout << "将自身传递给了Strategy并Strategy回调了自己（可同步回调或者异"
                 "步回调）"
              << std::endl;
  }

private:
  Strategy *_s;
};

/**
 * @brief 用模板来实现上下文，代码更简洁，但如果有回调就不能用，所以这里去掉回调
 * 
 * @tparam IStrategy 
 */
template <class IStrategy> 
class Context2 {
public:
  void ContextInterface() { _s.AlgorithmInterface(); }

private:
  IStrategy _s; //这里必须非指针类型
};

/**
 * @brief 继承策略类（也叫算法类）基类，很简单不做说明
 * 
 */
class ConcreteStrategyA : public Strategy {
public:
  void AlgorithmInterface() override {
    std::cout << "concrete strategy A" << std::endl;
  }
  void ContextCallback(Context *c) override { c->Callback(); }
};

/**
 * @brief 继承策略类（也叫算法类）基类，很简单不做说明
 * 
 */
class ConcreteStrategyB : public Strategy {
public:
  void AlgorithmInterface() override {
    std::cout << "concrete strategy B" << std::endl;
  }
  void ContextCallback(Context *c) override {
    { c->Callback(); }
  }
};

/**
 * @brief 继承策略类（也叫算法类）基类，很简单不做说明
 * 
 */
class ConcreteStrategyC : public Strategy {
public:
  void AlgorithmInterface() override {
    std::cout << "concrete strategy C" << std::endl;
  }
  void ContextCallback(Context *c) override {
    { c->Callback(); }
  }
};

/**
 * @brief 测试
 * 
 * @return int 
 */
int main() {
  Strategy *s = new ConcreteStrategyA; //指针构造，堆内存
  Context c(s); //非指针构造，栈内存
  c.ContextInterface(); // 正常调用算法
  s->ContextCallback(&c); // 扩展了一下，用于回调
  delete s; // 必须有析构

  Context2<ConcreteStrategyA> c2; //扩展了一下，用模板实现
  c2.ContextInterface(); // 正常调用算法
  return 0;
}