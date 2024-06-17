# C++

## i++ 和 ++i 的区别

i++ 的汇编代码如下：

```
mov eax, [ebx]  ; 将 i 的值加载到寄存器 eax，因为i可能需要参与运算，所以会把i提取到寄存器
inc eax         ; 递增 eax 中的值
mov [ebx], eax  ; 将新的值存回 i 的内存位置
```



++i 的汇编代码如下：

```
; 假设 i 存储在内存位置 [ebx]
inc dword ptr [ebx]  ; 直接在 [ebx] 中执行递增操作
; 此时 [ebx] 中包含了递增后的值
```



因此i++的效率要比++i低一些



## C++ 编译和使用静态库

静态库的组成部分，源文件1

```c++
// source1.cpp
#include "mylib.h"

int add(int a, int b) {
    return a + b;
}
```

静态库的组成部分，源文件2

```c++
// source2.cpp
#include "mylib.h"

int multiply(int a, int b) {
    return a * b;
}

```

静态库的组成部分，头文件

```
//mylib.h
int add(int a, int b);
int multiply(int a, int b);
```

编译出两个静态库文件
```c++
g++ source1.cpp -c -o source1.o
g++ source2.cpp -c -o source2.o
```

编译出静态库
```
ar rcs mylib.a source1.o source2.o
```



使用静态库的文件

```c++
//myapp.cpp
#include <iostream>
#include "mylib.h" // 包括静态库的头文件

int main() {
    int result = add(5, 3); // 调用静态库中的函数
    std::cout << "5 + 3 = " << result << std::endl;
    return 0;
}

```

通过g++ 命令链接静态库，头文件的目的在于提供静态库的接口，因此静态库需要带一个头文件和一个.a 文件
```
g++ myapp.cpp -o main mylib.a
./main
```



## C++ 编译和使用动态库

对于和静态库同样的一组文件，我们可以让他编译为动态库，并且使用它。

注意，库的名字前必须有lib ， 并且第三行要有 -l 作为前缀

```
g++ source1.cpp -shared -o libsource1.so 
g++ source2.cpp -shared -o libsource2.so 
g++ myapp.cpp -o main -L. -lsource1 -lsource2
./main
5 + 3 = 8
```



## C++多线程相关的特性和类：

 ### thread 类

创建一个新的线程，join函数是为了等待线程结束，如果不使用join，当进程结束后，线程强制结束

```c++
#include <iostream>
#include <thread>

void thread_function(int value1,int value2) {
    std::cout << "Received value1: " << value1 << std::endl;
	std::cout << "Received value2: " << value2 << std::endl;
}

int main() {
    int parameter = 42;
    std::thread t1(thread_function, parameter,2); // 将参数传递给线程函数
    t1.join();

    return 0;
}

```



C++11引入了以下多线程相关的特性和类：

-   `std::thread`：用于创建和管理线程的类。
-   `std::mutex`：用于互斥锁。
-   `std::condition_variable`：用于条件变量，支持线程的等待和通知机制。
-   `std::atomic`：提供原子操作，用于多线程环境下的数据同步。
-   其他多线程库和功能，如`std::async`、`std::future`、`std::promise`



### mutex 类

**std::mutex**：用于互斥锁，保护共享资源。下面是给函数 thread_function 加了一个锁，同时只能有一个函数访问临界资源。如果没有加锁，cout语句输出中途，可能发生进程的切换。

```C++
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void thread_function(int id) {
    mtx.lock(); // 锁定互斥锁
    std::cout << "Thread " << id << " is accessing the shared resource." << std::endl;
    mtx.unlock(); // 解锁互斥锁
}

int main() {
    std::thread t1(thread_function, 1);
    std::thread t2(thread_function, 2);

    t1.join();
    t2.join();

    return 0;
}

```



### shared_mutex 类

在这个示例中，我们有三个读者线程和两个写者线程，它们都试图访问 `sharedData`。`std::shared_mutex` 用于确保只有一个写者可以修改 `sharedData`，而多个读者可以同时访问它。使用 `lock_shared()` 来获取读锁，使用 `lock()` 来获取写锁，然后使用 `unlock_shared()` 和 `unlock()` 来释放锁。

请注意，写者在写入数据时会独占访问 `sharedData`，因此读者必须等待写者完成。读者可以同时访问数据，不会相互阻塞。这有助于提高程序的性能，特别是在具有大量读操作和较少写操作的情况下。

```c++
#include <iostream>
#include <thread>
#include <mutex>

std::shared_mutex dataMutex;
int sharedData = 0;

void ReaderFunction(int id) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 模拟一些工作
    dataMutex.lock_shared(); // 获取读锁
    std::cout << "Reader " << id << " is reading data: " << sharedData << std::endl;
    dataMutex.unlock_shared(); // 释放读锁
}

void WriterFunction(int id) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 模拟一些工作
    dataMutex.lock(); // 获取写锁，独占访问数据
    sharedData += 1;
    std::cout << "Writer " << id << " is writing data: " << sharedData << std::endl;
    dataMutex.unlock(); // 释放写锁
}

int main() {
    const int numReaders = 3;
    const int numWriters = 2;

    std::thread readers[numReaders];
    std::thread writers[numWriters];

    for (int i = 0; i < numReaders; ++i) {
        readers[i] = std::thread(ReaderFunction, i);
    }

    for (int i = 0; i < numWriters; ++i) {
        writers[i] = std::thread(WriterFunction, i);
    }

    for (int i = 0; i < numReaders; ++i) {
        readers[i].join();
    }

    for (int i = 0; i < numWriters; ++i) {
        writers[i].join();
    }

    return 0;
}

```





建议c++ 17 用下面的： 

```c++
#include <iostream>
#include <shared_mutex>
#include <thread>

std::shared_mutex dataMutex;
int sharedData = 0;

void ReaderFunction(int id) {
    std::shared_lock<std::shared_mutex> lock(dataMutex); // 获取共享锁
    std::cout << "Reader " << id << " is reading data: " << sharedData << std::endl;
}

void WriterFunction(int id) {
    std::unique_lock<std::shared_mutex> writeLock(dataMutex); // 获取独占锁
    sharedData += 1;
    std::cout << "Writer " << id << " is writing data: " << sharedData << std::endl;
}

int main() {
    const int numReaders = 3;
    const int numWriters = 2;

    std::thread readers[numReaders];
    std::thread writers[numWriters];

    for (int i = 0; i < numReaders; ++i) {
        readers[i] = std::thread(ReaderFunction, i);
    }

    for (int i = 0; i < numWriters; ++i) {
        writers[i] = std::thread(WriterFunction, i);
    }

    for (int i = 0; i < numReaders; ++i) {
        readers[i].join();
    }

    for (int i = 0; i < numWriters; ++i) {
        writers[i].join();
    }

    return 0;
}

```



### shared_lock 类

`std::shared_lock` 适用于 `std::shared_mutex`，允许多个线程同时共享访问。



### unique_lock 类

`std::unique_lock` 适用于 `std::shared_mutex`，允许一个线程独占锁定，也适用于 `std::mutex`，允许一个线程独占锁定。



### shared_timed_mutex 类

下面的代码相当于读写锁

```C++
std::shared_timed_mutex rwLock;
std::shared_timed_mutex::scoped_lock lock(rwLock);

std::map<KeyType, ValueType> myMap;
// 使用 myMap 进行读写操作
```



### shared_timed_mutex::scoped_lock 类






## 信号量

```C++
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

class Semaphore {
public:
    Semaphore(int count) : count_(count) {}

    void Wait() {
        std::unique_lock<std::mutex> lock(mutex_);
        while (count_ == 0) {
            condition_.wait(lock);
        }
        count_--;
    }

    void Signal() {
        std::unique_lock<std::mutex> lock(mutex_);
        count_++;
        condition_.notify_one();
    }

private:
    std::mutex mutex_;
    std::condition_variable condition_;
    int count_;
};

Semaphore semaphore(5); // 初始化信号量

void Worker(int id) {
    semaphore.Wait();
    std::cout << "Worker " << id << " is working." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2)); // 模拟工作
    semaphore.Signal();
    std::cout << "Worker " << id << " is done." << std::endl;
}

int main() {
    std::thread workers[10];
    for (int i = 0; i < 10; i++) {
        workers[i] = std::thread(Worker, i);
    }

    for (int i = 0; i < 10; i++) {
        workers[i].join();
    }

    return 0;
}

```



## 安装Boost

问题描述
我在Ubuntu上，并且想安装Boost。我尝试过

sudo apt-get install boost
1
但是没有这样的软件包。在Ubuntu上安装Boost的最佳方法是什么？

最佳方法
您可以使用apt-get命令(需要sudo)

sudo apt-get update
sudo apt-get install libboost-all-dev
1
2
或者你可以先查找一下

sudo apt search boost
1
安转好之后，默认安装目录在 /usr/include/boost


## 重载和重写

在面向对象编程中，重载（Overloading）和重写（Overriding）是两个不同的概念，用于实现多态性和灵活性。它们具有不同的含义和用途：

1. 重载（Overloading）：
   - 重载是指在同一个类中可以定义多个具有相同名称但不同参数列表的函数或操作符。
   - 重载的目的是为了提供不同的参数类型或个数的函数，以便根据传递给函数的参数来选择正确的函数版本。
   - 重载是一种编译时多态，也被称为静态多态，因为在编译时确定要调用的函数。

示例：
```cpp
class MathOperations {
public:
    int add(int a, int b) {
        return a + b;
    }

    double add(double a, double b) {
        return a + b;
    }
};
```

在上面的示例中，`MathOperations`类中的`add`函数被重载，分别接受不同类型的参数。

2. 重写（Overriding）：
   - 重写是指在派生类中重新定义基类中已经存在的虚函数，以改变其行为。
   - 重写用于实现运行时多态，也称为动态多态，因为在运行时根据对象的实际类型来确定要调用的函数版本。
   - 重写要求基类函数必须是虚函数（通过`virtual`关键字标记），并且派生类中的函数签名（函数名和参数列表）必须与基类中的虚函数一致。

示例：
```cpp
class Shape {
public:
    virtual void draw() {
        // 基类中的虚函数
        // 可在派生类中重写以改变其行为
    }
};

class Circle : public Shape {
public:
    void draw() override {
        // 派生类中的虚函数的重写版本
        // 改变了基类函数的行为
    }
};
```

在上面的示例中，`Shape`类中的`draw`函数是一个虚函数，而`Circle`类通过重写`draw`函数来改变其行为。

关键区别：
- 重载是在同一个类中定义多个同名函数，参数列表不同，用于处理不同的输入。
- 重写是在派生类中重新定义基类中已有的虚函数，用于改变函数的行为以实现多态性。

总之，重载和重写是两个不同的概念，用于不同的目的。重载用于提供同一类中的多个不同版本的函数，而重写用于实现派生类中的多态性，以改变基类中虚函数的行为。


## 运算符重载

```C++
#include <iostream>

template <typename T>
class OperatorOverloadDemo {
public:
    T value;

    OperatorOverloadDemo(T val) : value(val) {}

    // 重载加法运算符
    OperatorOverloadDemo operator+(const OperatorOverloadDemo& other) const {
        return OperatorOverloadDemo(value + other.value);
    }

    // 重载减法运算符
    OperatorOverloadDemo operator-(const OperatorOverloadDemo& other) const {
        return OperatorOverloadDemo(value - other.value);
    }

    // 重载乘法运算符
    OperatorOverloadDemo operator*(const OperatorOverloadDemo& other) const {
        return OperatorOverloadDemo(value * other.value);
    }

    // 重载除法运算符
    OperatorOverloadDemo operator/(const OperatorOverloadDemo& other) const {
        if (other.value != 0) {
            return OperatorOverloadDemo(value / other.value);
        } else {
            throw std::runtime_error("Division by zero!");
        }
    }

    // 重载赋值运算符
    OperatorOverloadDemo& operator=(const OperatorOverloadDemo& other) {
        if (this != &other) {
            value = other.value;
        }
        return *this;
    }

    // 重载比较运算符
    bool operator==(const OperatorOverloadDemo& other) const {
        return value == other.value;
    }

    bool operator!=(const OperatorOverloadDemo& other) const {
        return !(*this == other);
    }
};

int main() {
    OperatorOverloadDemo<int> a(5);
    OperatorOverloadDemo<int> b(3);

    // 使用重载的运算符
    OperatorOverloadDemo<int> result1 = a + b;
    OperatorOverloadDemo<int> result2 = a - b;
    OperatorOverloadDemo<int> result3 = a * b;
    OperatorOverloadDemo<int> result4 = a / b;

    std::cout << "a + b = " << result1.value << std::endl;
    std::cout << "a - b = " << result2.value << std::endl;
    std::cout << "a * b = " << result3.value << std::endl;
    std::cout << "a / b = " << result4.value << std::endl;

    // 比较运算符
    if (a == b) {
        std::cout << "a is equal to b" << std::endl;
    } else {
        std::cout << "a is not equal to b" << std::endl;
    }

    return 0;
}

```







## 实现线程之间的同步有哪些方法？

在C++中，有多种方法可以实现线程之间的同步，以确保线程以协调的方式执行任务。以下是一些常见的线程同步方法：

1. 互斥锁（Mutex）：使用`std::mutex`或其他互斥锁类型，可以确保在任何给定时间内只有一个线程能够访问临界区。互斥锁用于防止多个线程同时访问共享资源，以避免数据竞争和不一致性。

2. 条件变量（Condition Variable）：`std::condition_variable`用于在线程之间传递信号，以实现等待和通知机制。它通常与互斥锁一起使用，以实现线程的等待和唤醒操作，例如生产者-消费者问题。

3. 信号量（Semaphore）：信号量是一种通用的同步原语，它允许线程控制对共享资源的访问。信号量可以用来限制同时访问资源的线程数量。

4. 互斥量（Mutex）：`std::mutex`和`std::unique_lock`可以用于实现互斥的临界区，确保在任何时刻只有一个线程可以进入关键部分。

5. 原子操作（Atomic Operations）：C++标准库提供了原子类型和原子操作，例如`std::atomic`，以实现对共享数据的安全访问。原子操作是无锁同步的一种方式，适用于某些特定情况下的高性能需求。

6. 互斥条件变量（Mutex Condition Variable）：`std::condition_variable`通常与互斥锁结合使用，以等待某些条件成立，并在条件满足时唤醒等待的线程。这种方法用于解决多线程协作问题。

7. 屏障（Barrier）：`std::barrier`是C++20引入的同步原语，它允许一组线程在达到某个点时同步等待，并在所有线程都到达后继续执行。

8. 读写锁（Read-Write Lock）：`std::shared_mutex`（C++17引入）用于实现读写锁，允许多个线程并发地读取共享数据，但只允许一个线程写入数据。

9. 计数器：自定义的计数器可以用于在线程之间进行通信和同步。线程可以增加或减少计数器的值，并在特定值达到时等待或继续执行。

不同的同步机制适用于不同的情况和需求。选择合适的同步方法取决于你的应用程序的特定需求，以确保线程之间的协作和数据访问是安全和有效的。



## 重载复制构造函数的场景

1.   **深拷贝需求**： 如果你的类包含指针或资源句柄，并且你想要确保在复制对象时深拷贝底层资源而不是简单地复制指针，那么你需要自定义复制构造函数来执行深拷贝操作。这可以避免多个对象共享相同的资源，从而防止潜在的资源管理问题。
2.   **特定资源管理需求**：如果你的类使用了需要特殊处理的资源（如文件句柄、数据库连接等），你可能需要自定义复制构造函数来确保资源的正确管理和共享。
3.   **不可拷贝成员变量**：如果你的类包含不可拷贝的成员变量（例如，某些C++标准库容器，或者其他自定义类的对象），默认的复制构造函数可能无法正常工作。在这种情况下，你需要自定义复制构造函数，以确保这些成员变量正确地复制或重新初始化。
4.   **需要进行额外的逻辑或验证**：有时，你可能需要在复制构造函数中添加额外的逻辑或验证，以确保对象的正确状态。例如，你可以在复制构造函数中添加断言或记录操作，以帮助调试或跟踪对象的创建。
5.   **子类化需求**：如果你创建了一个子类，它需要在复制时保留父类的状态并添加自己的额外状态，你可以重载复制构造函数来确保正确地处理这两个方面。



## 为什么RAII 可以保证即使在异常发生时，资源也会被正确释放？

当一个异常被抛出时，C++ 会展开堆栈，直到找到能够处理该异常的 `catch` 块。在这个堆栈展开过程中，所有局部对象都会被销毁，其析构函数会被自动调用。这就是为什么 RAII 能够在异常发生时确保资源被释放。
