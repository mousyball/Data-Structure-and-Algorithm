#include "Source.hpp"

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
    neel->color = BLACK;
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
    int key = -1;                       // initialize key as '-1'
    short color = -1;                   // initialize color as '-1'
    string data = "";                   // initialize data as ""

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

vector<TreeNode*> RBT::levelOrder_vec()
{
    queue<TreeNode*> myQueue;                      // use Queue for level order traversal
    myQueue.push(this->root);                      // push the root pointer as the initialization
    vector<TreeNode*> level_order_vec;             // for Unit Test

    while (!myQueue.empty())                       // execute until there is no more element in the queue
    {
        TreeNode* current = myQueue.front();       // get the current (visiting) pointer
        myQueue.pop();                             // pop out the pointer once we have gotten the pointer

        level_order_vec.push_back(current);        // visiting operation

        if (current->leftchild != neel)            // push the leftchild's pointer
            myQueue.push(current->leftchild);

        if (current->rightchild != neel)           // push the rightchild's pointer
            myQueue.push(current->rightchild);
    }

    return level_order_vec;
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
    // case0: if parent is BLACK, skip the loop
    while (current->parent->color == RED) {   // if parent is red, do the FixedUp stuff.

                                              // upper hadf�Gparent is grandparent's leftchild
        if (current->parent == current->parent->parent->leftchild) {
            TreeNode *uncle = current->parent->parent->rightchild;
            // case1: if uncle is red
            if (uncle->color == RED) {
                current->parent->color = BLACK;
                uncle->color = BLACK;
                current->parent->parent->color = RED;             // paint grandparent to color RED
                current = current->parent->parent;
            }
            // case2 & 3: uncle is BLACK
            else {
                // case2
                if (current == current->parent->rightchild) {
                    current = current->parent;
                    leftRotation(current);
                }
                // case3
                current->parent->color = BLACK;                   // paint parent to color BLACK
                current->parent->parent->color = RED;             // paint grandparent to color RED
                rightRotation(current->parent->parent);
            }
        }
        // lower half�Gparent is grandparent's rightchild, symmetrical with the upper half
        else {
            TreeNode *uncle = current->parent->parent->leftchild;
            // case1: if uncle is RED
            if (uncle->color == RED) {
                current->parent->color = BLACK;
                uncle->color = BLACK;
                current->parent->parent->color = RED;            // paint grandparent to color RED
                current = current->parent->parent;
            }
            // case2 & 3: uncle�O�¦�
            else {
                // case2
                if (current == current->parent->leftchild) {
                    current = current->parent;
                    rightRotation(current);
                }
                // case3
                current->parent->color = BLACK;
                current->parent->parent->color = RED;
                leftRotation(current->parent->parent);
            }
        }
    }
    root->color = BLACK;    // �T�Oroot�O�¦�
}

void RBT::deleteFixedUpRBT(TreeNode *current)
{
    // Case0:(i)  current is RED, paint it to BLACK
    //       (ii) current is root, paint it to BLACK
    while (current != root && current->color == BLACK) {
        // current is leftchild
        if (current == current->parent->leftchild) {
            TreeNode *sibling = current->parent->rightchild;
            // Case1: if sibling is RED
            if (sibling->color == RED) {
                sibling->color = BLACK;
                current->parent->color = RED;
                leftRotation(current->parent);
                sibling = current->parent->rightchild;
            }
            // Case2, 3, 4: sibling is BLACK
            // Case2: sibling's both children are BLACK
            if (sibling->leftchild->color == BLACK && sibling->rightchild->color == BLACK) {
                sibling->color = RED;
                current = current->parent;           // if current updates to root, then break out the loop
            }
            // Case3 & 4: one of current's child is BLACK
            else {
                // case3: sibling's rightchild is BLACK, leftchild is RED
                if (sibling->rightchild->color == BLACK) {
                    sibling->leftchild->color = BLACK;
                    sibling->color = RED;
                    rightRotation(sibling);
                    sibling = current->parent->rightchild;
                }
                // After Case3, it definitely becomes case4
                // Case4: sibling's rightchild is RED, left child is BLACK
                sibling->color = current->parent->color;
                current->parent->color = BLACK;
                sibling->rightchild->color = BLACK;
                leftRotation(current->parent);
                current = root;     // current==root, break out the loop for sure
            }
        }
        // current is rightchild
        else {
            TreeNode *sibling = current->parent->leftchild;
            // Case1: if sibling is RED
            if (sibling->color == RED) {
                sibling->color = BLACK;
                current->parent->color = RED;
                rightRotation(current->parent);
                sibling = current->parent->leftchild;
            }
            // Case2, 3, 4: sibling is BLACK
            // Case2: sibling's both children are BLACK
            if (sibling->leftchild->color == BLACK && sibling->rightchild->color == BLACK) {
                sibling->color = RED;
                current = current->parent;             // current==root, break out the loop for sure
            }
            // Case3 & 4: current�u���䤤�@��child�O�¦�
            else {
                // case3: sibling's leftchild is BLACK, rightchild is RED
                if (sibling->leftchild->color == BLACK) {
                    sibling->rightchild->color = BLACK;
                    sibling->color = RED;
                    leftRotation(sibling);
                    sibling = current->parent->leftchild;
                }
                // After Case3, it definitely becomes case4
                // Case4: sibling's rightchild is RED, left child is BLACK
                sibling->color = current->parent->color;
                current->parent->color = BLACK;
                sibling->leftchild->color = BLACK;
                rightRotation(current->parent);
                current = root;     // current==root, break out the loop for sure
            }
        }
    }
    current->color = BLACK;
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
    if (del_real->color == BLACK)
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

int RBT_main()
{
    // Test_Case_01:
    string key_str = "50 30 70 20 35 -1 -1 -1 -1 34 -1";
    string data_str = "A B C D E x x x x J x";
    string color_str = "1 0 1 1 1 -1 -1 -1 -1 0 -1";
    RBT mytree(key_str, data_str, color_str);
    mytree.levelOrder();

    cout << endl;

    mytree.insertRBT(31, "Z");
    mytree.levelOrder();

    std::cin.get();
    return 0;
}