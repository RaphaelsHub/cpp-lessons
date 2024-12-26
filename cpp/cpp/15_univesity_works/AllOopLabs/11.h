#pragma once
#include <assert.h>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

struct node {
    string data;
    node *left{nullptr};
    node *right{nullptr};
};

void sort(node *root, string strs[], size_t i = 0){
    if (root == nullptr)
        return;
    sort(root->left, strs, i);
    strs[i++] = root->data;
    sort(root->right, strs, i);
}

void init(node *&root, const string a[], size_t count){
    if (!root)
        root = new node{a[0], nullptr, nullptr};

    for (size_t i = 1; i < count; ++i)
    {
        node *current = root;

        while (true)
        {
            if (a[i] > current->data)
            {
                if (current->right == nullptr)
                {
                    current->right = new node{a[i], nullptr, nullptr};
                    break;
                }
                else
                    current = current->right;
            }

            else
            {
                if (current->left == nullptr)
                {
                    current->left = new node{a[i], nullptr, nullptr};
                    break;
                }
                else
                    current = current->left;
            }
        }
    }
}

node *find(node *root, const string &str){
    while (root != nullptr && root->data != str)
        (root->data > str) ? root = root->left : root = root->right;
    return root;
}

void printTree(node *root){
    if (root == nullptr)
        return;

    printTree(root->left);
    cout << root->data << " ";
    printTree(root->right);
}

size_t height(node *root){
    if (root == nullptr)
        return 0;

    size_t leftCountHeads = height(root->left);
    size_t rightCountHeads = height(root->right);

    return (leftCountHeads > rightCountHeads) ? ++leftCountHeads : ++rightCountHeads;
}

void clear(node *&root){
    if (root != nullptr)
    {
        clear(root->left);
        clear(root->right);
        delete root;
        root = nullptr;
    }
}

// int main()
// {
//     size_t n = 0, k = 0;

//     cin >> n >> k;
//     // указатель на массив строк n элементов
//     string *a = new string[n];
//     // ввод
//     for (size_t i = 0; i < n; i++)
//         cin >> a[i];
//     // создание корня
//     node *root = nullptr;
//     init(root, a, n);          // выделение памяти и запись
//     assert(k == height(root)); // проверка правильно ли подсчитал высоту дерева

//     // проверка все ли элементы записались
//     for (size_t i = 0; i < n; ++i)
//         assert(a[i] == find(root, a[i])->data);

//     sort(root, a); // сортировка
//     clear(root);   // очистка

//     for (size_t i = 0; i < n; ++i)
//         cout << a[i] << " ";
// }
