//---------------------------------------------------------------------------
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
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
//---------------------------------------------------------------------------
void AssertSored(const std::vector<int>& arr)
{
    for(size_t i=1; i<arr.size(); i++)
    {
        assert(arr[i-1] <= arr[i]);
    }

    return;
}
//---------------------------------------------------------------------------
int partition(int a[], int left, int right)
{
    if(left >= right)
        assert(0);
    
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
    assert(i == j);
    a[i] = x;

    return i;
}
//---------------------------------------------------------------------------
int Select(int a[], int size, int num)
{
    num--;
    int left = 0;
    int right = size - 1;
    while(left < right)
    {
        int index = partition(a, left, right);
        if(index == num)
            return a[index];

        if(index > num)
            right = index - 1;
        else
            left = index + 1;
    }

    //在64行未返回的情况,可以认为是刚好搜索到num值的两边,这时候直接返回a[num]即可
    return a[num];
}
//---------------------------------------------------------------------------
int main(int, char**)
{
    std::vector<int> arr;
    for(size_t i=10; i>0; i--)
        arr.push_back(i);

    Print("before", arr);
    int val = Select(reinterpret_cast<int*>(arr.data()), arr.size(), 5);
    std::cout << "val:" << val << std::endl;

    arr.clear();
    for(size_t i=10; i>0; i--)
        arr.push_back(rand()%100);

    Print("before", arr);
    val = Select(reinterpret_cast<int*>(arr.data()), arr.size(), 5);
    std::cout << "val:" << val << std::endl;

    return 0;
}
//---------------------------------------------------------------------------
