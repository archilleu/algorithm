/*---------------------------------------------------------------------------
 * 二叉堆优先级队列
 * 二叉堆定义:当一个二叉树的每个节点都大于等于它的两个子节点时,被称为堆有序,而二叉堆是在数组中层级存储的二叉树
 * 二叉堆排序,在嵌入式中利用的较多(空间紧),但是在现代操作系统中,因为很少与相邻元素比较,缓存命中率低,比快排和希尔排序都低的多
 * 复杂度:<2NlgN次比较
 ---------------------------------------------------------------------------*/
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
void Print(const char* msg, int list[], int size)
{
    std::cout << msg << std::endl;
    for(int i=0; i<size; i++)
    {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;

    return;
}
//---------------------------------------------------------------------------
class MaxPQ
{
public:
    MaxPQ(size_t size)
    :   n_(0)
    {
        list_.resize(size+1);
        return;
    }
    ~MaxPQ()
    {
    }

    bool IsEmpty()
    {
        return (n_ == 0);
    }

    size_t Size()
    {
        return n_;
    }

    void Insert(int value)
    {
        list_[++n_] = value;
        Swin(n_);
    }

    int DelMax()
    {
        int ret_val = list_[1];
        Exch(1, n_--);
        Sink(1);

        return ret_val;
    }

private:
    bool Less(int left, int right)
    {
        return list_[left] < list_[right];
    }

    void Exch(int left, int right)
    {
        int temp    = list_[left];
        list_[left] = list_[right];
        list_[right]= temp;

        return;
    }

    void Swin(size_t index)
    {
        while((1<index) && Less(index/2, index))
        {
            Exch(index/2, index);
            index /= 2;
        }

        return;
    }

    void Sink(size_t index)
    {
        while(index*2 <= n_)
        {
            size_t temp = index * 2;
            if((temp<n_) && Less(temp, temp+1))
                temp++;

            if(!Less(index, temp))
                break;

            Exch(index, temp);
            index = temp;
        }

        return;
    }

public:
    std::vector<int>& list()    { return list_; }

private:
    std::vector<int> list_;
    size_t n_;
};
//---------------------------------------------------------------------------
class Heap
{
public:
    Heap()
    {
    }
    ~Heap()
    {
    }

    void Sort(int list[], int N)
    {
        for(int k=N/2; k>=1; k--)
            Sink(list, k, N);

        while(1 < N)
        {
            Exch(list, 1, N--);
            Sink(list, 1, N);
        }

        return;
    }

private:
    void Sink(int list[], int k, int N)
    {
        while(2*k <= N)
        {
            int j = 2 * k;
            if((j<N) && (Less(list, j, j+1))) j++;

            if(!Less(list, k, j))
                break;

            Exch(list, k, j);
            k = j;
        }

        return;
    }

    bool Less(int list[], int left, int right)
    {
        return list[left-1] < list[right-1];
    }

    void Exch(int list[], int left, int right)
    {
        int temp     = list[left-1];
        list[left-1] = list[right-1];
        list[right-1]= temp;

        return;
    }
};
//---------------------------------------------------------------------------
int main(int, char**)
{
    //MaxPQ pq(10);
    //for(size_t i=0; i<10; i++)
    //{
    //    pq.Insert(i);
    //    Print("val:", pq.list());
    //}

    //std::cout << "del:";
    //for(size_t i=0; i<10; i++)
    //{
    //    std::cout << pq.DelMax() << " ";
    //}
    //std::cout << std::endl;


    //for(size_t i=0; i<10; i++)
    //{
    //    pq.Insert(rand()%100);
    //    Print("val:", pq.list());
    //}


    //std::cout << "del:";
    //for(size_t i=0; i<10; i++)
    //{
    //    std::cout << pq.DelMax() << " ";
    //}
    //std::cout << std::endl;

//heap
    int list[10];
    for(int i=10; 0<i; i--)
        list[10-i] = i;

    Heap hp;
    Print("before", list, 10);
    hp.Sort(list, 10);
    Print("after", list, 10);

    for(size_t i=0; i<10; i++)
        list[i] = (rand()%100);

    Print("before", list, 10);
    hp.Sort(list, 10);
    Print("after", list, 10);

    return 0;
}
//---------------------------------------------------------------------------
