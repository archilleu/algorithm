/*---------------------------------------------------------------------------
 * 低位优先的字符串排序 
 ---------------------------------------------------------------------------*/
//---------------------------------------------------------------------------
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
//---------------------------------------------------------------------------
void Print(const std::string& tips, std::vector<std::string>& list)
{
    std::cout << "----" << tips << std::endl;
    for(size_t i=0; i<list.size(); i++)
        std::cout << list[i] << std::endl;

    return;
}
//---------------------------------------------------------------------------
void LSDSort(std::vector<std::string> list, int w)
{
    Print("befor", list);

    int N = list.size();
    int R = 256;
    std::vector<std::string> aux(N);

    //从左到右边遍历字符串
    for(int d=w-1; 0<=d; d--)
    {
        //计算频率
        int* count = new int[R+1];
        bzero(count, sizeof(int)*(R+1));

        for(int i=0; i<N; i++)
            count[list[i][d]+1]++;

        //将频率转换为索引
        for(int i=0; i<R; i++)
            count[i+1] += count[i];

        //将元素分类
        for(int i=0; i<N; i++)
        {
            int c = count[static_cast<int>(list[i][d])]++;
            aux[c] = list[i];
        }

        //回写
        for(int i=0; i<N; i++)
            list[i] = aux[i];

        delete[] count;

        Print("i", list);
    }
}
//---------------------------------------------------------------------------
int main(int, char**)
{
    std::vector<std::string> list;
    list.push_back("4PGC938");
    list.push_back("2IYE230");
    list.push_back("3CI0720");
    list.push_back("1ICK750");
    list.push_back("10HV845");
    list.push_back("4JZY524");
    list.push_back("1ICK750");
    list.push_back("3CIO720");
    list.push_back("10HV845");
    list.push_back("10HV845");
    list.push_back("2RLA629");
    list.push_back("24LA629");
    list.push_back("3ATW723");

    LSDSort(list, 7);

    return 0;
}
//---------------------------------------------------------------------------
