# Windows编程调试方法 — 控制台调试

## 前言
刚刚开始学windows编程，遇到问题不知道如何调试，控制台输入输出函数用不了，也尝试过MessageBox来输出，效果不是很好
## VS调试窗口调试
这种输出方式代码比较好写，缺点是只能在调试窗口看到输出语句
编译时选择“开始调试”，在需要输出的地方调用OutputDebugString函数

```C++
OutputDebugString(szBuffer);
```
## 控制台窗口调试
这种调试方式允许在控制台中输入和输出

### 1.打开窗口
使用AllocConsole函数打开一个控制台窗口，一个进程最多可以附加一个控制台

```
AllocConsole();
```

### 2.重定向输入和输出
freopen函数在VS中可能会报错，在程序第一行加入

```
#define _CRT_SECURE_NO_WARNINGS
```
```
freopen("CONOUT$", "w", stdout);
freopen("CONIN$", "r", stdin);
```
### 3.输出调试信息
可以用cin，cout，printf，scanf这些控制台输入输出语句

```
int x;
cin >> x;
cout << x << endl;
```
### 4.分离控制台窗口
分离与调用进程相关联的控制台窗口

```
FreeConsole();
```
### 示例

```
/* -------------------------------------------------------------------
                    MyWindows.c -- 基本窗口模型
                                《Windows 程序设计（SDK）》视频教程
--------------------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <tchar.h>
#include <iostream>
using namespace std;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{

    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONIN$", "r", stdin);
    static TCHAR szAppName[] = TEXT("MyWindows");
    HWND hwnd;//窗口句柄

    MSG msg;//消息结构
    WNDCLASS wndclass;//窗口类结构   


    wndclass.style = CS_HREDRAW | CS_VREDRAW;//窗口类型
    wndclass.lpfnWndProc = WndProc;//指定窗口过程
    wndclass.cbClsExtra = 0;//预留的额外空间
    wndclass.cbWndExtra = 0;//预留的额外空间
    wndclass.hInstance = hInstance;//应用程序的实例句柄
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//为所有基于该窗口类的窗口设定一个图标
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);//为所有基于该窗口类的窗口设定一个鼠标指针
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//	指定窗口背景色
    wndclass.lpszMenuName = NULL;//	指定窗口菜单
    wndclass.lpszClassName = szAppName;//指定窗口类名

    if (!RegisterClass(&wndclass))
    {
        MessageBox(NULL, TEXT("这个程序需要在 Windows NT 才能执行！"), szAppName, MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindow(szAppName,//类名
        TEXT("鱼C工作室"),//标题
        WS_OVERLAPPEDWINDOW,//风格
        CW_USEDEFAULT,//初始x坐标
        CW_USEDEFAULT,//初始y坐标
        CW_USEDEFAULT,//初始宽度
        CW_USEDEFAULT,//初始高度
        NULL,//父窗口句柄
        NULL,//窗口菜单句柄
        hInstance,//程序实例句柄
        NULL);//创建参数

    ShowWindow(hwnd, iCmdShow);//显示窗口
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0))//消息循环
    {
        TranslateMessage(&msg);//翻译一些键盘消息
        DispatchMessage(&msg);//将消息发送给窗口过程
    }

    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;//设备环境句柄
    PAINTSTRUCT ps;//绘制结构
    RECT rect;//矩形结构

    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);//获得设备句柄
        GetClientRect(hwnd, &rect);//获取矩形结构
        cout << "开始处理WM_PAINT消息" << endl;
        DrawText(hdc, TEXT("大家好，这是我的第一个窗口程序！"), -1, &rect,
            DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        EndPaint(hwnd, &ps);// 函数标记指定窗口的绘画过程结束
        return 0;

    case WM_DESTROY://窗口关闭
        PostQuitMessage(0);
        FreeConsole();
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);//交给windows去处理
}
```