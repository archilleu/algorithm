/*---------------------------------------------------------------------------
 * 选择排序
 * 首先选择队列中最小的元素,和第一个元素交换(如果是自身则和自身交换),
 * 再次在剩下的元素中找到最小的元素,和第二个元素交换.
 * 复杂度:比较次数N*N/2,交换次数N
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
void SortSelection(std::vector<int>& arr)
{
    if(2 > arr.size())
        return;

    for(size_t i=0; i<arr.size(); i++)
    {
        int min = i;
        for(size_t j=i+1; j<arr.size(); j++)
        {
            if(arr[j] < arr[min])
                min = j; 
        }

        Exch(&arr[i], &arr[min]);
    }

    return;
}
//---------------------------------------------------------------------------
int main(int, char**)
{
    std::vector<int> arr;
    for(size_t i=0; i<10; i++)
    {
        arr.push_back(rand()%100);
    }

    Print("before", arr);
    SortSelection(arr);
    Print("after", arr);

    AssertSored(arr);
    return 0;
}
//---------------------------------------------------------------------------
