#include <gtest/gtest.h>
#include "Source.hpp"

class RBTtest : public testing::Test
{
protected:
    RBT* RBT_tree;
    void SetUp() {
        // Initial status of RBT_tree:
        string key_str = "36 16 41 4 22 39 48 3 9 19 27 -1 -1 45 52 1 -1 7 10 -1 -1 24 -1 -1 -1 51 55";
        string data_str = "L G N C I M P B E H K x x O R A x D F x x J x x x Q S";
        string color_str = "1 0 1 1 1 1 0 1 0 1 1 -1 -1 1 1 0 -1 1 1 -1 -1 0 -1 -1 -1 0 0";
        RBT_tree = new RBT(key_str, data_str, color_str);
    };

    void setNodeColor(TreeNode* node, short color);
};

void RBTtest::setNodeColor(TreeNode* node, short color)
{
    node->color = color;
}

bool operator==(const TreeNode& node01, const TreeNode& node02)
{
    return (node01.color == node02.color) && (node01.data == node02.data);
}

std::ostream& operator<<(std::ostream& os, const TreeNode& node)
{
    os << "(Dict, color)=>(" << node.data << "," << node.color << ")";
    return os;
}

TEST_F(RBTtest, Test_Level_Order_Constructor)
{
    vector<TreeNode*> tested_vec;
    vector<TreeNode*> answer_vec;

    // Tested Pattern: get the tested output from the RBT method
    tested_vec = RBT_tree->levelOrder_vec();

    // Answer Pattern: produce verification pattern - key, data, color
    int key[] = { 36,16,41,4,22,39,48,3,9,19,27,45,52,1,7,10,24,51,55 };
    char data[] = { 'L','G','N','C','I','M','P','B','E','H','K','O','R','A','D','F','J','Q','S' };
    short color[] = { 1,0,1,1,1,1,0,1,0,1,1,1,1,0,1,1,0,0,0 };

    for (int i = 0; i < sizeof(key) / sizeof(*key); i++) {
        string data_str(1, data[i]);
        TreeNode* node = new TreeNode(key[i], data_str);
        setNodeColor(node, color[i]);
        answer_vec.push_back(node);
    }

    // Comparison Procedure
    int cnt = 0;
    vector<TreeNode*>::iterator answer_itr = answer_vec.begin();
    for (vector<TreeNode*>::iterator tested_itr = tested_vec.begin();
        tested_itr != tested_vec.end();
        ++tested_itr, ++answer_itr, ++cnt) {

        ASSERT_EQ(**tested_itr, **answer_itr) << "vec[" << cnt++ << "] is wrong";
    }
}

TEST_F(RBTtest, TEST_Remove_Case_3_to_4)
{
    vector<TreeNode*> tested_vec;
    vector<TreeNode*> answer_vec;

    // Tested Pattern: get the tested output from the RBT method
    RBT_tree->deleteRBT(19);
    tested_vec = RBT_tree->levelOrder_vec();

    // Answer Pattern: produce verification pattern - key, data, color
    int key[] = { 36,16,41,4,24,39,48,3,9,22,27,45,52,1,7,10,51,55 };
    char data[] = { 'L','G','N','C','J','M','P','B','E','I','K','O','R','A','D','F','Q','S' };
    short color[] = { 1,0,1,1,1,1,0,1,0,1,1,1,1,0,1,1,0,0 };

    for (int i = 0; i < sizeof(key) / sizeof(*key); i++) {
        string data_str(1, data[i]);
        TreeNode* node = new TreeNode(key[i], data_str);
        setNodeColor(node, color[i]);
        answer_vec.push_back(node);
    }

    // Comparison Procedure
    int cnt = 0;
    vector<TreeNode*>::iterator answer_itr = answer_vec.begin();
    for (vector<TreeNode*>::iterator tested_itr = tested_vec.begin();
        tested_itr != tested_vec.end();
        ++tested_itr, ++answer_itr, ++cnt) {

        ASSERT_EQ(**tested_itr, **answer_itr) << "vec[" << cnt++ << "] is wrong";
    }
}

TEST_F(RBTtest, TEST_Remove_Case_4)
{
    vector<TreeNode*> tested_vec;
    vector<TreeNode*> answer_vec;

    // Tested Pattern: get the tested output from the RBT method
    RBT_tree->deleteRBT(19);
    RBT_tree->deleteRBT(45);
    tested_vec = RBT_tree->levelOrder_vec();

    // Answer Pattern: produce verification pattern - key, data, color
    int key[] = { 36,16,41,4,24,39,52,3,9,22,27,48,55,1,7,10,51 };
    char data[] = { 'L','G','N','C','J','M','R','B','E','I','K','P','S','A','D','F','Q' };
    short color[] = { 1,0,1,1,1,1,0,1,0,1,1,1,1,0,1,1,0 };

    for (int i = 0; i < sizeof(key) / sizeof(*key); i++) {
        string data_str(1, data[i]);
        TreeNode* node = new TreeNode(key[i], data_str);
        setNodeColor(node, color[i]);
        answer_vec.push_back(node);
    }

    // Comparison Procedure
    int cnt = 0;
    vector<TreeNode*>::iterator answer_itr = answer_vec.begin();
    for (vector<TreeNode*>::iterator tested_itr = tested_vec.begin();
        tested_itr != tested_vec.end();
        ++tested_itr, ++answer_itr, ++cnt) {

        ASSERT_EQ(**tested_itr, **answer_itr) << "vec[" << cnt++ << "] is wrong";
    }
}


TEST_F(RBTtest, TEST_Remove_Case_1_to_4)
{
    vector<TreeNode*> tested_vec;
    vector<TreeNode*> answer_vec;

    // Tested Pattern: get the tested output from the RBT method
    RBT_tree->deleteRBT(19);
    RBT_tree->deleteRBT(45);
    RBT_tree->deleteRBT(39);
    tested_vec = RBT_tree->levelOrder_vec();

    // Answer Pattern: produce verification pattern - key, data, color
    int key[] = { 36,16,52,4,24,48,55,3,9,22,27,41,51,1,7,10 };
    char data[] = { 'L','G','R','C','J','P','S','B','E','I','K','N','Q','A','D','F' };
    short color[] = { 1,0,1,1,1,0,1,1,0,1,1,1,1,0,1,1 };

    for (int i = 0; i < sizeof(key) / sizeof(*key); i++) {
        string data_str(1, data[i]);
        TreeNode* node = new TreeNode(key[i], data_str);
        setNodeColor(node, color[i]);
        answer_vec.push_back(node);
    }

    // Comparison Procedure
    int cnt = 0;
    vector<TreeNode*>::iterator answer_itr = answer_vec.begin();
    for (vector<TreeNode*>::iterator tested_itr = tested_vec.begin();
        tested_itr != tested_vec.end();
        ++tested_itr, ++answer_itr, ++cnt) {

        ASSERT_EQ(**tested_itr, **answer_itr) << "vec[" << cnt++ << "] is wrong";
    }
}


TEST_F(RBTtest, TEST_Remove_Case_2)
{
    vector<TreeNode*> tested_vec;
    vector<TreeNode*> answer_vec;

    // Tested Pattern: get the tested output from the RBT method
    RBT_tree->deleteRBT(19);
    RBT_tree->deleteRBT(45);
    RBT_tree->deleteRBT(39);
    RBT_tree->deleteRBT(7);
    tested_vec = RBT_tree->levelOrder_vec();

    // Answer Pattern: produce verification pattern - key, data, color
    int key[] = { 36,16,52,4,24,48,55,3,9,22,27,41,51,1,10 };
    char data[] = { 'L','G','R','C','J','P','S','B','E','I','K','N','Q','A','F' };
    short color[] = { 1,0,1,1,1,0,1,1,1,1,1,1,1,0,0 };

    for (int i = 0; i < sizeof(key) / sizeof(*key); i++) {
        string data_str(1, data[i]);
        TreeNode* node = new TreeNode(key[i], data_str);
        setNodeColor(node, color[i]);
        answer_vec.push_back(node);
    }

    // Comparison Procedure
    int cnt = 0;
    vector<TreeNode*>::iterator answer_itr = answer_vec.begin();
    for (vector<TreeNode*>::iterator tested_itr = tested_vec.begin();
        tested_itr != tested_vec.end();
        ++tested_itr, ++answer_itr, ++cnt) {

        ASSERT_EQ(**tested_itr, **answer_itr) << "vec[" << cnt++ << "] is wrong";
    }
}

TEST_F(RBTtest, TEST_Remove_Case_0)
{
    vector<TreeNode*> tested_vec;
    vector<TreeNode*> answer_vec;

    // Tested Pattern: get the tested output from the RBT method
    RBT_tree->deleteRBT(19);
    RBT_tree->deleteRBT(45);
    RBT_tree->deleteRBT(39);
    RBT_tree->deleteRBT(7);
    RBT_tree->deleteRBT(3);
    tested_vec = RBT_tree->levelOrder_vec();

    // Answer Pattern: produce verification pattern - key, data, color
    int key[] = { 36,16,52,4,24,48,55,1,9,22,27,41,51,10 };
    char data[] = { 'L','G','R','C','J','P','S','A','E','I','K','N','Q','F' };
    short color[] = { 1,0,1,1,1,0,1,1,1,1,1,1,1,0 };

    for (int i = 0; i < sizeof(key) / sizeof(*key); i++) {
        string data_str(1, data[i]);
        TreeNode* node = new TreeNode(key[i], data_str);
        setNodeColor(node, color[i]);
        answer_vec.push_back(node);
    }

    // Comparison Procedure
    int cnt = 0;
    vector<TreeNode*>::iterator answer_itr = answer_vec.begin();
    for (vector<TreeNode*>::iterator tested_itr = tested_vec.begin();
        tested_itr != tested_vec.end();
        ++tested_itr, ++answer_itr, ++cnt) {

        ASSERT_EQ(**tested_itr, **answer_itr) << "vec[" << cnt++ << "] is wrong";
    }
}