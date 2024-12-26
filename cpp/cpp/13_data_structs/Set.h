#pragma once
#include <iostream>
#include <cassert>
#include <queue>
#include <cassert>
#include <sstream>
#include <iterator> 
#include <stack>


template <typename T>
class Node
{
public:
    Node* left;
    Node* right;
    T data;

    Node(T data): left(nullptr), right(nullptr), data(data){}
};

template <typename T>
class Iterator {
protected:
    std::stack<Node<T>*> stack;

public:
    Iterator () = default;
    Iterator(Node<T>* root) {
        while (root) {
            stack.push(root);
            root = root->left;
        }
    }

    Iterator& operator++() {
        if (stack.empty()) {
            throw std::out_of_range("Iterator out of range");
        }
        
        Node<T>* node = stack.top();
        stack.pop();

        Node<T>* current = node->right;
        while (current) {
            stack.push(current);
            current = current->left;
        }

        return *this;
    }

    Iterator operator++(int) {
        Iterator tmp = *this;
        ++(*this);
        return tmp;
    }

    std ::stack<Node<T>*> GetStack() { return stack; }
    
    T& operator*() const {
        if (stack.empty()) {
            throw std::out_of_range("Dereferencing empty iterator");
        }
        return stack.top()->data;
    }

    bool operator==(const Iterator& other) const {
        return stack == other.stack;
    }

    bool operator!=(const Iterator& other) const {
        return !(*this == other);
    }
};

template <typename T>
class RevIterator : public Iterator<T> {
public:
    RevIterator(Node<T>* root) : Iterator<T>() {
        while (root) {
            this->stack.push(root);
            root = root->right;
        }
    }

    RevIterator& operator++() {
        if (this->stack.empty()) {
            throw std::out_of_range("Iterator out of range");
        }

        Node<T>* node = this->stack.top();
        this->stack.pop();

        Node<T>* current = node->left;
        while (current) {
            this->stack.push(current);
            current = current->right;
        }

        return *this;
    }

    RevIterator operator++(int) {
        RevIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    T& operator*() const { return this->stack.top()->data; }
};


template <typename T>
class Abstract
{
public:
    virtual ~Abstract() = default; //+
    virtual T& Front() = 0; //+
    virtual T& Back() = 0; //+
    virtual void Push(T item) = 0; //+
    virtual void Pop() = 0; //+
    virtual void Extend(Abstract& container) = 0; //+
    virtual size_t Length() = 0; //+
    virtual bool Empty()  = 0; //+
    virtual void Clear() = 0; //+
    virtual Iterator<T> begin() = 0; //+
    virtual Iterator<T> end()  = 0; //+
    virtual void Assign(std::initializer_list<T>& items) = 0; //+
    virtual T& operator[](size_t position) = 0; //+
    virtual Iterator<T> Find(const T& value) = 0; //+
    virtual Iterator<T> Insert(const T& value) = 0; //+
    virtual Iterator<T> Erase(Iterator<T> cur) = 0; //+
    
    Abstract& operator=(Abstract& container)
    {
        if (this == &container) return *this;
        this->Clear();

        for (auto it = container.begin(); it != container.end(); ++it)
            this->Push(*it);
        return *this;
    } //+
    friend bool operator==(Abstract& a, Abstract& b)
    {
        if (a.Length() != b.Length()) return false;
        for (size_t i = 0; i < a.Length(); ++i)
            if (a[i] != b[i]) return false;
        return true;
    } //+
    friend bool operator!=(Abstract& a, Abstract& b) { return !(a == b); } //+
};

template <typename T>
class BinaryTree : public Abstract<T>
{
protected:
    size_t amountOfElements;
    Node<T>* root;

private:

    void RemoveLast()
    {
        if (!root) return;

        if (amountOfElements == 1)
        {
            delete root;
            root = nullptr;
            --amountOfElements;
            return;
        }

        size_t currentIndex = 0;
        size_t targetIndex = amountOfElements - 1;

        Node<T>* parent = nullptr;
        Node<T>* lastNode = FindLastNode(root, targetIndex, currentIndex, parent);

        if (lastNode)
        {
            if (parent)
            {
                if (parent->left == lastNode)
                    parent->left = nullptr;
                else if (parent->right == lastNode)
                    parent->right = nullptr;
            }

            delete lastNode;
            --amountOfElements;
        }
    }
    Node<T>* FindLastNode(Node<T>* root, size_t targetIndex, size_t& currentIndex, Node<T>*& parent)
    {
        if (!root)
            return nullptr;

        Node<T>* left = FindLastNode(root->left, targetIndex, currentIndex, root);
        if (left)
            return left;

        if (currentIndex == targetIndex)
            return root;

        ++currentIndex;

        return FindLastNode(root->right, targetIndex, currentIndex, root);
    }
    void CopyTree(Node<T>*& current, Node<T>* source)
    {
        if (!source)
            return;
        if (source->left)
        {
            current->left = new Node<T>(source->left->data);
            CopyTree(current->left, source->left);
        }
        if (source->right)
        {
            current->right = new Node<T>(source->right->data);
            CopyTree(current->right, source->right);
        }
    }
    Node<T>* FindByIndex(Node<T>* root, size_t targetIndex, size_t currentIndex) const
    {
        if (!root) return nullptr;

        Node<T>* left = FindByIndex(root->left, targetIndex, currentIndex);
        if (left)
            return left;

        if (currentIndex == targetIndex) return root;

        ++currentIndex;

        return FindByIndex(root->right, targetIndex, currentIndex);
    }
    

public:
    // constructors 
    BinaryTree() : amountOfElements(0), root(nullptr){}
    BinaryTree(size_t size) : amountOfElements(0), root(nullptr) { for (size_t i = 0; i < size; ++i) Insert(T()); }
    BinaryTree(const T arr[], size_t size) : amountOfElements(0), root(nullptr)
{
        for (size_t i = 0; i < size; ++i) Insert(arr[i]);
    }
    BinaryTree(const BinaryTree& a) : amountOfElements(a.amountOfElements), root(nullptr)
    {
        if (a.root)
        {
            root = new Node<T>(a.root->data);
            CopyTree(root, a.root);
        }
    }
    BinaryTree(BinaryTree&& a) noexcept : amountOfElements(a.amountOfElements), root(a.root)
    {
        a.root = nullptr;
        a.amountOfElements = 0;
    }
    ~BinaryTree() override { Clear(root); }
    void Clear(Node<T>*& root)
    {
        if (!root) return;
        Clear(root->left);
        Clear(root->right);
        delete root;
        root = nullptr;
        amountOfElements = 0;
    }
    T& At(size_t i) const
    {
        if (i >= amountOfElements) return FindByIndex(root, amountOfElements - 1, 0)->data;
        return FindByIndex(root, i, 0)->data;
    }
    void Resize(size_t newCapacity)
    {
        if (newCapacity < amountOfElements) RemoveLast();
        for (size_t i = amountOfElements; i < newCapacity; ++i) Insert(T());
        amountOfElements = newCapacity;
    }
    void Assign(size_t newCapacity, T& n)
    {
        Clear(root);
        for (size_t i = 0; i < newCapacity; ++i) Insert(n);
    }
    size_t Length() override { return amountOfElements; }
    bool Empty() override { return amountOfElements == 0; }
    void Swap(BinaryTree& a)
    {
        std::swap(root, a.root);
        std::swap(amountOfElements, a.amountOfElements);
    }
    static void PrintTree(Node<T>* root)
    {
        if (root == nullptr) return;
        PrintTree(root->left);
        std::cout << root->data << " ";
        PrintTree(root->right);
    }

    // Operators part 2
    friend bool operator==(const BinaryTree& a, const BinaryTree& b)
    {
        if (a.amountOfElements != b.amountOfElements) return false;
        for (size_t i = 0; i < a.amountOfElements; ++i) if (a.At(i) != b.At(i)) return false;
        return true;
    }
    friend bool operator!=(const BinaryTree& a, const BinaryTree& b) { return !(a == b); }
    friend bool operator<(const BinaryTree& a, const BinaryTree& b)
    {
        for (size_t i = 0; i < a.amountOfElements; ++i)
        {
            if (a.At(i) < b.At(i)) return true;
            if (a.At(i) > b.At(i)) return false;
        }
        return false;
    }
    friend bool operator>(const BinaryTree& a, const BinaryTree& b) { return b < a; }
    friend bool operator<=(const BinaryTree& a, const BinaryTree& b) { return !(a > b); }
    friend bool operator>=(const BinaryTree& a, const BinaryTree& b) { return !(a < b); }
    T& operator[](size_t i) override { return At(i); }
    friend std::ostream& operator<<(std::ostream& output, const BinaryTree& a)
    {
        for (size_t i = 0; i < a.amountOfElements; ++i) output << a.At(i) << " ";
        return output;
    }
    friend std::istream& operator>>(std::istream& input, BinaryTree& a)
    {
        a.Clear(a.root);
        T value;
        while (input >> value) a.Insert(value);
        return input;
    }
    bool Contains(T value)
    {
        Node<T>* current = root;
        while (current)
        {
            if (current->data == value) return true;
            if (value < current->data) current = current->left;
            else current = current->right;
        }
        return false;
    }
    void sort(Node<T> *root, T arr[], size_t i = 0){
        if (root == nullptr)
            return;
        sort(root->left, arr, i);
        arr[i++] = root->data;
        sort(root->right, arr, i);
    }
    size_t Count(T value)
    {
        int* arr = new int[amountOfElements];
        sort(root, arr);
        size_t count = 0;
        for (size_t i = 0; i < amountOfElements; ++i)
            if (arr[i] == value)
                ++count;
        delete[] arr;
        return count;
    }
    BinaryTree& operator=(const BinaryTree& a)
    {
        if (this == &a)
            return *this;
        Clear(root);
        amountOfElements = a.amountOfElements;
        if (a.root)
        {
            root = new Node<T>(a.root->data);
            CopyTree(root, a.root);
        }
        return *this;
    }

    // Methods part 3
    BinaryTree(Iterator<T> begin, Iterator<T> end) : amountOfElements(0), root(nullptr)
    {
        while (begin != end)
        {
            Insert(*begin);
            ++begin;
        }
    }
    BinaryTree (RevIterator<T> begin, RevIterator<T> end) : amountOfElements(0), root(nullptr)
    {
        while (begin != end)
        {
            Insert(*begin);
            ++begin;
        }
    }
    BinaryTree(std ::initializer_list<T> source) : amountOfElements(0), root(nullptr)
    {
        for (auto& item : source)
            Insert(item);
    }
    void Assign(Iterator<T> begin, Iterator<T> end)
    {
        Clear(root);
        while (begin != end)
        {
            Insert(*begin);
            ++begin;
        }
    }
    static bool IsEqual(const BinaryTree& a, const BinaryTree& b)
    {
        return a == b;
    }
    Iterator<T> begin() override { return {root}; }
    Iterator<T> end() override { return {nullptr};  }
    RevIterator<T> rbegin() { return {root}; }
    RevIterator<T> rend() { return {nullptr}; }

    // methods part 4
    void Push(T item) override { Insert(item); }
    void Pop() override{ RemoveLast(); }
    T &Front() override{ return FindByIndex(root, 0, 0)->data;}
    T &Back() override{ return FindByIndex(root, amountOfElements - 1, 0)->data; }
    void Clear () override { Clear(root); }
    void Extend(Abstract<T>& container) override
    {
        for (auto it = container.begin(); it != container.end(); ++it)
            Insert(*it);
    }
    void Assign(std::initializer_list<T>& items) override
    {
        Clear(root);
        for (auto& item : items)
            Insert(item);
    }

    // methods part 5
    Iterator<T> Find(const T& value) override
    {
        Node<T>* current = root;
        while (current)
        {
            if (current->data == value)
                return Iterator<T>(current);
            if (value < current->data)
                current = current->left;
            else
                current = current->right;
        }
        return end();
    }
    Iterator<T> Insert (const T& value) override
    {
        Node<T>** current = &root;
        while (*current != nullptr)
        {
            if (value == (*current)->data)
                return Find(value);
            
            if (value < (*current)->data)
                current = &(*current)->left;
            else
                current = &(*current)->right;
        }
        *current = new Node<T>(value);
        ++amountOfElements;
        return Find(value);
    }
    BinaryTree (const char* str) : amountOfElements(0), root(nullptr)
    {
        for (size_t i = 0; str[i] != '\0'; ++i)
            Insert(str[i]);
        Insert('\0');
    }
    static size_t Erase(Abstract<T>& a, const T& value)
    {
        size_t count = 0;
        Iterator<T> it = a.begin();
        while (it != a.end())
        {
            if (*it == value)
            {
                a.Erase(it);
                ++count;
            }
            else
            {
                ++it;
            }
        }
        return count;
    }
    Iterator<T> Erase(Iterator<T> cur) override
    {
        if (cur == Iterator<T>()) return end();

        T value = *cur;
        ++cur;
        Erase(value);
        return cur;
    }
    bool Erase(const T& value) {
        bool found = false;
        root = EraseNode(root, value, found);
        if (found) {
            --amountOfElements;
        }
        return found;
    }
private:
    Node<T>* EraseNode(Node<T>* node, const T& value, bool& found) {
        if (!node) {
            return nullptr;
        }

        if (value < node->data) {
            node->left = EraseNode(node->left, value, found);
        } else if (value > node->data) {
            node->right = EraseNode(node->right, value, found);
        } else {
            found = true;
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            } else if (!node->left) {
                Node<T>* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node<T>* temp = node->left;
                delete node;
                return temp;
            } else {
                Node<T>* successor = FindMin(node->right);
                node->data = successor->data;
                node->right = EraseNode(node->right, successor->data, found);
            }
        }

        return node;
    }
    Node<T>* FindMin(Node<T>* node) {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }
};
template <typename T>
class Set : public BinaryTree<T>
{
public:
    Set() : BinaryTree<T>() {}
    Set(size_t size) : BinaryTree<T>(size) {}
    Set(const T arr[], size_t size) : BinaryTree<T>(arr, size) {}
    Set(const Set& a) : BinaryTree<T>(a) {}
    Set(Set&& a) noexcept : BinaryTree<T>(std::move(a)) {}
    ~Set() override = default;
    
    void Clear() override { BinaryTree<T>::Clear(this->root); }
    T& At(size_t i) { return BinaryTree<T>::At(i); }
    void Resize(size_t newCapacity) { BinaryTree<T>::Resize(newCapacity); }
    void Assign(size_t newCapacity, T n) { BinaryTree<T>::Assign(newCapacity, n); }
    size_t Length() override { return BinaryTree<T>::Length(); }
    bool Empty() override { return BinaryTree<T>::Empty(); }
    void Swap(Set& a) { BinaryTree<T>::Swap(a); }
    static void PrintTree(Set& a) { BinaryTree<T>::PrintTree(a.root); }
    bool Contains(T value) { return BinaryTree<T>::Contains(value); }
    size_t Count(T value) { return BinaryTree<T>::Count(value); }
    Set& operator=(const Set& a) { return static_cast<Set&>(BinaryTree<T>::operator=(a)); }
    Iterator<T> begin() override { return BinaryTree<T>::begin(); }
    Iterator<T> end() override { return BinaryTree<T>::end(); }
    RevIterator<T> rbegin() { return BinaryTree<T>::rbegin(); }
    RevIterator<T> rend() { return BinaryTree<T>::rend(); }
    Set(const RevIterator<T>& rbegin, const RevIterator<T>& rend) : BinaryTree<T>(rbegin, rend) {}
    Set(const Iterator<T>& begin, const Iterator<T>& end) : BinaryTree<T>(begin, end) {}
    Set(std::initializer_list<T> source) : BinaryTree<T>(source) {}
    void Assign(const Iterator<T>& begin, const Iterator<T>& end) { BinaryTree<T>::Assign(begin, end); }
    static bool IsEqual(const Set& a, const Set& b) { return BinaryTree<T>::IsEqual(a, b); }
    T& Front() override { return BinaryTree<T>::Front(); }
    T& Back() override { return BinaryTree<T>::Back(); }
    void Push(T item) override { BinaryTree<T>::Push(item); }
    void Pop() override { BinaryTree<T>::Pop(); }
    void Extend(Abstract<T>& container) override {
        BinaryTree<T>::Extend(container);
    }
    void Assign(std::initializer_list<T>& items) override { BinaryTree<T>::Assign(items); }
    Iterator<T> Find(const T& value) override { return BinaryTree<T>::Find(value); }
    Iterator<T> Insert(const T& value) override { return BinaryTree<T>::Insert(value); }
    Iterator<T> Erase(Iterator<T> cur) override { return BinaryTree<T>::Erase(cur); }
    bool Erase(const T& value) { return BinaryTree<T>::Erase(value); }
    static size_t Erase(Abstract<T>& a, const T& value) { return BinaryTree<T>::Erase(a, value); }
    Set(const char* str) : BinaryTree<T>(str) {}
};

// int main(int argc, char const *argv[])
// {
//     Set<int> s1;
//
//     s1.Insert(3);
//     s1.Insert(3);
//     assert(1 == s1.Count(3));
//
//     Set<int> s2 = {1, 2, 3, 4, 1, 2, 3, 4};
//     assert(4 == s2.Length());
//
//     for (auto it = s2.begin(); it != s2.end();)
//     {
//         if (*it % 2)
//             it = s2.Erase(it);
//         else
//             ++it;
//     }
//     assert(0 == s2.Erase(1));
// }