#include <iostream>
#include <cassert>
#include <vector>
#include "BinaryTree.h"
using namespace std;

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

    auto arr = new int[10]{ 1, 2, 3, 5, 7, 9, 10, 20, 25, 30 };
    auto res = CreateMinimalBST(arr, 0, 10 - 1);

    for (int i = 0; i < 10; i++)
        assert(res->Search(arr[i])->getValue() == arr[i]);

    res->Print();
}
