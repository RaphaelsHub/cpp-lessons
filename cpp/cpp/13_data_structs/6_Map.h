#pragma once
#include <iostream>
#include <sstream>
#include <iterator>
#include <cassert>
#include <utility>
#include <algorithm>

#define TEMPLATE_T template <typename T>
#define TEMPLATE_HASH_TABLE template <typename KEY, typename VALUE, typename PAIR = std ::pair <KEY, VALUE>> 

TEMPLATE_T
class Node
{
public:
    Node* next;
    T data;
    Node(T data) : next(nullptr), data(std::move(data)) {}
    friend bool operator==(const Node& a, const Node& b) { return a.data == b.data; }
    friend bool operator!=(const Node& a, const Node& b) { return !(a == b); }
};

TEMPLATE_T
class Iter {
protected:
    Node<T>* ptr_;
public:
    Iter() : ptr_(nullptr) {}
    Iter(Node<T>* ptr) : ptr_(ptr) {}
    Iter(Node<T>& cur) : ptr_(&cur) {}

    Iter& operator++() {
        ptr_ = ptr_->next; 
        return *this;
    }
    Iter operator++(int) {
        Iter tmp = *this;
        ++(*this);
        return tmp;
    }
    T* operator->() const { return &ptr_->data; }
    T& operator*() const { return ptr_->data; }

    friend bool operator==(const Iter& a, const Iter& b) { return a.ptr_ == b.ptr_; }
    friend bool operator!=(const Iter& a, const Iter& b) { return a.ptr_ != b.ptr_; }
};

TEMPLATE_T
class FList
{
private:
    size_t size_ = 0;
    Node<T>* head_ = nullptr;
    Node<T>* tail_ = nullptr;
public:
    FList() = default; 
    FList(const FList& other)
    {
        for (auto& item : other) 
            Push_Back(item);
    } 
    ~FList() { Clear(); } 
    
    Iter<T>begin() { return {head_}; } 
    Iter<T> end() { return {nullptr}; } 
    const Iter<T> begin() const { return {head_}; } 
    const Iter<T> end() const { return {nullptr}; } 
    
    void Push_Back(T data)
    {
        Node<T>* newNode = new Node<T>(data);
        
        if (!size_)
            tail_ = head_ = newNode;
        else
        {
            tail_->next = newNode;
            tail_ = newNode;
        }
        size_++;
    } 
    void Pop_Back() {
        if (!head_) return; 
        if (!head_->next)
        {
            delete head_;
            tail_ = nullptr;
            head_ = nullptr;
            size_--;
            return;
        }

        Node<T>* current = head_;
        while (current->next->next) current = current->next;
        
        delete current->next; 
        current->next = nullptr;
        tail_ = current;
        size_--;
    } 
    size_t Size() const { return size_; } 
    bool Empty() const { return size_ == 0; } 
    bool Contains(const T& a)  
    {
        for (auto it = begin(); it != end(); ++it)
                if (*it == a) return true;
        return false;
    } 
    T& Front() { return head_->data; } 
    T& Back() { return tail_->data; } 
    const T& Front() const { return head_->data; } 
    const T& Back() const { return tail_->data; } 
    void Clear() { for (size_t i = size_; i > 0; i--) Pop_Back(); } 
    Iter<T> Find(const T& elem)
    {
        for (auto it = begin(); it != end(); ++it)
            if (*it == elem) return it;
        return end();
    } 
    Iter<T> Erase(Iter<T> iterator) {
        if (iterator == end()) return end();

        if (iterator == begin()) {
            const Node<T>* target = head_;
            head_ = head_->next;
            Iter<T> tmp = {head_};
            delete target;
            --size_;
            return tmp;
        }

        Node<T>* current = head_;
        while (current->next && Iter<T>(current->next) != iterator) {
            current = current->next;
        }

        if (current->next) {
            const Node<T>* target = current->next;
            current->next = target->next;
            delete target;
            --size_;
        }
        return {current->next};
    }
    static bool AreEqual(const FList& a, const FList& b)
    {
        if (a.Size() != b.Size())
            return false;

        for (auto iter1 = a.begin(), iter2 = b.begin(); iter1 != a.end(); ++iter1, ++iter2)
            if (*iter1 != *iter2)return false;
        return true;
    }  
    friend bool operator==(const FList& a, const FList& b) { return AreEqual(a, b); } 
    friend bool operator!=(const FList& a, const FList& b) { return !(a == b); } 
    FList<T>& operator=(const FList<T>& other)
    {
        if (this == &other)
            return *this;

        this->Clear();
        for (auto it = other.begin(); it != other.end(); ++it)
            this->Push_Back(*it);

        return *this;
    } 
};

template<typename PAIR>
class MapIter {
protected:
    using iterator_category = std::forward_iterator_tag;
    using value_type = Iter<PAIR>; 
    using difference_type = std::ptrdiff_t;

    FList<PAIR>* table; 
    size_t table_size;  
    size_t table_index; 
    Iter<PAIR> list_iterator; 

    void moveToNextValidBucket() {
        while (table_index < table_size && table[table_index].Empty()) {
            ++table_index;
        }
        if (table_index < table_size) {
            list_iterator = table[table_index].begin();
        }
    }

public:
    MapIter() : table(nullptr), table_size(0), table_index(0) {}

    MapIter(FList<PAIR>* table, size_t table_size, size_t table_index = 0)
        : table(table), table_size(table_size), table_index(table_index) {
        moveToNextValidBucket();
    }

    MapIter& operator++() {
        if (table_index < table_size) {
            ++list_iterator; 
            if (list_iterator == table[table_index].end()) {
                ++table_index;
                moveToNextValidBucket(); 
            }
        }
        return *this;
    }
    
    MapIter operator++(int) {
        MapIter temp = *this;
        ++(*this);
        return temp;
    }

    PAIR& operator*() {
        if (table_index < table_size && list_iterator != table[table_index].end()) {
            return *list_iterator;
        }
        throw std::out_of_range("Iterator is out of range or points to an empty list.");
    }

    PAIR* operator->() {
        if (table_index < table_size && list_iterator != table[table_index].end()) {
            return &(*list_iterator);
        }
        return nullptr;
    }

    friend bool operator==(const MapIter& a, const MapIter& b) {
        return a.table == b.table && a.table_index == b.table_index &&
               (a.table_index >= a.table_size || a.list_iterator == b.list_iterator);
    }
    friend bool operator!=(const MapIter& a, const MapIter& b) {
        return !(a == b);
    }
};

template <typename KeyType, typename ValueType>
class AbstractData {
public:
    using PAIR = std::pair<KeyType, ValueType>;
    using abstract_data_t = AbstractData<KeyType, ValueType>;

    virtual ~AbstractData() = default;
    virtual void Insert_abs(PAIR pair) = 0;
    virtual void Erase_abs(const KeyType& key) = 0;
    virtual void Extend_abs(const abstract_data_t& other) = 0;
};

TEMPLATE_HASH_TABLE
class UnOrdered_Map: public AbstractData<KEY, VALUE>
{
private:
    FList<PAIR>* table;
    size_t table_size;
    size_t element_count;

    size_t hash_function(const KEY& key) const { return std::hash<KEY>()(key) % table_size; } 
    void Rehash(size_t new_size)
    {
        UnOrdered_Map temp(new_size);
        for (size_t i = 0; i < table_size; ++i)
            if (!table[i].Empty())
            {
                for (auto it = table[i].begin(); it != table[i].end(); ++it)
                {
                    size_t id_bucket = temp.GetBucketId(it->first);
                    temp.table[id_bucket].Push_Back(*it);
                }
            }
        *this = temp;
    }  
public:
    //----------------------------------------------------------------------2 lab----------------------------------------------------------------
    UnOrdered_Map() : table(new FList<PAIR>[11]), table_size(11), element_count(0) {} 
    UnOrdered_Map(size_t size) : table(new FList<PAIR>[size]), table_size(size), element_count(0) {} 
    UnOrdered_Map(std::initializer_list<PAIR> list) : UnOrdered_Map()
    {
        for (auto it = list.begin(); it != list.end(); ++it)
        {
            size_t id_bucket = GetBucketId(it->first);
            table[id_bucket].Push_Back(*it);
            element_count++;       
        }
    } 
    UnOrdered_Map(const UnOrdered_Map& other) : table(new FList<PAIR>[other.table_size]), table_size(other.table_size), element_count(other.element_count)
    {
        for (size_t i = 0; i < table_size; ++i)
            table[i] = other.table[i];
    } 
    UnOrdered_Map(const PAIR *a, const size_t size) : UnOrdered_Map()
    {
        if (a == nullptr) return;
        for (size_t i = 0; i < size; ++i)
        {
            size_t id_bucket = GetBucketId(a[i].first);
            table[id_bucket].Push_Back(a[i]);
            element_count++;
        }
    }
    ~UnOrdered_Map() override { delete[] table; } 
    void Clear() {
        delete[] table;
        table_size = 11;
        table = new FList<PAIR>[table_size];
        element_count = 0;
    }  
    auto At(const KEY key)
    {
        size_t id_bucket = GetBucketId(key);
        auto& list = table[id_bucket];
        for (auto it = list.begin(); it != list.end(); ++it)
            if (it->first == key)
                return it->second;
        return VALUE();
    } 
    void Resize(const size_t new_size) { if (new_size > table_size) Rehash(new_size); } 
    bool Empty() const { return element_count == 0; }  
    size_t Size() const { return element_count; } 
    void Swap(UnOrdered_Map& other)
    {
        std::swap(table, other.table);
        std::swap(table_size, other.table_size);
        std::swap(element_count, other.element_count);
    }  
    void Assign(const size_t count, const PAIR& pair) // ЭТОТ МЕТОД БЕСПОЛЕЗНЫЙ, ПОТОМУ ЧТО У НАС НЕ ПОДДЕРЖИВАЮТСЯ КОЛЛИЗИИ В НАШЕЙ ХЕШ ТАБЛИЦЕ
    {
        Clear();
        for (size_t i = 0; i < count; ++i)
        {
            size_t id_bucket = GetBucketId(pair.first);
            table[id_bucket].Push_Back(pair);
            element_count++;
        }
    } 
    static bool Is_Equal(const UnOrdered_Map& a,const UnOrdered_Map& b)
    {
        if(a.Bucket_count() != b.Bucket_count())
            return false;

        if(a.element_count != b.element_count)
            return false;

        for (int i=0; i < a.Bucket_count(); ++i)
            if (!FList<PAIR>::AreEqual(a.table[i], b.table[i]))
                return false;
        return true;
    }   
    static void Print(UnOrdered_Map& map)
    {
        for(int i = 0; i < map.Bucket_count(); ++i)
            for(auto it = map.table[i].begin(); it != map.table[i].end(); ++it)
                std::cout << "{" << it->first << " : " << it->second << "} ";
    }  


    // Дополнительные методы
    size_t GetBucketId(const typename PAIR::first_type& key) const { return hash_function(key); } 
    size_t Bucket_count() const { return table_size; }  
    size_t Bucket_size(size_t index) const { return table[index].Size(); } 
    float Load_factor() const { return static_cast<float>(element_count) / table_size; } 

    
    //----------------------------------------------------------------------3 lab----------------------------------------------------------------
    friend bool operator==(const UnOrdered_Map& a, const UnOrdered_Map& b) {return Is_Equal(a,b);} 
    friend bool operator!=(const UnOrdered_Map& a, const UnOrdered_Map& b) { return !(a == b); }
    UnOrdered_Map& operator=(const UnOrdered_Map& other)
    {
        if (this == &other) return *this;
        delete[] table;
        table_size = other.table_size;
        element_count = other.element_count;

        table = new FList<PAIR>[table_size];
        for (size_t i = 0; i < table_size; ++i)
            table[i] = other.table[i];

        return *this;
    } 
    VALUE& operator[](const KEY& key)
    {
        size_t bucket_index = GetBucketId(key);
        auto& list = table[bucket_index];
        
        for (auto& pair : list)
            if (pair.first == key)
                return pair.second;
        
        list.Push_Back({ key, VALUE() });
        ++element_count;
        return list.Back().second;
    }
    bool Contains(const KEY& key) const
    {
        size_t id_bucket = GetBucketId(key);
        auto& list = table[id_bucket];
        for (auto it = list.begin(); it != list.end(); ++it)
            if (it->first == key)
                return true;
        return false;
    }

    //ОПЕРАТОРА МЕНЬШЕ ДЛЯ ВАРИАНТА HASH TABLE НЕТ operator < > <= >= << >>
    //ОПЕРАТОРА COUNT ДЛЯ ВАРИАНТА HASH TABLE НЕТ, КОТОРЫЙ ЧИТАЕТ СКОЛЬКО РАЗ ЭЛЕМЕНТ ВСТРЕЧАЕТСЯ В ХЭШ ТАБЛИЦЕ, ПОТОМУ ЧТО У НАС НЕ ПОДДЕРЖИВАЮТСЯ КОЛЛИЗИИ В НАШЕЙ ХЭШ ТАБЛИЦЕ
    
    //----------------------------------------------------------------------4 lab----------------------------------------------------------------
    UnOrdered_Map(const MapIter<PAIR> begin, const MapIter<PAIR> end) : UnOrdered_Map()
    {
        for (auto it = begin; it != end; ++it)
        {
            size_t id_bucket = GetBucketId(it->first);
            table[id_bucket].Push_Back(*it);
        }
    }
    MapIter<PAIR> begin() { return MapIter<PAIR>(table, table_size); }
    MapIter<PAIR> end() { return MapIter<PAIR>(table, table_size, table_size); }
    const MapIter<PAIR> cbegin() const { return MapIter<PAIR>(table, table_size); } 
    const MapIter<PAIR> cend() const { return MapIter<PAIR>(table, table_size,table_size); }
    void Assign(const MapIter<PAIR>& begin,const MapIter<PAIR>& end)
    {
        Clear(); 
        for (auto it = begin; it != end; ++it)
        {
            size_t id_bucket = GetBucketId(it->first);
            table[id_bucket].Push_Back(*it);
        }
    }
    
    //----------------------------------------------------------------------5 lab----------------------------------------------------------------
    // МЕТОДА FRONT У ХЭШ ТАБЛИЦЫ НЕТ
    // МЕТОДА BACK У ХЭШ ТАБЛИЦЫ НЕТ
    // POP МЕТОДА У ХЭШ ТАБЛИЦЫ НЕТ
    // PUSH МЕТОДА У ХЭШ ТАБЛИЦЫ НЕТ, НО ЕСТЬ МЕТОД INSERT
    void Insert_abs(typename AbstractData<KEY, VALUE>::PAIR pair) override {this->Insert(pair);} 
    void Erase_abs(const KEY& key) override {this->Erase(key);}
    void Extend_abs(const typename AbstractData<KEY, VALUE>::abstract_data_t& other) override
    {
        const auto* map = dynamic_cast<const UnOrdered_Map<KEY, VALUE>*>(&other);
        if (map) this->Extend(*const_cast<UnOrdered_Map<KEY, VALUE>*>(map)); 
        else throw std::invalid_argument("Argument is not of type UnOrdered_Map");
    } 
    void Insert(const PAIR& pair) 
    {
        size_t bucket_index = GetBucketId(pair.first);
        auto& bucket = table[bucket_index];

        Iter<PAIR> tmp = Find(pair.first);

        if (tmp != bucket.end())
        {
            tmp->second = pair.second;
            return;
        }

        bucket.Push_Back(pair);
        ++element_count;

        if (Load_factor() > 20) { Rehash(table_size * 2); }
    } 
    void Extend(UnOrdered_Map& other)
    {
        for (auto it = other.begin(); it != other.end(); ++it)
                Insert(*it);
    } 
    void Erase(const KEY key)
    {
        auto& list = table[GetBucketId(key)];
        if(Find(key)!=list.end())
        {
            list.Erase(Find(key));
            --element_count;
        }
    } 
    
    //----------------------------------------------------------------------6 lab----------------------------------------------------------------
    auto Find(const KEY key)
    {
        size_t id_bucket = GetBucketId(key);
        auto& list = table[id_bucket];
        
        for (auto it = list.begin(); it != list.end(); ++it)
            if (it->first == key)
                return it;
        return table[table_size].end();
    } 
    void Emplace(const PAIR& pair)
    {
        auto it = Find(pair.first);
        
        if (it == nullptr)
        {
            Insert(pair);
            return;
        }
        it->second = pair.second;
    }
    void Copy_From(const UnOrdered_Map& other)
    {
        this->table_size = other.Bucket_count();
        this->table = new FList<PAIR>[table_size];
        this->element_count = other.Size();
        for (size_t i = 0; i < table_size; ++i)
            this->table[i] = other.table[i];
    }
};
