#include <iostream>
#include <algorithm>
#include <ctime>
#include <queue>

using namespace std;

class Patient {
public:
    int severity;
    float survivalChance;
    bool quarantineCompliance;

    bool operator<(const Patient &other) const {
        if (severity != other.severity)
            return severity > other.severity;
        return survivalChance < other.survivalChance;
    }

    bool operator>(const Patient &other) const {
        if (severity != other.severity)
            return severity < other.severity;
        return survivalChance > other.survivalChance;
    }

    bool operator==(const Patient &other) const {
        return severity == other.severity && survivalChance == other.survivalChance &&
               quarantineCompliance == other.quarantineCompliance;
    }
};

class DynamicArray {
private:
    Patient* array;
    size_t capacity;
    size_t length;

    void resize() {
        capacity *= 2;
        Patient* new_array = new Patient[capacity];
        std::copy(array, array + length, new_array);
        delete[] array;
        array = new_array;
    }

public:
    DynamicArray() : capacity(4), length(0) {
        array = new Patient[capacity];
    }

    ~DynamicArray() {
        delete[] array;
    }

    void push_back(const Patient& patient) {
        if (length == capacity) {
            resize();
        }
        array[length++] = patient;
    }

    void pop_back() {
        if (length > 0) {
            length--;
        }
    }

    Patient& operator[](size_t index) {
        return array[index];
    }

    const Patient& operator[](size_t index) const {
        return array[index];
    }

    size_t size() const {
        return length;
    }

    bool empty() const {
        return length == 0;
    }

    Patient* begin() {
        return array;
    }

    Patient* end() {
        return array + length;
    }

    Patient& front() {
        return array[0];
    }

    Patient& back() {
        return array[length - 1];
    }
};

class PriorityQueue {
private:
    DynamicArray heap;

    int getParent(int index) { return (index - 1) / 2; }
    int getLeftChild(int index) { return 2 * index + 1; }
    int getRightChild(int index) { return 2 * index + 2; }

    void siftUp(int index) {
        while (index != 0 && heap[getParent(index)] < heap[index]) {
            std::swap(heap[getParent(index)], heap[index]);
            index = getParent(index);
        }
    }

    void siftDown(int index) {
        int maxIndex = index;
        int left = getLeftChild(index);
        int right = getRightChild(index);

        if (left < heap.size() && heap[left] > heap[maxIndex])
            maxIndex = left;
        if (right < heap.size() && heap[right] > heap[maxIndex])
            maxIndex = right;

        if (index != maxIndex) {
            std::swap(heap[index], heap[maxIndex]);
            siftDown(maxIndex);
        }
    }

public:
    void push(const Patient &patient) {
        heap.push_back(patient);
        siftUp(heap.size() - 1);
    }

    Patient top() {
        return heap.front();
    }

    void pop() {
        std::swap(heap.front(), heap.back());
        heap.pop_back();
        siftDown(0);
    }

    int size() const {
        return heap.size();
    }

    bool empty() const {
        return heap.empty();
    }
};

template <typename T>
float testPriorityQueueSpeed(T&& priorityQueue)
{
    const int iters = 100000;
    clock_t timeStart = clock();
    for (int i = 0; i < iters; i++)
    {
        int insertDataAmount = rand() % 6 + 5;
        for (int j = 0; j < insertDataAmount; j++)
        {
            priorityQueue.push(Patient());
        }
        priorityQueue.top();
        priorityQueue.pop();
    }
    clock_t timeEnd = clock();
    float time = (float(timeEnd - timeStart)) / CLOCKS_PER_SEC;
    return time;
}
bool testPriorityQueue()
{
    srand(time(NULL));
    const int iters = 20000;
    PriorityQueue myPriorQueue;
    priority_queue<Patient> stlPriorQueue;
    bool isDataEqual = true;
    for (int i = 0; i < iters; i++)
    {
        int insertDataAmount = rand() % 6 + 5;
        for (int j = 0; j < insertDataAmount; j++)
        {
            Patient randData = Patient();
            myPriorQueue.push(randData);
            stlPriorQueue.push(randData);
        }
        if (!(myPriorQueue.top() == stlPriorQueue.top()))
        {
            isDataEqual = false;
            cerr << "Comparing failed on iteration " << i << endl << endl;
            break;
        }
        int removeDataAmount = rand() % insertDataAmount;
        for (int j = 0; j < removeDataAmount; j++)
        {
            myPriorQueue.pop();
            stlPriorQueue.pop();
        }
    }
    int myQueueSize = myPriorQueue.size();
    int stlQueueSize = stlPriorQueue.size();
    float stlTime =
        testPriorityQueueSpeed<priority_queue<Patient>>(priority_queue<Patient>());
    float myTime = testPriorityQueueSpeed<PriorityQueue>(PriorityQueue());
    cout << "My PriorityQueue:" << endl;
    cout << "Time: " << myTime << ", size: " << myQueueSize << endl;
    cout << "STL priority_queue:" << endl;
    cout << "Time: " << stlTime << ", size: " << stlQueueSize << endl << endl;
    if (isDataEqual && myQueueSize == stlQueueSize)
    {
        cout << "The lab is completed" << endl << endl;
        return true;
    }
    cerr << ":(" << endl << endl;
    return false;
}

int main() {
    int size;
    int *array = new int[size];
    testPriorityQueue();

    return 0;
}
