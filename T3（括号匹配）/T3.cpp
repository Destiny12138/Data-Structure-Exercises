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
    LinkedStack();                  //构造函数
    ~LinkedStack() { makeEmpty(); } //析构函数
    void Push(char &ch);            //进栈
    int Pop(char &ch);              //退栈
    char getTop(char &ch);          //取栈顶 元素
    int IsEmpty() { return (top == NULL) ? 1 : 0; }
    int getSize();
    void makeEmpty(); //清空栈的内容
    void output();
};

LinkedStack::LinkedStack()
{
    top = top = NULL;
    ;
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
int LinkedStack::getSize()
{
    if (IsEmpty())
        return 0; //栈空返回
    else
    {
        int a = 0;
        StackNode *p = top;
        while (p != NULL)
        {
            a++;
            p = p->link;
        }
        return a;
    }
}
int main()
{
    LinkedStack s;
    char ch, ch1;
    cin >> ch;
    int num = 0;
    while (ch != '#')
    {
        num++;
        if (ch == '{' || ch == '[' || ch == '(' || ch == '<')
        {
            s.Push(ch);
        }
        else if (ch == '}' || ch == ']' || ch == ')' || ch == '>')
        {
            s.Pop(ch1);
            if (!((ch == '}' && ch1 == '{') || (ch == ']' && ch1 == '[') || (ch == ')' && ch1 == '(') || (ch == '>' && ch1 == '<')))
            {
                cout << "The " << num << " character '" << ch << "' is wrong.";
                return 0;
            }
        }
        cin >> ch;
    }
    if (!s.IsEmpty())
    {
        cout << "loss of right character ";

        while (!s.IsEmpty())
        {
            s.Pop(ch1);
            if (ch1 == '{')
            {
                cout << "}";
            }
            else if (ch1 == '[')
            {
                cout << "]";
            }
            else if (ch1 == '(')
            {
                cout << ")";
            }
            else if (ch1 == '<')
            {
                cout << ">";
            }
        }
        cout << ".";
    }
    else
    {
        cout << "right";
    }
    return 0;
}