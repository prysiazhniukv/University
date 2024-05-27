#include <iostream>
#include <cstdlib> 
#include <ctime>   

struct Cup
{
    double diameter;
    char color[10];
    double capacity;
};

void printCup(const Cup &cup)
{
    std::cout << "Diameter: " << cup.diameter << ", Color: " << cup.color << ", Capacity: " << cup.capacity << std::endl;
}


struct DynamicArray
{
    Cup *arr;
    int capacity, size;

    DynamicArray()
    {
        capacity = 2;
        arr = new Cup[capacity];
        size = 0;
    }

    ~DynamicArray()
    {
        delete[] arr;
    }

    void resize()
    {
        capacity *= 2;
        Cup *temp = new Cup[capacity];
        for (int i = 0; i < size; ++i)
        {
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
    }

    void push_back(const Cup &cup)
    {
        if (size == capacity)
        {
            resize();
        }
        arr[size++] = cup;
    }

    void push_front(const Cup &cup)
    {
        if (size == capacity)
        {
            resize();
        }
        for (int i = size; i > 0; --i)
        {
            arr[i] = arr[i - 1];
        }
        arr[0] = cup;
        ++size;
    }

    Cup pop_back()
    {
        if (size > 0)
        {
            return arr[--size];
        }
        else
        {
            std::cerr << "Cannot pop from an empty array" << std::endl;
            return Cup();
        }
    }

    Cup pop_front()
    {
        if (size > 0)
        {
            Cup frontCup = arr[0];
            for (int i = 0; i < size - 1; ++i)
            {
                arr[i] = arr[i + 1];
            }
            --size;
            return frontCup;
        }
        else
        {
            std::cerr << "Cannot pop from an empty array" << std::endl;
            return Cup();
        }
    }

    int getSize() const
    {
        return size;
    }

    Cup get(int index) const
    {
        if (index < 0 || index >= size)
        {
            std::cerr << "Invalid index" << std::endl;
            return Cup();
        }
        return arr[index];
    }
};

int main()
{
    DynamicArray cups;

    std::srand(std::time(nullptr));

    for (int i = 0; i < 50000; ++i)
    {
        Cup cup = {i + 1, "Red", i * 10}; 
        cups.push_back(cup);
    }

    for (int i = 0; i < 10000; ++i)
    {
        Cup cup = {i + 1, "Blue", i * 10}; 
        cups.push_front(cup);
    }

    for (int i = 0; i < 20000; ++i)
    {
        int index = std::rand() % cups.getSize();
        Cup cup = cups.get(index);
        std::cout << "Cup at index " << index << ": ";
        printCup(cup);
    }

    for (int i = 0; i < 5000; ++i)
    {
        cups.pop_front();
    }

    for (int i = 0; i < 5000; ++i)
    {
        cups.pop_back();
    }

    return 0;
}

