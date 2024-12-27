#pragma once
#include <iostream>
#include <cassert>

template <typename T>
class ForwardIterator
{
protected:
    T* _ptr;
public:
    ForwardIterator() : _ptr(nullptr) {}
    ForwardIterator(T* ptr) : _ptr(ptr) {}
    ForwardIterator(T& ptr) : _ptr(&ptr) {}
    ~ForwardIterator() = default;

    ForwardIterator operator+(size_t n) const { return ForwardIterator(_ptr + n); }
    ForwardIterator operator-(size_t n) const { return ForwardIterator(_ptr - n); }
    ForwardIterator& operator++()
    {
        ++_ptr;
        return *this;
    }
    ForwardIterator operator++(int)
    {
        ForwardIterator tmp = *this;
        ++(*this);
        return tmp;
    }
    ForwardIterator& operator--()
    {
        --_ptr;
        return *this;
    }
    ForwardIterator operator--(int)
    {
        ForwardIterator tmp = *this;
        --(*this);
        return tmp;
    }

    T& operator*() const { return *_ptr; }
    T* operator->() const { return _ptr; }
    
    T* GetPointer () { return _ptr; }
    
    friend bool operator==(const ForwardIterator& a, const ForwardIterator& b) { return a._ptr == b._ptr; }
    friend bool operator!=(const ForwardIterator& a, const ForwardIterator& b) { return a._ptr != b._ptr; }
};

template <typename T>
class BackwardIterator
{
    T* _ptr;
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;
    
    BackwardIterator() : _ptr(nullptr) {}
    BackwardIterator(T* ptr) : _ptr(ptr) {}
    BackwardIterator(T& ptr) : _ptr(&ptr) {}
    ~BackwardIterator() = default;

    BackwardIterator& operator++()
    {
        --this->_ptr;
        return *this;
    }

    BackwardIterator operator++(int)
    {
        BackwardIterator tmp = *this;
        --(*this);
        return tmp;
    }

    BackwardIterator& operator--()
    {
        ++this->_ptr;
        return *this;
    }

    BackwardIterator operator--(int)
    {
        BackwardIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    T& operator*() const { return *_ptr; }
    T* operator->() const { return _ptr; }

    friend bool operator==(const BackwardIterator& a, const BackwardIterator& b) { return a._ptr == b._ptr; }
    friend bool operator!=(const BackwardIterator& a, const BackwardIterator& b) { return a._ptr != b._ptr; }
    friend bool operator==(const BackwardIterator& lhs, const ForwardIterator<T>& rhs) {
        return lhs._ptr == rhs;
    }
};

template <typename T>
class AbstractContainer
{
public:
    virtual ~AbstractContainer() = default;
    virtual T& Front() = 0;
    virtual T& Back() = 0;
    virtual void Push_Back(const T& item) = 0;
    virtual void Push_Front(const T& item) = 0;
    virtual void Pop_Back() = 0;
    virtual void Pop_Front() = 0;
    virtual void Extend(const AbstractContainer& container) = 0;
    virtual size_t Size() const = 0;
    virtual bool Empty() const = 0;
    virtual void Clear() = 0;
    virtual const ForwardIterator<T> begin() const = 0;
    virtual const ForwardIterator<T> end() const = 0;
    virtual void Assign(std::initializer_list<T> items) = 0;
    virtual T& At(size_t position) const = 0;
    virtual T& operator[](size_t position) const = 0;

    AbstractContainer& operator=(const AbstractContainer& container)
    {
        if (this == &container) return *this;
        this->Clear();

        for (T& it : container)
            this->Push_Back(it);
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
    size_t currentCapacity;
    size_t currentSize;
    T* dataArray = nullptr;

    void Allocate(size_t newCapacity)
    {
        T* tempArray = new T[newCapacity];
        if (dataArray != nullptr)
        {
            CopyElements(tempArray, dataArray, currentSize);
            delete[] dataArray;
        }
        dataArray = tempArray;
        currentCapacity = newCapacity;
    }
    void CopyElements(T* destination, const T* source, size_t count) const
    {
        size_t i = 0;
        while (i < count)
        {
            destination[i] = source[i];
            i++;
        }
    }
    void InitializeArray(T* array, size_t count, const T& value = T()) const
    {
        size_t i = 0;
        while (i < count)
        {
            array[i] = value;  
            i++;            
        }
    }
    void EnsureCapacity()
    {
        if (currentSize >= currentCapacity) { Allocate(currentCapacity == 0 ? 1 : currentCapacity * 2); }
    }
    virtual size_t GetIndex(ForwardIterator<T> ForwardIterator)
    {
        size_t index = 0;
        for (auto it = begin(); it != end(); ++it, ++index)
            if (it == ForwardIterator)
                return index;
        throw std::out_of_range("ForwardIterator out of range");
    }
public:
    Vector() : currentCapacity(2), currentSize(0), dataArray(new T[currentCapacity]){}
    Vector(size_t initialSize) : currentCapacity(initialSize), currentSize(initialSize), dataArray(new T[currentCapacity]) { InitializeArray(dataArray, currentSize); }
    Vector(const T* sourceArray, size_t arrayLength) : currentCapacity(arrayLength), currentSize(arrayLength), dataArray(new T[currentCapacity]) { CopyElements(dataArray, sourceArray, currentSize); }
    Vector(const Vector& sourceVector) : currentCapacity(sourceVector.currentCapacity), currentSize(sourceVector.currentSize), dataArray(new T[sourceVector.currentCapacity]) { CopyElements(dataArray, sourceVector.dataArray, currentSize); }
    Vector(Vector&& otherVector) noexcept : currentCapacity(otherVector.currentCapacity), currentSize(otherVector.currentSize), dataArray(otherVector.dataArray)
    {
        otherVector.dataArray = nullptr;
        otherVector.currentSize = 0;
        otherVector.currentCapacity = 0;
    }
    ~Vector() override { delete[] dataArray; }
    virtual void Resize(size_t newSize)
    {
        if (newSize > currentCapacity) Allocate(newSize);
        currentSize = newSize;
        InitializeArray(dataArray + currentSize, currentCapacity - currentSize);
    }
    void Clear() override
    {
        delete[] dataArray;
        dataArray = new T[2];
        currentSize = 0;
        currentCapacity = 2;
    }
    size_t Size() const override { return currentSize; }
    bool Empty() const override { return currentSize == 0; }
    T& At(size_t index) const override { return index >= currentSize ? dataArray[this->currentSize - 1] : dataArray[index]; }
    void Swap(Vector& otherVector)
    {
        std::swap(currentCapacity, otherVector.currentCapacity);
        std::swap(currentSize, otherVector.currentSize);
        std::swap(dataArray, otherVector.dataArray);
    }
    virtual void Assign(size_t newSize, const T& value)
    {
        T* tempArray = new T[newSize];
        InitializeArray(tempArray, newSize, value);
        delete[] dataArray;
        dataArray = tempArray;
        currentSize = newSize;
        currentCapacity = newSize;
    }
    static bool IsEqual(const Vector& a, const Vector& b)
    {
        if (a.currentSize != b.currentSize) return false;
        size_t i = 0;
        while (i < a.currentSize) {if (a.dataArray[i] != b.dataArray[i]) return false; i++;}
        return true;
    }
    friend bool operator==(const Vector& a, const Vector& b)
    {
        if (a.currentSize != b.currentSize) return false;
        size_t i = 0;
        while (i < a.currentSize)
        {
            if (a.dataArray[i] != b.dataArray[i]) return false;
            ++i;
        }
        return true;
    }
    friend bool operator!=(const Vector& a, const Vector& b) { return !(a == b); }
    friend bool operator<(const Vector& a, const Vector& b)
    {
        size_t minSize = a.currentSize < b.currentSize ? a.currentSize : b.currentSize;
        size_t i = 0;
        while (i < minSize)
        {
            if (a.dataArray[i] < b.dataArray[i]) return true;
            if (a.dataArray[i] > b.dataArray[i]) return false;
            ++i;
        }
        return a.currentSize < b.currentSize;
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
            if (index >= vector.currentCapacity)
            {
                vector.Allocate(vector.currentCapacity == 0 ? 1 : vector.currentCapacity * 2);
            }
            if (index >= vector.currentSize)
            {
                ++vector.currentSize;
            }
            vector.dataArray[index++] = value;
        }
        return input;
    }
    friend std::ostream& operator<<(std::ostream& output, const Vector& vector)
    {
        size_t i = 0;
        while (i < vector.currentSize)
        {
            output << vector.dataArray[i] << " ";
            i++;
        }
        return output;
    }
    Vector& operator=(const Vector& sourceVector)
    {
        if (this == &sourceVector) return *this;
        delete[] dataArray;
        currentCapacity = sourceVector.currentCapacity;
        currentSize = sourceVector.currentSize;
        dataArray = new T[currentCapacity];
        CopyElements(dataArray, sourceVector.dataArray, currentSize);
        return *this;
    }
    T& operator[](size_t position) const override { return dataArray[position]; }
    virtual bool Contains(const T& value) const
    {
        size_t i = 0;
        while (i < currentSize)
        {
            if (dataArray[i] == value) return true;
            i++;
        }
        return false;
    }
    virtual size_t Count(const T& value) const
    {
        size_t count = 0;
        size_t i = 0;
        while (i < currentSize)
        {
            if (dataArray[i] == value) ++count;
            ++i;
        }
        return count;
    }
    Vector(std::initializer_list<T> source) : currentSize(0), currentCapacity(0)
    {
        for (auto& item : source)
        {
            EnsureCapacity();
            dataArray[currentSize++] = item;
        }
    }
    Vector(ForwardIterator<T> begin, ForwardIterator<T> end)
    {
        auto it = begin;
        while (it != end)
        {
            EnsureCapacity();
            dataArray[currentSize++] = *it;
            ++it;
        }
    }
    Vector(BackwardIterator<T> begin, BackwardIterator<T> end)
    {
        auto it = begin;
        while (it != end)
        {
            EnsureCapacity();
            dataArray[currentSize++] = *it;
            ++it;
        }
    }
    virtual void Assign(ForwardIterator<T> begin, ForwardIterator<T> end)
    {
        Clear();
        for (auto it = begin; it != end; ++it)
        {
            if (currentSize >= currentCapacity) Allocate(currentCapacity == 0 ? 1 : currentCapacity * 2);
            dataArray[currentSize++] = *it;
        }
    }
    virtual ForwardIterator<T> begin() {return currentSize == 0 ? ForwardIterator<T>(nullptr) : ForwardIterator<T>(dataArray);}
    virtual ForwardIterator<T> end() { return ForwardIterator<T>(dataArray + currentSize); }
    const ForwardIterator<T> begin() const override {return currentSize == 0 ? ForwardIterator<T>(nullptr) : ForwardIterator<T>(dataArray);}
    const ForwardIterator<T> end() const override { return ForwardIterator<T>(dataArray + currentSize); }
    virtual BackwardIterator<T> rbegin() { return BackwardIterator<T>(dataArray + currentSize - 1); }
    virtual BackwardIterator<T> rend() { return BackwardIterator<T>(dataArray - 1); }
    virtual const BackwardIterator<T> rbegin() const { return BackwardIterator<T>(dataArray + currentSize - 1); }
    virtual const BackwardIterator<T> rend() const { return BackwardIterator<T>(dataArray - 1); }
    T& Front() override { return dataArray[0]; }
    T& Back() override { return dataArray[currentSize - 1]; }
    void Push_Back(const T& item) override
    {
        if (currentSize >= currentCapacity) Allocate(currentCapacity == 0 ? 1 : currentCapacity * 2);
        dataArray[currentSize++] = item;
    }
    void Pop_Back() override
    {
        if (currentSize == 0) return;
        --currentSize;
        dataArray[currentSize] = T();
    }
    void Extend(const AbstractContainer<T>& container) override
    {
        for (size_t i = 0; i < container.Size(); ++i)
        {
            if (currentSize >= currentCapacity) Allocate(currentCapacity == 0 ? 1 : currentCapacity * 2);
            dataArray[currentSize++] = container.At(i);
        }
    }
    void Assign(std::initializer_list<T> items) override
    {
        Clear();
        for (const auto& item : items)
        {
            if (currentSize >= currentCapacity) Allocate(currentCapacity == 0 ? 1 : currentCapacity * 2);
            dataArray[currentSize++] = item;
        }
    }
    void Push_Front(const T& item) override
    {
        if (currentSize >= currentCapacity) Allocate(currentCapacity == 0 ? 1 : currentCapacity * 2);
        for (size_t i = currentSize; i > 0; --i) { dataArray[i] = dataArray[i - 1]; }
        dataArray[0] = item;
        ++currentSize;
    }
    void Pop_Front() override
    {
        if (currentSize == 0) return;
        for (size_t i = 0; i < currentSize - 1; ++i)
        {
            dataArray[i] = dataArray[i+1];
        }
        --currentSize;
    }
    Vector (const char *str) : currentSize(0), currentCapacity(2), dataArray(new T[currentCapacity])
    {
        for (int i = 0; str[i] != '\0'; i++)
        {
            if (currentSize >= currentCapacity) Allocate(currentCapacity == 0 ? 1 : currentCapacity * 2);
            dataArray[currentSize++] = str[i];
        }
        if (currentSize >= currentCapacity) Allocate(currentCapacity == 0 ? 1 : currentCapacity * 2);
        dataArray[currentSize++] = '\0';
    }
    
    virtual ForwardIterator<T> Find(const T& value)
    {
        for (size_t i = 0; i < currentSize; ++i)
            if (dataArray[i] == value) return ForwardIterator<T>(dataArray + i);
        return end();
    }
    virtual ForwardIterator<T> Insert(ForwardIterator<T> iter, const T& value)
    {
        if (currentSize >= currentCapacity) 
            Allocate(currentCapacity == 0 ? 1 : currentCapacity * 2);

        size_t index = 0;
        for (ForwardIterator<T> it = begin(); it != end(); ++it, ++index)
            if (it == iter)
                break;
        for (size_t i = currentSize; i > index; --i)
            dataArray[i] = dataArray[i - 1];

        dataArray[index] = value;
        ++currentSize;
        return ForwardIterator<T>(dataArray + index);
    }
    virtual ForwardIterator<T> Erase(ForwardIterator<T> position)
    {
        size_t index = 0;
        for (ForwardIterator<T> it = begin(); it != end(); ++it, ++index)
            if (it == position) 
                break;

        for (size_t i = index; i < currentSize - 1; ++i)
        {
            dataArray[i] = dataArray[i + 1];
        }

        --currentSize;

        if (index < currentSize)
            return ForwardIterator<T>(dataArray + index);  
        else
            return ForwardIterator<T>(dataArray + currentSize);  
    }
    virtual BackwardIterator<T> Erase(BackwardIterator<T> position)
    {
        size_t index = currentSize - 1;
        for (BackwardIterator<T> it = rbegin(); it != rend(); ++it, --index)
            if (it == position) 
                break;

        for (size_t i = index; i < currentSize - 1; ++i)
        {
            dataArray[i] = dataArray[i + 1];
        }

        --currentSize;

        if (index < currentSize)
            return BackwardIterator<T>(dataArray + index);  
        else
            return BackwardIterator<T>(dataArray + currentSize);  
    }



};

template <typename T>
class Deque : public Vector<T>
{
public:
    Deque() = default;
    Deque(size_t initialSize) : Vector<T>(initialSize) {}
    Deque(const T* sourceArray, size_t arrayLength) : Vector<T>(sourceArray, arrayLength) {}
    Deque(const Deque& sourceDeque) = default;
    Deque(Deque&& otherDeque) noexcept : Vector<T>(std::move(otherDeque)) {}
    ~Deque() override = default;
    void Resize (size_t newSize) override { Vector<T>::Resize(newSize); }
    void Clear() override { Vector<T>::Clear(); }
    T& At(size_t index) const override { return Vector<T>::At(index); }
    void Swap(Deque& otherDeque) { Vector<T>::Swap(otherDeque); }
    void Assign(size_t newSize, const T& value) override { Vector<T>::Assign(newSize, value); }
    static bool IsEqual(const Deque& a, const Deque& b) { return Vector<T>::IsEqual(a, b); }
    size_t Size () const override { return Vector<T>::Size(); }
    bool Empty() const override { return Vector<T>::Empty(); }
    bool Contains(const T& value) const override { return Vector<T>::Contains(value); }
    size_t Count(const T& value) const override { return Vector<T>::Count(value); }
    Deque& operator=(const Deque& sourceDeque) { return dynamic_cast<Deque&>(Vector<T>::operator=(sourceDeque)); }
    Deque(std::initializer_list<T> source) : Vector<T>(source) {}
    Deque(ForwardIterator<T> begin, ForwardIterator<T> end) : Vector<T>(begin, end) {}
    Deque(BackwardIterator<T> begin, BackwardIterator<T> end) : Vector<T>(begin, end) {}
    
    void Assign(ForwardIterator<T> begin, ForwardIterator<T> end) override { Vector<T>::Assign(begin, end); }
    ForwardIterator<T> begin() override { return Vector<T>::begin(); }
    ForwardIterator<T> end() override { return Vector<T>::end(); }
    BackwardIterator<T> rbegin() override { return Vector<T>::rbegin(); }
    BackwardIterator<T> rend() override { return Vector<T>::rend(); }
    T& Front() override { return Vector<T>::Front(); }
    T& Back() override { return Vector<T>::Back(); }
    void Push_Back(const T& item) override { Vector<T>::Push_Back(item); }
    void Pop_Back() override { Vector<T>::Pop_Back(); }
    void Extend(const AbstractContainer<T>& container) override { Vector<T>::Extend(container); }
    void Push_Front(const T& item) override { Vector<T>::Push_Front(item); }
    void Pop_Front() override { Vector<T>::Pop_Front(); }
    void Assign(std::initializer_list<T> items) override { Vector<T>::Assign(items); }
    Deque(const char* str) : Vector<T>(str) {}
    ForwardIterator<T> Find(const T& value) override { return Vector<T>::Find(value); }
    ForwardIterator<T> Insert(ForwardIterator<T> iter, const T& value) override { return Vector<T>::Insert(iter, value); }
    ForwardIterator<T> Erase(ForwardIterator<T> position) override { return Vector<T>::Erase(position); }
    BackwardIterator<T> Erase(BackwardIterator<T> position) override { return Vector<T>::Erase(position); }
};
