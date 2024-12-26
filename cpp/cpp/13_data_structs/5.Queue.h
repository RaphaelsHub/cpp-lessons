#pragma once

#include <assert.h>
#include <sstream>
#include <string.h>

#include "15.IteratrorRiterator.h"

// abstract class
TEMPLATE_T
class abstract_data_t
{
public:
    virtual ~abstract_data_t() = 0;
    virtual T& Front() = 0;
    virtual T& Back() = 0;
    virtual void Push_back(const T& a) = 0;
    virtual T Pop_front() = 0;
    virtual T Pop_back() = 0;
    virtual void Extend(const abstract_data_t<T>& a) = 0;
    virtual size_t Length() const = 0;
    virtual bool Empty() = 0;
    virtual Iterator<T> begin() const = 0;
    virtual Iterator<T> end() const = 0;
    virtual void Clear() = 0;
    virtual Iterator<T> Find(const T& elem) = 0;
    virtual Iterator<T> Insert(Iterator<T>, const T& elem) = 0;
    virtual Iterator<T> Erase(Iterator<T> iter) = 0;
    virtual void Assign(std::initializer_list<T>& a) = 0;

    virtual T& operator[](size_t index) = 0;

    abstract_data_t<T>& operator=(const abstract_data_t<T>& list)
    {
        Clear();
        Extend(list);
        return *this;
    }

    friend bool operator==(abstract_data_t<T>& l, abstract_data_t<T>& r)
    {
        if (l.Length() != r.Length())
            return false;
        auto lit = l.begin();
        auto rit = r.begin();
        while (lit != l.end() && rit != r.end())
        {
            if (*lit != *rit)
                return false;
            ++lit;
            ++rit;
        }
        return true;
    }
};

TEMPLATE_T
inline abstract_data_t<T>::~abstract_data_t()
{
}

TEMPLATE_T
class List : public abstract_data_t<T>
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
    List() = default;

    List(size_t size) : List()
    {
        for (size_t i = 0; i < size; ++i)
            List<T>::Push_back(T());
    }

    List(const T a[], const size_t _size) : List()
    {
        for (size_t i = 0; i < _size; ++i)
            List<T>::Push_back(a[i]);
    }

    List(const List<T>& b) : List() { InitializeQueue(b.begin(), b.end()); }
    List(const Iter& begin, const Iter& end) : List() { InitializeQueue(begin, end); }
    List(const rIter& begin, const rIter& end) : List() { InitializeQueue(begin, end); }
    List(std::initializer_list<T> a) : List() { InitializeQueue(a.begin(), a.end()); }

    // Destructors
    ~List() override { List<T>::Clear(); }

    // Calling iterators && reiterates
    Iter begin() const override { return Iter(head); }
    Iter end() const override { return Iter(nullptr); }
    rIter rbegin() const { return rIter(tail); }
    rIter rend() const { return rIter(nullptr); }

    // Basic List Functions
    void Push_back(const T& a) override
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

    T Pop_front() override
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

    T Pop_back() override
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

    T& Front() override { return head->data; }
    T& Back() override { return tail->data; }
    const T& Front() const { return head->data; }
    const T& Back() const { return tail->data; }
    size_t Length() const override { return size; }
    bool Empty() override { return (size == 0); }
    void Copy_From(const List<T>& other) { InitializeQueue(other.begin(), other.end()); }

    void Swap(List<T>& b)
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

    T At(const size_t index) const
    {
        if (index >= size)
            return tail->data;

        pointerNode tmp = head;
        for (size_t i = 0; i < index; ++i)
            tmp = tmp->next;

        return tmp->data;
    }

    void Extend(const abstract_data_t<T>& other) override { InitializeQueue(other.begin(), other.end()); }
    void Extend(const List<T>& other) { InitializeQueue(other.begin(), other.end()); }

    void Assign(std::initializer_list<T>& a) override
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

    static bool AreEqual(const List<T>& a, const List<T>& b)
    {
        if (a.Length() != b.Length())
            return false;

        for (auto belka = a.begin(), Strelka = b.begin(); belka != a.end(); ++belka, ++Strelka)
            if (*belka != *Strelka)
                return false;
        return true;
    }

    Iter Find(const T& elem) override
    {
        for (auto it = this->begin(); it != this->end(); ++it)
            if (*it == elem)
                return it;
        return this->end();
    }

    Iter Insert(Iter iter, const T& elem) override
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

    Iter Erase(Iter iter) override
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

    void Clear() override
    {
        for (size_t i = size; i > 0; i--)
            Pop_back();
    }

    // List Operators
    friend bool operator==(const List& a, const List& b)
    {
        return a.size == b.size && std::equal(a.begin(), a.end(), b.begin());
    }

    friend bool operator<(const List& a, const List& b)
    {
        return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end()) || a.size < b.size;
    }

    friend bool operator!=(const List& a, const List& b) { return !(a == b); }
    friend bool operator>(const List& a, const List& b) { return b < a; }
    friend bool operator<=(const List& a, const List& b) { return !(b < a); }
    friend bool operator>=(const List& a, const List& b) { return !(a < b); }

    friend std::istream& operator>>(std::istream& input, List& list)
    {
        T value;
        size_t i = 0;
        while (input >> value && i < list.size)
            list[i++] = value;
        return input;
    }

    friend std::ostream& operator<<(std::ostream& output, const List<T>& list)
    {
        for (const auto& element : list)
            output << element << " ";
        return output;
    }

    List<T>& operator=(const List<T>& other)
    {
        if (this != &other)
        {
            Clear();
            Copy_From(other);
        }
        return *this;
    }

    friend bool operator==(const T& value, const rIter& iter) { return value == *iter; }

    T& operator[](size_t index) override
    {
        if (index >= size)
            throw std::out_of_range("Index out of range");

        pointerNode current = head;
        for (size_t i = 0; i < index; ++i)
            current = current->next;
        return current->data;
    }
};

template <typename T, typename container = List<T>>
class Queue
{
private:
    using Iter = Iterator<T>;
    using rIter = rIterator<T>;

    container list; // Объект списка внутри класса Queue
public:
    // Constructors
    Queue() : list()
    {
    }

    Queue(const T a[], size_t size) : list(a, size)
    {
    }

    Queue(size_t size) : list(size)
    {
    }

    Queue(const Queue& b) : list(b.list)
    {
    }

    Queue(Iter begin, Iter end) : list(begin, end)
    {
    }

    Queue(rIter rbegin, rIter rend) : list(rbegin, rend)
    {
    }

    Queue(std::initializer_list<T> a) : list(a)
    {
    }

    Queue(const T a[]) : list(a, strlen(a) + 1)
    {
    }

    // Destructor
    ~Queue() { list.Clear(); }

    // Iterator calling
    Iter begin() const { return list.begin(); }
    Iter end() const { return list.end(); }
    rIter rbegin() const { return list.rbegin(); }
    rIter rend() const { return list.rend(); }

    // Queue Functions
    void Push(const T& a) { list.Push_back(a); }
    T Pop() { return list.Pop_front(); }
    T& Front() { return list.Front(); }
    T& Back() { return list.Back(); }
    const T& Front() const { return list.Front(); }
    const T& Back() const { return list.Back(); }
    bool Empty() const { return list.Empty(); }
    size_t Count() const { return list.Length(); }
    void Clear() { list.Clear(); }
    void Swap(Queue<T>& a) { list.Swap(a.list); }
};
