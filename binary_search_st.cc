/*---------------------------------------------------------------------------
 * 二进制查找符号表 
 * 复杂度:最坏lgN/2+1次比较
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
class BinarySearchST
{
public:
    BinarySearchST()
    :   size_(0)
    {
        keys_.resize(INIT_CAPACITY);
        values_.resize(INIT_CAPACITY);
    }
    ~BinarySearchST()
    {
    }

    int     Size()      { return size_; }
    bool    IsEmpty()   { return Size() == 0; }

    bool Get(int key, int* val)
    {
        if(IsEmpty())
            return false;

        int index = Rank(key);
        if((index<size_) && (keys_[index]==key))
        {
            *val = values_[index];
            return true;
        }

        return false;
    }

    bool Put(int key, int val)
    {
        int index = Rank(key);
        if((index<size_) && (keys_[index]==key))
        {
            values_[index] = val;
            return false;
        }

        //新添加
        if(static_cast<size_t>(size_)==keys_.size())
            Resize(static_cast<int>(2*keys_.size()));

        for(int i=size_; i>index; i--)
        {
            keys_[i]    = keys_[i-1];
            values_[i]  = values_[i-1];
        }
        keys_[index] = key;
        values_[index] = val;
        size_++;

        return true;
    }

    bool Delete(int key)
    {
        if(IsEmpty())   return false;

        int index = Rank(key);
        if(index==size_ || (keys_[index]!=key))
            return false;

        for(int i=index; i<size_-1; i++)
        {
            keys_[i]    = keys_[i+1];
            values_[i]  = values_[i+1];
        }
        size_--;
        return true;
    }

    int Rank(int key)
    {
        int lo = 0;
        int hi = size_ - 1;
        while(lo <= hi)
        {
            int mid = lo + (hi-lo)/2;
            if(keys_[mid] > key)
                hi = mid - 1;
            else if(keys_[mid] < key)
                lo = mid + 1;
            else
                return mid;
        }

        //lo 可能大于size_
        return lo;
    }

    void Print()
    {
        for(int i=0; i<size_; i++)
            std::cout << "keys: " << keys_[i] << " val: " << values_[i] << std::endl;

        return;
    }

private:
    void Resize(int capacity)
    {
        assert(capacity > size_);
        keys_.resize(capacity);
        values_.resize(capacity);

        return;
    }

private:
    int                 size_;
    std::vector<int>    keys_;
    std::vector<int>    values_;
    
private:
    static const int INIT_CAPACITY = 2;
};
//---------------------------------------------------------------------------
int main(int, char**)
{
    BinarySearchST bs;
    for(int i=0; i<10; i++)
        bs.Put(i, i*10);
    bs.Print();

    int val;
    for(int i=0; i<10; i++)
    {
        bool err_code = bs.Get(i, &val);
        std::cout << "err_code:" << err_code << " val:" << val << std::endl;
    }
    std::cout << "err_code:" << bs.Get(1000, &val) << " val:" << val << std::endl;
    std::cout << "size: " << bs.Size() << std::endl;

    for(int i=0; i<10; i++)
    {
        std::cout << "del result:" << bs.Delete(i) << std::endl;
    }
    std::cout << "size: " << bs.Size() << std::endl;
    std::cout << "del result:" << bs.Delete(1) << std::endl;
    
    
    return 0;
}
//---------------------------------------------------------------------------
