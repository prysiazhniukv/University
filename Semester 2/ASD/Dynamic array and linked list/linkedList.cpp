#include <iostream>
#include <cstring>
#include <cstdlib> 
#include <ctime>   


struct Node
{
    double diameter;
    char color[10];
    double capacity;
    Node *next;
};

struct LinkedList
{
    Node *head;

    LinkedList()
    {
        head = nullptr; 
    }

    ~LinkedList()
    {
        Node *current = head;
        Node *next;
        while (current != nullptr)
        {
            next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }

    void push_front(Node *&head, double diameter, const char *color, double capacity)
    {
        Node *newNode = new Node;           
        newNode->diameter = diameter;       
        std::strcpy(newNode->color, color); 
        newNode->capacity = capacity;       
        newNode->next = head;               
        head = newNode;                     
    }

    void push_back(Node *&head, double diameter, const char *color, double capacity)
    {
        Node *newNode = new Node;          
        newNode->diameter = diameter;       
        std::strcpy(newNode->color, color); 
        newNode->capacity = capacity;       
        newNode->next = nullptr;            

        if (head == nullptr)
        { 
            head = newNode;
        }
        else
        {
            Node *current = head;
            while (current->next != nullptr)
            { 
                current = current->next;
            }
            current->next = newNode; 
        }
    }

    Node *get(Node *head, int index)
    {
        if (index < 0) 
            return nullptr;

        int count = 0;
        Node *current = head;
        while (current != nullptr)
        {
            if (count == index)
                return current;
            current = current->next;
            count++;
        }

        return nullptr; 
    }

    void pop_front(Node *&head)
    {
        if (head == nullptr) 
            return;

        Node *temp = head; 
        head = head->next; 
        delete temp;       
    }

    void pop_back(Node *&head)
    {
        if (head == nullptr) 
            return;

        if (head->next == nullptr)
        { 
            delete head;
            head = nullptr;
            return;
        }

        Node *current = head;
        while (current->next->next != nullptr)
        { 
            current = current->next;
        }
        delete current->next;    
        current->next = nullptr; 
    }
    int size(Node *head)
    {
        int count = 0;
        Node *current = head;
        while (current != nullptr)
        {
            count++;
            current = current->next;
        }
        return count;
    }


    void print(Node *head)
    {
        Node *current = head; 
        while (current != nullptr)
        { 
            std::cout << "Diameter: " << current->diameter << ", Color: " << current->color << ", Capacity: " << current->capacity << std::endl;
            current = current->next; 
        }
    }
};

int main()
{
    LinkedList list; 

    std::srand(std::time(nullptr));

    for (int i = 0; i < 50000; ++i)
    {
        list.push_back(list.head, i + 1, "Red", i * 10);
    }

    for (int i = 0; i < 10000; ++i)
    {
        list.push_front(list.head, i + 1, "Blue", i * 10);
    }

    for (int i = 0; i < 20000; ++i)
    {
        int index = std::rand() % list.size(list.head);
        Node *node = list.get(list.head, index);
        if (node != nullptr)
        {
            std::cout << "Random Element at Index " << index << ": ";
            std::cout << "Diameter: " << node->diameter << ", Color: " << node->color << ", Capacity: " << node->capacity << std::endl;
        }
        else
        {
            std::cout << "Invalid index." << std::endl;
        }
    }

    for (int i = 0; i < 5000; ++i)
    {
        list.pop_front(list.head);
    }

    for (int i = 0; i < 5000; ++i)
    {
        list.pop_back(list.head);
    }

    return 0;
}
