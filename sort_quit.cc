/*---------------------------------------------------------------------------
 * 快速排序
 * i=left, j=right,将基准数挖出来形成第一个坑a[i]
 * j--向前找比它小的数,找到后也挖出来填在前一个坑a[i]中
 * i++向前找比他大的数,找到后也挖出来填到前一个a[j]中
 * 重复上述步骤,知道i==j将基准数填入a[i]中
 * 复杂度:平均nlogn,最坏n*n
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
void AdjustArray(int a[], int left, int right)
{
    if(left < right)
    {
        int i = left;
        int j = right;
        int x = a[i];

        while(i < j)
        {
            while((i<j) && (a[j]>=x))
                j--;
            if(i < j)
                a[i++] = a[j];

            while((i<j) && (a[i]<x))
                i++;
            if(i < j)
                a[j--] = a[i];
        }

        a[i] = x;
        AdjustArray(a, left, i-1);
        AdjustArray(a, i+1, right);
    }
    
    return;
}
//---------------------------------------------------------------------------
void SortQuit(std::vector<int>& arr)
{
    if(2 > arr.size())
        return;

    AdjustArray(reinterpret_cast<int*>(arr.data()), 0, arr.size());
    return;
}
//---------------------------------------------------------------------------
int main(int, char**)
{
    std::vector<int> arr;
    for(size_t i=10; i>0; i--)
        arr.push_back(i);

    Print("before", arr);
    SortQuit(arr);
    Print("after", arr);
    AssertSored(arr);

    arr.clear();
    for(size_t i=10; i>0; i--)
        arr.push_back(rand()%100);

    Print("before", arr);
    SortQuit(arr);
    Print("after", arr);

    return 0;
}
//---------------------------------------------------------------------------
