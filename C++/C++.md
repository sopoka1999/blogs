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



