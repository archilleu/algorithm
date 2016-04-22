/*---------------------------------------------------------------------------
 * 顺序查找符号表
 * 复杂度:最坏N,新插入N*N/2
 ---------------------------------------------------------------------------*/
//---------------------------------------------------------------------------
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
//---------------------------------------------------------------------------
class SequentialSearchST
{
public:
    SequentialSearchST()
    :   head_(new Node(0, 0, 0)),
        size_(0)
    {
    }
    ~SequentialSearchST()
    {
        //del
    }

    struct Node
    {
        Node(int k, int v, Node* n=0)
        {
            key = k;
            val = v;
            next= n;
        }

        int key;
        int val;
        Node* next;
    };

    bool Get(int key, int* val)
    {
        for(Node* i=head_->next; 0!=i; i=i->next)
        {
            if(key == i->key)
            {
                *val = i->val;
                return true;
            }
        }

        return false;
    }

    int Size()  { return size_; }

    bool Put(int key, int val)
    {
        for(Node* i=head_->next; 0!=i; i=i->next)
        {
            if(key == i->key)
            {
                i->val = val;
                return false;
            }
        }

        Node* node  = new Node(key, val, head_->next);
        head_->next = node;
        size_++;

        return true;
    }

    bool Del(int key)
    {
        return Del(head_, key);
    }

    bool Del(Node* node, int key)
    {
        Node* next = node->next;
        if(0 == next)
            return false;

        if(next->key == key)
        {
            node->next = next->next;
            delete next;
            size_--;
            return true;
        }

        return Del(next, key);
    }

private:
    Node*   head_;
    int     size_;
};
//---------------------------------------------------------------------------
int main(int, char**)
{
    SequentialSearchST ss;
    for(int i=0; i<10; i++)
        ss.Put(i, i*10);

    int val;
    for(int i=0; i<10; i++)
    {
        bool err_code = ss.Get(i, &val);
        std::cout << "err_code:" << err_code << " val:" << val << std::endl;
    }
    std::cout << "err_code:" << ss.Get(1000, &val) << " val:" << val << std::endl;
    std::cout << "size: " << ss.Size() << std::endl;

    for(int i=0; i<10; i++)
    {
        std::cout << "del result:" << ss.Del(i) << std::endl;
    }
    std::cout << "size: " << ss.Size() << std::endl;
    
    return 0;
}
//---------------------------------------------------------------------------
