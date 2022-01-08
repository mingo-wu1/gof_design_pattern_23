#include <iostream>

/**
 * @brief 定义抽象原语操作
 *
 */
class AbstractClass {
public:
  ~AbstractClass(){}
  void TemplateMethod() {
    PrimitiveOperation1();
    PrimitiveOperation2();
  }
  virtual void PrimitiveOperation1() = 0;
  virtual void PrimitiveOperation2() = 0;
};

class ConcreteClass : public AbstractClass {
public:
  void PrimitiveOperation1() override {
    std::cout << "add 减法操作" << std::endl;
  }
  void PrimitiveOperation2() override {
    std::cout << "multiplication 乘法操作" << std::endl;
  }
};

/**
 * @brief 测试
 *
 * @return int
 */

int main() {
  AbstractClass *absClass = new ConcreteClass;
  absClass->TemplateMethod();
  delete absClass;
  return 0;
}