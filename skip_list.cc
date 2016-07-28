#include <cstdlib>
#include <iostream>
#include <time.h>
#include <map>

class SkipList
{
private:
    struct Node
    {
        int key;
        int val;
        Node* forward[1];
    };

public:
    SkipList()
    :   header_(0),
        level_(0)
    {
        header_ = NewNodeOfLevel(kMaxLevel);
        for(int i=0; i<=kMaxLevel; i++)
            header_->forward[i] = (Node*)&kNIL;
    }

    ~SkipList()
    {
        DeleteNode(header_);
    }

    bool Search(int key, int* val)
    {
        Node* p = header_;
        Node* q = 0;
        for(int i=level_; 0<=i; i--)
        {
            while((q=p->forward[i]) && (q->key<key))
                p = q;
        }
        if(q->key != key)
            return false;

        *val = q->key;
        return true;
    }

    bool Insert(int key, int val)
    {
        //填充update数组，update数组保存的是每个level层
        //小于key节点前面的一个节点
        Node*   update[kMaxNumberOfLevels];
        Node*   q;
        Node*   p       = header_;
        int     level   = level_;
        for(int i=level; 0<=i; i--)
        {
            while((q=p->forward[i]) && (q->key<key))
                p = q;

            update[i] = p;
        }

        if(q->key == key)
        {
            q->val = val;
            return false;
        }

        level = RandomLevel();
        if(level > level_)
        {
            level           = ++level_;
            update[level]   = header_;
        }

        Node* node = NewNodeOfLevel(level);
        node->key = key;
        node->val = val;
        for(;0<=level; level--)
        {
            node->forward[level] = update[level]->forward[level];
            update[level]->forward[level] = node;
        }

        return true;
    }

    bool Delete(int key)
    {
        Node*   update[kMaxNumberOfLevels];
        Node*   q;
        Node*   p       = header_;
        int     level   = level_; 
        for(int i=level; 0<=i; i--)
        {
            while((q=p->forward[i]) && (q->key<key))
                p = q;

            update[i] = p;
        }

        if(q->key != key)
            return false;

        for(int i=0; (i<=level_)&&((p=update[i])->forward[i]==q); i++)
            p->forward[i] = q->forward[i];
        DeleteNode(q);

        while((header_->forward[level_]==&kNIL) && 0<level_)
            level_--;

        return true;
    }

    void Dump()
    {
        std::cout << "----------------------------------------" << std::endl;
        for(int i=kMaxLevel; 0<=i; i--)
        {
           std::cout << "l:" << i << " ";
           for(Node* node=header_->forward[i]; node!=&kNIL; node=node->forward[i])
               std::cout << node->key << ":" << node->val << "->";
           std::cout << std::endl;
        }
        std::cout << "----------------------------------------" << std::endl;
    }

private:
    Node* NewNodeOfLevel(int level)
    {
        return (Node*)malloc(sizeof(Node) + sizeof(Node*)*level); 
    }

    void DeleteNode(const Node* node)
    {
        if(0 != node)
            free((void*)node);

        return;
    }

    void FreeSkipList()
    {
        return;
    }

    int RandomLevel()
    {
        int level = 1;
        while(random()%2)
            level++;

        return (level>kMaxLevel) ? kMaxLevel : level;
    }

private:
    Node*   header_;
    int     level_;

private:
    static const Node   kNIL;
    static const int    kMaxNumberOfLevels  = 16;
    static const int    kMaxLevel           = kMaxNumberOfLevels-1;
};

const SkipList::Node   SkipList::kNIL = {0x7fffffff, 0, 0};


int main(int, char**)
{
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);

    const int size = 65536;
    SkipList s;
    int keys[size];
    for(int i=0; i<size; i++)
    {
        keys[i] = random();
        s.Insert(keys[i], keys[i]);
    }


    int val;
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<size; j++)
        {
            if(0x7fffffff == keys[j])
                continue;

            if(!s.Search(keys[j], &val))
                std::cout << "error in search:" << j << std::endl;
            if(val != keys[j])
                std::cout << "search retured worng:" << j << std::endl;
            if(!s.Delete(keys[j]))
                std::cout << "error in delel:" << j << std::endl;

            keys[j] = random();
            if(!s.Insert(keys[j], keys[j]))
                keys[j] = 0x7fffffff;
        }
    }

    /*std::map<int, int> s;
    int keys[size];
    for(int i=0; i<size; i++)
    {
        keys[i] = random();
        if(!(s.insert(std::pair<int, int>(keys[i], keys[i])).second))
            keys[i] = 0x7fffffff;
    }
    
    std::map<int, int>::iterator val;
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<size; j++)
        {
            if(0x7fffffff == keys[j])
                continue;

            val = s.find(keys[j]);
            if(val == s.end())
                std::cout << "error in search:" << j << std::endl;
            if(val->second != keys[j])
                std::cout << "search retured worng:" << j << std::endl;
            s.erase(val);

            keys[j] = random();
            if(!(s.insert(std::pair<int, int>(keys[j], keys[j])).second))
                keys[j] = 0x7fffffff;
        }
    }
   */ 

    struct timespec stop;
    clock_gettime(CLOCK_MONOTONIC, &stop);

    double total = stop.tv_sec-start.tv_sec + (stop.tv_nsec-start.tv_nsec);
    std::cout << "total:" << total << std::endl;

    return 0;
}
