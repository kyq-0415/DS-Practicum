#include <utils.h>
#include <random>
#include <algorithm>
#include <iomanip>
#include "../include/ljj_Vector.h"
#include "../include/ljj_Sort.h"
using namespace std;


int main(){
    double totaltime;
    clock_t start, finish;
    default_random_engine e;
    Vector<long> p,pp;
    int n;
    cout << endl;
    cout<<setfill('=')<<setw(65)<<" "<<endl;
    cout<<setfill(' ')<<"=="<<setw(15)<<""<<setw(45)<< left << "Comparison of sorting algorithms"<< setw(2)<< right <<"=="<<endl;
    cout<<setfill('=')<<setw(65)<<" "<<endl;
    cout<<setfill(' ')<<"=="<<setw(20)<<""<<setw(40)<< left << "1 -- Bubble Sort"<< setw(2)<< right <<"=="<<endl;
    cout<<setfill(' ')<<"=="<<setw(20)<<""<<setw(40)<< left << "2 -- Selection Sort"<< setw(2)<< right <<"=="<<endl;
    cout<<setfill(' ')<<"=="<<setw(20)<<""<<setw(40)<< left << "3 -- Insertion Sort"<< setw(2)<< right <<"=="<<endl;
    cout<<setfill(' ')<<"=="<<setw(20)<<""<<setw(40)<< left << "4 -- Shell Sort"<< setw(2)<< right <<"=="<<endl;
    cout<<setfill(' ')<<"=="<<setw(20)<<""<<setw(40)<< left << "5 -- Heap Sort"<< setw(2)<< right <<"=="<<endl;
    cout<<setfill(' ')<<"=="<<setw(20)<<""<<setw(40)<< left << "6 -- Merge Sort"<< setw(2)<< right <<"=="<<endl;
    cout<<setfill(' ')<<"=="<<setw(20)<<""<<setw(40)<< left << "7 -- Radix Sort"<< setw(2)<< right <<"=="<<endl;
    cout<<setfill(' ')<<"=="<<setw(20)<<""<<setw(40)<< left << "8 -- Quick Sort"<< setw(2)<< right <<"=="<<endl;
    cout<<setfill(' ')<<"=="<<setw(20)<<""<<setw(40)<< left << "9 -- EXIT"<< setw(2)<< right <<"=="<<endl;
    cout<<setfill('=')<<setw(65)<<" "<<endl<<endl;
    cout << "Please input the number of random integers: ";
    cin >> n;
    for (int i=0;i<n;++i) p.push_back(e());

    bool tag_exit=false;
    while (!tag_exit) {
        int selection;
        cout << "Please select sorting algorithm: ";
        cin >> selection;
        switch (selection) {
            case (1): {
                start = clock();
                pp = p;
                cout << "Bubble Sort number of swaps: " << Bubble_Sort(pp) << endl;
                finish = clock();
                totaltime = (double) (finish - start) / CLOCKS_PER_SEC;
                cout << "Bubble Sort time cost: " << 1000 * totaltime << " ms" << endl << endl;
                break;
            }
            case 2: {
                start = clock();
                pp = p;
                cout << "Selection Sort number of swaps: " << Selection_Sort(pp) << endl;
                finish = clock();
                totaltime = (double) (finish - start) / CLOCKS_PER_SEC;
                cout << "Selection Sort time cost: " << 1000 * totaltime << " ms" << endl << endl;
                break;
            }
            case 3 : {
                start = clock();
                pp = p;
                cout << "Insertion Sort number of swaps: " << Insertion_Sort(pp) << endl;
                finish = clock();
                totaltime = (double) (finish - start) / CLOCKS_PER_SEC;
                cout << "Insertion Sort time cost: " << 1000 * totaltime << " ms" << endl << endl;
                break;
            }
            case 4: {
                start = clock();
                pp = p;
                cout << "Shell Sort number of swaps: " << Shell_Sort(pp) << endl;
                finish = clock();
                totaltime = (double) (finish - start) / CLOCKS_PER_SEC;
                cout << "Shell Sort time cost: " << 1000 * totaltime << " ms" << endl << endl;
                break;
            }
            case 5: {
                start = clock();
                pp = p;
                cout << "Heap Sort number of swaps: " << Heap_Sort(pp) << endl;
                finish = clock();
                totaltime = (double) (finish - start) / CLOCKS_PER_SEC;
                cout << "Heap Sort time cost: " << 1000 * totaltime << " ms" << endl << endl;
                break;
            }
            case 6: {
                start = clock();
                pp = p;
                cout << "Merge Sort number of swaps: " << Merge_Sort(pp) << endl;
                finish = clock();
                totaltime = (double) (finish - start) / CLOCKS_PER_SEC;
                cout << "Merge Sort time cost: " << 1000 * totaltime << " ms" << endl << endl;
                break;
            }
            case 7: {
                start = clock();
                pp = p;
                cout << "Radix Sort number of swaps: " << Radix_Sort(pp) << endl;
                finish = clock();
                totaltime = (double) (finish - start) / CLOCKS_PER_SEC;
                cout << "Radix Sort time cost: " << 1000 * totaltime << " ms" << endl << endl;
                break;
            }
            case 8: {
                start = clock();
                pp = p;
                cout << "Quick Sort number of swaps: " << Quick_Sort(pp) << endl;
                finish = clock();
                totaltime = (double) (finish - start) / CLOCKS_PER_SEC;
                cout << "Quick Sort time cost: " << 1000 * totaltime << " ms" << endl << endl;
                break;
            }
            case 9: {
                tag_exit = true;
                break;
            }
            default:
                cout << "Invaild Selection, please input an integer from 1 to 9!" <<endl << endl;
        }
    }
    //cout << "length=" <<p.size() <<endl;
    //for (int i=0;i<n;++i) cout<< pp[i] <<endl;
    return 0;
}
