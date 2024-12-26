#pragma once

#include <iostream>
#include <string>
#include <cassert>

using std::string;

struct data_t
{
    string group;
};

void init(data_t *&a, size_t count)
{
    auto b = new data_t[count];
    for (size_t g = 0; g < count; g++)
        b[g] = a[g];
    delete [] a;
    a=b;
}

void output(data_t *a, size_t count)
{
    for (size_t i = 0; a && i < count; i++)
        std::cout << a[i].group << " ";
}

data_t find(data_t *a, size_t count, string edit)
{
    data_t b;
    for (size_t i = 0; i < count; i++)
        if (a[i].group == edit)
            return a[i];
    return b;
}

void push_back(data_t *&a, size_t &count, size_t &cap, const data_t str)
{
    if (count + 1 >= cap)
        init(a, (cap) ? cap*2 : 1);
    a[count++] = str;
}

void pop_back(data_t *&a, size_t &count)
{
    if(count > 0)
        count--;
    a[count].group = "";
}

void remove(data_t *&a, size_t &count, size_t index)
{
    for (size_t i = index, j = index + 1; i < count; i++, j++)
        a[i].group = a[j].group;
    count--;
}

void insert(data_t *&a, size_t &count, size_t &cap, size_t index, const data_t str)
{
    if (cap <= count)
        init(a, cap+2);
    for (size_t i = count, j = count - 1; i > index; i--, j--)
        a[i].group = a[j].group;
    a[index].group = str.group;
    count++;
}

// int main()
// {
//     string search_term, edit_term;
//     size_t index = 0, count = 0, cap = 0;
//     data_t *a = nullptr;
    
//     cin >> search_term >> edit_term >> count >> index;

//     cap = count;

//     push_back(a, count, cap, {"one"});
//     push_back(a, count, cap, {"two"});
//     push_back(a, count, cap, {"three"});

//     assert(3 == count);
//     insert(a, count, cap, index, {edit_term});
    
//     assert(edit_term == find(a, count, search_term).group);
//     remove(a, count, index);
    
//     pop_back(a, count);
//     assert(2 == count);
//     output(a, count);
//     delete[] a;
// }
