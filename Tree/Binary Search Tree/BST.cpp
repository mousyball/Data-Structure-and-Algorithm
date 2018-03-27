#include <iostream>
#include <string>
#include <queue>
using std::cout;
using std::endl;
using std::string;
using std::queue;

class TreeNode {
private:
    TreeNode *leftchild;
    TreeNode *rightchild;
    TreeNode *parent;
    int key;
    string data;
public:
    TreeNode() :leftchild(nullptr), rightchild(nullptr), parent(nullptr), key(0), data("") {};
    TreeNode(int a, string b) :leftchild(nullptr), rightchild(nullptr), parent(nullptr), key(a), data(b) {};

    int getKey() { return key; }
    string getData() { return data; }

    friend class BST;
};

class BST {
private:
    TreeNode *root;
    TreeNode* leftmost(TreeNode *current);
    TreeNode* successor(TreeNode *current);
public:
    BST() :root(nullptr) {};

    TreeNode* search(int key);
    void insertBST(int key, string in_data);
    void inorderPrint();
    void levelorder();
    void deleteBST(int KEY);
};

TreeNode* BST::leftmost(TreeNode *current)
{
    while (current->leftchild != nullptr)
        current = current->leftchild;

    return current;
}

TreeNode* BST::successor(TreeNode *current)
{
    if (current->rightchild != nullptr)
        return leftmost(current->rightchild);

    TreeNode *successor = current->parent;
    while (successor != nullptr && current == successor->rightchild) {
        current = successor;
        successor = current->parent;
    }
    return successor;
}

TreeNode* BST::search(int key)
{
    TreeNode* current = this->root;

    while (current != nullptr && current->key != key) {
        if (key > current->key)
            current = current->rightchild;
        else if (key < current->key)
            current = current->leftchild;
    }

    //if (current == nullptr)
    //    cout << "Failed to search key(" << key << ")" << endl;

    return current;
}

void BST::insertBST(int key, string in_data)
{
    TreeNode* parent = nullptr;
    TreeNode* ptr = this->root;
    TreeNode* new_node = new TreeNode(key, in_data);

    // search the parent of the inserted node
    while (ptr != nullptr) {
        parent = ptr;
        
        if (key > ptr->key)
            ptr = ptr->rightchild;
        else
            ptr = ptr->leftchild;
    }

    // insert the new_node
    new_node->parent = parent;

    if (parent == nullptr)
        this->root = new_node;
    else if (new_node->key < parent->key)
        parent->leftchild = new_node;
    else
        parent->rightchild = new_node;
}

void BST::inorderPrint()
{
    TreeNode* ptr = leftmost(this->root);

    while (ptr != nullptr) {
        cout << ptr->data << "(" << ptr->key << ") ";
        ptr = successor(ptr);
    }
}

void BST::levelorder()
{
    queue<TreeNode*> myQueue;
    myQueue.push(this->root);

    while (!myQueue.empty()) {
        TreeNode *current = myQueue.front();
        myQueue.pop();
        cout << current->data << "(" << current->key << ") ";
        
        if (current->leftchild != nullptr)
            myQueue.push(current->leftchild);

        if (current->rightchild != nullptr)
            myQueue.push(current->rightchild);
    }
}

void BST::deleteBST(int key)
{
    TreeNode *delete_node = search(key);
    if (delete_node == nullptr) {
        cout << "key(" << key << ") isn't in the BST."<< endl;
        return;
    }

    TreeNode *del_real = nullptr;
    TreeNode *del_real_child = nullptr;

    // tranform all cases into ONE-CHILD case
    if (delete_node->leftchild == NULL || delete_node->rightchild == NULL)
        del_real = delete_node;
    else
        del_real = successor(delete_node);

    // assign the del_real_child
    if (del_real->leftchild != nullptr)
        del_real_child = del_real->leftchild;
    else
        del_real_child = del_real->rightchild;

    // link del_real_child->parent to del_real->parent
    if (del_real_child != nullptr)
        del_real_child->parent = del_real->parent;
        
    if (del_real->parent == nullptr)                     // case0: delete root
        this->root = del_real_child;
    else if (del_real == del_real->parent->leftchild)    // case1: delete leftchild
        del_real->parent->leftchild = del_real_child;
    else                                                 // case2: delete rightchild
        del_real->parent->rightchild = del_real_child;

    if (del_real != delete_node) {                       // case3: two child situation
        delete_node->key = del_real->key;
        delete_node->data = del_real->data;
    }

    delete del_real;
    del_real = nullptr;
}


int main()
{
    BST myBST;

    myBST.insertBST(8, "龜仙人");
    myBST.insertBST(1000, "悟空");
    myBST.insertBST(2, "克林");
    myBST.insertBST(513, "比克");

    cout << "Inorder Traversal:\n";
    myBST.inorderPrint();
    cout << endl << endl;

    cout << "Level-order Traversal:\n";
    myBST.levelorder();
    cout << endl << endl;

    myBST.deleteBST(8);

    cout << "Level-order Traversal:\n";
    myBST.levelorder();
    cout << endl << endl;

    TreeNode *node = myBST.search(1000);
    if (node != NULL)
        cout << "There is " << node->getData() << "(" << node->getKey() << ")" << endl;
    else
        cout << "no data with Key(1000)" << endl;

    node = myBST.search(8);
    if (node != NULL)
        cout << "There is " << node->getData() << "(" << node->getKey() << ")" << endl;
    else
        cout << "no data with Key(8)" << endl;

    std::cin.get();
    return 0;
}