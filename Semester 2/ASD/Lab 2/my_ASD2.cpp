#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <unordered_map>

using namespace std;

// Necessery parts for Universal Hash-Function.
#define p 9149658775000477
int a = rand() % 200 + 1;
int b = rand() % 200 + 1;
int M = 8;

int loadfactor = 2;

struct Data
{
    string name;
    int satellites;
    bool habitable;
};

struct HashNode
{
    long long key; // Key for each Node, is used to access it with O(1).
    Data data;
    HashNode *next; // To hold memory address of another node in case of collision(LinkedList).
};

struct LinkedList
{
    HashNode *head; // Points to the first Node in LinkedList.

    LinkedList()
    {
        head = nullptr; // This is a contrsuctor that say's the head initially when LinkedList is created point's to null.
    }

    Data *get(long long key) // Function to get data from LinkedList.
    {
        HashNode *curr = head;  // curr points to the first node in LinkedList.
        while (curr != nullptr) // Traverses LinkedList while curr is not nullptr.
        {
            if (curr->key == key) // Checks if the key that's stored in curr matches the one passed on by user.
            {
                return &(curr->data); // If sucess then it returns address of the data assosiated with the key.
            }
            curr = curr->next; // Moves to the next node in the LinkedList.
        }
        return nullptr; // If nothing was found it return's nullptr.
    }

    void push_front(long long key, Data newData)
    {
        HashNode *newNode = new HashNode;
        newNode->key = key;
        newNode->data = newData;
        newNode->next = head;
        head = newNode;
    }

    void pop(long long key)
    {
        if (head != nullptr)
        {
            if (head->key == key)
            {
                HashNode *temp = head;
                head = head->next;
                delete temp;
                return;
            }
            HashNode *prev = head;
            HashNode *curr = head->next;
            while (curr != nullptr)
            {
                if (curr->key == key)
                {
                    prev->next = curr->next;
                    delete curr;
                    return;
                }
                prev = curr;
                curr = curr->next;
            }
        }
    }
    ~LinkedList()
    { // Destructor.
        delete head;
    }
};

struct HashTable
{
    LinkedList *bucketsArray;
    int s = 0;

    HashTable()
    {
        bucketsArray = new LinkedList[M];
    }
    int hash(long long key)
    {
        return ((a * key + b) % p) % M;
    }
    void relocate_memory()
    {
        LinkedList *copy;
        M *= 2;
        copy = new LinkedList[M];
        for (int i = 0; i < M / 2; i++)
        {
            LinkedList *list = &bucketsArray[i];
            while (list->head != nullptr)
            {
                int new_ind = hash(list->head->key);
                copy[new_ind].push_front(list->head->key, list->head->data);
                list->head = list->head->next;
            }
        }
        delete[] bucketsArray;
        bucketsArray = copy;
    }
    void push(long long key, const Data &value)
    {
        if ((float)s / (float)M >= loadfactor)
        {
            relocate_memory();
        }

        int index = hash(key);
        LinkedList *list = &bucketsArray[index];
        if (list->get(key) != nullptr)
        {
            list->pop(key);
        }
        else
        {
            s++;
        }
        list->push_front(key, value);
    }

    Data *get(long long key)
    {
        int index = hash(key);
        LinkedList *list = &bucketsArray[index];
        return list->get(key);
    }
    void remove(long long key)
    {
        int index = hash(key);
        LinkedList *list = &bucketsArray[index];
        if (list->get(key) != nullptr)
        {
            s--;
            list->pop(key);
        }
    }
    int size()
    {
        return s;
    }
    ~HashTable()
    {
        delete[] bucketsArray;
    }
};

long long generateRandLong()
{
    int siz = rand() % 4 + 10;
    long long numb = 0;
    for (int i = 0; i < siz; i++)
    {
        numb *= 10;
        if (i)
            numb += rand() % 10;
        else
            numb += rand() % 9 + 1;
    }
    return numb;
}

bool testHashTable()
{
    const int iters = 500000;
    const int keysAmount = iters * 1;
    // generate random keys:
    long long *keys = new long long[keysAmount];
    long long *keysToInsert = new long long[iters];
    long long *keysToErase = new long long[iters];
    long long *keysToFind = new long long[iters];
    for (int i = 0; i < keysAmount; i++)
    {
        keys[i] = generateRandLong();
    }
    for (int i = 0; i < iters; i++)
    {
        keysToInsert[i] = keys[generateRandLong() % keysAmount];
        keysToErase[i] = keys[generateRandLong() % keysAmount];
        keysToFind[i] = keys[generateRandLong() % keysAmount];
    }
    // test my HashTable:
    HashTable hashTable;
    clock_t myStart = clock();
    for (int i = 0; i < iters; i++)
    {
        hashTable.push(keysToInsert[i], Data());
    }
    int myInsertSize = hashTable.size();
    for (int i = 0; i < iters; i++)
    {
        hashTable.remove(keysToErase[i]);
    }
    int myEraseSize = hashTable.size();
    int myFoundAmount = 0;
    for (int i = 0; i < iters; i++)
    {
        if (hashTable.get(keysToFind[i]) != NULL)
        {
            myFoundAmount++;
        }
    }
    clock_t myEnd = clock();
    float myTime = (float(myEnd - myStart)) / CLOCKS_PER_SEC;
    unordered_map<long long, Data> unorderedMap;
    clock_t stlStart = clock();
    for (int i = 0; i < iters; i++)
    {
        unorderedMap.insert({keysToInsert[i], Data()});
    }
    int stlInsertSize = unorderedMap.size();
    for (int i = 0; i < iters; i++)
    {
        unorderedMap.erase(keysToErase[i]);
    }
    int stlEraseSize = unorderedMap.size();
    int stlFoundAmount = 0;
    for (int i = 0; i < iters; i++)
    {
        if (unorderedMap.find(keysToFind[i]) != unorderedMap.end())
        {
            stlFoundAmount++;
        }
    }
    clock_t stlEnd = clock();
    float stlTime = (float(stlEnd - stlStart)) / CLOCKS_PER_SEC;
    cout << "My HashTable:" << endl;
    cout << "Time: " << myTime << ", size: " << myInsertSize << " - " << myEraseSize << ", found amount: " << myFoundAmount << endl;
    cout << "STL unordered_map:" << endl;
    cout << "Time: " << stlTime << ", size: " << stlInsertSize << " - " << stlEraseSize
         << ", found amount: " << stlFoundAmount << endl
         << endl;
    delete keys;
    delete keysToInsert;
    delete keysToErase;
    delete keysToFind;
    if (myInsertSize == stlInsertSize && myEraseSize == stlEraseSize && myFoundAmount == stlFoundAmount)
    {
        cout << "The lab is completed" << endl;
        return true;
    }
    cerr << ":(" << endl;
    return false;
}

int main()
{
    srand(time(nullptr));
    cout << testHashTable() << endl;

    return 0;
}