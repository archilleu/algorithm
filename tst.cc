/*---------------------------------------------------------------------------
 * 三向单词查找树
 ---------------------------------------------------------------------------*/
//---------------------------------------------------------------------------
#include <vector>
#include <queue>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
//---------------------------------------------------------------------------
class TST
{
public:
    TST()
    :   root_(0)
    {}

private:
    struct Node
    {
        Node()
        :   left(0),
            mid(0),
            right(0),
            val(0)
        {}
        ~Node()
        {}

        char c;
        Node* left;
        Node* mid;
        Node* right;
        int* val;
    };

public:
    bool Get(const std::string& key, int* val)
    {
        Node* node = Get(root_, key, 0);
        if(0 == node)
            return false;

        *val = *node->val;
        return true;
    }

    void Put(const std::string& key, int val)
    {
        root_ = Put(root_, key, val, 0);
    }

private:
    Node* Get(Node* node, const std::string& key, size_t d)
    {
        if(0 == node)
            return 0;

        char c = key[d];
        if(c < node->c)
            return Get(node->left, key, d);
        else if(c > node->c)
            return Get(node->right, key, d);
        else if(d < (key.length()-1))
            return Get(node->mid, key, d+1);
        else
            return node;
    }

    Node* Put(Node* node, const std::string& key, int val, size_t d)
    {   
        char c = key[d];
        if(0 == node)
        {
            node = new Node;
            node->val = new int(c);
        }

        if(c < node->c)
            node->left = Put(node->left, key, val, d);
        else if(c > node->c)
            node->right = Put(node->right, key, val, d);
        else if(d < (key.length()-1))
            node->mid = Put(node->mid, key, val, d+1);
        else
            *node->val = val;

        return node;
    }

private:
    Node* root_;
};

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

    std::vector<std::string> Keys()
    {
        return KeyWithPrefix("");
    }

    std::vector<std::string> KeyWithPrefix(std::string pre)
    {
        std::vector<std::string> result;
        Node* node = Get(root_, pre, 0);
        if(0 == node)
            return result;

        Collect(node, pre, result);
        return result;
    }

    std::vector<std::string> KeysThatMatch(const std::string pat)
    {
        std::vector<std::string> result;
        Collect(root_, "", pat, result);
        return result;
    }

    std::string LongestPrefixOf(const std::string s)
    {
        int len = Search(root_, s, 0, 0);
        return s.substr(0, len);
    }

    void Delete(const std::string& key)
    {
        root_ = Delete(root_, key, 0);
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

    void Collect(Node* node, std::string pre, std::vector<std::string>& q)
    {
        if(0 == node)       return;
        if(0 != node->val)
            q.push_back(pre);

        for(int i=0; i<R; i++)
        {
            Collect(node->next[i], pre+static_cast<char>(i), q);
        }

        return;
    }

    void Collect(Node* node, std::string pre, std::string pat, std::vector<std::string>& q)
    {
        if(0 == node)
            return;

        size_t len = pre.length();
        if(len==pat.length() && node->val!=0)
            q.push_back(pre);

        if(len == pat.length())
            return;

       char next = pat.at(len);
       for(int i=0; i<R; i++)
           if(next=='.' || next==i)
               Collect(node->next[i], pre+static_cast<char>(i), pat, q);
    }

    int Search(Node* node, std::string s, size_t d, size_t length)
    {
        if(0 == node)       return length;
        if(node->val != 0)  length = d;
        if(d == s.length()) return length;

        int index = static_cast<int>(s[d]);
        return Search(node->next[index], s, d+1, length);
    }

    Node* Delete(Node* node, std::string key, size_t d)
    {
        if(0 == node)
            return 0;
        if(d == key.length())
        {
            delete node->val;
            node->val = 0;
        }
        else
        {
            int index = static_cast<int>(key[d]);
            node->next[index] = Delete(node->next[index], key, d+1);
        }

        if(0 != node->val)
            return node;
        for(int i=0; i<R; i++)
        {
            if(0 != node->next[i])
                return node;
        }

        delete node;
        return 0;
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
    
    std::cout << "keys:" << std::endl;
    std::vector<std::string> keys = st.Keys();
    for(auto iter : keys)
        std::cout << iter << ",";
    std::cout << std::endl;

    std::cout << "prefix with:" << std::endl;
    std::vector<std::string> prefix = st.KeyWithPrefix("sh");
    for(auto iter : prefix)
        std::cout << iter << ",";
    std::cout << std::endl;

    std::cout << "keys with ... :" << std::endl;
    std::vector<std::string> keywith = st.KeysThatMatch("sh.");
    for(auto iter : keywith)
        std::cout << iter << ",";
    std::cout << std::endl;

    st.Delete("s");
    st.Delete("she");
    st.Delete("sh");

    return 0;
}
