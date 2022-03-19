#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
using namespace std;
class List;
class LinkNode
{
    friend class List;

private:
    LinkNode *link;
    int coef;
    int exp;

public:
    LinkNode(LinkNode *p = NULL) { link = p; }
    LinkNode(int num, LinkNode *p = NULL)
    {
        coef = num;
        link = p;
    }
    LinkNode(const int &a, const int &b, LinkNode *ptr = NULL)
    {
        coef = a;
        exp = b;
        link = ptr;
    }
};
class List
{
protected:
    LinkNode *first;

public:
    List();
    ~List()
    {
        MakeEmpty();
    }
    void MakeEmpty();
    void input();
    void output();
    void Insert(const int &a, const int &b); //插入
    void Add(List &l1, List &l2, List &l3);  //加
    void Sub(List &l1, List &l2, List &l3);  //减
    void Mul(List &l1, List &l2, List &l3);  //乘
    void Dao();                              //导数
    void Cal(float a);                       //计算
    void Qc();                               //去重
    void Copy(List &l3);
    void sort();
};
List::List()
{
    first = new LinkNode();
}
void List::MakeEmpty() //置空
{
    LinkNode *q;
    while (first->link != NULL)
    {
        q = first->link;
        first->link = q->link;
        delete q;
    }
}
void List::input()
{
    int coef, exp;
    cin >> coef;
    while (coef)
    {
        cin >> exp;
        LinkNode *newnode = new LinkNode(coef, exp);
        newnode->link = first->link;
        first->link = newnode;
        cin >> coef;
    }
}
void List::output()
{
    cout << "C(x)=";
    LinkNode *node = first->link;
    while (node != NULL)
    {
        if (node->exp != 0)
        {
            if (node->coef != 1)
            {
                if (node->coef < 0)
                {
                    cout << node->coef << "x";
                }
                if (node->coef > 0)
                {
                    cout << node->coef << "x";
                }
            }
            if (node->coef == 1)
            {
                cout << "x";
            }
            if (node->exp != 1)
            {
                if (node->exp > 0)
                {
                    cout << "^" << node->exp;
                }
                else
                {
                    cout << "^(" << node->exp << ")";
                }
            }
        }
        if (node->exp == 0)
        {
            cout << node->coef;
        }

        if (node->link != NULL && node->link->coef > 0)
        {
            cout << "+";
        }
        node = node->link;
    }
    cout << endl;
}
void List::sort()
{
    for (LinkNode *node1 = first->link; node1 != NULL; node1 = node1->link)
    {
        for (LinkNode *node2 = node1->link; node2 != NULL; node2 = node2->link)
        {
            int j;
            if (node1->exp > node2->exp)
            {
                j = node2->exp;
                node2->exp = node1->exp;
                node1->exp = j;
                j = node2->coef;
                node2->coef = node1->coef;
                node1->coef = j;
            }
        }
    }
}
void List::Insert(const int &a, const int &b)
{
    LinkNode *newnode = new LinkNode(a, b);
    newnode->link = first->link;
    first->link = newnode;
}
void List::Qc()
{
    LinkNode *pc, *p;
    p = first->link;
    while (p->link != NULL)
    {
        LinkNode *q = p->link;
        while (q != NULL)
        {
            if (p->exp == q->exp)
            {
                p->coef = p->coef + q->coef;
                q->coef = 0;
            }
            q = q->link;
        }
        p = p->link;
    }
    LinkNode *r = first;
    while (r != NULL)
    {
        if (r->link != NULL)
        {
            LinkNode *q = r->link;
            int flag = 0;
            if (q->coef == 0)
            {
                r->link = q->link;
                delete q;
                flag = 1;
            }
            if (!flag && r != NULL)
                r = r->link;
        }
        else
        {
            if (r->coef == 0)
                delete r;
            r = r->link;
        }
    }
}
void List::Add(List &l1, List &l2, List &l3)
{
    LinkNode *node1 = l1.first->link;
    LinkNode *node2 = l2.first->link;
    while (node1 != NULL)
    {
        l3.Insert(node1->coef, node1->exp);
        node1 = node1->link;
    }
    while (node2 != NULL)
    {
        l3.Insert(node2->coef, node2->exp);
        node2 = node2->link;
    }
    l3.Qc();
}
void List::Sub(List &l1, List &l2, List &l3)
{
    LinkNode *node1 = l1.first->link;
    LinkNode *node2 = l2.first->link;
    while (node1 != NULL)
    {
        l3.Insert(node1->coef, node1->exp);
        node1 = node1->link;
    }
    while (node2 != NULL)
    {
        l3.Insert(-(node2->coef), node2->exp);
        node2 = node2->link;
    }
    l3.Qc();
}
void List::Mul(List &l1, List &l2, List &l3)
{
    l1.sort();
    l2.sort();
    LinkNode *p = l1.first->link;
    LinkNode *q;
    while (p != NULL)
    {
        q = l2.first->link;
        while (q != NULL)
        {
            l3.Insert(p->coef * q->coef, p->exp + q->exp);
            q = q->link;
        }
        p = p->link;
    }
    l3.Qc();
    if (l3.first->link == NULL)
    {
        l3.Insert(0, 0);
    }
}
void List::Dao()
{
    LinkNode *p = first->link;
    while (p != NULL)
    {
        p->coef = p->coef * p->exp;
        p->exp = p->exp - 1;
        p = p->link;
    }
}
void List::Cal(float a)
{
    float sum = 0;

    for (LinkNode *p = first->link; p != NULL; p = p->link)
    {
        sum = sum + (p->coef) * pow(a, p->exp);
    }
    cout << setiosflags(ios::fixed) << setprecision(2);
    cout << sum << endl;
}
void List::Copy(List &l3)
{
    for (LinkNode *p = first->link; p != NULL; p = p->link)
    {
        l3.Insert(p->coef, p->exp);
    }
}

int main()
{

    List l1, l2, l3, l4;
    while (1)
    {
        char a;
        cin >> a;
        if (a == 'C')
        {
            l1.input();
            l2.input();
        }
        else if (a == 'P')
        {
            l3.MakeEmpty();
            l3.Add(l1, l2, l3);
            l3.sort();
            l3.output();
        }
        else if (a == 'S')
        {
            l3.MakeEmpty();
            l3.Sub(l1, l2, l3);
            l3.sort();
            l3.output();
        }
        else if (a == 'M')
        {
            l3.MakeEmpty();
            l3.Mul(l1, l2, l3);
            l3.sort();
            l3.output();
        }
        else if (a == 'D')
        {
            l3.MakeEmpty();
            l1.Copy(l3);
            l3.Dao();
            l3.sort();
            l3.Qc();
            l3.output();
        }
        else if (a == 'V')
        {
            float x;
            cin >> x;
            l1.Cal(x);
        }
        else if (a == 'E')
        {
            l1.MakeEmpty();
            l2.MakeEmpty();
            l3.MakeEmpty();
        }
        else if (a == 'X')
        {
            return 0;
        }
    }
    return 0;
}