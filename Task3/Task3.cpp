#include <iostream>
#include <cassert>
#include <vector>
#include "BinaryTree.h"
using namespace std;

BinaryTree* CreateMinimalBSTnew(int* arr, int firstIndex, int lastIndex)
{
    int count = lastIndex - firstIndex + 1;
    int val = arr[firstIndex + count / 2];
    BinaryTree* result = new BinaryTree(val);
    if (count != 1)
        result->getFirstNode()->setLeft(CreateMinimalBSTnew(arr, firstIndex, firstIndex + count / 2 - 1)->getFirstNode());
    if (count > 2)
        result->getFirstNode()->setRight(CreateMinimalBSTnew(arr, firstIndex + count / 2 + 1, lastIndex)->getFirstNode());
    return result;
}

BinaryTree* CreateMinimalBSTold(int* arr, int firstIndex, int lastIndex)
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
    auto res = CreateMinimalBSTold(arr, 0, 10 - 1);

    for (int i = 0; i < 10; i++)
        assert(res->Search(arr[i])->getValue() == arr[i]);

    res->Print();
    
    //замечание по поводу деструктора: выводится звездочка, когда вызывается деструктор TreeNode
    delete res;

    cout << endl;
    auto res2 = CreateMinimalBSTnew(arr, 0, 10 - 1);
    for (int i = 0; i < 10; i++)
        assert(res2->Search(arr[i])->getValue() == arr[i]);

    res2->Print();

    delete res2;
}
