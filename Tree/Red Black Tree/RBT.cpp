#include <iostream>
#include <string>
#include <sstream>
#include <queue>
using std::cout;
using std::endl;
using std::string;
using std::queue;
using std::stringstream;

class TreeNode {
private:
    TreeNode *leftchild;
    TreeNode *rightchild;
    TreeNode *parent;
    int key;
    bool color;           // 0: Red, 1: Black
    string data;
public:
    TreeNode() :leftchild(nullptr), rightchild(nullptr), parent(nullptr), key(0), color(0), data("") {};
    TreeNode(int key, string str = "") :leftchild(nullptr), rightchild(nullptr), parent(nullptr), key(key), color(0), data(str) {};

    int getKey() { return key; }
    string getData() { return data; }

    friend class RBT;
};

class RBT {
private:
    TreeNode *root;
    TreeNode *neel;       // namely nil, and also called sentinel

    void leftRotation(TreeNode *current);
    void rightRotation(TreeNode *current);
    void insertFixedUpRBT(TreeNode *current);
    void deleteFixedUpRBT(TreeNode *current);
    TreeNode* successor(TreeNode *current);       // called by DeleteRBT()
    TreeNode* leftmost(TreeNode *current);        // called by Successor()
public:
    RBT() {
        neel = new TreeNode();   // default color of RBT node is red
        neel->color = 1;         // we reset nil's color to black
        root = neel;             // There is only nil node in the empty RBT
        root->parent = neel;     // root's parent is nil.
    };
    RBT(string &key_str, string &data_str, string &color_str);
    void levelorderConstruct(stringstream &key_ss, stringstream &data_ss, stringstream &color_ss);
    void levelOrder();

    void insertRBT(int key, string str);
    void deleteRBT(int key);

    TreeNode* search(int key);   // called by DeleteRBT()
};

/*
[NOTE] you should follow the rules of RBT when using this constructor to create RBT
*/
RBT::RBT(string &key_str, string &data_str, string &color_str) {
    stringstream  key_ss, data_ss, color_ss;
    key_ss << key_str;
    data_ss << data_str;
    color_ss << color_str;

    // initialize nil node
    neel = new TreeNode();
    neel->color = 1;
    root = neel;
    root->parent = neel;

    // insert root
    root = new TreeNode();
    root->parent = neel;
    key_ss >> root->key;
    data_ss >> root->data;
    color_ss >> root->color;            // note that root should be black

    levelorderConstruct(key_ss, data_ss, color_ss);
}

void RBT::levelorderConstruct(stringstream &key_ss, stringstream &data_ss, stringstream &color_ss)
{
    queue<TreeNode*> q;                 // create a queue to handle level-roder rule
    TreeNode *current = root;           // point *current to root
    int key = -1;                       // initializa key as '-1'
    bool color = 0;                     // initializa color as '0'
    string data = "";                   // initializa data as ""

    while (key_ss >> key && data_ss >> data && color_ss >> color)
    {
        if (key >= 0)                                  // process current->leftchild
        {
            TreeNode *new_node = new TreeNode(key, data);
            new_node->color = color;
            new_node->parent = current;
            new_node->leftchild = neel;
            new_node->rightchild = neel;

            current->leftchild = new_node;
            q.push(new_node);
        }

        if (!(key_ss >> key && data_ss >> data && color_ss >> color))
            break;                                     // if the input data is odd, end the loop here

        if (key >= 0)                                  // process current->rightchild
        {
            TreeNode *new_node = new TreeNode(key, data);
            new_node->color = color;
            new_node->parent = current;
            new_node->leftchild = neel;
            new_node->rightchild = neel;
            
            current->rightchild = new_node;
            q.push(new_node);
        }
        current = q.front();                           // update current pointer from queue
        q.pop();                                       // queue pop
    }
}

void RBT::levelOrder()
{
    queue<TreeNode*> myQueue;                      // use Queue for level order traversal
    myQueue.push(this->root);                      // push the root pointer as the initialization

    while (!myQueue.empty())                       // execute until there is no more element in the queue
    {
        TreeNode* current = myQueue.front();       // get the current (visiting) pointer
        myQueue.pop();                             // pop out the pointer once we have gotten the pointer

        cout << current->key << " ";               // visiting operation

        if (current->leftchild != neel)            // push the leftchild's pointer
            myQueue.push(current->leftchild);

        if (current->rightchild != neel)           // push the rightchild's pointer
            myQueue.push(current->rightchild);
    }
}

void RBT::leftRotation(TreeNode *x)
{
    TreeNode *y = x->rightchild;

    x->rightchild = y->leftchild;

    if (y->leftchild != neel)             // skip if node is nil, because nil got no parent
        y->leftchild->parent = x;

    y->parent = x->parent;
    
    if (x->parent == neel)                // case0: (x == root)
        root = y;
    else if (x == x->parent->leftchild)   // case1: (x == x->parent->leftchild)
        x->parent->leftchild = y;
    else                                  // case2: (x == x->parent->rightchild)
        x->parent->rightchild = y;

    y->leftchild = x;
    x->parent = y;
}

void RBT::rightRotation(TreeNode *x)
{
    TreeNode *y = x->leftchild;

    x->leftchild = y->rightchild;

    if (y->rightchild != neel)            // skip if node is nil, because nil got no parent
        y->rightchild->parent = x;

    y->parent = x->parent;

    if (x->parent == neel)                // case0: (x == root)
        root = y;
    else if (x == x->parent->leftchild)   // case1: (x == x->parent->leftchild)
        x->parent->leftchild = y;
    else                                  // case2: (x == x->parent->rightchild)
        x->parent->rightchild = y;

    y->rightchild = x;
    x->parent = y;
}

void RBT::insertFixedUpRBT(TreeNode *current)
{
    // case0: parent是黑色, 就不用進回圈
    while (current->parent->color == 0) {   // 若parent是紅色即進入迴圈

                                            // 上半部：parent是grandparent的left child
        if (current->parent == current->parent->parent->leftchild) {
            TreeNode *uncle = current->parent->parent->rightchild;
            // case1: 若uncle是紅色
            if (uncle->color == 0) {
                current->parent->color = 1;
                uncle->color = 1;
                current->parent->parent->color = 0;              //grandparent改成紅色
                current = current->parent->parent;
            }
            // case2 & 3: uncle是黑色
            else {
                if (current == current->parent->rightchild) {     // case2
                    current = current->parent;
                    leftRotation(current);
                }
                // case3
                current->parent->color = 1;                      //把parent塗黑
                current->parent->parent->color = 0;              // grandparent塗紅
                rightRotation(current->parent->parent);
            }
        }
        // 下半部：parent是grandparent的right child, 與上半部對稱
        else {
            TreeNode *uncle = current->parent->parent->leftchild;
            // case1: 若uncle是紅色
            if (uncle->color == 0) {
                current->parent->color = 1;
                uncle->color = 1;
                current->parent->parent->color = 0;              //grandparent改成紅色
                current = current->parent->parent;
            }
            // case2 & 3: uncle是黑色
            else {
                if (current == current->parent->leftchild) {     // case2
                    current = current->parent;
                    rightRotation(current);
                }
                // case3
                current->parent->color = 1;
                current->parent->parent->color = 0;
                leftRotation(current->parent->parent);
            }
        }
    }
    root->color = 1;    // 確保root是黑色
}

void RBT::deleteFixedUpRBT(TreeNode *current)
{
    // Case0:(i)  current是紅色的, 直接把它塗黑
    //       (ii) current是root, 直接把它塗黑
    while (current != root && current->color == 1) {
        // current是leftchild
        if (current == current->parent->leftchild) {
            TreeNode *sibling = current->parent->rightchild;
            // Case1: 如果sibling是紅色
            if (sibling->color == 0) {
                sibling->color = 1;
                current->parent->color = 0;
                leftRotation(current->parent);
                sibling = current->parent->rightchild;
            }
            // 進入 Case2、3、4: sibling是黑色
            // Case2: sibling的兩個child都是黑色
            if (sibling->leftchild->color == 1 && sibling->rightchild->color == 1) {
                sibling->color = 0;
                current = current->parent;           // 若current更新到root, 即跳出迴圈
            }
            // Case3 & 4: current只有其中一個child是黑色
            else {
                // case3: sibling的right child是黑的, left child是紅色
                if (sibling->rightchild->color == 1) {
                    sibling->leftchild->color = 1;
                    sibling->color = 0;
                    rightRotation(sibling);
                    sibling = current->parent->rightchild;
                }
                // 經過Case3後, 一定會變成Case4
                // Case 4: sibling的right child 是紅色的, left child是黑色
                sibling->color = current->parent->color;
                current->parent->color = 1;
                sibling->rightchild->color = 1;
                leftRotation(current->parent);
                current = root;     // 將current移動到root, 一定跳出迴圈
            }
        }
        // current是rightchild
        else {
            TreeNode *sibling = current->parent->leftchild;
            // Case1: 如果sibling是紅色
            if (sibling->color == 0) {
                sibling->color = 1;
                current->parent->color = 0;
                rightRotation(current->parent);
                sibling = current->parent->leftchild;
            }
            // 進入 Case2、3、4: sibling是黑色
            // Case2: sibling的兩個child都是黑色
            if (sibling->leftchild->color == 1 && sibling->rightchild->color == 1) {
                sibling->color = 0;
                current = current->parent;             // 若current更新到root, 即跳出迴圈
            }
            // Case3 & 4: current只有其中一個child是黑色
            else {
                // case3: sibling的left child是黑的, right child是紅色
                if (sibling->leftchild->color == 1) {
                    sibling->rightchild->color = 1;
                    sibling->color = 0;
                    leftRotation(sibling);
                    sibling = current->parent->leftchild;
                }
                // 經過Case3後, 一定會變成Case4
                // Case 4: sibling的left child 是紅色的, rightt child是黑色
                sibling->color = current->parent->color;
                current->parent->color = 1;
                sibling->leftchild->color = 1;
                rightRotation(current->parent);
                current = root;     // 將current移動到root, 一定跳出迴圈
            }
        }
    }
    current->color = 1;
}

TreeNode* RBT::successor(TreeNode *current)
{
    if (current->rightchild != nullptr)
        return leftmost(current->rightchild);

    TreeNode* successor = current->parent;
    while (successor != nullptr && successor->leftchild != current) {
        successor = successor->parent;
        current = current->parent;
    }
    return successor;
}

TreeNode* RBT::leftmost(TreeNode *current)
{
    while (current->leftchild != nullptr)
        current = current->leftchild;

    return current;
}

void RBT::insertRBT(int key, string str)
{
    TreeNode* parent = neel;     // BST: nullptr, RBT: nil
    TreeNode* ptr = this->root;
    TreeNode* new_node = new TreeNode(key, str);

    // search the parent of the inserted node
    while (ptr != neel) {        // use nil as condition in RBT
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

    // Additional operations for RBT
    new_node->leftchild = neel;
    new_node->rightchild = neel;

    // Fix case: Red to Red
    insertFixedUpRBT(new_node);
}

void RBT::deleteRBT(int key)
{
    TreeNode *delete_node = search(key);
    if (delete_node == nullptr) {
        cout << "key(" << key << ") isn't in the BST." << endl;
        return;
    }

    TreeNode *del_real = nullptr;
    TreeNode *del_real_child = nullptr;

    // tranform all cases into ONE-CHILD case
    if (delete_node->leftchild == neel || delete_node->rightchild == neel)  // replace NULL with nil
        del_real = delete_node;
    else
        del_real = successor(delete_node);

    // assign the del_real_child - data or neel node
    if (del_real->leftchild != neel)
        del_real_child = del_real->leftchild;
    else
        del_real_child = del_real->rightchild;

    // even if del_real_child is neel, del_real_child->parent should point to effective address
    // because del_real_child->parent is used to judge if x is leftchild or rightchild in FixUp step.
    del_real_child->parent = del_real->parent;

    if (del_real->parent == neel)                        // case0: delete root
        this->root = del_real_child;
    else if (del_real == del_real->parent->leftchild)    // case1: delete leftchild
        del_real->parent->leftchild = del_real_child;
    else                                                 // case2: delete rightchild
        del_real->parent->rightchild = del_real_child;

    if (del_real != delete_node) {                       // case3: two child situation
        delete_node->key = del_real->key;
        delete_node->data = del_real->data;
    }

    // if the del_real node is black, use FixUp at del_real_child.
    if (del_real->color == 1)
        deleteFixedUpRBT(del_real_child);

    delete del_real;
    del_real = nullptr;
}

TreeNode* RBT::search(int key)
{
    TreeNode* current = root;

    while (current != nullptr && key != current->key) {
        if (key > current->key)
            current = current->rightchild;
        else
            current = current->leftchild;
    }

    return current;
}

int main()
{
    // Test_Case_01:
    string key_str = "50 30 70 20 35 -1 -1 -1 -1 34 -1";
    string data_str = "A B C D E x x x x J x";
    //string color_str = "1 0 1 1 1 -1 -1 -1 -1 0 -1";
    string color_str = "1 0 1 1 1 0 0 0 0 0 0";
    RBT mytree(key_str, data_str, color_str);
    mytree.levelOrder();

    cout << endl;

    mytree.insertRBT(31, "Z");
    mytree.levelOrder();

    std::cin.get();
    return 0;
}