/*---------------------------------------------------------------------------
 * 线性探测的符号表 
 * N=使用个数,M=总个数,令a=N/M,推荐使用率为1/8~1/2之间
 ---------------------------------------------------------------------------*/
//---------------------------------------------------------------------------
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
//---------------------------------------------------------------------------
class LinearProbingHashST
{
public:
    LinearProbingHashST()
    :   size_(0),
        capacity_(16),
        keys_(capacity_, static_cast<int>(0x80000000)),
        vals_(capacity_, static_cast<int>(0x80000000))
    {
    }
    ~LinearProbingHashST()
    {
    }

    bool Put(int key, int val)
    {
        if(size_ >= (capacity_/2))
            Resize(2*capacity_);

        int i = Hash(key);
        for(; static_cast<int>(0x80000000)!=keys_[i]; i=(i+1)%capacity_)
            if(keys_[i] == key)  { vals_[i] = val; return false; }

        keys_[i] = key;
        vals_[i] = val;
        size_++;
        return true;
    }

    bool Get(int key, int* val=0)
    {
        for(int i=Hash(key); static_cast<int>(0x80000000)!=keys_[i]; i=(i+i)%capacity_)
            if(keys_[i] == key) { if(0 != val) *val = vals_[i]; return true; }

        return false;
    }

    bool Delete(int key)
    {
       if(false == Get(key))
           return false;

       int i = Hash(key);
       while(keys_[i] != key)
           i = (i + 1) % capacity_;

       keys_[i] = static_cast<int>(0x80000000);
       vals_[i] = static_cast<int>(0x80000000);

       i = (i + 1) % capacity_;
       while(keys_[i] != static_cast<int>(0x80000000))
       {
           int old_key = keys_[i];
           int old_val = vals_[i];

           keys_[i] = static_cast<int>(0x80000000);
           vals_[i] = static_cast<int>(0x80000000);
           size_--;
           Put(old_key, old_val);
           i = (i + 1) % capacity_;
       }

       size_--;

       if(0<size_ && size_==capacity_/8)
           Resize(capacity_ / 2);

       return true;
    }

private:
    int Hash(int key)
    {
        return (key&0x7FFFFFFFF) % capacity_;
    }

    void Resize(int size)
    {
        std::vector<int> keys(size, static_cast<int>(0x80000000));
        std::vector<int> vals(size, static_cast<int>(0x80000000));

        for(int i=0; i<capacity_; i++)
        {
            if(keys_[i] != static_cast<int>(0x80000000))
            {
                int hash = Hash(keys_[i]);
                for(; static_cast<int>(0x80000000)!=keys[hash]; hash=(hash+1)%capacity_)
                    ;
                keys[hash] = keys_[i];
                vals[hash] = vals_[i];
            }
        }

        keys_.swap(keys);
        vals_.swap(vals);
        capacity_ = size;
        return;
    }

private:
    int                 size_;
    int                 capacity_;
    std::vector<int>    keys_;
    std::vector<int>    vals_;
};
//---------------------------------------------------------------------------
int main(int, char**)
{
    LinearProbingHashST st;
    for(int i=0; i<10; i++)
        st.Put(i, i*10);

    for(int i=0; i<10; i++)
    {
        int val = 0;
        st.Get(i, &val);
        std::cout << " key:" << i << " val:" << val;
    }
    std::cout << std::endl;

    for(int i=0; i<10; i++)
    {
        st.Delete(i);
    }

    for(int i=0; i<10; i++)
    {
        std::cout << " result:" << st.Get(i);
    }
    std::cout << std::endl;
    return 0;
}
//---------------------------------------------------------------------------
