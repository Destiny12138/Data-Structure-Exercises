#include <iostream>
using namespace std;
struct Triple
{                             //三元组
    int row, col;             //非零元素行号/列号
    int value;                //非零元素的值
    void operator=(Triple &R) //赋值
    {
        row = R.row;
        col = R.col;
        value = R.value;
    }
};
class SparseMatrix
{
private:
    int Rows, Cols, Terms; //行／列／非零元素数
    Triple *smArray;       //三元组表
public:
    SparseMatrix(int Rw, int Cl, int Tm); //构造函数
    void Transpose(SparseMatrix &b);      //转置
    void FastTranspos(SparseMatrix &B);
};
SparseMatrix::SparseMatrix(int Rw, int Cl, int Tm)
{
    Rows = Rw;
    Cols = Cl;
    Terms = Tm;
    smArray = new Triple[Terms]; //三元组表
    if (smArray == NULL)
    {
        cout << “存储分配失败！” << endl;
        exit(1);
    }
};
void SparseMatrix::Transpose(SparseMatrix &B)
{
    //转置this矩阵，转置结果由B返回
    B.Rows = Cols;
    B.Cols = Rows;
    B.Terms = Terms;
    //转置矩阵的列数,行数和非零元素个数

    if (Terms == 0)
        return;
    int CurrentB = 0; //转置三元组表存放下标
    int i, k;
    for (k = 0; k < Cols; k++) //处理所有列号
        for (i = 0; i < Terms; i++)
            if (smArray[i].col == k)
            {
                B.smArray[CurrentB].row = k;
                B.smArray[CurrentB].col = smArray[i].row;
                B.smArray[CurrentB].value = smArray[i].value;
                CurrentB++;
            }
}
void SparseMatrix::FastTranspos(SparseMatrix &B)
{
    int *rowSize = new int[Cols];  //列元素数数组
    int *rowStart = new int[Cols]; //转置位置数组
    B.Rows = Cols;
    B.Cols = Rows;
    B.Terms = Terms;
    if (Terms > 0)
    {
        int i, j;
        for (i = 0; i < Cols; i++)
            rowSize[i] = 0;
        for (i = 0; i < Terms; i++)
            rowSize[smArray[i].col]++;
        rowStart[0] = 0;
        for (i = 1; i < Cols; i++)
            rowStart[i] = rowStart[i - 1] + rowSize[i - 1];
        for (i = 0; i < Terms; i++)
        {
            j = rowStart[smArray[i].col];
            B.smArray[j].row = smArray[i].col;
            B.smArray[j].col = smArray[i].row;
            B.smArray[j].value = smArray[i].value;
            rowStart[smArray[i].col]++;
        }
    }
    delete[] rowSize;
    delete[] rowStart;
}