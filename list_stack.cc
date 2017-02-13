//---------------------------------------------------------------------------
//栈的列表实现
#include <iostream>
#include <string>
//---------------------------------------------------------------------------
template <typename T>
class ListStack
{
public:
    ListStack()
    :   first_(0),
        size_(0)
    {}
    ~ListStack()
    {
        if(size()>0)
            pop();
    }

    void push(T v)
    {
        Node* oldfirst = first_;
        first_ = new Node(v, oldfirst);
        size_++;
    }

    T pop()
    {
        Node* oldfirst = first_;
        first_ = first_->next;
        T v = oldfirst->val;
        delete oldfirst;
        size_--;
        return v;
    }

    size_t size() { return size_; }

private:
    struct Node
    {
        Node(T v, Node* n)
        :   val(v),
            next(n)
        {}
        T val;
        Node* next;
    };

    Node* first_;
    size_t size_;
};
//---------------------------------------------------------------------------
int main(int, char**)
{
    ListStack<std::string> s;
    for(int i=0; i<16; i++)
        s.push("a");

    while(s.size()>0)
        std::cout << s.pop() << " ";
    std::cout << std::endl;
}
//---------------------------------------------------------------------------

