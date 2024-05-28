// Binary Search Tree
// Insert, find, erase, size, print, height, findinRange(MinObject, MaxObject).
// Additional features: Merge(tree1, tree2), split(tree, object), eraseRange(minObject,
// maxObject)
// Реалізувати логіку балансування по типу АВЛ-дерева або червоно-чорного дерева, або
// splay дерево.
// Структура Гравець має наступні поля: нікнейм, ранг, кількість досвіду,
// розмір донату тощо. Створити відсортовану “базу даних” гравців, в якій можна
// швидко перевіряти наявність потрібного гравця та знаходити всіх гравців на
// вказаному проміжку.

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm> // For std::max

struct Player {
    std::string nickname;
    int rank;
    int experience;
    int donation;

    Player() = default;
    Player(const std::string& nick, int r, int exp, int don)
        : nickname(nick), rank(r), experience(exp), donation(don) {}

    bool operator<(const Player& other) const {
        return rank + experience + donation < other.rank + other.experience + other.donation;
    }
    bool operator>(const Player& other) const {
        return rank + experience + donation > other.rank + other.experience + other.donation;
    }
    bool operator==(const Player& other) const {
        return rank + experience + donation == other.rank + other.experience + other.donation;
    }
    bool operator<=(const Player& other) const {
        return rank + experience + donation <= other.rank + other.experience + other.donation;
    }
    bool operator>=(const Player& other) const {
        return rank + experience + donation >= other.rank + other.experience + other.donation;
    }
};

struct Node {
    Player data;
    Node* left;
    Node* right;
    Node* parent;
    int height;
    Node(Player data) : data(data), left(nullptr), right(nullptr), parent(nullptr), height(1) {}
};

struct BinarySearchTree {
    Node* root;

    BinarySearchTree() : root(nullptr) {}

    void insert(Player data) {
        root = insert(root, data);
    }

    Node* insert(Node* node, Player data) {
        if (node == nullptr) {
            return new Node(data);
        }
        if (data < node->data) {
            node->left = insert(node->left, data);
        } else {
            node->right = insert(node->right, data);
        }

        node->height = 1 + std::max(height(node->left), height(node->right));
        int balance = getBalance(node);


        if (balance > 1 && data > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && data < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;

        return y;
    }

    int height(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int getBalance(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return height(node->left) - height(node->right);
    }

    Node* findMin(Node* node) {
        Node* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    void erase(Player data) {
        root = erase(root, data);
    }

    Node* erase(Node* node, Player data) {
        if (node == nullptr) {
            return node;
        }
        if (data < node->data) {
            node->left = erase(node->left, data);
        } else if (data > node->data) {
            node->right = erase(node->right, data);
        } else {
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = node->left ? node->left : node->right;
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                Node* temp = findMin(node->right);
                node->data = temp->data;
                node->right = erase(node->right, temp->data);
            }
        }

        if (node == nullptr) {
            return node;
        }

        node->height = 1 + std::max(height(node->left), height(node->right));
        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0) {
            return rightRotate(node);
        }
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && getBalance(node->right) <= 0) {
            return leftRotate(node);
        }
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    int size(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + size(node->left) + size(node->right);
    }

    void print(Node* node) {
        if (node == nullptr) {
            return;
        }
        print(node->left);
        std::cout << node->data.nickname << " " << node->data.rank << " " << node->data.experience << " " << node->data.donation << std::endl;
        print(node->right);
    }

    int findInRange(Node* node, Player left, Player right) {
        if (node == nullptr) {
            return 0;
        }
        int count = 0;
        if (node->data >= left && node->data <= right) {
            count = 1;
            std::cout << node->data.nickname << " " << node->data.rank << " " << node->data.experience << " " << node->data.donation << std::endl;
        }
        if (node->data >= left) {
            count += findInRange(node->left, left, right);
        }
        if (node->data <= right) {
            count += findInRange(node->right, left, right);
        }
        return count;
    }

};

long generateRandLong() {
    return rand() % 1000000;
}

Player generateRandomPlayer() {
    int rank = generateRandLong() % 1000;
    int experience = generateRandLong() % 10000;
    int donation = generateRandLong() % 500;
    return Player("Player" + std::to_string(generateRandLong() % 10000), rank, experience, donation);
}


bool testBinarySearchTree() {
    srand(time(NULL));
    const int iters = 80000;
    const int keysAmount = iters * 2;
    const int itersToRangeQueries = 1000;

    std::vector<Player> dataToInsert(iters);
    std::vector<Player> dataToErase(iters);
    std::vector<Player> dataToFind(iters);
    std::vector<std::pair<Player, Player>> dataToRangeQueries;

    for (int i = 0; i < iters; i++) {
        dataToInsert[i] = generateRandomPlayer();
        dataToErase[i] = generateRandomPlayer();
        dataToFind[i] = generateRandomPlayer();
    }

    for (int i = 0; i < itersToRangeQueries; i++) {
        Player minData = generateRandomPlayer();
        Player maxData = generateRandomPlayer();
        if (maxData < minData) {
            std::swap(minData, maxData);
        }
        dataToRangeQueries.push_back({minData, maxData});
    }

    BinarySearchTree myTree;
    clock_t myStart = clock();

    for (int i = 0; i < iters; i++) {
        myTree.insert(dataToInsert[i]);
    }

    int myInsertSize = myTree.size(myTree.root);
    int myTreeHeight = myTree.height(myTree.root);
    int optimalTreeHeight = log2(myInsertSize) + 1;

    for (int i = 0; i < iters; i++) {
        myTree.erase(dataToErase[i]);
    }

    int myEraseSize = myInsertSize - myTree.size(myTree.root);
    int myFoundAmount = 0;

    for (int i = 0; i < iters; i++) {
        if (myTree.findInRange(myTree.root, dataToFind[i], dataToFind[i]) > 0) {
            myFoundAmount++;
        }
    }

    clock_t myEnd = clock();
    float myTime = (float(myEnd - myStart)) / CLOCKS_PER_SEC;

    std::set<Player> stlTree;
    clock_t stlStart = clock();

    for (int i = 0; i < iters; i++) {
        stlTree.insert(dataToInsert[i]);
    }

    int stlInsertSize = stlTree.size();

    for (int i = 0; i < iters; i++) {
        stlTree.erase(dataToErase[i]);
    }

    int stlEraseSize = stlInsertSize - stlTree.size();
    int stlFoundAmount = 0;

    for (int i = 0; i < iters; i++) {
        if (stlTree.find(dataToFind[i]) != stlTree.end()) {
            stlFoundAmount++;
        }
    }

    clock_t stlEnd = clock();
    float stlTime = (float(stlEnd - stlStart)) / CLOCKS_PER_SEC;

    clock_t myRangeStart = clock();
    int myRangeFoundAmount = 0;

    for (int i = 0; i < itersToRangeQueries; i++) {
        myRangeFoundAmount += myTree.findInRange(myTree.root, dataToRangeQueries[i].first, dataToRangeQueries[i].second);
    }

    clock_t myRangeEnd = clock();
    float myRangeTime = (float(myRangeEnd - myRangeStart)) / CLOCKS_PER_SEC;

    clock_t stlRangeStart = clock();
    int stlRangeFoundAmount = 0;

    for (int i = 0; i < itersToRangeQueries; i++) {
        const auto& low = stlTree.lower_bound(dataToRangeQueries[i].first);
        const auto& up = stlTree.upper_bound(dataToRangeQueries[i].second);
        stlRangeFoundAmount += std::distance(low, up);
    }

    clock_t stlRangeEnd = clock();
    float stlRangeTime = (float(stlRangeEnd - stlRangeStart)) / CLOCKS_PER_SEC;

    std::cout << "My BinaryTree: height = " << myTreeHeight << ", optimal height = " << optimalTreeHeight << std::endl;
    std::cout << "Time: " << myTime << ", size: " << myInsertSize << " - " << myEraseSize << ", found amount: " << myFoundAmount << std::endl;
    std::cout << "Range time: " << myRangeTime << ", range found amount: " << myRangeFoundAmount << std::endl << std::endl;
    std::cout << "STL Tree:" << std::endl;
    std::cout << "Time: " << stlTime << ", size: " << stlInsertSize << " - " << stlEraseSize << ", found amount: " << stlFoundAmount << std::endl;
    std::cout << "Range time: " << stlRangeTime << ", range found amount: " << stlRangeFoundAmount << std::endl << std::endl;

    if (myInsertSize == stlInsertSize && myEraseSize == stlEraseSize && myFoundAmount == stlFoundAmount && myRangeFoundAmount == stlRangeFoundAmount) {
        std::cout << "The lab is completed" << std::endl;
        return true;
    }
    std::cerr << ":(" << std::endl;
    return false;
}

int main() {
    testBinarySearchTree();
    return 0;
}
