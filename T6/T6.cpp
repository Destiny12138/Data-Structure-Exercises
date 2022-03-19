#include <iostream>
using namespace std;
typedef char DataType;
class BinaryTree;
class BinTreeNode
{ //结点类的定义
    friend BinaryTree;

public:
    BinTreeNode()
    {
        leftChild = NULL;
        rightChild = NULL;
    }
    BinTreeNode(DataType x, BinTreeNode *left = NULL, BinTreeNode *right = NULL) : data(x), leftChild(left), rightChild(right) {} //构造函数
    ~BinTreeNode() {}                                                                                                             //析构函数
private:
    BinTreeNode *leftChild, *rightChild; //左、右子女链域
    DataType data;                       //数据域
};
class BinaryTree
{
public:
    BinaryTree() : root(NULL) {}
    BinaryTree(DataType value)
    {
        EndTag = value;
        root = NULL;
    }
    void CreateBinTree() { CreateBinTree(root); }
    bool IsEmpty() { return (root == NULL) ? true : false; }
    BinTreeNode *GetRoot() const { return root; }
    void inOrder() { inOrder(root); } //中序遍历
    int priority(char op1, char op2);
    int calculate() { return calculate(root); }

private:
    int leafcount = 0;
    int charcount = 0;
    BinTreeNode *root; //二叉树的根指针
    DataType EndTag;   //数据输入停止标志
    void CreateBinTree(BinTreeNode *&subTree);
    void inOrder(BinTreeNode *subTree); //中序遍历
    int calculate(BinTreeNode *subTree);
};
void BinaryTree ::CreateBinTree(BinTreeNode *&subTree)
{
    //私有函数: 建立根为subTree的子树
    char item;
    cin >> item;
    if (item != EndTag)
    {

        subTree = new BinTreeNode(item);

        CreateBinTree(subTree->leftChild);

        CreateBinTree(subTree->rightChild);
    }
    else
        subTree = NULL;
};

void BinaryTree::inOrder(BinTreeNode *subTree)
{
    //私有函数，中序遍历以subTree为根的二叉树
    if (subTree != NULL)
    {
        if (subTree->rightChild != NULL && priority(subTree->data, subTree->rightChild->data))
        {
            inOrder(subTree->leftChild);
            cout << subTree->data;
            cout << '(';
            inOrder(subTree->rightChild);
            cout << ')';
        }
        else
        {
            inOrder(subTree->leftChild);
            cout << subTree->data;
            inOrder(subTree->rightChild);
        }
    }
}
int BinaryTree::priority(char op1, char op2)
{
    if ((op1 == '*' || op1 == '/') && (op2 == '+' || op2 == '-'))
        return 1;
    else
        return 0;
}
int BinaryTree::calculate(BinTreeNode *subTree)
{
    if (subTree != NULL)
    {
        switch (subTree->data)
        {
        case '+':
            return calculate(subTree->leftChild) + calculate(subTree->rightChild);
            break;
        case '-':
            return calculate(subTree->leftChild) - calculate(subTree->rightChild);
            break;
        case '*':
            return calculate(subTree->leftChild) * calculate(subTree->rightChild);
            break;
        case '/':
            return calculate(subTree->leftChild) / calculate(subTree->rightChild);
            break;
        default:
            return int(subTree->data - '0');
            break;
        }
    }
    else
        return 0;
}
int main()
{
    BinaryTree a = BinaryTree('@');
    a.CreateBinTree();
    a.inOrder();
    cout << '=' << a.calculate();
}