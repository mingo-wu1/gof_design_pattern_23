#include <iostream>

/**
 * @brief 实际物体的基类，接口
 * 
 */
class Subject {
public:
  ~Subject(){}
  virtual void Request() = 0;
};

/**
 * @brief
 * 核心，他只是代理，那么必须拥有实际物体指针，同时他还必须跟实际物体绑定成同一种类型（同样的继承），无缝调用
 * 实际物体的方法
 */
class Proxy : public Subject {
public:
  /**
   * @brief Construct a new Proxy object
   *
   * @param s 核心点：因为是个代理，所有必须拥有实际物体指针
   */
  Proxy(Subject *s) { _s = s; }
  /**
   * @brief 核心点：调用实际物体的方法
   *
   */
  void Request() override { _s->Request(); }

private:
  Subject *_s;
};

/**
 * @brief 实际物体
 * 
 */
class RealSubject : public Subject {
public:
  void Request() override { std::cout << "real subject request." << std::endl; }
};

/**
 * @brief 测试
 * 
 * @return int 
 */
int main() {
  Subject *s = new RealSubject;
  Proxy p(s);
  p.Request();
  delete s;
  return 0;
}