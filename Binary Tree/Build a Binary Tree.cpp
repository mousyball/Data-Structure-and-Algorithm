#include <iostream>
#include <sstream>
#include <string>
#include <queue>
using std::cout;
using std::endl;
using std::string;
using std::queue;
using std::stringstream;

template <class T>
class BinaryTree;                // Forward Declaration for using friend class BinaryTree

template <class T>
class TreeNode {
private:
    TreeNode *leftchild;
    TreeNode *rightchild;
    TreeNode *parent;
    T data;
public:
    TreeNode() :leftchild(0), rightchild(0), parent(0), data(0) {};
    TreeNode(T a) :leftchild(0), rightchild(0), parent(0), data(a) {};

    friend class BinaryTree<T>;
};

template <class T>
class BinaryTree {
public:
    TreeNode<T> *root;
    BinaryTree() :root(0) {};
    BinaryTree(T *str);
    //BinaryTree(TreeNode<T> *node);

    void levelorderConstruct(stringstream &ss);
    void insertLevelorder(T data);

    TreeNode<T>* leftmost(TreeNode<T> *current);
    TreeNode<T>* rightmost(TreeNode<T> *current);
    TreeNode<T>* inorderSuccessor(TreeNode<T> *current);
    TreeNode<T>* inorderPredecessor(TreeNode<T> *current);
    void inorderByParent();
    void inorderReverse();
};

template <class T>
BinaryTree<T>::BinaryTree(T *str) {
    stringstream  ss;
    ss << str;                     // magic!

    root = new TreeNode<T>;        // allocate memory for root
    ss >> root->data;              // assign character to root

    levelorderConstruct(ss);
}

template <class T>
void BinaryTree<T>::levelorderConstruct(stringstream &ss)
{
    queue<TreeNode<T>*> q;              // create a queue to handle level-roder rule
    TreeNode<T> *current = root;        // point *current to root
    char data = 'x';                    // initializa data as 'x'

    while (ss >> data)
    {
        if (data >= 65 && data <= 90)                  // process current->leftchild
        {                
            TreeNode<T> *new_node = new TreeNode<T>(data);
            new_node->parent = current;
            current->leftchild = new_node;
            q.push(new_node);
        }

        if (!(ss >> data))                             // if the input data is odd
            break;                                     // end the loop here

        if (data >= 65 && data <= 90)                  // process current->rightchild
        {
            TreeNode<T> *new_node = new TreeNode<T>;
            new_node->parent = current;
            current->rightchild = new_node;
            new_node->data = data;
            q.push(new_node);
        }
        current = q.front();                           // update current pointer from queue
        q.pop();                                       // queue pop
    }
}

template <class T>
void BinaryTree<T>::insertLevelorder(T data) {

    queue<TreeNode<T>*> q;
    TreeNode<T> *current = root;

    while (current) {
        if (current->leftchild != nullptr) {                  // current->leftchild is not NULL
            q.push(current->leftchild);                       // push into queue
        }
        else {                                                // current->leftchild is EMPTY
            TreeNode<T> *new_node = new TreeNode<T>(data);    // insert a new node
            new_node->parent = current;
            current->leftchild = new_node;
            break;
        }
        if (current->rightchild != nullptr) {                 // current->rightchild is not NULL
            q.push(current->rightchild);                      // push into queue
        }
        else {                                                // current->rightchild is EMPTY
            TreeNode<T> *new_node = new TreeNode<T>(data);    // insert a new node
            new_node->parent = current;
            current->rightchild = new_node;
            break;
        }
        current = q.front();
        q.pop();
    }
}

template <class T>
TreeNode<T>* BinaryTree<T>::leftmost(TreeNode<T> *current)
{
    while (current->leftchild != nullptr)
        current = current->leftchild;

    return current;
}

template <class T>
TreeNode<T>* BinaryTree<T>::rightmost(TreeNode<T> *current)
{
    while (current->rightchild != nullptr)
        current = current->rightchild;

    return current;
}

template <class T>
TreeNode<T>* BinaryTree<T>::inorderSuccessor(TreeNode<T> *current)
{
    if (current->rightchild != nullptr)
        return leftmost(current->rightchild);

    TreeNode<T> *successor = current->parent;
    // find the rightchild as leftchild, and successor(root) eqaul to NULL is the termination condition
    while (successor != nullptr && successor->rightchild == current)
    {
        current = successor;
        successor = successor->parent;
    }
    return successor;

}

template <class T>
TreeNode<T>* BinaryTree<T>::inorderPredecessor(TreeNode<T> *current)
{
    if (current->leftchild != nullptr)
        return rightmost(current->leftchild);

    TreeNode<T> *predecessor = current->parent;
    // find the rightchild as leftchild, and successor(root) eqaul to NULL is the termination condition
    while (predecessor != nullptr && predecessor->leftchild == current)
    {
        current = predecessor;
        predecessor = predecessor->parent;
    }
    return predecessor;
}

template <class T>
void BinaryTree<T>::inorderByParent()
{
    TreeNode<T>* current = leftmost(root);

    while (current)
    {
        cout << current->data << " ";              // visiting
        current = inorderSuccessor(current);       // find the inorder successor
    }
}

template <class T>
void BinaryTree<T>::inorderReverse()
{
    TreeNode<T>* current = rightmost(root);

    while (current)
    {
        cout << current->data << " ";              // visiting
        current = inorderPredecessor(current);     // find the inorder predecessor
    }
}

int main()
{
    char a[] = "A B C D E F x x x G H x I";
    BinaryTree<char> myTree(a);                   // build a binary tree by level-order
    myTree.inorderByParent();                     // print binary tree using inorder-traversal
    cout << endl;
    
    myTree.insertLevelorder('K');
    myTree.insertLevelorder('L');
    myTree.insertLevelorder('M');
    myTree.insertLevelorder('N');
    myTree.inorderByParent();
    cout << endl;

    std::cin.get();
    return 0;
}