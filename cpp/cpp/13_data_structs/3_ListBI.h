#pragma once

#include "15.IteratrorRiterator.h"

TEMPLATE_T
class ListBI
{
private:
    using pointerNode = Node<T>*;
    using referenceNode = Node<T>&;
    using Iter = Iterator<T>;
    using rIter = rIterator<T>;

    pointerNode head = nullptr;
    pointerNode tail = nullptr;
    size_t size = 0;

    template <typename InputIterator>
    void InitializeQueue(const InputIterator& begin, const InputIterator& end)
    {
        for (auto it = begin; it != end; ++it)
            Push_back(*it);
    }

public:
    // Constructors
    ListBI() = default;
    ListBI(size_t size) : ListBI()
    {
        for (size_t i = 0; i < size; ++i)
            ListBI<T>::Push_back(T());
    }
    ListBI(const T a[], const size_t _size) : ListBI()
    {
        for (size_t i = 0; i < _size; ++i)
            ListBI<T>::Push_back(a[i]);
    }
    ListBI(const ListBI<T>& b) : ListBI() { InitializeQueue(b.begin(), b.end()); }
    ListBI(const Iter& begin, const Iter& end) : ListBI() { InitializeQueue(begin, end); }
    ListBI(const rIter& begin, const rIter& end) : ListBI() { InitializeQueue(begin, end); }
    ListBI(std::initializer_list<T> a) : ListBI() { InitializeQueue(a.begin(), a.end()); }

    // Destructors
    ~ListBI() { Clear(); }

    // Calling iterators && reiterates
    Iter begin() const  { return Iter(head); }
    Iter end() const  { return Iter(nullptr); }
    rIter rbegin() const { return rIter(tail); }
    rIter rend() const { return rIter(nullptr); }

    // Basic List Functions
    void Push_back(const T& a)
    {
        auto newNode = new Node<T>(a);
        if (!size)
            tail = head = newNode;
        else
        {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        ++size;
    }
    T Pop_front() 
    {
        if (head == nullptr)
            return T();

        pointerNode tmp = head;
        head = head->next;

        if (head != nullptr)
            head->prev = nullptr;

        T tmpData = tmp->data;

        delete tmp;
        size--;

        return tmpData;
    }
    void Push_front(const T& a)
    {
        auto newNode = new Node<T>(a);

        if (size == 0)
            head = tail = newNode;
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }

        ++size;
    }
    T Pop_back() 
    {
        if (tail == nullptr)
            return T();

        pointerNode tmp = tail;
        tail = tail->prev;

        T tmpData = tmp->data;

        delete tmp;
        --size;

        return tmpData;
    }
    T& Front() { return head->data; }
    T& Back()  { return tail->data; }
    const T& Front() const { return head->data; }
    const T& Back() const { return tail->data; }
    size_t Length() const  { return size; }
    bool Empty()  { return (size == 0); }
    void Clear()
    {
        for (size_t i = size; i > 0; i--)
            Pop_back();
    }
    void Copy_From(const ListBI<T>& other) { InitializeQueue(other.begin(), other.end()); }
    void Swap(ListBI<T>& b)
    {
        std::swap(head, b.head);
        std::swap(tail, b.tail);
        std::swap(size, b.size);
    }
    void Resize(const size_t Size)
    {
        while (size != Size)
            size < Size ? Push_back(0) : Pop_back();
    }
    bool Contains(const T& a)
    {
        for (auto it : *this)
            if (it == a)
                return true;
        return false;
    }
    size_t CountRp(const T& a)
    {
        size_t count = 0;
        for (auto it = this->begin(); it != this->end(); ++it)
            if (*it == a)
                count++;
        return count;
    }
    void Extend(const ListBI<T>& other) { InitializeQueue(other.begin(), other.end()); }
    void Assign(std::initializer_list<T>& a) 
    {
        Clear();
        InitializeQueue(a.begin(), a.end());
    }
    void Assign(Iter begin, Iter end)
    {
        Clear();
        InitializeQueue(begin, end);
    }
    void Assign(rIter begin, rIter end)
    {
        Clear();
        InitializeQueue(begin, end);
    }
    void Assign(const size_t Size, const T& a)
    {
        Clear();
        for (size_t i = 0; i < Size; ++i)
            Push_back(a);
    }
    Iter Find(const T& elem)
    {
        for (auto it = this->begin(); it != this->end(); ++it)
            if (*it == elem)
                return it;
        return this->end();
    }
    Iter Insert(Iter iter, const T& elem)
    {
        Iter tmpIter(nullptr);
        auto newNode = new Node<T>(elem);

        if (iter == nullptr)
        {
            Push_back(elem);
            return tmpIter;
        }

        for (pointerNode current = head; current != nullptr; current = current->next)
        {
            if (current == iter)
            {
                newNode->next = current;
                newNode->prev = current->prev;

                (current->prev != nullptr) ? current->prev->next = newNode : head = newNode;

                current->prev = newNode;

                size++;

                Iter tmp_iter(current->next);

                return tmp_iter;
            }
        }

        return tmpIter;
    }
    Iter Erase(Iter iter)
    {
        Iter tmpIter(nullptr);

        for (pointerNode current = head; current != nullptr; current = current->next)
        {
            if (current == iter)
            {
                const pointerNode deleteNode = current;

                (current->prev != nullptr) ? current->prev->next = current->next : head = current->next;
                (current->next != nullptr) ? current->next->prev = current->prev : tail = current->prev;

                size--;

                delete deleteNode;

                Iter tmp_iter(current->next);

                return tmp_iter;
            }
        }
        return tmpIter;
    }
    static bool AreEqual(const ListBI<T>& a, const ListBI<T>& b)
    {
        if (a.Length() != b.Length())
            return false;

        for (auto belka = a.begin(), Strelka = b.begin(); belka != a.end(); ++belka, ++Strelka)
            if (*belka != *Strelka)
                return false;
        return true;
    }
    
    // List Operators
    friend bool operator==(const ListBI& a, const ListBI& b)
    {
        return a.size == b.size && std::equal(a.begin(), a.end(), b.begin());
    }
    friend bool operator<(const ListBI& a, const ListBI& b)
    {
        return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end()) || a.size < b.size;
    }
    friend bool operator!=(const ListBI& a, const ListBI& b) { return !(a == b); }
    friend bool operator>(const ListBI& a, const ListBI& b) { return b < a; }
    friend bool operator<=(const ListBI& a, const ListBI& b) { return !(b < a); }
    friend bool operator>=(const ListBI& a, const ListBI& b) { return !(a < b); }
    friend std::istream& operator>>(std::istream& input, ListBI& list)
    {
        T value;
        size_t i = 0;
        while (input >> value && i < list.size)
            list[i++] = value;
        return input;
    }
    friend std::ostream& operator<<(std::ostream& output, const ListBI<T>& list)
    {
        for (const auto& element : list)
            output << element << " ";
        return output;
    }
    ListBI<T>& operator=(const ListBI<T>& other)
    {
        if (this != &other)
        {
            Clear();
            Copy_From(other);
        }
        return *this;
    }
};
