/*---------------------------------------------------------------------------
 * 高位优先的字符串排序 
 ---------------------------------------------------------------------------*/
//---------------------------------------------------------------------------
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <cstdio>
void DumpArray(const char**, int);
//---------------------------------------------------------------------------
void Print(const std::string& tips, std::vector<std::string>& list)
{
    std::cout << "----" << tips << std::endl;
    for(size_t i=0; i<list.size(); i++)
        std::cout << list[i] << std::endl;

    return;
}
//---------------------------------------------------------------------------
#define CHAR_BASE 256

//查找指定索引处char的值,如果不存在则返回-1
char CharAt(const char* pStr, int index)
{
    const char *pOldStr = pStr;  
  
    if ( pStr == NULL )  
    {  
        return -1;   
    }  
  
    while ( *pStr != '\0' )  
    {  
        if ( (pStr-pOldStr) == index )  
        {  
            return *pStr;   
        }  
  
        pStr++;  
    }  
  
    return -1;  
}

void MSDSort(const char* str_array[], int lo, int hi, int d)
{
    int     count[CHAR_BASE+2]  = {0};
    const char**  aux                 = 0;

    //当前函数是递归函数,这里为递归跳出点,当进行字符串排序时,如果少于
    //二组条目,则不再进行排序处理
    if(lo >= hi)
        return;

    //统计频率
    for(int i=lo; i<=hi; i++)
        count[CharAt(str_array[i], d)+2]++;

    //频率转换为索引
    for(int i=0; i<CHAR_BASE+1; i++)
        count[i+1] += count[i];

    aux = (const char**)malloc((hi-lo+1)*sizeof(char*));
    memset(aux, 0, (hi-lo+1)*sizeof(char*));

    //根据索引排序
    for(int i=lo; i<=hi; i++)
    {
        int index = count[CharAt(str_array[i], d)+1]++;
        aux[index] = str_array[i];
    }

    for(int i=lo; i<=hi; i++)
        str_array[i] = aux[i-lo];

    free(aux);

    for(int i=0; i<CHAR_BASE; i++)
        MSDSort(str_array, lo+count[i], lo+count[i+1]-1, d+1);

    return;
}

void DumpArray(const char* str_array[], int count)
{
    std::cout << "----" << std::endl;
    for(int i=0; i<count; i++)
        printf("[%d] %s \r\n", i, str_array[i]);

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
            list[i].swap(aux[i]);

        delete[] count;

        Print("i", list);
    }
}
//---------------------------------------------------------------------------
#define CHAR_BASE 256  
  
//查找提指定索引处char的值，如果不存在则返回-1  
char charAt(const char *pStr, const int index)  
{  
    const char *pOldStr = pStr;  
  
    if ( pStr == NULL )  
    {  
        return -1;   
    }  
  
    while ( *pStr != '\0' )  
    {  
        if ( (pStr-pOldStr) == index )  
        {  
            return *pStr;   
        }  
  
        pStr++;  
    }  
  
    return -1;  
}  
  
//高位优先字符串排序核心算法  
//正如上面描述，该算法是基于键索引计数法的思想，对于键索引计数法  
//这里不详细描述，有兴趣可以参考相关信息，这里仅对特定点进行注释  
//说明。  
void msdSort(const char *strArray[], int lo, int hi, int d)  
{  
    int count[CHAR_BASE+2] = {0};  
    const char **ppAux = NULL;  
    int i = 0;  
  
    //当前函数是递归函数，这里为递归跳出点。当进行字符串排序时，如  
    //果少于二组条目，则不再进行排序处理。  
    if ( lo >= hi )  
    {  
        return;   
    }  
  
    //对键值进行个数统计，这里选取本组排序字符串中第d列索引字符做为键  
    //值。  
    //为什么会出现+2,该步中count[0]预留出来，用于下面步骤的算法使用，  
    //详细原因参见键索引计数法中的解释，所以当前键值统计需要从索引1开始，  
    //charAt的实现是找出的字符索引范围为-1~(length(string)-1)，所以如  
    //果需要满足从索引1开始，则需要在charAt的结果之后+2.  
    for ( i = lo; i <= hi; i++ )   
    {  
        count[charAt(strArray[i], d) + 2]++;   
    }  
  
    //将键值统计转换为排序索引  
    //这里CHAR_BASE+1，是因为CHAR_BASE仅表示合法字符基数，该算法中由于  
    //支持不等长处理，对于不满足比较长度的键-1也参与了算法处理，所以这  
    //里为其+1.  
    for ( i = 0; i < CHAR_BASE + 1; i++ )  
    {  
        count[i+1] += count[i];  
    }  
  
    ppAux = (const char **)malloc((hi - lo + 1) * sizeof(char *));  
    if ( ppAux == NULL )  
    {  
        return;   
    }  
    memset(ppAux, 0, (hi - lo + 1) * sizeof(char *));  
  
    //根据排序索引进行分类，将排序好的分类存储到临时空间ppAux中  
    //这里会出现+1，也是因为charAt的实现返回索引范围是-1~(lenght(string)-1)，  
    //当前步骤count有效使用是从索引0开始，所以需要+1来满足。  
    for ( i = lo; i <= hi; i++ )  
    {  
        int index = count[charAt(strArray[i], d) + 1]++;  
        ppAux[index] = strArray[i];   
    }  
  
    //将排序好的临时空间ppAux内容回写到原来数组中。  
    for ( i = lo; i <= hi; i++)  
    {  
        strArray[i] = ppAux[i-lo];  
    }  
  
    free(ppAux);  
  
    //在每一轮排序后，采用分治思想，将当前组拆分为几个更小的组，并对每个更  
    //小的组进行递归排序处理，这里划分组的依据为，根据本次键值索引的分类进  
    //行分组，同时在下一轮对更小的组进行算法处理时，键值d则切换为下一列字符  
    //做为键值，因为本轮算法处理后，每个小组的当前键值d已经相同了。  
    //这里需要注意一下此时count[0]的为不满足长度处理的键值-1的最后索引位置，  
    //该键值是不需要参与分组处理的。  
    for ( i = 0; i < CHAR_BASE; i++ )  
    {  
       msdSort(strArray, lo + count[i], lo + count[i+1] - 1, d + 1);    
    }  
}  
  
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

    //LSDSort(list, 7);

    const char* test[10] = {  
        "she",  
        "sells",  
        "seashells",  
        "by",  
        "the",  
        "seashore",  
        "she",  
        "are",  
        "surely",  
        "secca"  
    };  
  
    DumpArray(test, 10);  
  
    MSDSort(test, 0, 9, 0);  
  
    printf("*****************\r\n");  
    DumpArray(test, 10);  

    return 0;
}

//---------------------------------------------------------------------------
