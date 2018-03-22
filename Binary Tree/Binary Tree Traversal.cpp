#include <iostream>
#include <string>
#include <queue>
using std::cout;
using std::endl;
using std::string;
using std::queue;

template <class T>
class BinaryTree;                // Forward Declaration for using friend class BinaryTree

template <class T>
class TreeNode {
private:
    //TreeNode *leftchild;
    //TreeNode *rightchild;
    //TreeNode *parent;
    //T data;
public:
    TreeNode * leftchild;        // For convenient instantiation, all the variables are public.
    TreeNode *rightchild;
    TreeNode *parent;
    T data;

    TreeNode() :leftchild(0), rightchild(0), parent(0), data(0) {};
    TreeNode(T a) :leftchild(0), rightchild(0), parent(0), data(a) {};

    friend class BinaryTree<T>;
};

template <class T>
class BinaryTree {
public:
    TreeNode<T> *root;                            // root is the beginning of tree.
    BinaryTree() :root(0) {};
    BinaryTree(TreeNode<T> *node) :root(node) {};

    void preOrder(TreeNode<T> *current);
    void inOrder(TreeNode<T> *current);
    void postOrder(TreeNode<T> *current);
    void levelOrder();

    TreeNode<T>* leftmost(TreeNode<T> *current);
    TreeNode<T>* rightmost(TreeNode<T> *current);

    TreeNode<T>* inorderSuccessor(TreeNode<T> *current);
    TreeNode<T>* inorderPredecessor(TreeNode<T> *current);

    void inorderByParent(TreeNode<T> *root);
    void inorderReverse(TreeNode<T> *root);
};

template <class T>
void BinaryTree<T>::preOrder(TreeNode<T> *current)
{
    // recursive call
    if (current)
    {
        cout << current->data << " ";
        preOrder(current->leftchild);
        preOrder(current->rightchild);
    }
}

template <class T>
void BinaryTree<T>::inOrder(TreeNode<T> *current)
{
    // recursive call
    if (current)
    {
        inOrder(current->leftchild);
        cout << current->data << " ";
        inOrder(current->rightchild);
    }
}

template <class T>
void BinaryTree<T>::postOrder(TreeNode<T> *current)
{
    // recursive call
    if (current)
    {		
        postOrder(current->leftchild);
        postOrder(current->rightchild);
        cout << current->data << " ";
    }
}

template <class T>
void BinaryTree<T>::levelOrder()
{
    queue<TreeNode<T>*> myQueue;                   // use Queue for level order traversal
    myQueue.push(this->root);                      // push the root pointer as the initialization

    while (!myQueue.empty())                       // execute until there is no more element in the queue
    {
        TreeNode<T>* current = myQueue.front();    // get the current (visiting) pointer
        myQueue.pop();                             // pop out the pointer once we have gotten the pointer

        cout << current->data << " ";              // visiting operation

        if (current->leftchild)                    // push the leftchild's pointer
            myQueue.push(current->leftchild);

        if (current->rightchild)                   // push the rightchild's pointer
            myQueue.push(current->rightchild);
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
void BinaryTree<T>::inorderByParent(TreeNode<T> *root)
{
    TreeNode<T>* current = leftmost(root);
    
    while (current)
    {
        cout << current->data << " ";              // visiting
        current = inorderSuccessor(current);       // find the inorder successor
    }
}

template <class T>
void BinaryTree<T>::inorderReverse(TreeNode<T> *root)
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
    // TreeNode instantiation
    TreeNode<string> *nodeA = new TreeNode<string>("A"); TreeNode<string> *nodeB = new TreeNode<string>("B");
    TreeNode<string> *nodeC = new TreeNode<string>("C"); TreeNode<string> *nodeD = new TreeNode<string>("D");
    TreeNode<string> *nodeE = new TreeNode<string>("E"); TreeNode<string> *nodeF = new TreeNode<string>("F");
    TreeNode<string> *nodeG = new TreeNode<string>("G"); TreeNode<string> *nodeH = new TreeNode<string>("H");
    TreeNode<string> *nodeI = new TreeNode<string>("I");

    // construct the Binary Tree
    nodeA->leftchild = nodeB; nodeA->rightchild = nodeC;
    nodeB->leftchild = nodeD; nodeB->rightchild = nodeE;
    nodeE->leftchild = nodeG; nodeE->rightchild = nodeH;
    nodeC->leftchild = nodeF; nodeF->rightchild = nodeI;

    // link parent pointer
    nodeB->parent = nodeA; nodeC->parent = nodeA;
    nodeD->parent = nodeB; nodeE->parent = nodeB;
    nodeG->parent = nodeE; nodeH->parent = nodeE;
    nodeF->parent = nodeC;
    nodeI->parent = nodeF;

    BinaryTree<string> myTree(nodeA);

    
    cout << "PreOrder Traversal: " << endl;
    myTree.preOrder(myTree.root);
    cout << endl << endl;

    cout << "InOrder Traversal: " << endl;
    myTree.inOrder(myTree.root);
    cout << endl << endl;

    cout << "PostOrder Traversal: " << endl;
    myTree.postOrder(myTree.root);
    cout << endl << endl;

    cout << "LevelOrder Traversal: " << endl;
    myTree.levelOrder();
    cout << endl << endl;

    TreeNode<string> *ptr = myTree.leftmost(myTree.root);
    cout << "content of leftmost: " << ptr->data << endl;
    ptr = myTree.rightmost(myTree.root);
    cout << "content of rightmost: " << ptr->data << endl;
    cout << endl;

    cout << "InOrder Traversal by using inorderSuccessor: " << endl;
    myTree.inorderByParent(myTree.root);
    cout << endl;

    cout << "InOrder Reverse Traversal by using inorderReverse: " << endl;
    myTree.inorderReverse(myTree.root);
    cout << endl;

    std::cin.get();
    return 0;
}