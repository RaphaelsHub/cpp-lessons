#pragma once

#define TAMPLATE_POINTER_NODE template <typename T> using pointerNode = Node<T> *
#define TEMPLATE_REFERENCE_NODE (template <typename T> using referenceNode = Node<T> &)
#define TEMPLATE_T template <typename T>

TEMPLATE_T
struct Node
{
    T data;
    Node* next;
    Node* prev;

    Node(const T& value) : data(value), next(nullptr), prev(nullptr)
    {
    }
};

// Iterator realization
TEMPLATE_T
class Iterator
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
    Iterator() : _ptr(nullptr)
    {
    }

    Iterator(const pointerNode ptr) : _ptr(ptr)
    {
    }

    Iterator(referenceNode cur) : _ptr(cur)
    {
    }

    // Destructors
    ~Iterator() = default;

    // Operators
    Iterator& operator++()
    {
        _ptr = _ptr->next;
        return *this;
    }

    Iterator operator++(int)
    {
        Iterator tmp = *this;
        _ptr = _ptr->next;
        return tmp;
    }

    Iterator& operator--()
    {
        _ptr = _ptr->prev;
        return *this;
    }

    Iterator operator--(int)
    {
        Iterator tmp = *this;
        _ptr = _ptr->prev;
        return tmp;
    }

    reference operator*() { return _ptr->data; }
    pointer operator->() { return &(_ptr->data); }

    // Boolean Operators
    friend bool operator==(const Iterator& a, const Iterator& b) { return a._ptr == b._ptr; }
    friend bool operator!=(const Iterator& a, const Iterator& b) { return a._ptr != b._ptr; }
};

// rIterator realization
TEMPLATE_T
class rIterator : public Iterator<T>
{
public:
    //using
    using pointerNode = Node<T>*;
    using referenceNode = Node<T>&;
    // Constructors
    rIterator() : Iterator<T>::_ptr(nullptr)
    {
    }

    rIterator(const pointerNode ptr) : Iterator<T>::Iterator(ptr)
    {
    }

    // Operators
    rIterator<T>& operator++()
    {
        Iterator<T>::_ptr = this->_ptr->prev;
        return *this;
    }

    rIterator<T> operator++(int)
    {
        rIterator _tmp = *this;
        Iterator<T>::_ptr = this->_ptr->prev;
        return _tmp;
    }
};