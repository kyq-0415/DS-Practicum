#include<utils.h>
#include<cmath>
#include<string>
#include"../include/ljj_Stack.h"
#include"../include/ljj_Queue.h"
using namespace std;

#define isNum(x) (x>='0'&&x<='9')
#define isOp(x) (x=='+'||x=='-'||x=='*'||x=='/'||x=='%'||x=='<'||x=='>'||x=='^'||x=='('||x==')')
int lev[128];
stack<double> data;
stack<char> op;

string init(string s){
    int p=0;
    if (s[p]=='+'||s[p]=='-') s=s.insert(p,1,'0');
    while (p<s.length()) {
        if (s[p]>=128) s[p]='*';
        if (!isNum(s[p])&&s[p]!=')'&&(s[p+1]=='+'||s[p+1]=='-')) s[p+1]=s[p+1]=='+'?'<':'>',s=s.insert(p+1,1,'0');
        ++p;
    }
    return s;
}


void calculate(){
    double x,y;
    x=data.top(); data.pop();
    y=data.top(); data.pop();
    switch (op.top()) {
        case '+': data.push(x + y); break;
        case '-': data.push(y - x); break;
        case '<': data.push(x + y); break;
        case '>': data.push(y - x); break;
        case '*': data.push(x * y); break;
        case '/': data.push(y / x); break;
        case '%': data.push((int)y % (int)x); break;
        case '^': data.push(pow(y,x)); break;
    }
    op.pop();
}

int main(){
    cout << "请使用+、-、*、/、%、^作为运算符，允许使用小数" << endl;
    while (true) {
        cout << "输入表达式：" ;
        string s;
        cin >> s;
        s.erase(remove(s.begin(), s.end(), ' '), s.end());
        s = init(s);
        s.erase(remove(s.begin(), s.end(), '='), s.end());
        bool tag = false;
        for (int i = 0; i < s.length(); ++i) if (!isNum(s[i])&&!isOp(s[i])) tag = true;
        if (tag) {
            cout << "运算符不合法，请使用+、-、*、/、%、^作为运算符。"<<endl;
            continue;
        }
        int count=0;
        for (int i = 0; i < s.length(); ++i) {
            if (s[i]=='(') ++count;
            if (s[i]==')') --count;
        }
        if (count) {
            cout << "括号不匹配。"<<endl;
            continue;
        }
        //cout<< s<<endl;
        lev['-'] = 1;
        lev['+'] = 1;
        lev['*'] = 2;
        lev['/'] = 2;
        lev['%'] = 2;
        lev['^'] = 3;
        lev['<'] = 4;
        lev['>'] = 4;
        for (int i = 0; i < s.length(); ++i) {
            if (isNum(s[i])) {
                double temp = s[i] - '0';
                while ((i + 1) < s.length() && isNum(s[i + 1])) {
                    ++i;
                    temp = temp * 10 + s[i] - '0';
                }
                if (s[i + 1] == '.') {
                    ++i;
                    double temp2 = 0;
                    while ((i + 1) < s.length() && isNum(s[i + 1])) {
                        ++i;
                        temp2 = temp2 * 10 + s[i] - '0';
                    }
                    while (temp2 > 1) temp2 = temp2 / 10;
                    temp += temp2;
                }
                data.push(temp);
            } else {
                if (s[i] == ')') {
                    while (op.top() != '(') calculate();
                    op.pop();
                } else if (s[i] == '(') op.push(s[i]);
                else {
                    while (!op.empty() && lev[op.top()] >= lev[s[i]])
                        calculate();
                    op.push(s[i]);
                }
            }
            //op.c.plist();
            //data.c.plist();
            //cout << endl;
        }

        while (!op.empty()) calculate();
        cout << data.top() << endl << "是否要继续(y,n)?";
        char t;
        cin >> t;
        if (t=='n') break;
    }
    return 0;
}