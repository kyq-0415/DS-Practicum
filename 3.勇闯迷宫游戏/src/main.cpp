#include<utils.h>
#include<string>
using namespace std;
int n=7,m=7,p_tag=0;
int dir[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
int tag[100][100];
string t[100];

int init(){
    t[0]="#######";
    t[1]="#0#000#";
    t[2]="#0#0###";
    t[3]="#000#0#";
    t[4]="#0#000#";
    t[5]="#0#0#0#";
    t[6]="#######";
}

int dfs(int x, int y){
    if (x==1 && y==1) {
        p_tag=1;
        cout << endl << "迷宫地图："  << endl << endl << "    ";
        for (int i=0;i<n;++i) cout <<  "c"<< i << "  ";
        cout << endl << endl;
        for (int i=0;i<n;++i){
            cout << "r" << i << "   ";
            for (int j=0;j<m;++j)
                if (tag[i][j]) cout << t[i][j] << "   ";
                else cout<<"x   ";
            cout << endl << endl;
        }
        cout << endl << "迷宫路径："  << endl << "(1,1)";
        return 0;
    }

    for (int i=0;i<4;++i)
        if (tag[x+dir[i][0]][y+dir[i][1]] && t[x+dir[i][0]][y+dir[i][1]]=='0') {
            tag[x+dir[i][0]][y+dir[i][1]]=0;
            dfs(x+dir[i][0],y+dir[i][1]);
            tag[x+dir[i][0]][y+dir[i][1]]=1;
            if (p_tag) {
                cout << " ---> (" << x << "," << y << ")";
                return 1;
            }
    }
    return 0;
}

int main(){
    string temp;
    init();
    cout << "使用默认地图吗？(Y/n)";
    cin >> temp;
    if (temp[0]=='n') {
        cout << "请输入地图的尺寸n,m:" ;
        cin >> n >> m;
        cout << "请输入地图(#为墙壁 0为道路):" ;
        for (int i = 0; i < n; ++i) cin >> t[i];
    }
    fill(tag[0],tag[0]+100*100,1);
    tag[n-2][m-2]=0;

    dfs(n-2,m-2);
    return 0;
}