/*---------------------------------------------------------------------------
 * KMP
 * http://www.cnblogs.com/yjiyjige/p/3263858.html
 */
//---------------------------------------------------------------------------
#include <vector>
#include <queue>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
//---------------------------------------------------------------------------
//暴力查找搜索
int BombSearch(const std::string& txt, const std::string& pat)
{
    int n = txt.size();
    int m = pat.size();
    for(int i=0; i<=n-m; i++)
    {
        int j;
        for(j=0; j<m; j++)
        {
            if(txt[i+j] != pat[j])
                break;
        }

        if(j == m)
            return i;
    }

    return n;
}

int BombSearch2(const std::string& txt, const std::string& pat)
{
    int n = txt.size();
    int m = pat.size();
    int i = 0;
    int j = 0;
    for(; i<n && j<m; i++)
    {
        if(txt[i] == pat[j])
            j++;
        else
        {
            i -= j;
            j  = 0;
        }
    }

    if(j == m)
        return i - m;

    return n;
}
//---------------------------------------------------------------------------
std::vector<int> GetNext(const std::string& pat)
{
    std::vector<int> next;
    next.resize(pat.size());
    next[0] = -1;

    int k = -1;
    for(size_t i=0; i<pat.size()-1; )
    {
        if((-1==k) || (pat[i]==pat[k]))
        {
            i++;
            k++;
            if(pat[i] == pat[k])
                next[i] = next[k];
            else
                next[i] = k;
        }
        else
            k = next[k];
    }

    return next;
}
//---------------------------------------------------------------------------
int KMP(const std::string& text, const std::string& pat)
{
    std::vector<int> next = GetNext(pat);

    int m = text.size();
    int n = pat.size();
    int i = 0;
    int j = 0;
    while(i<m&&j<n)
    {
        if((-1==j) || (text[i]==pat[j]))
        {
            i++;
            j++;
        }
        else
            j = next[j];
    }

    if(j == n)
        return i-n;

    return m;
}
//---------------------------------------------------------------------------
int main(int, char**)
{
    std::string txt = "ababababc";
    std::string pat = "ababc";

    int index = BombSearch(txt, pat);
    std::cout << "1:" << txt.substr(index, pat.size()) << std::endl;

    index = BombSearch2(txt, pat);
    std::cout << "2:" << txt.substr(index, pat.size()) << std::endl;

    index = KMP(txt, pat);
    std::cout << "kmp:" << txt.substr(index, pat.size()) << std::endl;

    return 0;
}
