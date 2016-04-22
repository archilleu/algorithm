/*---------------------------------------------------------------------------
 * 二插查找数 
 * 复杂度:最坏lgN/2+1次比较
 ---------------------------------------------------------------------------*/
//---------------------------------------------------------------------------
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
//---------------------------------------------------------------------------
class BST
{
public:
    BST()
    :   root(0)
    {
    }
    ~BST()
    {
    }

    struct Node
    {
        Node(int key, int val, int size)
        :   key_(key),
            val_(val),
            left_(0),
            right_(0),
            size_(size)
        {
        }

        int     key_;
        int     val_;
        Node*   left_;
        Node*   right_;
        int     size_;
    };

    int Size()
    {
        return Size(root);
    }

    int Size(Node* node)
    {
        if(0 == node)
            return 0;

        return node->size_;
    }

    bool Put(int key, int val)
    {
        if(0 == root)
        {
            root = new Node(key, val, 1);
            return true;
        }

        Node* node = root;
        while(!node)
        {
            if(node->key_ > key)
                node = node->left_;
            else if(node->key_ < key)
                node = node->right_;
        }

        if(0 == node)
        {
            node = new Node(key, val, 1);
            return true;
        }
        else
        {
            node->val_ = val;
            return false;
        }
    }

    bool Get(int key, int* val)
    {
        Node* node = root;
        while(0 != node)
        {
            if(node->key_ > key)
                node = node->left_;
            else if(node->key_ < key)
                node = node->right_;
            else
            {
                *val = node->val_;
                return true;
            }
        }

        return false;
    }

    void Print()
    {
        Print(root); 
    }

    Node* Min()
    {
        if(0 == root)
            return 0;

        Node* node = root;
        while(0 != node->left_)
            node = node->left_;

        return node;
    }

    bool Floor(int key, int* rkey)
    {
        Node* node = Floor(root, key);
        if(0 == node)
            return false;

        *rkey = node->key_;
        return true;
    }

    bool Select(int k, int* key)
    {
        Node* node = Select(root, k);
        if(0 == node)
            return false;

        *key = node->key_;
        return true;
    }

    void DeleteMin()
    {
        root = DeleteMin(root);
    }


private:
    bool Get(Node* node, int key, int* val)
    {
        if(0 == node)
            return false;

        if(node->key_ > key)
            return Get(node->left_, key, val);
        else if(node->key_ < key)
            return Get(node->right_, key, val);

        *val = node->val_;
        return true;
    }

    bool Put(Node*& node, int key, int val)
    {
        if(0 == node)
        {
            node = new Node(key, val, 1);
            return true;
        }

        if(node->key_ > key)
        {
            Put(node->left_, key, val);
        }
        else if(node->key_ < key)
        {
            Put(node->right_, key, val);
        }
        else
        {
            node->val_ = val;
        }

        node->size_ = Size(node->left_) + Size(node->right_) + 1;
        return false;
    }

    Node* Min(Node* node)
    {
        if(0 == node->left_)
            return node;
        
        return Min(node->left_);
    }

    Node* Floor(Node* node, int key)
    {
        if(0 == node)
            return 0;

        if(node->key_ == key)
            return node;

        if(node->key_ < key)
            return Floor(node->left_, key);

        Node* temp = Floor(node->right_, key);
        if(0 !=  temp)  return temp;
        return node;
    }

    Node* Select(Node* node, int k)
    {
        if(0 == node)
            return 0;

        int nums = Size(node->left_);
        if(nums > k)
            return Select(node->left_, k);
        else if(nums < k)
            return Select(node->left_, k-nums-1);
        else
            return node;
    }

    int Rand(Node* node, int key)
    {
        if(0 == node)
            return 0;

        if(node->key_ > key)
            return Rand(node->left_, key);
        else if(node->key_ < key)
            return Rand(node->right_, key) + Size(node->left_) + 1;

        return Size(node->left_);
    }

    Node* DeleteMin(Node* node)
    {
        if(0 == node->left_)
        {
            Node* right = node->right_;
            delete node;
            return right;
        }

        node->left_ = DeleteMin(node->left_);
        node->size_ = Size(node->left_) + Size(node->right_) + 1;
        return node;
    }

    void Print(Node* node)
    {
        if(0 == node)
            return;

        Print(node->left_);
        std::cout << "key:" << node->key_ << " val:" << node->val_ << std::endl;
        Print(node->right_);
    }


private:
    Node* root;
};
//---------------------------------------------------------------------------
int main(int, char**)
{
    BST bst;
    for(int i=0; i<10; i++)
        bst.Put(i, i*10);
    bst.Print();
    std::cout << std::endl;

    int val;
    for(int i=0; i<10; i++)
    {
        bool err_code = bst.Get(i, &val);
        std::cout << "err_code:" << err_code << " val:" << val << std::endl;
    }
    std::cout << "err_code:" << bst.Get(1000, &val) << " val:" << val << std::endl;
    std::cout << "size: " << bst.Size() << std::endl;

    {
    BST bst;
    for(int i=0; i<10; i++)
    {
        int key = rand()%100;
        std::cout << "key:" << key << std::endl;
        bst.Put(key, i);
    }
    bst.Print();
    std::cout << std::endl;
    std::cout << "err_code:" << bst.Get(1000, &val) << " val:" << val << std::endl;
    std::cout << "size: " << bst.Size() << std::endl;
    }
    //for(int i=0; i<10; i++)
    //{
    //    std::cout << "del result:" << bst.Delete(i) << std::endl;
    //}
    //std::cout << "size: " << bst.Size() << std::endl;
    //std::cout << "del result:" << bst.Delete(1) << std::endl;
    
    return 0;
}
//---------------------------------------------------------------------------
