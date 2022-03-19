#include <iostream>

using namespace std;
class LinkedStack;
class LinkedStack2;
class StackNode
{
    friend class LinkedStack;

public:
    StackNode *link;
    char data;
    float data2;

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
    StackNode(float &c, StackNode *ptr = NULL)
    {
        data2 = c;
        link = ptr;
    }
};
class LinkedStack
{ //链式栈类定义
public:
    StackNode *top; //栈顶指针
public:
    LinkedStack(); //构造函数
    char getTop(char &ch);
    void Push(char &ch); //进栈
    int Pop(char &ch);   //退栈
    float getTop(float &ch);
    void Push(float &ch); //进栈
    int Pop(float &ch);   //退栈
    void makeEmpty();    //清空栈的内容
    int IsEmpty() { return (top == NULL) ? 1 : 0; }
};
LinkedStack::LinkedStack()
{
    top = NULL;
}
char LinkedStack::getTop(char &ch)
{
    ch = top->data;
    return ch;
}
float LinkedStack::getTop(float &ch)
{
    ch = top->data2;
    return ch;
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
void LinkedStack::Push(float &ch)
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
int LinkedStack::Pop(float &ch)
{
    //删除栈顶结点, 返回被删栈顶元素的值。
    if (IsEmpty())
        return 0;       //栈空返回
    StackNode *p = top; //暂存栈顶元素
    top = top->link;    //退栈顶指针
    ch = p->data2;
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
void Calculator() //把中缀表达式e转换成后缀表示并输出
{
    LinkedStack OPTR,OPND;
    float ch2;
    char ch = '#', ch1, op;
    OPTR.Push(ch);
    cin.get(ch);
    while (ch != '#' || OPTR.getTop(ch1) != '#')
    {
        if (isdigit(ch))
        {
            cin.putback(ch); //回退一下，
            cin >> ch2;      //读取操作数
            cin.get(ch);
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
    float result;
    OPND.getTop(result);
    cout << result;
}
int main()
{
    Calculator();
    return 0;
}
