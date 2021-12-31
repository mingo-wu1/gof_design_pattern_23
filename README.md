## 一看就懂的最核心最精简的设计模式

### 创建型：抽象了实例化过程

### 结构型：涉及到如何组合 （类和对象）以获得更大的结构（类和对象 组合 出更大的结构）

### 行为型：涉及到 算法和对象间 职责 的分配（算法和对象间，负责啥，之间好的分配）

- chain of responsibility（责任链） : 将对象连成一条链，并沿着这条链传递该请求，直到有一个对象处理它为止（核心要义）**(行为型的设计模式是不是有点责任分离的意思)**

  - **重点在个链字（用链分离责任）**
  - 结构（核心且最精简的示意图）：

    ![chain_of_responsibility1](/home/victor/workspace/73_design_pattern/gof_design_pattern_23/images/chain_of_responsibility1.png)
  - 一个典型的对象结构可能如下图所示：

    ![chain_of_responsibility2](/home/victor/workspace/73_design_pattern/gof_design_pattern_23/images/chain_of_responsibility2.png)
  - 使用场景：
  - 最精简最核心的代码（复制粘贴即可用）:
- command（命令模式） ：命令作为中间类(包装接受者)、可以扩展很多命令，隔离掉接受者(接受者才是真正处理请求的各种sao操作)，从而使得你可以包装出各种请求者的请求（核心要义）**(行为型的设计模式是不是有点责任分离的意思)**

  - 重点在于**命令作为中间类(包装接受者)、可以扩展很多命令，并隔离掉接受者（用命令类分离具体执行操作的接受者）**
  - 结构（核心且最精简的示意图）：
  - 使用场景：
  - 最精简最核心的代码（复制粘贴即可用）:
- interpreter（解释器模式） ：翻译器（翻译要重点理解），**递归般的判断的**去翻译一个句子，**翻译的语法做隔离**，核心点是**递归般的判断的** 和 **翻译的语法隔离**，翻译的语法可以扩展很多种（核心要义）**(行为型的设计模式是不是有点责任分离的意思)**

  - 结构（核心且最精简的示意图）：
  - 使用场景：
  - 最精简最核心的代码（复制粘贴即可用）:

### ubuntu编译测试指令例子：

```
g++ -o test chain_of_responsibility.cpp --std=c++11
```

### git 地址

```
git clone https://hub.fastgit.org/mingo-wu1/gof_design_pattern_23.git
```
