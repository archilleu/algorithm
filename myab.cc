//---------------------------------------------------------------------------
#include <stack>
#include <string>
#include <iostream>
#include <cctype>
//---------------------------------------------------------------------------
template <typename T>
class A
{
public:
    void Fun()
    {
        T* t = new T[4];
        t[0] = "a";
        std::cout << t[0] << std::endl;
    }
};
class Myab
{
public:
    double Calc(const std::string& exp)
    {
        idx_ = 0;
        len_ = exp.size();

        std::stack<double> vals;
        std::stack<std::string> ops;
        for(std::string val=ReadVal(exp); ""!=val; val=ReadVal(exp))
        {
            if("(" == val) continue;
            else if("+" == val) {ops.push(val);continue;} 
            else if("-" == val) {ops.push(val);continue;}
            else if("*" == val) {ops.push(val);continue;}
            else if("/" == val) {ops.push(val);continue;}
            else if(")" == val)
            {
                std::string op = ops.top();
                ops.pop();
                double val = vals.top();
                vals.pop();

                if("+" == op) {val += vals.top(); vals.pop();} 
                else if("-" == op) {val -= vals.top(); vals.pop();} 
                else if("*" == op) {val *= vals.top(); vals.pop();} 
                else if("/" == op) {val /= vals.top(); vals.pop();} 
                vals.push(val);
            }
            else
                vals.push(std::stod(val));
        }
            
        return vals.top(); 
    }

private:
    std::string ReadVal(const std::string& exp)
    {
        SkipSpace(exp);

        if(idx_ == len_)
            return "";

        if('(' == exp[idx_])
        {
            idx_++;
            return "(";
        }
        if(')' == exp[idx_])
        {
            idx_++;
            return ")";
        }

        size_t idx = 0; 
        while(isdigit(exp[idx_+idx]))
            idx++;

        if(0 == idx)
            return std::string(exp, idx_++, 1);

        std::string ret = exp.substr(idx_, idx);
        idx_ += idx;
        return ret;
    }

    void SkipSpace(const std::string& exp)
    {
        while(idx_ <= len_)
        {
            if(isspace(exp[idx_]))
            {
                idx_++;
                continue;
            }

            return;
        }
    }

private:
    int idx_;
    int len_;
};
//---------------------------------------------------------------------------
int main(int, char**)
{
    std::string exp = "(1 + ( ( 2 + 3 ) * (4 * 5)))";
    Myab ab;
    double result = ab.Calc(exp);
    std::cout << "result: " << result << std::endl;

    A<std::string> a;
    a.Fun();
    return 0;
}
//---------------------------------------------------------------------------
