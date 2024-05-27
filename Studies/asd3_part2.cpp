#include <iostream>
#include <ctime>
using namespace std;

void swap (int *a, int *b) 
{ 
    int temp = *a; 
    *a = *b; 
    *b = temp; 
} 

void randomize (int N[], int size) 
{ 

    srand (time(NULL)); 
 

    for (int i = size - 1; i > 0; i--) 
    { 

        int j = rand() % (i + 1); 
        
        swap(&N[i], &N[j]); 
    } 
}

int LastNumber(int n) {
    return n % 10;
}


void selectionSortByLastDigit(int N[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < size; j++) {
            if (LastNumber(N[j]) < LastNumber(N[minIndex]) ||
                (LastNumber(N[j]) == LastNumber(N[minIndex]) && N[j] < N[minIndex])) {
                minIndex = j;
            }
        }

        int temp = N[i];
        N[i] = N[minIndex];
        N[minIndex] = temp;
    }
}


int main() {
    int MIN = 1;
    int MAX = 200;
    const int size = 200;
    int N[size];

    for (int i = 0; i < size; i++ ){
        N[i] = i + 1;
        cout << N[i] << " ";
    }

    cout << "\n";

    randomize(N, size);

    for (int i = 0; i < size; i++ ){
        cout << N[i] << " ";
    }

    selectionSortByLastDigit(N, size);
    cout << "Sorted Nay by Last Digit: ";
    for (int i = 0; i < size; ++i) {
        cout << N[i] << " ";
    }
    cout << endl;



}