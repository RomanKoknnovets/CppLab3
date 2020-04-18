#include <iostream>
#include <cassert>
#include <vector>
#include "BinaryTree.h"
using namespace std;


//struct BinaryTree
//{
//    struct TreeNode
//    {
//    private:
//        int value;
//        TreeNode* left, * right;
//    public:
//        TreeNode() : value(0), left(nullptr), right(nullptr) {}
//        TreeNode(const int value) : value(value), left(nullptr), right(nullptr) {}
//        ~TreeNode()
//        {
//            delete left;
//            delete right;
//        }
//        int getValue() { return value; }
//        void setValue(const int value) { this->value = value; }
//        TreeNode* getLeft() { return left; }
//        void setLeft(TreeNode* left) { this->left = left; }
//        TreeNode* getRight() { return right; }
//        void setRight(TreeNode* right) { this->right = right; }
//    };
//    BinaryTree() : count(0), firstNode(nullptr) {}
//    BinaryTree(int firstValue) : count(1), firstNode(new TreeNode(firstValue)) {}
//    ~BinaryTree() { delete firstNode; }
//    int Count() { return count; }
//    void Insert(int value)
//    {
//        if (firstNode)
//        {
//            auto node = firstNode;
//            while (true)
//            {
//                if (node->getValue() > value)
//                {
//                    auto left = node->getLeft();
//                    if (left)
//                    {
//                        node = left;
//                    }
//                    else
//                    {
//                        Insert(node, value);
//                        break;
//                    }
//                }
//                else
//                {
//                    auto right = node->getRight();
//                    if (right)
//                    {
//                        node = right;
//                    }
//                    else
//                    {
//                        Insert(node, value);
//                        break;
//                    }
//                }
//            }
//        }
//        else firstNode = new TreeNode(value);
//        count++;
//    }
//    TreeNode* Search(int value)
//    {
//        auto node = firstNode;
//        while (!Search(node, value))
//        {
//            auto nodeValue = node->getValue();
//            if (nodeValue < value)
//            {
//                auto left = node->getLeft();
//                if (left)
//                {
//                    node = left;
//                }
//                else
//                {
//                    return nullptr;
//                }
//            }
//            else
//            {
//                auto right = node->getRight();
//                if (right)
//                {
//                    node = right;
//                }
//                else
//                {
//                    return nullptr;
//                }
//            }
//        }
//        return node;
//    }
//private:
//    TreeNode* firstNode;
//    int count;
//    //догадался разве что так использовать приватные функции
//    void Insert(TreeNode* node, int value)
//    {
//        assert(node);
//        if (node->getValue() > value)
//        {
//            assert(node->getLeft() == nullptr);
//            node->setLeft(new TreeNode(value));
//        }
//        else
//        {
//            assert(node->getRight() == nullptr);
//            node->setRight(new TreeNode(value));
//        }
//    }
//    bool Search(TreeNode* node, int value)
//    {
//        assert(node);
//        return node->getValue() == value;
//    }
//};

BinaryTree* CreateMinimalBST(int* arr, int firstIndex, int lastIndex)
{
    struct Interval
    {
        int start;
        int end;
        Interval(const int start, const int end) : start(start), end(end) { assert((end - start) >= 0); }
    };

    auto intervals = vector<Interval>{ Interval(firstIndex, lastIndex) };
    auto result = new BinaryTree();
    while (intervals.size())
    {
        auto nextIntervals = vector<Interval>();
        for (Interval interval : intervals)
        {
            int count = interval.end - interval.start + 1;
            if (count != 1)
                nextIntervals.push_back(Interval(interval.start, interval.start + count / 2 - 1));
            int val = arr[interval.start + count / 2];
            result->Insert(val);
            if (count > 2)
                nextIntervals.push_back(Interval(interval.start + count / 2 + 1, interval.end));
        }
        intervals = nextIntervals;
    }
    return result;
}

int main()
{
    setlocale(LC_ALL, "ru");

    auto res = CreateMinimalBST(new int[10]{ 1, 2, 3, 5, 7, 9, 10, 20, 25, 30}, 0, 9);

    res->Print();
}
