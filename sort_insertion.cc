/*---------------------------------------------------------------------------
 * 插入排序
 * 从头开始扫描元素,一边扫描一边对已扫描的元素排序,正在扫描的元素在已排好序的元素中插入
 * 插入后面的运算一次移动位置
 * 复杂度,最坏的情况是N*N/2比较和N*N/2移动,最好N-1次比较和0次交换
 ---------------------------------------------------------------------------*/
//---------------------------------------------------------------------------
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
//---------------------------------------------------------------------------
void Exch(int* a, int* b)
{   
    int tmp = *a;
    *a      = *b;
    *b      = tmp;
    return;
}
//---------------------------------------------------------------------------
void Print(const char* msg, std::vector<int>& arr)
{
    std::cout << msg << std::endl;
    for(size_t i=0; i<arr.size(); i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return;
}
void AssertSored(const std::vector<int>& arr)
{
    for(size_t i=1; i<arr.size(); i++)
    {
        assert(arr[i-1] <= arr[i]);
    }

    return;
}
//---------------------------------------------------------------------------
void SortInsertion(std::vector<int>& arr)
{
    if(2 > arr.size())
        return;

    int j;
    int temp;
    for(size_t i=1; i<arr.size(); i++)
    {
        temp = arr[i];
        for(j=i-1; (0<=j)&&(arr[j]>temp); j--)
            arr[j+1] = arr[j];

        arr[j+1] = temp;
    }

    return;
}
//---------------------------------------------------------------------------
int main(int, char**)
{
    std::vector<int> arr;
    for(size_t i=10; i>0; i--)
        arr.push_back(i);

    Print("before", arr);
    SortInsertion(arr);
    Print("after", arr);
    AssertSored(arr);

    arr.clear();
    for(size_t i=10; i>0; i--)
        arr.push_back(rand()%100);

    Print("before", arr);
    SortInsertion(arr);
    Print("after", arr);
    AssertSored(arr);

    return 0;
}
//---------------------------------------------------------------------------
