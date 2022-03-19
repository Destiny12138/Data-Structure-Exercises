#include <iostream>

using namespace std;
class steak;
class StackNode
{
    friend class LinkedStack;

public:
    StackNode *link;
    char data;

public:
    StackNode(StackNode *ptr = NULL)
    {
        link = ptr;
    }
    StackNode(char &c, StackNode *ptr = NULL)
    {
        data = c;
        link = ptr;
    }
};
class LinkedStack
{ //链式栈类定义
public:
    StackNode *top; //栈顶指针
public:
    LinkedStack(); //构造函数
    void getTop(char &ch);
    void Push(char &ch); //进栈
    int Pop(char &ch);   //退栈
    void makeEmpty();    //清空栈的内容
    int IsEmpty() { return (top == NULL) ? 1 : 0; }
};
LinkedStack::LinkedStack()
{
    top = NULL;
}
void LinkedStack::getTop(char &ch)
{
    ch = top->data;
}
void LinkedStack::makeEmpty()
{
    if (top != NULL)
    {
        StackNode *p = top->link;
        while (top != NULL)
        { //逐个结点释放
            p = top;
            top = top->link;
            delete p;
        }
    }
}
void LinkedStack::Push(char &ch)
{
    top = new StackNode(ch, top); //创建新结点
}

int LinkedStack::Pop(char &ch)
{
    //删除栈顶结点, 返回被删栈顶元素的值。
    if (IsEmpty())
        return 0;       //栈空返回
    StackNode *p = top; //暂存栈顶元素
    top = top->link;    //退栈顶指针
    ch = p->data;
    delete p; //释放结点
    return 1;
}
int isp(char &c)
{
    //返回栈内优先级
    if (c == '#')
    {
        return 0;
    }
    else if (c == '(')
    {
        return 1;
    }
    else if (c == ')')
    {
        return 6;
    }
    else if (c == '+' || c == '-')
    {
        return 3;
    }
    else
    {
        return 5;
    }
}
int icp(char &c)
{
    //返回栈外优先级
    if (c == '#')
    {
        return 0;
    }
    else if (c == '(')
    {
        return 6;
    }
    else if (c == ')')
    {
        return 1;
    }
    else if (c == '+' || c == '-')
    {
        return 2;
    }
    else
    {
        return 4;
    }
}
void postfix() //把中缀表达式e转换成后缀表示并输出
{
    LinkedStack S;
    char ch = '#', ch1, op;
    S.Push(ch);
    cin.get(ch);
    while (!S.IsEmpty())
    {
        if (isdigit(ch))
        {
            cout << ch;
            cin.get(ch);
        }
        else
        {
            S.getTop(ch1);
            if (icp(ch) > isp(ch1))
            {
                S.Push(ch);
                cin.get(ch);
            }
            else if (icp(ch) < isp(ch1))
            {
                S.Pop(op);
                cout << op;
            }
            else
            {
                S.Pop(op);
                if (op == '(')
                    cin.get(ch); //相等，此时ch为’)’ ，op=‘(‘ 或者#(准备结束)；
            }
        }
    }
}
int main()
{
    postfix();
    return 0;
}