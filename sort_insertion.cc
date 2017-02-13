/*---------------------------------------------------------------------------
 * 插入排序
 * 从头开始扫描元素,一边扫描一边对已扫描的元素排序,正在扫描的元素在已排好序的元素中插入
 * 插入后面的运算一次移动位置
 * 复杂度,最坏的情况是N*N/2比较和N*N/2移动,最好N-1次比较和0次交换
 ---------------------------------------------------------------------------*/
//---------------------------------------------------------------------------
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
        for(size_t i=1; i<vals_.size(); i++)
        {
            for(size_t j=i; (j>0)&&Less(vals_[j], vals_[j-1]); j--)
                Exch(vals_[j], vals_[j-1]);
            /*T tmp = *vals_[i];
            size_t j; 
            for(j=i; (j>0)&&Less(vals_[j], vals_[j-1]); j--)
            {
                vals_[j] = vals_[j-1];
            }

            vals_[j] = tmp;*/
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
