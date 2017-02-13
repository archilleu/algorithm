/*---------------------------------------------------------------------------
 * 选择排序
 * 首先选择队列中最小的元素,和第一个元素交换(如果是自身则和自身交换),
 * 再次在剩下的元素中找到最小的元素,和第二个元素交换.
 * 复杂度:比较次数N*N/2,交换次数N
 ---------------------------------------------------------------------------*/
//---------------------------------------------------------------------------
#include <memory>
#include <vector>
#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;
//---------------------------------------------------------------------------
template <typename T>
class Example
{
public:
    Example(vector<shared_ptr<T>>& vals)
    :   vals_(vals)
    {}
    void Sort()
    {
        for(size_t i=0; i<vals_.size(); i++)
        {
            size_t tmp = i;
            for(size_t j=i+1; j<vals_.size(); j++)
            {
                if(Less(vals_[j], vals_[tmp]))
                    tmp = j;
            }

            Exch(vals_[i], vals_[tmp]);
        }
    }

    bool isSorted()
    {
        for(size_t i=0; i<vals_.size()-1; i++)
        {
            if(!Less(vals_[i], vals_[i+1]))
            {
                if(*(vals_[i]) == *(vals_[i+1]))
                    continue;

                return false;
            }
        }

        return true;
    }

    void Show()
    {
        for(int i=0; i<vals_.size(); i++)
        {
            std::cout << *(vals_[i]) << " ";
        }

        std::cout << std::endl;
    }

private:
    bool Less(const shared_ptr<T>& l, const shared_ptr<T>& r)
    {
        return *l < *r;
    }

    void Exch(shared_ptr<T>& l, shared_ptr<T>& r)
    {
        l.swap(r);
    }

    vector<shared_ptr<T>> vals_;
};
//---------------------------------------------------------------------------
int main(int , char** )
{
    std::vector<shared_ptr<int>> vals;
    for(size_t i=0; i<10; i++)
    {
        vals.push_back(shared_ptr<int>(new int(rand()%100)));
    }
    Example<int> sort(vals);

    sort.Sort();
    assert(sort.isSorted());
    sort.Show();

    return 0;
}
//---------------------------------------------------------------------------
