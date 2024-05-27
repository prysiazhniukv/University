#include <iostream>
#include <ctime>
using namespace std;


void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void BubbleSort(int N[], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i; j++) {
            if (N[j] > N[j + 1]) {
                swap(N[j], N[j + 1]);
            }
        }
    }
}

void LinearSearch(int N[], int size) {
    int num, success = 0;
    cout << "\nPlease type in a number you're searching";
    cin >> num;
    for (int i = 0; i < size; i++) {
        if (N[i] == num) {
            cout << "Found at index " << i << endl;
            success = 1;
            break;
        }}
    if (success == 0){
        cout << "-1" << endl;
    }
}

int binarySearch(int N[], int start, int end, int num)
{
    if (end >= start) {
        int mid = start + (end - start) / 2;

        if (N[mid] == num)
            return mid;
 
        if (N[mid] > num)
            return binarySearch(N, start, mid - 1, num);
 

        return binarySearch(N, mid + 1, end, num);
    }
 
    return -1;
}


int main() {
    unsigned seed = time(0);
    srand(seed);

    const int MIN_Value = -2000;
    const int MAX_Value = 2000;
    const int size = 1000;
    int N[size];
    
    for (int i = 0; i < size; i++) {
        N[i] = rand()%4001-2000;
        cout << N[i] << " ";
    }

    clock_t start1 = clock();
    BubbleSort(N, size);
    clock_t end1 = clock();
    float seconds1 = (float(end1 - start1)) / CLOCKS_PER_SEC;


    cout << "\nSorted array: ";
    for (int i = 0; i < size; i++) {
        cout << N[i] << " ";
    }

    clock_t start2 = clock();
    LinearSearch(N, size);
    clock_t end2 = clock();
    float seconds2 = (float(end2 - start2)) / CLOCKS_PER_SEC;

    
    int size_2 = 1000;
    int middle_idx, middle_num, end = size_2 - 1, start = 0, num;
    cout << "Please type a number you're searching for: ";
    cin >> num;

    clock_t start3 = clock();
    int result = binarySearch(N,0, size_2 - 1, num);
    clock_t end3 = clock();
    float seconds3 = (float(end3 - start3)) / CLOCKS_PER_SEC;

    if (result != -1) {
        cout << result << endl;
    } else {
        cout << "Not found";
    }

    cout << "BubbleSort: " << seconds1 << endl;
    cout << "LinearSearch: " << seconds2 << endl;
    cout << "binarySearch: " << seconds3 << endl;

    return 0;

}