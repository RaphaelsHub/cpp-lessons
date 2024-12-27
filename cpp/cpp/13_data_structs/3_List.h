#pragma once

#include <iostream>
#include <cassert>
#include <sstream>
#include <string>
#include <iostream>
#include <cassert>


template <typename T>
struct Node
{
    Node* nextNode;
    Node* prevNodeNode;
    T info;

    Node(const T& data) : nextNode(nullptr), prevNodeNode(nullptr), info(data)
    {
    }
};


template <typename T>
class Iter
{
protected:
    using pointerNode = Node<T>*;
    using referenceNode = Node<T>&;
    pointerNode _ptr;

public:
    // Using
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t; // size_t
    using pointer = T*;
    using reference = T&;

    // Constructors
    Iter() : _ptr(nullptr)
    {
    }

    Iter(const pointerNode ptr) : _ptr(ptr)
    {
    }

    Iter(referenceNode cur) : _ptr(cur)
    {
    }

    // Destructors
    ~Iter() = default;

    // Operators
    Iter& operator++()
    {
        _ptr = _ptr->nextNode;
        return *this;
    }

    Iter operator++(int)
    {
        Iter tmp = *this;
        _ptr = _ptr->nextNode;
        return tmp;
    }

    Iter& operator--()
    {
        _ptr = _ptr->prevNode;
        return *this;
    }

    Iter operator--(int)
    {
        Iter tmp = *this;
        _ptr = _ptr->prevNode;
        return tmp;
    }

    reference operator*() { return _ptr->info; }
    pointer operator->() { return &(_ptr->info); }

    // Boolean Operators
    friend bool operator==(const Iter& a, const Iter& b) { return a._ptr == b._ptr; }
    friend bool operator!=(const Iter& a, const Iter& b) { return a._ptr != b._ptr; }
};

template <typename T>
class RIter : public Iter<T>
{
public:
    //using
    using pointerNode = Node<T>*;
    using referenceNode = Node<T>&;
    // Constructors
    RIter() : Iter<T>::_ptr(nullptr)
    {
    }

    RIter(const pointerNode ptr) : Iter<T>::Iter(ptr)
    {
    }

    // Operators
    RIter<T>& operator++()
    {
        Iter<T>::_ptr = this->_ptr->prevNode;
        return *this;
    }

    RIter<T> operator++(int)
    {
        RIter _tmp = *this;
        Iter<T>::_ptr = this->_ptr->prevNode;
        return _tmp;
    }
};

template <typename T>
class AbstractContainer
{
public:
    virtual ~AbstractContainer() = 0; //+
    virtual T& Front() = 0; //+
    virtual T& Back() = 0; //+
    virtual void Push_Back(const T& item) = 0; //+
    virtual T Pop_Back() = 0; //+
    virtual void Extend(const AbstractContainer<T>& container) = 0;
    virtual size_t Size() const = 0; //+
    virtual bool Empty() const = 0; //+
    virtual void Clear() = 0; //+
    virtual const Iter<T> begin() const = 0; //+
    virtual const Iter<T> end() const = 0; //+
    virtual void Assign(std::initializer_list<T>& items) = 0; //+
    virtual T& At(const size_t position) const = 0; //+

    AbstractContainer<T>& operator=(const AbstractContainer<T>& container)
    {
        Clear();
        Extend(container);
        return *this;
    }
    friend bool operator==(AbstractContainer<T>& lhs, AbstractContainer<T>& rhs)
    {
        if (lhs.Size() != rhs.Size())
            return false;
        auto lhsIter = lhs.begin();
        auto rhsIter = rhs.begin();
        while (lhsIter != lhs.end() && rhsIter != rhs.end())
        {
            if (*lhsIter != *rhsIter)
                return false;
            ++lhsIter;
            ++rhsIter;
        }
        return true;
    }
    friend bool operator!=(AbstractContainer<T>& lhs, AbstractContainer<T>& rhs) { return !(lhs == rhs); }
};

template <typename T>
AbstractContainer<T>:: ~AbstractContainer() = default;

template <typename T>
class List : public AbstractContainer<T>
{
private:
    size_t count = 0;
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;

public:
    List() = default;
    List(size_t initialSize) : List()
    {
        for (size_t i = 0; i < initialSize; ++i)
            List<T>::Push_Back(T());
    }
    List(const T array[], size_t arrayLength) : List()
    {
        for (size_t i = 0; i < arrayLength; ++i)
            List<T>::Push_Back(array[i]);
    }
    List(const List<T>& sourceList) : List()
    {
        Node<T>* tmp = sourceList.head;
        for (size_t i = 0; i < sourceList.count; ++i)
        {
            List<T>::Push_Back(tmp->info);
            tmp = tmp->nextNode;
        }
    }
    List(List<T>&& otherList) noexcept
    {
        head = otherList.head;
        tail = otherList.tail;
        count = otherList.count;
        otherList.head = nullptr;
        otherList.tail = nullptr;
        otherList.count = 0;
    }
    List(const char* str)
    {
        for (size_t i = 0; i < strlen(str); ++i) {
            List<T>::Push_Back(str[i]);
        }
        List<T>::Push_Back('\0');
    }
    List(std::initializer_list<T> source) : List()
    {
        for (const T& item : source)
            List<T>::Push_Back(item);
    }
    ~List() override
    {
        List<T>::Clear();
    }

    void Clear() override
    {
        while (head != nullptr)
        {
            Node<T>* tmp = head;
            head = head->nextNode;
            delete tmp;
        }
        tail = nullptr;
        count = 0;
    }

    T& At(size_t index) const override
    {
        if (index >= count)
        {
            return tail->info;
        }
        Node<T>* tmp = head;
        for (size_t i = 0; i < index; ++i)
        {
            tmp = tmp->nextNode;
        }
        return tmp->info;
    }
    void Resize(size_t newSize)
    {
        while (count != newSize)
        {
            if (count < newSize)
            {
                Push_Back(T());
            }
            else
            {
                Pop_Back();
            }
        }
    }
    void Assign(size_t newSize, const T& value)
    {
        Clear();
        for (size_t i = 0; i < newSize; ++i)
        {
            Push_Back(value);
        }
    }
    size_t Size() const override
    {
        return count;
    }
    bool Empty() const override
    {
        return count == 0;
    }
    void Swap(List<T>& otherList)
    {
        std::swap(head, otherList.head);
        std::swap(tail, otherList.tail);
        std::swap(count, otherList.count);
    }
    void Push_Back(const T& value) override
    {
        Node<T>* newNode = new Node<T>(value);
        if (count == 0)
        {
            head = tail = newNode;
        }
        else
        {
            newNode->prevNodeNode = tail;
            tail->nextNode = newNode;
            tail = newNode;
        }
        count++;
    }
    T Pop_Back() override
    {
        if (count == 0) return T();

        Node<T>* lastNode = tail;
        T returnValue = lastNode->info;
        tail = tail->prevNodeNode;
        if (tail) tail->nextNode = nullptr;
        else head = nullptr;
        delete lastNode;
        count--;
        return returnValue;
    }
    void PushFront(const T& value)
    {
        Node<T>* newNode = new Node<T>(value);

        if (count == 0) head = tail = newNode;

        newNode->nextNode = head;
        head->prevNodeNode = newNode;
        head = newNode;

        count++;
    }
    T PopFront()
    {
        if (count == 0) return T();

        Node<T>* firstNode = head;
        T returnValue = firstNode->info;

        head = head->nextNode;
        if (head) head->prevNodeNode = nullptr;
        else tail = nullptr;

        delete firstNode;
        count--;

        return returnValue;
    }
    static bool IsEqual(const List<T>& lhs, const List<T>& rhs)
    {
        if (lhs.count != rhs.count)
        {
            return false;
        }
        Node<T>* tmp1 = lhs.head;
        Node<T>* tmp2 = rhs.head;
        for (size_t i = 0; i < lhs.count; ++i)
        {
            if (tmp1->info != tmp2->info)
            {
                return false;
            }
            tmp1 = tmp1->nextNode;
            tmp2 = tmp2->nextNode;
        }
        return true;
    }
    friend bool operator==(const List& lhs, const List& rhs) { return IsEqual(lhs, rhs); }
    friend bool operator!=(const List& lhs, const List& rhs) { return !(lhs == rhs); }
    friend bool operator<(const List& lhs, const List& rhs)
    {
        if (lhs.Size() < rhs.Size()) return true;
        if (lhs.Size() > rhs.Size()) return false;
        Node<T>* tmp1 = lhs.head;
        Node<T>* tmp2 = rhs.head;
        while (tmp1 != nullptr && tmp2 != nullptr)
        {
            if (tmp1->info < tmp2->info) return true;
            if (tmp1->info > tmp2->info) return false;
            tmp1 = tmp1->nextNode;
            tmp2 = tmp2->nextNode;
        }
        return false;
    }
    friend bool operator>(const List& lhs, const List& rhs) { return rhs < lhs; }
    friend bool operator<=(const List& lhs, const List& rhs) { return !(rhs < lhs); }
    friend bool operator>=(const List& lhs, const List& rhs) { return !(lhs < rhs); }
    friend std::istream& operator>>(std::istream& input, List& list)
    {
        T element;
        size_t index = 0;
        while (input >> element && index < list.Size()) list[index++] = element;
        return input;
    }
    friend std::ostream& operator<<(std::ostream& output, const List<T>& list)
    {
        for (size_t i = 0; i < list.Size(); ++i)
            output << list.At(i) << " ";
        return output;
    }
    List<T>& operator=(const List<T>& sourceList)
    {
        if (this == &sourceList) return *this;
            Clear();
        for (size_t i = 0; i < sourceList.Size(); ++i)
            Push_Back(sourceList.At(i));
        return *this;
    }
    T& operator[](size_t position)
    {
        return this->At(position);
    }
    bool Contains(const T& listValue)
    {
        for (size_t i = 0; i < count; ++i)
                if (At(i) == listValue) return true;
        return false;
    } 
    size_t Count(const T& listValue)
    {
        size_t cnt = 0;
        for (size_t i = 0; i < count; ++i)
                if (At(i) == listValue) cnt++;
        return cnt;
    }
    Iter<T> begin() { return Iter<T>(head); }
    Iter<T> end() { return Iter<T>(nullptr); }
    const Iter<T> begin() const override { return Iter<T>(head); }
    const Iter<T> end() const override { return Iter<T>(nullptr); }
    RIter<T> rbegin() { return RIter<T>(tail); }
    RIter<T> rend() { return RIter<T>(nullptr); }
    const RIter<T> rbegin() const { return RIter<T>(tail); }
    const RIter<T> rend() const { return RIter<T>(nullptr); }
    void Assign(Iter<T> begin, Iter<T> end)
    {
        Clear();
        for (auto it = begin; it != end; ++it)
            List<T>::Push_Back(*it);
    }
    T& Front() override { return head->info; } 
    T& Back() override { return tail->info; }
    void Assign(std::initializer_list<T>& items) override
    {
        Clear();
        for (const T& item : items)
            List<T>::Push_Back(item);
    }
    void Extend(const AbstractContainer<T>& container) override
    {
        for (auto it = container.begin(); it != container.end(); ++it)
            List<T>::Push_Back(*it);
    }
    Iter<T> Find(const T& targetValue)
    {
        for (auto iter = begin(); iter != end(); ++iter)
            if (*iter == targetValue) return iter;
        return end();
    }
    void Copy_From(const List<T>& sourceList)
    {
        for (auto iter = sourceList.start(); iter != sourceList.finish(); ++iter)
            Push_Back(*iter);
    }
    Iter<T> Insert(Iter<T> position, const T& value)
    {
        Iter<T> resultIter(nullptr);
        Node<T>* newNode = new Node<T>(value);

        if (position == nullptr)
        {
            Push_Back(value);
            return resultIter;
        }

        for (Node<T>* currentNode = head; currentNode != nullptr; currentNode = currentNode->nextNode)
        {
            if (currentNode == position)
            {
                newNode->nextNode = currentNode;
                newNode->prevNodeNode = currentNode->prevNodeNode;

                (currentNode->prevNodeNode != nullptr) ? currentNode->prevNodeNode->nextNode = newNode : head = newNode;

                currentNode->prevNodeNode = newNode;

                count++;

                Iter<T> newIter(currentNode->nextNode);

                return newIter;
            }
        }

        return resultIter;
    }
    Iter<T> Erase(Iter<T> iter) 
    {
        Iter<T> tmpIter(nullptr);

        for (Node<T>* current = head; current != nullptr; current = current->nextNode)
        {
            if (current == iter)
            {
                const Node<T>* deleteNode = current;

                (current->prevNodeNode != nullptr) ? current->prevNodeNode->nextNode = current->nextNode : head = current->nextNode;
                (current->nextNode != nullptr) ? current->nextNode->prevNodeNode = current->prevNodeNode : tail = current->prevNodeNode;

                count--;

                delete deleteNode;

                Iter<T> tmp_iter(current->nextNode);

                return tmp_iter;
            }
        }
        return tmpIter;
    }
};
