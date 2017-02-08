//名称：二分查找算法(折半查找）
//介绍：要求数组是有序的
//复杂度:log2N;
#include <vector>
#include <iostream>
#include <cassert>

int BinarySearch(int key, std::vector<int>& list)
{
    int lo = 0;
    int hi = list.size() - 1;
    while(lo <= hi)
    {
        int mid = lo + (hi-lo)/2;
        if(key < list[mid])
            hi = mid - 1;
        else if(key > list[mid])
            lo = mid + 1;
        else
            return mid;
    }

    return -1;
}

int main(int , char** )
{
    std::vector<int> list = {10, 11, 12, 16, 18, 23, 29, 33, 48, 54, 57, 77, 84, 88};
    int result = BinarySearch(23, list);
    assert(-1 != result);
    assert(5 == result);
    std::cout << "idx: " << result << " value: " << list[result] << std::endl;

    result = BinarySearch(50, list);
    assert(-1 == result);

    return 0;
}


