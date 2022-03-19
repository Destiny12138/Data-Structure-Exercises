#include <iostream>
#include <stdlib.h>
using namespace std;
typedef int T;
class SeqList
{
private:
    T *data;
    int MaxSize; //顺序表最多可以存放的元素个数。
    int last;    //顺序表最后一个元素的下标，初始值为-1。
public:
    SeqList(int sz);
    ~SeqList() { delete[] data; }
    void Input();                   //首先输入元素的个数，然后顺次输入元素的值。
    void Output();                  //输出线性表的所有元素。
    void Insert(const T &x, int i); //在线性表中第i个位置插入值为x的元素。
    int Remove(T &x);               //从线性表中删除第一个值等于x的元素。
    int Find(T &x);
};
SeqList::SeqList(int sz)
{
    data = new T[sz];
    MaxSize = sz;
    last = -1;
}
void SeqList::Input()
{
    int num;
    cin >> num;
    while (num)
    {
        cin >> data[last + 1];
        last++;
        num--;
    }
}
void SeqList::Output()
{
    cout << "The elements are:" << endl;
    for (int i = 0; i <= last; i++)
    {
        cout << data[i] << endl;
    }
}
void SeqList::Insert(const T &x, int i)
{
    for (int j = last; j >= i; j--)
    {
        data[j + 1] = data[j];
    }
    data[i] = x;
    last++;
}
int SeqList::Remove(T &x)
{
    int flag = last;
    for (int i = 0; i <= flag; i++)
    {
        if (data[i] == x)
        {
            for (int j = i; j < flag; j++)
            {
                data[j] = data[j + 1];
            }
            last--;
            return i;
        }
    }
    return -1;
}

int main()
{
    SeqList myList(100);
    myList.Input();
    myList.Output();
    int i;
    for (i = 0; i < 5; i++)
        myList.Insert(i + 10, i);
    myList.Output();
    for (i = 10; i < 15; i++)
        myList.Remove(i);
    myList.Output();

    return 0;
}