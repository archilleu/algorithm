/*---------------------------------------------------------------------------
 * 二叉堆优先级队列
 * 二叉堆定义:当一个二叉树的每个节点都大于等于它的两个子节点时,被称为堆有序,而二叉堆是在数组中层级存储的二叉树
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
int main(int, char**)
{
    MaxPQ pq(10);
    for(size_t i=0; i<10; i++)
    {
        pq.Insert(i);
        Print("val:", pq.list());
    }

    std::cout << "del:";
    for(size_t i=0; i<10; i++)
    {
        std::cout << pq.DelMax() << " ";
    }
    std::cout << std::endl;


    for(size_t i=0; i<10; i++)
    {
        pq.Insert(rand()%100);
        Print("val:", pq.list());
    }


    std::cout << "del:";
    for(size_t i=0; i<10; i++)
    {
        std::cout << pq.DelMax() << " ";
    }
    std::cout << std::endl;
    return 0;
}
//---------------------------------------------------------------------------
