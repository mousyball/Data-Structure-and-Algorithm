#ifndef RBT_HPP
#define RBT_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::queue;
using std::stringstream;
using std::vector;

enum Node_Color {
    RED = 0,
    BLACK = 1
};

class TreeNode {
private:
    TreeNode *leftchild;
    TreeNode *rightchild;
    TreeNode *parent;
    int key;
    short color;           // 0: Red, 1: Black
    string data;
public:
    TreeNode() :leftchild(nullptr), rightchild(nullptr), parent(nullptr), key(0), color(RED), data("") {};
    TreeNode(int key, string str = "") :leftchild(nullptr), rightchild(nullptr), parent(nullptr), key(key), color(RED), data(str) {};

    int getKey() { return key; }
    string getData() { return data; }

    friend class RBT;

    // For Unit Test
    friend class RBTtest;
    friend bool operator==(const TreeNode& node01, const TreeNode& node02);
    friend std::ostream& operator<<(std::ostream& os, const TreeNode& dt);
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

    // For Unit Test
    vector<TreeNode*> levelOrder_vec();
};

#endif // !_RBT_HPP
