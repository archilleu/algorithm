//名称：2个数相加结果为0
//介绍：先排序数组，再从中查找相反值的数值，作为3sum的基础思想
//复杂度:logN;
#include <vector>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cstdlib>

int BinarySearch(int key, std::vector<int>& list)
{
    int lo = 0;
    int hi = list.size() - 1;
    while(lo <= hi)
    {
        int mid = lo + (hi-lo)/2;
        if(key < list[mid])
            hi = mid - 1;
        else if(key > list[mid])
            lo = mid + 1;
        else
            return mid;
    }

    return -1;
}

class TowSum
{
public:
    size_t Count(std::vector<int>& vals)
    {
        std::sort(vals.begin(), vals.end());
        size_t count = 0;
        for(size_t i=0; i<vals.size(); i++)
        {
            int val = vals[i];
            if(val > 0)
                break;

            if(0 < BinarySearch(-val, vals))
            //if(vals.end() != std::find(vals.begin(), vals.end(), -val))
                count++;
        }

        return count;
    }
};

int main()
{
    std::vector<int> vals;
    char buffer[16];
    std::fstream frd;
    frd.open("./res/1Mints.txt", std::ios::in);
    while(!frd.eof())
    {
        frd.getline(buffer, sizeof(buffer), '\n');
        vals.push_back(std::atoi(buffer));
    }
    vals.pop_back();

    TowSum towsum;
    size_t count = towsum.Count(vals);
    std::cout << "result: " << count << std::endl;

    return 0;
}
