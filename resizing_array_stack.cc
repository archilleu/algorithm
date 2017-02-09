//---------------------------------------------------------------------------
#include <iostream>
#include <string>
//---------------------------------------------------------------------------
template <typename T>
class ResizingArrayStack
{
public:
    ResizingArrayStack(size_t cap)
    :   array_(0),
        size_(0),
        capacity_(cap)
    {
        if(0 != cap)
            array_ = new T[cap];
    }
    ~ResizingArrayStack()
    {
        delete[] array_;
    }
public:
    void push(T v)
    {
        if(size_ == capacity_)
            Resize(capacity_*2);
        array_[size_++] = v;
    }

    T pop()
    {
        T ret = array_[--size_];

        if(size_ == capacity_/4) Resize(capacity_/2);
        return ret;
    }

    size_t Size()
    {
        return size_;
    }

private:
    void Resize(size_t cap)
    {
        T* tmp = new T[cap];
        for(size_t i=0; i<size_; i++)
            tmp[i] = array_[i];
        delete[] array_;
        array_ = tmp;
        capacity_ = cap;
    }

private:
    T* array_;
    size_t size_;
    size_t capacity_;
};
//---------------------------------------------------------------------------
int main(int, char**)
{
    ResizingArrayStack<std::string> s(8);
    for(int i=0; i<16; i++)
        s.push("a");

    while(s.Size()>0)
        std::cout << s.pop() << " ";
    std::cout << std::endl;
}
//---------------------------------------------------------------------------
