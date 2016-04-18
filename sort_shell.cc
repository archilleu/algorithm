/*---------------------------------------------------------------------------
 * 希尔排序,分组的插入排序
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
void SortShell(std::vector<int>& arr)
{
    if(2 > arr.size())
        return;

    for(int gap=(arr.size())>>1; 0<gap; gap >>=1)
    {
        int j;
        int temp;
        for(size_t i=gap; i<arr.size(); i++)
        {
            temp = arr[i];
            for(j=i-gap; (0<=j)&&(arr[j]>temp); j-=gap)
                arr[j+gap] = arr[j];

            arr[j+gap] = temp;
        }
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
    SortShell(arr);
    Print("after", arr);
    AssertSored(arr);

    arr.clear();
    for(size_t i=10; i>0; i--)
        arr.push_back(rand()%100);

    Print("before", arr);
    SortShell(arr);
    Print("after", arr);
    AssertSored(arr);

    return 0;
}
//---------------------------------------------------------------------------
