#include "../include/ljj_Vector.h"
#include "../include/ljj_Heap.h"

using namespace std;

int main(){
    int n, temp;
    long long cost = 0;
    Heap<int> h;
    cin >> n;
    for (int i=0; i<n; ++i) cin >> temp, h.push_heap(temp);
    while (h.size()!=1) {
        int x=h.pop_heap(), y=h.pop_heap();
        cost+=x;
        cost+=y;
        h.push_heap(x+y);
    }
    cout << cost << endl;
}