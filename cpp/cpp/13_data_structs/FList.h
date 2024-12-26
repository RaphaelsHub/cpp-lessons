#include <iostream>
#include <sstream>
#include <iterator>
#include <cassert>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <sstream>
#include <string.h>

template <typename U>
class Node
{
public:
    Node* next;
    U info;
    Node(U data) : next(nullptr), info(std::move(data)) {}
};

//4 лаба
template <typename U>
class Iter
{
private:
    using iterator_category = std::forward_iterator_tag;
    using value_type = U;
    using difference_type = std::ptrdiff_t;
    Node<U> *ptr;

    template <typename> 
    friend class FList;
public:
    Iter() : ptr(nullptr) {}
    Iter(Node<U> *ptr) : ptr(ptr) {}
    Iter(Node<U> &ptr) : ptr(ptr) {}
    ~Iter() = default;

    Iter operator++(int)
    {
        Iter tmp = *this;
        ++(*this);
        return tmp;
    }
    Iter& operator++()
    {
        ptr = ptr->next;
        return *this;
    }
    
    U* operator->() { return &ptr->info; }
    U& operator*() { return ptr->info; }
    friend bool operator==(const Iter& a, const Iter& b) { return a.ptr == b.ptr; }
    friend bool operator!=(const Iter& a, const Iter& b) { return !(a.ptr == b.ptr); }
};


//5 лаба
template <typename T>
class abstract_data_t
{
public:
    virtual ~abstract_data_t() = 0;
    virtual T& Front() = 0;
    virtual T& Back() = 0;
    virtual void Push(const T& a) = 0;
    virtual T Pop() = 0;
    virtual void Extend(const abstract_data_t<T>& a) = 0;
    virtual size_t Size() const = 0;
    virtual bool Empty() const = 0;
    virtual void Clear() = 0;
    virtual Iter<T> begin() const = 0;
    virtual Iter<T> end() const = 0;
    virtual void Assign(std::initializer_list<T>& a) = 0;
    virtual T& At(const size_t index) const = 0;

    abstract_data_t<T>& operator=(const abstract_data_t<T>& list)
    {
        Clear();
        Extend(list);
        return *this;
    }

    friend bool operator==(abstract_data_t<T>& l, abstract_data_t<T>& r)
    {
        if (l.Size() != r.Size())
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
    friend bool operator!=(abstract_data_t<T>& l, abstract_data_t<T>& r) { return !(l == r); }
};

template <typename T>
inline abstract_data_t<T>::~abstract_data_t()
= default;

template <typename U>
class FList: public abstract_data_t<U>
{
private:
    size_t count = 0;
    Node<U>* head = nullptr;
    Node<U>* tail = nullptr;
public:
    // 1 и 2 лаба
    // 1 и 2 лаба
    FList() = default;
    FList(const size_t count) : FList()
    {
        for (size_t i = 0; i < count; ++i)
            FList<U>::Push(U());
    }
    FList(const char* a)
    {
        for (size_t i = 0; i < strlen(a); ++i) {
            Push(a[i]); 
        }
        Push('\0');
    }
    FList(const U array[], const size_t length) : FList()
    {
        for (size_t i = 0; i < length; ++i)
            FList<U>::Push(array[i]);
    }
    FList(const FList<U>& source) : FList()
    {
        Node<U> *tmp = source.head;
        for(size_t i = 0; i<source.Size(); i++)
        {
            FList<U>::Push(tmp->info);
            tmp = tmp->next;
        }
    }
    ~FList() override
    {
        FList<U>::Clear();
    }
    void Clear() override
    {
        while (!Empty())
            Pop();
    }
    U& At(const size_t index) const override
    {
        if (index >= count)
            return tail->info;
        Node<U> *tmp = head;
        for (size_t i = 0; i < index; ++i)
            tmp = tmp->next;

        return tmp->info;
    }
    void Resize(const size_t Size)
    {
        while (count != Size)
            if (count < Size) Push(U());
            else Pop();
    }
    void Assign(const size_t Size, const U& a)
    {
        Clear();
        for (size_t i = 0; i < Size; ++i)
            Push(a);
    }
    size_t Size() const override { return count; }
    bool Empty() const override { return count == 0; }
    void Swap (FList<U>& other)
    {
        std::swap(count, other.count);
        std::swap(head, other.head);
        std::swap(tail, other.tail);
    }
    static bool IsEqual(const FList<U>& a, const FList<U>& b)
    {
        if (a.Size() != b.Size())
            return false;

        Node<U> *tmp1 = a.head;
        Node<U> *tmp2 = b.head;
        
        for(auto i = 0; i<a.Size(); i++)
        {
            if(tmp1->info != tmp2->info)
                return false;
            tmp1 = tmp1->next;
            tmp2 = tmp2->next;
        }
        return true;
    }

    //5 лаба повсюде где слово override в конце это из 5 лабы
    void Push(const U& data) override
    {
        Node<U>* newNode = new Node<U>(data);
        
        if (!count)
            tail = head = newNode;
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }
    U Pop() override
    {
        if (!head) return U(); 
        if (!head->next)
        {
            U data = head->info;
            delete head;
            tail = nullptr;
            head = nullptr;
            count--;
            return data;
        }

        Node<U>* current = head;
        while (current->next->next) current = current->next;

        U data = current->next->info;
        delete current->next; 
        current->next = nullptr;
        tail = current;
        count--;
        return data;
    } 
    U& Front() override { return head->info; }
    U& Back() override { return tail->info; }
    const U& Front() const { return head->info; }
    const U& Back() const { return tail->info; }
    void Extend(const abstract_data_t<U>& other) override 
    {
        for (auto it = other.begin(); it != other.end(); ++it)
            Push(*it);
    }
    void Assign(std::initializer_list<U>& a) override
    {
        Clear();
        for (const auto& elem : a)
            Push(elem);
    }
    void Extend(const FList<U>& other) 
    {
        for (auto it = other.begin(); it != other.end(); ++it)
            Push(*it);
    }
    

    
    //3 лаба
    bool Contains(const U& listValue)
    {
        for (int i = 0; i < count; ++i)
            if (At(i) == listValue) return true;
        return false;
    }
    size_t Count(const U& listValue)
    {
        size_t count = 0;
        for (int i = 0; i < count; ++i)
            if (At(i) == listValue) count++;

        return count;
    }
    FList<U>& operator=(const FList<U>& source)
    {
        if (this == &source)
            return *this;
        this->Clear();

        Node<U> *tmp = source.head;
        for(auto i = 0; i<source.Size(); i++)
        {
            Push(tmp->info);
            tmp = tmp->next;
        }
        return *this;
    }
    friend bool operator==(const FList& lhs, const FList& rhs) { return FList<U>::IsEqual(lhs, rhs); }
    friend bool operator!=(const FList& lhs, const FList& rhs) { return !(lhs == rhs); }
    friend bool operator>(const FList<U>& lhs, const FList<U>& rhs) {
        if (lhs.Size() > rhs.Size()) return true;
        if (lhs.Size() < rhs.Size()) return false;

        auto tmp1 = lhs.head;
        auto tmp2 = rhs.head;

        while (tmp1 && tmp2) {
            if (tmp1->info > tmp2->info)
                return true;
            if (tmp1->info < tmp2->info)
                return false;

            tmp1 = tmp1->next;
            tmp2 = tmp2->next;
        }

        return false; // Списки равны
    }
    friend bool operator<(const FList<U>& lhs, const FList<U>& rhs) {
        // Сравнение по размеру
        if (lhs.Size() < rhs.Size()) return true;
        if (lhs.Size() > rhs.Size()) return false;

        // Сравнение по содержимому
        auto tmp1 = lhs.head;
        auto tmp2 = rhs.head;

        while (tmp1 && tmp2) {
            if (tmp1->info < tmp2->info)
                return true;
            if (tmp1->info > tmp2->info)
                return false;

            tmp1 = tmp1->next;
            tmp2 = tmp2->next;
        }

        return false; // Списки равны
    }
    friend bool operator<=(const FList& lhs, const FList& rhs) { return !(lhs > rhs); }
    friend bool operator>=(const FList& lhs, const FList& rhs) { return !(lhs < rhs); }
    friend std::istream& operator>>(std::istream& input, FList& list)
    {
        U element;
        size_t index = 0;
        Node<U> *tmp = list.head;
        
        while (input >> element && index < list.count)
        {
            tmp->info = element;
            tmp = tmp->next;
            index++;
        }
        return input;
    }
    friend std::ostream& operator<<(std::ostream& output, const FList<U>& list)
    {
        Node<U> *tmp = list.head;
        for (int i =0; i<list.Size(); i++)
        {
            output << tmp->info << " ";
            tmp = tmp->next;
        }
        return output;
    }
    //оператора [] у forward_list нет

    //4 лаба
    FList(const Iter<U>& start, const Iter<U>& stop) : FList() { 
        for (auto it = start; it != stop; ++it)
           FList<U>::Push(*it);
    }
    FList(std::initializer_list<U> source) : FList()
    {
        for (auto& elem : source)
            Push(elem);
    }
    void Assign(const Iter<U>& begin, const Iter<U>& end)
    {
        Clear();
        for (auto it = begin; it != end; ++it)
            Push(*it);
    }
    Iter<U> begin() { return Iter<U>(head); }
    Iter<U> end()  { return Iter<U>(nullptr); }
    Iter<U> begin() const override { return Iter<U>(head); }
    Iter<U> end() const override { return Iter<U>(nullptr); }
    //6 лаба
    Iter<U> Find(const U& value)
    {
        for (auto it = begin(); it != end(); ++it)
            if (*it == value) return it;
        return end();
    }
    Iter<U> Insert(Iter<U> pos, const U& value)
    {
        Node<U>* newNode = new Node<U>(value);
        if (pos == begin()) // Inserting at the beginning
        {
            newNode->next = head;
            head = newNode;
            if (tail == nullptr) tail = newNode; // Handle empty list case
        }
        else
        {
            Node<U>* current = head;
            while (current->next != pos.ptr) // Traverse to find the preceding node
                current = current->next;
            newNode->next = current->next;
            current->next = newNode;
            if (newNode->next == nullptr) tail = newNode; // Handle tail case
        }
        ++count;
        return Iter<U>(newNode);
    }
    Iter<U> Erase(Iter<U> pos)
    {
        if (head == nullptr || pos == end()) // Empty list or invalid position
            return end();

        if (pos == begin()) // Removing the head
        {
            Node<U>* toDelete = head;
            head = head->next;
            delete toDelete;
            --count;
            if (count == 0) tail = nullptr; // Handle empty list case
            return Iter<U>(head);
        }

        Node<U>* current = head;
        while (current->next != pos.ptr) // Traverse to find the preceding node
            current = current->next;

        Node<U>* toDelete = current->next;
        current->next = toDelete->next;
        if (toDelete == tail) tail = current; // Handle tail case
        delete toDelete;
        --count;

        return Iter<U>(current->next);
    }

};


int main()
{
    FList<int> fl1{1, 2, 3, 4, 5};
    FList<int> fl2(fl1.begin(), fl1.end());

    for (; !fl1.Empty(); fl1.Pop())
    {
        std::cout << fl1.Front() << " ";
    }

    assert(fl1.Empty());

    auto itbegin = fl2.begin();
    fl2.Insert(itbegin, 0);
    fl2.Pop();
    assert(0 == fl2.Front());
    for (; !fl2.Empty(); fl2.Pop())
    {
        std::cout << fl2.Back() << " ";
    }
    
}

