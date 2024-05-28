#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <unordered_map>

#define p 100019


using namespace std;

int a = rand() % 100 + 1, b = rand() % 100 + 1, M = 8;

float loadfactor = 2.4;

long long generateRandLong(){
    int siz = rand() % 4 + 10;
    long long numb = 0;
    for(int i = 0; i < siz; i ++) {
        numb *= 10;
        if (i) numb += rand() % 10;
        else numb += rand() % 9 + 1;
    }
    return numb;
}

struct Data{
    string fac, type;
    float prob;

    Data(){
        fac = "aaa";
        type = "qwe";
        prob = (float)rand() / 100.0;
    }
};

struct HashNode{
    long long key;
    Data data;
    HashNode* next;
};

struct LinkedList{
    HashNode* head;

    LinkedList() {
        head = nullptr;
    }
    Data* get(long long key){
        HashNode* curr = head;
        while(curr != nullptr){
            if(curr->key == key){
                return &(curr->data);
            }
            curr = curr->next;
        }
        return nullptr;
    }
    void push_front(long long key, const Data &new_data){
        HashNode* new_node = new HashNode();
        new_node->data = new_data;
        new_node->next = head;
        new_node->key = key;

        head = new_node;
    }
    void pop(long long key){
        if(head != nullptr) {
            HashNode *prev = head;
            if(prev->key == key){
                head = head->next;
                delete prev;
                return;
            }
            HashNode *curr = head->next;
            while (curr != nullptr) {
                if (curr->key == key) {
                    prev->next = curr->next;
                    delete curr;
                    return;
                }
                prev = curr;
                curr = curr->next;
            }
        }
        return;
    }
    ~LinkedList(){
        delete head;
    }
};

struct HashTable{
    LinkedList* bucketsArray;
    int s = 0;

    HashTable(){
        bucketsArray = new LinkedList[M];
    }
    int hash(long long key){
        return ((a * key + b) % p) % M;
    }
    void relocate_memory(){
        LinkedList* copy;
        M *= 2;
        copy = new LinkedList[M];
        for(int i = 0; i < M / 2; i ++){
            LinkedList* list = &bucketsArray[i];
            while(list->head != nullptr){
                int new_ind = hash(list->head->key);
                copy[new_ind].push_front(list->head->key, list->head->data);
                list->head = list->head->next;
            }
        }
        delete[] bucketsArray;
        bucketsArray = copy;
    }
    void insert(long long key, const Data &value){
        if((float)s/(float)M >= loadfactor){
            relocate_memory();
        }

        int index = hash(key);
        LinkedList* list = &bucketsArray[index];
        if(list->get(key) != nullptr){
            list -> pop(key);
        }
        else{
            s ++;
        }
        list->push_front(key, value);
    }

    Data* find(long long key){
        int index = hash(key);
        LinkedList* list = &bucketsArray[index];
        return list->get(key);
    }
    void erase(long long key){
        int index = hash(key);
        LinkedList* list = &bucketsArray[index];
        if(list->get(key) != nullptr){ s --; list -> pop(key); }
    }
    int size(){
        return s;
    }
    ~HashTable(){
        delete [] bucketsArray;
    }
};

bool testHashTable()
{
    const int iters = 500000;
    const int keysAmount = iters * 1;
    // generate random keys:
    long long* keys = new long long[keysAmount];
    long long* keysToInsert = new long long[iters]; long long* keysToErase = new long long[iters]; long long* keysToFind = new long long[iters];
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
        hashTable.insert(keysToInsert[i], Data());
    }
    int myInsertSize = hashTable.size();
    for (int i = 0; i < iters; i++)
    {
        hashTable.erase(keysToErase[i]);
    }
    int myEraseSize = hashTable.size();
    int myFoundAmount = 0;
    for (int i = 0; i < iters; i++)
    {
        if (hashTable.find(keysToFind[i]) != NULL) {
            myFoundAmount++;
        }
    }
    clock_t myEnd = clock();
    float myTime = (float(myEnd - myStart)) / CLOCKS_PER_SEC;
    // test STL hash table:
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
        if (unorderedMap.find(keysToFind[i]) != unorderedMap.end()) {
            stlFoundAmount++;
        }
    }
    clock_t stlEnd = clock();
    float stlTime = (float(stlEnd - stlStart)) / CLOCKS_PER_SEC;
    cout << "My HashTable:" << endl;
    cout << "Time: " << myTime << ", size: " << myInsertSize << " - " << myEraseSize << ", found amount: " << myFoundAmount << endl;
    cout << "STL unordered_map:" << endl;
    cout << "Time: " << stlTime << ", size: " << stlInsertSize << " - " << stlEraseSize << ", found amount: " << stlFoundAmount << endl << endl;
    delete keys;
    delete keysToInsert;
    delete keysToErase;
    delete keysToFind;
    if (myInsertSize == stlInsertSize && myEraseSize == stlEraseSize && myFoundAmount == stlFoundAmount)
    {
        cout << "The lab is completed" << endl; return true;
    }
    cerr << ":(" << endl;
    return false;
}

int main() {
    srand(time(nullptr));
    cout << testHashTable() << endl;

    return 0;
}
