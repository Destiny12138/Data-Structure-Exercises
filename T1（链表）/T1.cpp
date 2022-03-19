#include <iostream>

using namespace std;
class List;
class LinkNode
{
    friend class List;

protected:
    LinkNode *link;
    int data;

public:
    LinkNode(LinkNode *p = NULL) { link = p; }
    LinkNode(int num, LinkNode *p = NULL)
    {
        data = num;
        link = p;
    }
    ~LinkNode(){};
};
class List
{
protected:
    int all;
    LinkNode *first;

public:
    List();

    void input();
    void output();
    int remove(int &a);
    void merge(List *l2);
    int find(int a);
    void sort();
};
List::List()
{
    first = new LinkNode();
    all = 0;
}
void List::input()
{
    int num, val;
    cin >> num;
    while (num)
    {
        cin >> val;
        LinkNode *newnode = new LinkNode(val);
        newnode->link = first->link;
        first->link = newnode;
        num--;
    }
}
void List::output()
{
    LinkNode *node = first->link;
    while (node != NULL)
    {
        cout << node->data << endl;
        node = node->link;
    }
}
int List::remove(int &a)
{
    LinkNode *node = first;
    LinkNode *p;
    while (node->link != NULL)
    {
        if (node->link->data == a)
        {
            p = node->link;
            node->link = p->link;
            delete p;
            return 1;
        }
        node = node->link;
        return 0;
    }
}
int List::find(int a)
{
    LinkNode *node = first->link;
    while (node != NULL)
    {
        if (node->data == a)
        {
            return 1;
        }
        node = node->link;
    }
    return 0;
}
void List::merge(List *l2)
{
    for (LinkNode *node = l2->first->link; node != NULL; node = node->link)
    {
        if (!find(node->data))
        {
            LinkNode *newnode = new LinkNode(node->data);
            newnode->link = first->link;
            first->link = newnode;
        }
    }
}
void List::sort()
{
    for (LinkNode *node1 = first->link; node1 != NULL; node1 = node1->link)
    {
        for (LinkNode *node2 = node1->link; node2 != NULL; node2 = node2->link)
        {
            int j;
            if (node1->data > node2->data)
            {
                j = node2->data;
                node2->data = node1->data;
                node1->data = j;
            }
        }
    }
}
int main()
{
    int k = 2;
    List l1, l2, l3;
    l1.input();
    // l1.output();
    l2.input();
    // l2.output();
    l1.merge(&l2);
    l1.sort();
    l1.output();
    return 0;
}