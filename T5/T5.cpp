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

    void CreateBinTree()
    {
        CreateBinTree(root);
        cout << "Created success!" << endl;
    }
    bool IsEmpty() { return (root == NULL) ? true : false; }

    int Height() { return Height(root); }
    int Size() { return Size(root); }
    BinTreeNode *GetRoot() const { return root; }
    void preOrder()
    {
        cout << "Preorder is:";
        preOrder(root);
        cout << '.' << endl;
    } //前序遍历
    void inOrder()
    {
        cout << "Inorder is:";
        inOrder(root);
        cout << '.' << endl;
    } //中序遍历
    void postOrder()
    {
        cout << "Postorder is:";
        postOrder(root);
        cout << '.' << endl;
    } //后序遍历
    int Leaf()
    {
        Leaf(root);
        return leafcount;
    }
    int Find(char value)
    {
        Find(root, value);
        return charcount;
    }
    void Index_print() { Index_print(root, 1); }

private:
    int leafcount = 0;
    int charcount = 0;
    BinTreeNode *root; //二叉树的根指针
    DataType EndTag;   //数据输入停止标志
    void CreateBinTree(BinTreeNode *&subTree);
    int Height(BinTreeNode *subTree);
    int Size(BinTreeNode *subTree);
    void preOrder(BinTreeNode *subTree);  //前序遍历
    void inOrder(BinTreeNode *subTree);   //中序遍历
    void postOrder(BinTreeNode *subTree); //后序遍历
    void Leaf(BinTreeNode *subTree);
    void Find(BinTreeNode *subTree, char value);
    void Index_print(BinTreeNode *subTree, int l);
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
void BinaryTree::preOrder(BinTreeNode *subTree)
{
    //私有函数，前序遍历以subTree为根的二叉树
    if (subTree != NULL)
    {
        cout << subTree->data << ' ';
        preOrder(subTree->leftChild);
        preOrder(subTree->rightChild);
    }
}
void BinaryTree::inOrder(BinTreeNode *subTree)
{
    //私有函数，中序遍历以subTree为根的二叉树
    if (subTree != NULL)
    {
        inOrder(subTree->leftChild);
        cout << subTree->data << ' ';
        inOrder(subTree->rightChild);
    }
}
void BinaryTree::postOrder(BinTreeNode *subTree)
{
    //私有函数，后序遍历以subTree为根的二叉树
    if (subTree != NULL)
    {
        postOrder(subTree->leftChild);
        postOrder(subTree->rightChild);
        cout << subTree->data << ' ';
    }
}
int BinaryTree::Size(BinTreeNode *subTree)
{
    //私有函数，计算以subTree为根的二叉树结点个数，后序遍历的应用
    if (subTree == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + Size(subTree->leftChild) + Size(subTree->rightChild);
    }
}
int BinaryTree::Height(BinTreeNode *subTree)
{
    //私有函数，计算以subTree为根的二叉树高度，后序遍历的应用
    if (subTree == NULL)
    {
        return 0;
    }
    else
    {
        int i = Height(subTree->leftChild);
        int j = Height(subTree->rightChild);
        return (i < j) ? j + 1 : i + 1;
    }
}
void BinaryTree::Leaf(BinTreeNode *subTree)
{
    if (subTree != NULL)
    {

        if ((subTree->leftChild == NULL) && (subTree->rightChild == NULL))
        {
            ++leafcount;
        }
        else
        {
            Leaf(subTree->leftChild);
            Leaf(subTree->rightChild);
        }
    }
}
void BinaryTree::Find(BinTreeNode *subTree, char value)
{
    if (subTree != NULL)
    {
        Find(subTree->leftChild, value);
        Find(subTree->rightChild, value);
        if (subTree->data == value)
        {
            charcount++;
        }
    }
}
void BinaryTree::Index_print(BinTreeNode *subTree, int l)
{
    if (subTree == NULL)
        return;
    else
    {
        for (int i = 0; i < l - 1; i++)
            cout << "  ";
        cout << subTree->data << endl;
        Index_print(subTree->leftChild, l + 1);
        Index_print(subTree->rightChild, l + 1);
    }
}
int main()
{
    BinaryTree a = BinaryTree('#');
    char flag;
    cin >> flag;
    while (flag != 'X')
    {
        switch (flag)
        {
        case 'C':
            a.CreateBinTree();
            cin >> flag;
            break;
        case 'H':
            cout << "Height=" << a.Height() << '.' << endl;
            cin >> flag;
            break;
        case 'L':
            cout << "Leaf=" << a.Leaf() << '.' << endl;
            cin >> flag;
            break;
        case 'N':
            cout << "Nodes=" << a.Size() << '.' << endl;
            cin >> flag;
            break;
        case '1':
            a.preOrder();
            cin >> flag;
            break;
        case '2':
            a.inOrder();
            cin >> flag;
            break;
        case '3':
            a.postOrder();
            cin >> flag;
            break;
        case 'F':
            char value;
            cin >> value;
            cout << "The count of " << value << " is " << a.Find(value) << '.' << endl;
            cin >> flag;
            break;
        case 'P':
            cout << "The tree is:" << endl;
            a.Index_print();
            flag = 'X';
            break;
        default:
            flag = 'X';
            break;
        }
    }
}