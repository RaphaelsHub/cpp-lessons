#pragma once

#include <iostream>
#include <string>
#include <cassert>

using std::cin;
using std::cout;
using std::string;

struct data_t
{
    string group;
};

void init(data_t *&a, size_t count)
{
    a = new data_t[count];
}

void input(data_t *a, size_t count)
{
    for (size_t i = 0; i < count; i++)
        cin >> a[i].group;
}

void output(data_t *a, size_t count)
{
    for (size_t i = 0; i < count; i++)
        cout << a[i].group << " ";
}

data_t find(data_t *a, size_t count, string edit)
{
    data_t b;
    for (size_t i = 0; i < count; i++)
        if (a[i].group == edit)
            return a[i];
    return b;
}

void edit(data_t *&a, size_t count, size_t index, string edit)
{
    if (index < count)
        a[index].group = edit;
}

// Это не функция main(), но я оставлю ее для тестирования кода.
// В вашем коде должна быть функция main(), чтобы программа запускалась.
// int main()
// {
//     string search_term, edit_term;
//     size_t index = 0, count = 0;
//     cin >> search_term >> edit_term >> count >> index;
//     data_t *a = nullptr;
//     init(a, count);
//     input(a, count);
//     edit(a, count, index + 100, edit_term);
//     edit(a, count, index, edit_term);
//     assert(search_term != find(a, count, "test").group);
//     assert(search_term == find(a, count, search_term).group);
//     output(a, count);
//     delete[] a;
//     return 0;
// }
