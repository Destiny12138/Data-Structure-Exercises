#include <iostream>

using namespace std;
class LinkedStack;
class LinkedStack2;
class StackNode
{
    friend class LinkedStack;

public:
    StackNode* link;
    char data;

public:
    StackNode(StackNode* ptr = NULL)
    {
        link = ptr;
    }
    StackNode(char& c, StackNode* ptr = NULL)
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
    LinkedStack(); //构造函数
    char getTop(char& ch);
    void Push(char& ch); //进栈
    int Pop(char& ch);   //退栈
    void makeEmpty();    //清空栈的内容
    int IsEmpty() { return (top == NULL) ? 1 : 0; }
};
LinkedStack::LinkedStack()
{
    top = NULL;
}
char LinkedStack::getTop(char& ch)
{
    ch = top->data;
    return ch;
}
void LinkedStack::makeEmpty()
{
    if (top != NULL)
    {
        StackNode* p = top->link;
        while (top != NULL)
        { //逐个结点释放
            p = top;
            top = top->link;
            delete p;
        }
    }
}
void LinkedStack::Push(char& ch)
{
    top = new StackNode(ch, top); //创建新结点
}
int LinkedStack::Pop(char& ch)
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

class StackNode2
{
    friend class LinkedStack2;

public:
    StackNode2* link;
    float data;

public:
    StackNode2(StackNode2* ptr = NULL)
    {
        link = ptr;
    }
    StackNode2(float& c, StackNode2* ptr = NULL)
    {
        data = c;
        link = ptr;
    }
};
class LinkedStack2
{ //链式栈类定义
public:
    StackNode2* top; //栈顶指针
public:
    LinkedStack2(); //构造函数
    float getTop(float& ch);
    void Push(float& ch); //进栈
    int Pop(float& ch);   //退栈
    void makeEmpty();     //清空栈的内容
    int IsEmpty() { return (top == NULL) ? 1 : 0; }
};
LinkedStack2::LinkedStack2()
{
    top = NULL;
}
float LinkedStack2::getTop(float& ch)
{
    ch = top->data;
    return ch;
}
void LinkedStack2::makeEmpty()
{
    if (top != NULL)
    {
        StackNode2* p = top->link;
        while (top != NULL)
        { //逐个结点释放
            p = top;
            top = top->link;
            delete p;
        }
    }
}
void LinkedStack2::Push(float& ch)
{
    top = new StackNode2(ch, top); //创建新结点
}
int LinkedStack2::Pop(float& ch)
{
    //删除栈顶结点, 返回被删栈顶元素的值。
    if (IsEmpty())
        return 0;       //栈空返回
    StackNode2* p = top; //暂存栈顶元素
    top = top->link;    //退栈顶指针
    ch = p->data;
    delete p; //释放结点
    return 1;
}

int isp(char& c)
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
int icp(char& c)
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
void Calculator() //把中缀表达式e转换成后缀表示并输出
{
    LinkedStack OPTR;
    LinkedStack2 OPND;
    float ch2;
    char ch = '#', ch1, op;
    OPTR.Push(ch);
    cin.get(ch);
    while (ch != '#' || OPTR.getTop(ch1) != '#')
    {
        if (isdigit(ch))
        {
            cin.putback(ch);        //回退一下，
            cin >> ch2;      //读取操作数
            OPND.Push(ch2);
        }
        else
        {
            OPTR.getTop(ch1);
            if (icp(ch) > isp(ch1))
            {

                OPTR.Push(ch);
                cin.get(ch);
            }
            else if (icp(ch) < isp(ch1))
            {
                float right, left, value;
                OPTR.Pop(op);
                OPND.Pop(right);
                OPND.Pop(left);
                if (op == '+')
                {
                    value = left + right;
                    OPND.Push(value);
                }
                else if (op == '-')
                {
                    value = left - right;
                    OPND.Push(value);
                }
                else if (op == '*')
                {
                    value = left * right;
                    OPND.Push(value);
                }
                else
                {
                    if (right == 0.0)
                    {
                        cerr << "Divide by 0 !" << endl;
                        ch = '#';
                        OPTR.Push(ch);
                    }
                    else
                    {
                        value = left / right;
                        OPND.Push(value);
                    }
                }
            }
            else
            {
                if (ch == ')')
                {
                    OPTR.Pop(op);
                    cin.get(ch);
                }
            }
        }
    }
}
    int main() {
     
        Calculator();
        return 0;
    }
    