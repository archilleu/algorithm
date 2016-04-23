/*---------------------------------------------------------------------------
 * 二插查找数 
 * 复杂度:最坏lgN/2+1次比较
 * http://noalgo.info/603.html
 * http://www.cnblogs.com/Anker/archive/2013/01/28/2880581.html
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
        Node(int key, int val, Node* parent, int size)
        :   key_(key),
            val_(val),
            left_(0),
            right_(0),
            parent_(parent),
            size_(size)
        {
        }

        int     key_;
        int     val_;
        Node*   left_;
        Node*   right_;
        Node*   parent_;
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
            root = new Node(key, val, 0, 1);
            return true;
        }

        Node* node  = root;
        Node* pnode = 0;
        while(0 != node)
        {
            pnode = node;
            if(node->key_ > key)
                node = node->left_;
            else if(node->key_ < key)
                node = node->right_;
            else
                break;
        }

        if(0 == node)
        {
            node = new Node(key, val, pnode, 1);
            if(pnode->key_ > key)
                pnode->left_ = node;
            else
                pnode->right_ = node;
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

    Node* Min(Node* node)
    {
        while(0 != node->left_)
            node = node->left_;

        return node;
    }

    Node* Max(Node* node)
    {
        while(0 != node->right_)
            node = node->right_;

        return node;
    }

    Node* SearchSuccessor(Node* node)
    {
        if(0 == node)
            return 0;

        //如果有右子树,则是右子树最小的那个
        if(node->right_)
            return Min(node->right_);

        //无右子树,则为最低的祖先
        Node* parent = node->parent_;
        while(0!=parent && node==parent->right_)
        {
            node    = parent;
            parent  = parent->parent_;
        }

        return parent;
    }

    Node* SearchPredecessor(Node* node)
    {
        if(0 == node)
            return 0;

        //如果有左子树,则左子树最大的那个
        if(node->left_)
            return Max(node->left_);

        //无左子树,同上
        Node* parent = node->parent_;
        while(0!=parent && node==parent->left_)
        {
            node    = parent;
            parent  = parent->parent_;
        }

        return parent;
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

    bool Delete(int key)
    {
        Node* node = root;
        while(0 != node)
        {
            if(node->key_ > key)
                node = node->left_;
            else if(node->key_ < key)
                node = node->right_;
            else
                break;
        }
        if(0 == node)
            return false;

        //真正要删除的节点和儿子
        Node* node_del = (0==node->left_ || 0==node->right_) ? node : SearchSuccessor(node);
        Node* node_son = node_del->left_ ? node_del->left_ : node_del->right_;

        if(0 != node_son)
            node_son->parent_ = node_del->parent_;//修正儿子节点的父节点

        if(0 == node_del->parent_)//父亲为空,说明删除了根节点
            root = node_son;
        else if(node_del == node_del->parent_->left_)//删除的为左儿子,修正左儿子
            node_del->parent_->left_ = node_son;
        else    //删除右儿子,修正右节点
            node_del->parent_->right_ = node_son;

        //把真正删除的节点数据拷贝到原来带删除的节点,在删除节点
        if(node_del != node)
        {
            node->key_ = node_del->key_;
            node->val_ = node_del->val_;
        }
        delete node_del;

        return true;
    }


private:
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

    for(int i=0; i<10; i++)
    {
        bst.Delete(i);
        bst.Print();
    }

    std::vector<int> keys;
    {
    BST bst;
    for(int i=0; i<10; i++)
    {
        int key = rand()%100;
        keys.push_back(key);
        std::cout << "key:" << key << std::endl;
        bst.Put(key, i);
    }
    bst.Print();
    std::cout << std::endl;
    std::cout << "err_code:" << bst.Get(1000, &val) << " val:" << val << std::endl;
    std::cout << "size: " << bst.Size() << std::endl;

    for(int i=0; i<10; i++)
    {
        bst.Delete(keys[i]);
        bst.Print();
    }
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
