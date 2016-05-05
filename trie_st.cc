/*---------------------------------------------------------------------------
 * R向单词查找树
 ---------------------------------------------------------------------------*/
//---------------------------------------------------------------------------
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
//---------------------------------------------------------------------------
class TireST
{
private:
    struct Node
    {
        Node()
        :   val(0)
        {
            next = new Node*[R];
            bzero(next, sizeof(Node*)*R);
        }
        ~Node()
        {
            if(0 != val)
                delete val;

            delete[] next;
        }

        int*    val;
        Node**  next;
    };

public:
    TireST()
    :   root_(0)
    {
    }

    bool Get(const std::string key, int* val)
    {
        Node* node = Get(root_, key, 0);
        if(0 == node)
            return false;

        *val = *(node->val);
        return true;
    }

    bool Put(std::string key, int val)
    {
        root_ = Put(root_, key, val, 0);
        return true;
    }

private:
    Node* Get(Node* node, std::string key, size_t d)
    {
        if(0 == node)           return 0;
        if(d == key.length())   return node;

        Node* x = node->next[static_cast<int>(key.at(d))];
        return Get(x, key, d+1);
    }

    Node* Put(Node* node, std::string key, int val, size_t d)
    {
        if(0 == node)
            node = new Node();

        if(d == key.length())
        {
            if(0 == node->val)
                node->val = new int;

            *node->val = val;
            return node;
        }

        int c = static_cast<int>(key.at(d));
        node->next[c] = Put(node->next[c], key, val, d+1);
        return node;
    }

private:
    static const int R = 256;
    Node* root_;
};
//---------------------------------------------------------------------------
int main(int, char**)
{
    TireST st;
    st.Put("s", 1);
    st.Put("sh", 2);
    st.Put("she", 3);

    int val;
    bool err_code = st.Get("s", &val);
    std::cout << "result: " << err_code << "val: " << val << std::endl;

    err_code = st.Get("sh", &val);
    std::cout << "result: " << err_code << "val: " << val << std::endl;

    err_code = st.Get("she", &val);
    std::cout << "result: " << err_code << "val: " << val << std::endl;

    return 0;
}
