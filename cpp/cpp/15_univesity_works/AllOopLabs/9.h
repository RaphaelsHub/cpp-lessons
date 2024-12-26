#pragma once

#include <cassert>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

struct node {
    string data;
    node *next{nullptr};
};

size_t length(node *head){
    size_t count = 0;
    for(;head!=nullptr; head=head->next)
        count++;
    return count;
}

void input(node *&head, size_t count){
    node *tmp=head;
    for (size_t i = 0; i < count && tmp; i++, tmp=tmp->next)
        cin >>tmp->data;
}

void output(node *head){
    for (;head!=nullptr;head=head->next)
        cout << head->data <<" ";
    cout<<"\n";
}

node *find(node *head, const string str){
    for (;head!=nullptr;head=head->next)
        if (head->data == str)
            return head;
    return nullptr;
}

void edit(node *head, const string &search_term, const string &edit_term){
    for (; head != nullptr; head=head->next)
        if (head->data == search_term)
            head->data = edit_term;
}

void push_front(node*& head, const string& push_term) {
    head = new node {push_term, head};
}

string pop_front(node *&head){
    if(head==nullptr)
        return "";

    string returnStr=head->data;   

    node *deletedHead=head;
    head=head->next;
    delete deletedHead;
    return returnStr;
}

// int main()
// {
//     // создание перменных, элемент, который мы ищем, который редактируем, который закидываем
//     string search_term, edit_term, push_term;
//     // ввод
//     cin >> search_term >> edit_term >> push_term;

//     node *head = new node{"", new node{"", new node{}}};
//     input(head, length(head));
//     assert(nullptr == find(head, "test"));
//     output(head);
//     edit(head, search_term, edit_term);
//     assert(edit_term == find(head, edit_term)->data);
//     push_front(head, push_term);
//     assert(push_term == find(head, push_term)->data);
//     output(head);
//     pop_front(head);
//     output(head);
//     pop_front(head);
//     output(head);
//     pop_front(head);
//     output(head);
//     pop_front(head);
//     output(head);
// }
