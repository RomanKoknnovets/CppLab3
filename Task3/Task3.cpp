#include <iostream>
#include <cassert>
#include <vector>
#include "BinaryTree.h"
using namespace std;

//думаю лучший вариант, но он с параметром по умолчанию tree
BinaryTree* CreateMinimalBST1(int* arr, int firstIndex, int lastIndex, BinaryTree* tree = new BinaryTree())
{
    int count = lastIndex - firstIndex + 1;
    int val = arr[firstIndex + count / 2];
    tree->Insert(val);
    if (count != 1)
        CreateMinimalBST1(arr, firstIndex, firstIndex + count / 2 - 1, tree);
    if (count > 2)
        CreateMinimalBST1(arr, firstIndex + count / 2 + 1, lastIndex, tree);
    return tree;
}

//без параметра по умолчанию
BinaryTree* CreateMinimalBST2(int* arr, int firstIndex, int lastIndex)
{
    int count = lastIndex - firstIndex + 1;
    int val = arr[firstIndex + count / 2];
    BinaryTree* result = new BinaryTree(val);
    //понимаю, что так создаются лишние экземпляры BinaryTree 
    //и скорее всего ещё зарезервированная память не освобождается
    //но зато без вспомогательных методов и возвращается сразу BinaryTree
    if (count != 1)
        result->getFirstNode()->setLeft(CreateMinimalBST2(arr, firstIndex, firstIndex + count / 2 - 1)->getFirstNode());
    if (count > 2)
        result->getFirstNode()->setRight(CreateMinimalBST2(arr, firstIndex + count / 2 + 1, lastIndex)->getFirstNode());
    return result;
}

//без рекурсии
BinaryTree* CreateMinimalBST3(int* arr, int firstIndex, int lastIndex)
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
    
    auto arr = new int[10]{ 1, 2, 3, 5, 7, 9, 10, 20, 25, 30 };
    auto res = CreateMinimalBST1(arr, 0, 10 - 1);

    for (int i = 0; i < 10; i++)
        assert(res->Search(arr[i])->getValue() == arr[i]);

    res->Print();
    
    //замечание по поводу деструктора: выводится звездочка, когда вызывается деструктор TreeNode
    delete res;
}
