#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include "BinaryTree.h"
using namespace std;
void BinaryTree::Insert(int value)
{
    if (firstNode)
    {
        auto node = firstNode;
        while (true)
        {
            if (node->getValue() > value)
            {
                auto left = node->getLeft();
                if (left)
                {
                    node = left;
                }
                else
                {
                    Insert(node, value);
                    break;
                }
            }
            else
            {
                auto right = node->getRight();
                if (right)
                {
                    node = right;
                }
                else
                {
                    Insert(node, value);
                    break;
                }
            }
        }
    }
    else firstNode = new TreeNode(value);
    count++;
}
BinaryTree::TreeNode* BinaryTree::Search(int value) const
{
    auto node = firstNode;
    while (!Search(node, value))
    {
        auto nodeValue = node->getValue();
        if (nodeValue < value)
        {
            auto left = node->getLeft();
            if (left)
            {
                node = left;
            }
            else
            {
                return nullptr;
            }
        }
        else
        {
            auto right = node->getRight();
            if (right)
            {
                node = right;
            }
            else
            {
                return nullptr;
            }
        }
    }
    return node;
}
void BinaryTree::Print() const
{
    if (firstNode)
    {
        vector<vector<TreeNode*>> nodesToLevels(1, vector<TreeNode*>(1, firstNode));
        for (int i = 0; nodesToLevels[i].size(); i++)
        {
            nodesToLevels.push_back(vector<TreeNode*>());
            cout << "Вершины на уровне " << i + 1 << ":" << endl;
            for (TreeNode* node : nodesToLevels[i])
            {
                cout << node->getValue() << ' ';
                if (node->getLeft())
                    nodesToLevels[i + 1].push_back(node->getLeft());
                if (node->getRight())
                    nodesToLevels[i + 1].push_back(node->getRight());
            }
            cout << endl;
            if (nodesToLevels[i + 1].size() == 0)
                cout << "Высота дерева = " << i + 1 << endl;
        }
    }
    else cout << "Дерево пустое";
}
void BinaryTree::Insert(TreeNode* node, int value)
{
    assert(node);
    if (node->getValue() > value)
    {
        assert(node->getLeft() == nullptr);
        node->setLeft(new TreeNode(value));
    }
    else
    {
        assert(node->getRight() == nullptr);
        node->setRight(new TreeNode(value));
    }
}
bool BinaryTree::Search(TreeNode* node, int value) const
{
    assert(node);
    return node->getValue() == value;
}
