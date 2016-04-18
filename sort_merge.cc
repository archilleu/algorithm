/*---------------------------------------------------------------------------
 *归并排序,对两组有序数组进行归并排序
 左边有序|右边有序->归并
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
//把a[first-mid] a[mid-last]排序 
//---------------------------------------------------------------------------
void MergeArray(int a[], int left, int mid, int right, int temp[])
{
    int i = left;
    int j = mid + 1;
    int k = 0;

    while(i<=mid && j<=right)
    {
        if(a[i] < a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while(i <= mid)
        temp[k++] = a[i++];

    while(j <= right)
        temp[k++] = a[j++];

    for(i=0; i<k; i++)
        a[left+i] = temp[i];

    return;
}
//---------------------------------------------------------------------------
void MergeSort(int a[], int first, int last, int temp[])
{
    if(first < last)
    {
        int mid = (first+last) / 2;
        MergeSort(a, first, mid, temp);
        MergeSort(a, mid+1, last, temp);
        MergeArray(a, first, mid, last, temp);
    }

    return;
}
//---------------------------------------------------------------------------
int main(int, char**)
{
    std::vector<int> arr;
    for(size_t i=10; i>0; i--)
        arr.push_back(i);

    int temp[10];

    Print("before", arr);
    MergeSort(reinterpret_cast<int*>(arr.data()), 0, arr.size(), temp);
    Print("after", arr);
    AssertSored(arr);

    arr.clear();
    for(size_t i=10; i>0; i--)
        arr.push_back(rand()%100);

    Print("before", arr);
    MergeSort(reinterpret_cast<int*>(arr.data()), 0, arr.size(), temp);
    Print("after", arr);
    AssertSored(arr);

    return 0;
}
//---------------------------------------------------------------------------
