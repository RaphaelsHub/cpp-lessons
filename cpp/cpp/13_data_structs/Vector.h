#pragma once
#include <iostream>
#include <cassert>

template <typename T>
class Iterator
{
protected:
    using pointerNode = T*;
    using referenceNode = T&;
    pointerNode _ptr;
public:
    Iterator() : _ptr(nullptr){}
    Iterator(pointerNode ptr) : _ptr(ptr){}
    Iterator(referenceNode ptr) : _ptr(&ptr){}
    ~Iterator() = default;

    Iterator<T> operator+(size_t n) const
    {
        return Iterator<T>(_ptr + n);
    }
    Iterator<T> operator-(size_t n) const
    {
        return Iterator<T>(_ptr - n);
    }

    
    Iterator& operator++()
    {
        _ptr++;
        return *this;
    }
    Iterator operator++(int)
    {
        Iterator tmp = *this;
        ++(*this);
        return tmp;
    }
    Iterator& operator--()
    {
        _ptr--;
        return *this;
    }
    Iterator operator--(int)
    {
        Iterator tmp = *this;
        --(*this);
        return tmp;
    }

    T& operator*() const { return *_ptr; }
    T* operator->() const { return _ptr; }
    friend bool operator==(const Iterator& a, const Iterator& b) { return a._ptr == b._ptr; }
    friend bool operator!=(const Iterator& a, const Iterator& b) { return a._ptr != b._ptr; }
};

template <typename T>
class ReverseIterator : public Iterator<T>
{
public:
    ReverseIterator() : Iterator<T>(){}
    ReverseIterator(typename Iterator<T>::pointerNode ptr) : Iterator<T>(ptr){}
    ReverseIterator(typename Iterator<T>::referenceNode ptr) : Iterator<T>(ptr){}
    ReverseIterator& operator++()
    {
        this->_ptr--;
        return *this;
    }
    ReverseIterator operator++(int)
    {
        ReverseIterator tmp = *this;
        --(*this);
        return tmp;
    }
    ReverseIterator& operator--()
    {
        this->_ptr++;
        return *this;
    }
    ReverseIterator operator--(int)
    {
        ReverseIterator tmp = *this;
        ++(*this);
        return tmp;
    }
};

template <typename T>
class AbstractContainer
{
public:
    virtual ~AbstractContainer() = default;
    virtual T& Front() = 0;
    virtual T& Back() = 0;
    virtual void Push(const T& item) = 0;
    virtual void Pop() = 0;
    virtual void Extend(const AbstractContainer& container) = 0;
    virtual size_t Size() const = 0;
    virtual bool Empty() const = 0;
    virtual void Clear() = 0;
    virtual const Iterator<T> begin() const = 0;
    virtual const Iterator<T> end() const = 0;
    virtual void Assign(std::initializer_list<T> items) = 0;
    virtual T& At(size_t position) const = 0;

    virtual T& operator[](size_t position) const = 0;
    AbstractContainer& operator=(const AbstractContainer& container)
    {
        if (this == &container) return *this;
        this->Clear();

        for (auto it = container.begin(); it != container.end(); ++it)
            this->Push(*it);
        return *this;
    }

    friend bool operator==(const AbstractContainer& a, const AbstractContainer& b)
    {
        if (a.Size() != b.Size()) return false;
        for (size_t i = 0; i < a.Size(); ++i)
        {
            if (a.At(i) != b.At(i)) return false;
        }
        return true;
    }
    friend bool operator!=(const AbstractContainer& a, const AbstractContainer& b)
    {
        return !(a == b);
    }
};

template <typename T>
class Vector : public AbstractContainer<T>
{
    size_t capacity = 0;
    size_t size = 0;
    T* array = nullptr;

    void Allocate(size_t newCapacity)
    {
        T* newArray = new T[newCapacity];
        for (size_t i = 0; i < size; ++i) { newArray[i] = array[i]; }
        delete[] array;
        array = newArray;
        capacity = newCapacity;
    }

public:
    Vector() : capacity(10), size(0), array(new T[capacity])
    {
    }
    Vector(size_t initialSize) : capacity(initialSize), size(initialSize), array(new T[capacity])
    {
        for (size_t i = 0; i < size; ++i) array[i] = T();
    }
    Vector(const T* arr, size_t arrayLength) : capacity(arrayLength), size(arrayLength), array(new T[capacity])
    {
        for (size_t i = 0; i < size; ++i) array[i] = arr[i];
    }
    Vector(const Vector& sourceVector) : capacity(sourceVector.capacity), size(sourceVector.size),
                                         array(new T[sourceVector.Size()])
    {
        for (size_t i = 0; i < size; ++i) array[i] = sourceVector.array[i];
    }
    Vector(Vector&& otherVector) noexcept : capacity(otherVector.capacity), size(otherVector.size),
                                            array(otherVector.array)
    {
        otherVector.array = nullptr;
        otherVector.size = 0;
        otherVector.capacity = 0;
    }
    ~Vector() override { delete[] array; }

    void Clear() override
    {
        delete[] array;
        array = new T[10];
        size = 0;
        capacity = 10;
    }
    T& At(size_t index) const override
    {
        if (index >= size) return array[size - 1];
        return array[index];
    }
    void Resize(size_t newSize)
    {
        if (newSize > capacity) Allocate(newSize);
        size = newSize;
        for (size_t i = size; i < capacity; ++i) array[i] = T();
    }
    void Assign(size_t newSize, const T& value)
    {
        T* newArray = new T[newSize];
        for (size_t i = 0; i < newSize; ++i) newArray[i] = value;
        delete[] array;
        array = newArray;
        size = newSize;
        capacity = newSize;
    }
    size_t Size() const override { return size; }
    bool Empty() const override { return size == 0; }
    void Swap(Vector& otherVector)
    {
        std::swap(capacity, otherVector.capacity);
        std::swap(size, otherVector.size);
        std::swap(array, otherVector.array);
    }
    static bool IsEqual(const Vector& a, const Vector& b)
    {
        if (a.size != b.size) return false;
        for (size_t i = 0; i < a.size; ++i) { if (a.array[i] != b.array[i]) return false; }
        return true;
    }

    //--------------------------------------------------------------------------------
    friend bool operator==(const Vector& a, const Vector& b)
    {
        if (a.size != b.size) return false;
        for (size_t i = 0; i < a.size; ++i) { if (a.array[i] != b.array[i]) return false; }
        return true;
    }
    friend bool operator!=(const Vector& a, const Vector& b) { return !(a == b); }
    friend bool operator<(const Vector& a, const Vector& b)
    {
        size_t minSize = a.size < b.size ? a.size : b.size;
        for (size_t i = 0; i < minSize; ++i)
        {
            if (a.array[i] < b.array[i]) return true;
            if (a.array[i] > b.array[i]) return false;
        }
        return a.size < b.size;
    }
    friend bool operator>(const Vector& a, const Vector& b) { return b < a; }
    friend bool operator<=(const Vector& a, const Vector& b) { return !(b > a); }
    friend bool operator>=(const Vector& a, const Vector& b) { return !(a < b); }
    friend std::istream& operator>>(std::istream& input, Vector& vector)
    {
        size_t index = 0;
        T value;
        while (input >> value)
        {
            if (index >= vector.capacity) { vector.Allocate(vector.capacity == 0 ? 1 : vector.capacity * 2); }
            if (index >= vector.size) { vector.size++; }
            vector.array[index++] = value;
        }
        return input;
    }
    friend std::ostream& operator<<(std::ostream& output, const Vector& vector)
    {
        for (size_t i = 0; i < vector.size; ++i) { output << vector.array[i] << " "; }
        return output;
    }
    Vector& operator=(const Vector& sourceVector)
    {
        if (this == &sourceVector) return *this;
        delete[] array;
        capacity = sourceVector.capacity;
        size = sourceVector.size;
        array = new T[capacity];
        for (size_t i = 0; i < size; ++i) { array[i] = sourceVector.array[i]; }
        return *this;
    }
    T& operator[](size_t position) const override { return array[position]; }
    bool Contains(const T& vectorValue) const
    {
        for (size_t i = 0; i < size; ++i) { if (array[i] == vectorValue) return true; }
        return false;
    }
    size_t Count(const T& vectorValue) const
    {
        size_t count = 0;
        for (size_t i = 0; i < size; ++i) { if (array[i] == vectorValue) ++count; }
        return count;
    }

    //--------------------------------------------------------------------------------
    Vector(std::initializer_list<T> source)
    {
        for (auto& item : source)
        {
            if (size >= capacity) Allocate(capacity == 0 ? 1 : capacity * 2);
            array[size++] = item;
        }
    }
    Vector(Iterator<T> begin, Iterator<T> end)
    {
        for (auto it = begin; it != end; ++it)
        {
            if (size >= capacity) Allocate(capacity == 0 ? 1 : capacity * 2);
            array[size++] = *it;
        }
    }
    Vector(ReverseIterator<T> begin, ReverseIterator<T> end)
    {
        for (auto it = begin; it != end; ++it)
        {
            if (size >= capacity) Allocate(capacity == 0 ? 1 : capacity * 2);
            array[size++] = *it;
        }
    }
    void Assign(Iterator<T> begin, Iterator<T> end)
    {
        T* newArray = new T[capacity];
        size_t newSize = 0;
        for (auto it = begin; it != end; ++it)
        {
            if (newSize >= capacity) Allocate(capacity == 0 ? 1 : capacity * 2);
            newArray[newSize++] = *it;
        }
        size = newSize;
        delete[] array;
        array = newArray;
    }
    Iterator<T> begin()
    {
        if (size == 0) return Iterator<T>(nullptr);
        return Iterator<T>(array);
    }
    Iterator<T> end() { return Iterator<T>(array + size); }
    const Iterator<T> begin() const override
    {
        if (size == 0) return Iterator<T>(nullptr);
        return Iterator<T>(array);
    }
    const Iterator<T> end() const override { return Iterator<T>(array + size); }
    ReverseIterator<T> rbegin() { return ReverseIterator<T>(array + size - 1); }
    ReverseIterator<T> rend() { return ReverseIterator<T>(array - 1); }
    const ReverseIterator<T> rbegin() const { return ReverseIterator<T>(array + size - 1); }
    const ReverseIterator<T> rend() const { return ReverseIterator<T>(array - 1); }
    
    //--------------------------------------------------------------------------------
    T& Front() override { return array[0]; }
    T& Back() override { return array[size - 1]; }
    void Push(const T& item) override
    {
        if (size >= capacity) Allocate(capacity == 0 ? 1 : capacity * 2);
        array[size++] = item;
    }
    void Pop() override
    {
        if (size == 0) return;
        --size;
        array[size] = T();
    }
    void Extend(const AbstractContainer<T>& container) override
    {
        for (size_t i = 0; i < container.Size(); ++i)
        {
            if (size >= capacity) Allocate(capacity == 0 ? 1 : capacity * 2);
            array[size++] = container.At(i);
        }
    }
   void Assign(std::initializer_list<T> items) override
    {
        Clear();
        for (auto& item : items)
        {
            if (size >= capacity) Allocate(capacity == 0 ? 1 : capacity * 2);
            array[size++] = item;
        }
    }
    
    //--------------------------------------------------------------------------------
    Vector (const char *str)
    {
        for (int i = 0; str[i] != '\0'; i++)
        {
            if (size >= capacity) Allocate(capacity == 0 ? 1 : capacity * 2);
            array[size++] = str[i];
        }
        Push('\0');
    }
    Iterator<T> Find(const T& value)
    {
        for (size_t i = 0; i < size; ++i)
            if (array[i] == value) return Iterator<T>(array + i);
        return end();
    }
    Iterator<T> Insert(Iterator<T> iter, const T& value)
    {
        if (size >= capacity) 
            Allocate(capacity == 0 ? 1 : capacity * 2);

        size_t index = 0;
        for (Iterator<T> it = begin(); it != end(); ++it, ++index)
            if (it == iter)
                break;
        for (size_t i = size; i > index; --i)
            array[i] = array[i - 1];

        array[index] = value;
        ++size;
        return Iterator<T>(array + index);
    }


    Iterator<T> Erase(Iterator<T> position)
    {
        size_t index = 0;
        for (Iterator<T> it = begin(); it != end(); ++it, ++index)
            if (it == position) 
                break;

        for (size_t i = index; i < size - 1; ++i)
        {
            array[i] = array[i + 1];
        }

        --size;

        if (index < size)
            return Iterator<T>(array + index);  
        else
            return Iterator<T>(array + size);  
    }
    
    Iterator<T> Erase(Iterator<T> first, Iterator<T> last)
    {
        size_t start_index = 0;
        size_t end_index = 0;
    
        for (Iterator<T> it = begin(); it != end(); ++it, ++start_index)
        {
            if (it == first) break;
        }
        for (Iterator<T> it = begin(); it != end(); ++it, ++end_index)
        {
            if (it == last) break;
        }

        size_t num_to_remove = end_index - start_index;

        for (size_t i = start_index; i < size - num_to_remove; ++i)
        {
            array[i] = array[i + num_to_remove];
        }

        size -= num_to_remove;

        if (start_index < size)
        {
            return Iterator<T>(array + start_index);
        }
        else
        {
            return Iterator<T>(array + size);
        }
    }
};

// int main()
// {
//     Vector<int> v{0, 1, 2, 3, 4, 5, 6, 7};
//
//     v.Push(8);
//     v.Push(9);
//
//     for (int n : v)
//         std::cout << n << " ";
//     std::cout << "\n";
//
//     v.Pop();
//
//     v.Erase(v.begin());
//
//     v.Insert(v.end(), 10);
//
//     v.Erase(v.begin() + v.Size() - 1, v.end());
//
//     for (auto it = v.begin(); it != v.end();)
//     {
//         if (*it % 2)
//             it = v.Erase(it);
//         else
//             ++it;
//     }
//
//     for (int n : v)
//         std::cout << n << " ";
// }
