#include <iostream>

using namespace std;
class steak;
class StackNode
{
    friend class LinkedStack;

public:
    StackNode* link;
    int data;

public:
    StackNode(StackNode* ptr = NULL)
    {
        link = ptr;
    }
    StackNode(int& c, StackNode* ptr = NULL)
    {
        data = c;
        link = ptr;
    }
};
class LinkedStack
{ //链式栈类定义
public:
    StackNode* top; //栈顶指针
public:
    LinkedStack();                  //构造函数
   
    void Push(int& ch);             //进栈
    int Pop(int& ch);               //退栈
    
    int IsEmpty() { return (top == NULL) ? 1 : 0; }
    int getSize();
    
    void output();
};
LinkedStack::LinkedStack()
{
    top = NULL;
}
void LinkedStack::Push(int& ch)
{
    top = new StackNode(ch, top); //创建新结点
}

int LinkedStack::Pop(int& ch)
{
    //删除栈顶结点, 返回被删栈顶元素的值。
    if (IsEmpty())
        return 0;       //栈空返回
    StackNode* p = top; //暂存栈顶元素
    top = top->link;    //退栈顶指针
    ch = p->data;
    delete p; //释放结点
    return 1;
}
void LinkedStack::output()
{
    int b;
    while (top != NULL)
    {
        Pop(b);
        cout << b;
    }
}
void conversion()
{
    LinkedStack S;
    int N;
    cin >> N;
    while (N)
    {
        //此处的2表示2进制，其他进制同理
        int a = N % 2;
        S.Push(a);
        N = N / 2;
    }
    S.output();
}

int main()
{
    conversion();
    return 0;
}