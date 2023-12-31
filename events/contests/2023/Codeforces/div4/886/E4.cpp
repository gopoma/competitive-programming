#include <iostream>
#include <thread>
#include <assert.h>

using namespace std;

#define MACRO(code) do {code} while (false)
#define DBG(x) MACRO(cerr << #x << " = " << (x) << endl;)
#define DBGY(x) MACRO(cerr << #x << " = " << (x) << " , ";)
#define DBG2(x,y) MACRO(DBGY(x); DBG(y);)
#define DBG3(x,y,z) MACRO(DBGY(x); DBGY(y); DBG(z);)
#define DBG4(x,y,z,w) MACRO(DBGY(x); DBGY(y); DBGY(z); DBG(w);)
#define RAYA MACRO(cerr << " ================ " << endl;)

void search(int element, int start, int end, int* list, int *position);

int threadSearch(int element, int* list, int length){
    int position = -1;

    thread th(search, element, 0, length - 1, list, &position);
    if(th.joinable())
        th.join();
    
    return position;
}

void search(int element, int start, int end, int* list, int *position){
    if(start > end) {
        *position = -1;
        return;
    }

    int mid = start + (end - start) / 2;
    int pivot = list[mid];

    assert(start <= end);

    if(pivot == element) {
        *position = mid;
    } else if(pivot > element) {
        thread th(search, element, start, mid - 1, list, position);
        if(th.joinable())
            th.join();
    } else{
        thread th(search, element, mid + 1, end, list, position);
        if(th.joinable())
            th.join();
    }
    return;
}

int main() {
    int list[10] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    int element;
    
    printf("Ingrese el numero a buscar: ");
    cin >> element;
    
    int pos = threadSearch(element, list, 10);

    if(pos == -1) cout << "Numero no encontrado" << endl;
    else cout << "Numero " << element << " encontrado en la posicion " << pos << endl;

    return 0;
}
