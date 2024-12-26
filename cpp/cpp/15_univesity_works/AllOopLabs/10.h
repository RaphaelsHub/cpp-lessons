#pragma once


#include <cassert>
#include <iostream>
#include <string>

using namespace std;

struct node {
    string data;
    node *next{nullptr};
};

size_t length(node *head){
    size_t count = 0;
    for (; head != nullptr; head = head->next)
        count++;
    return count;
}

void output(node *head){
    for (; head != nullptr; head = head->next)
        cout << head->data << " ";
    cout << "\n";
}

void push_back(node *&head, const string &str){
    static node *last; //запоминаем последний элемент
    node *taile = new node {str,nullptr}; //при помощи встроенного конструктора пихаем данные

    (head==nullptr) ? head=taile : last->next=taile;//тернарным способом проверяем
    last=taile;//сохраняем хвост
}

node *find(node *head, const string &str){
    while (head && head->data != str)
        head = head->next;
    return head;
}

void insert_after(node *head, const string &findStr, const string &newStr){
    node *tmp = find(head, findStr);
    if (tmp != nullptr){
        node *a = tmp->next;
        tmp->next = new node{newStr, a};
    }
}

node *split(node *&head, const string &str){
    node *splitedHead;
    node *tmpHead = head;
    for (; tmpHead->next->data != str; tmpHead=tmpHead->next);
    splitedHead=tmpHead->next;
    tmpHead->next=nullptr;
    return splitedHead;
}

void remove_after(node *head, const string &str){
    head = find(head, str);
    node *deleteMember = head->next;
    head->next = head->next->next;
    delete deleteMember;
}

string pop_back(node *head){
    for (; head->next->next != nullptr; head = head->next);
    delete head->next->next;
    head->next = nullptr;
    return "";
}

void insert_after1(node *head1, node *&head2){
    node *tmp = head1->next;
    node *tmp1 = head2->next;
    head1->next = head2;
    head1->next->next = tmp;
    head2 = tmp1;
}

void merge_sorted(node *&head1, node *&head2){
    if (head1 == head2)
        return;
     node *nacolo = head1;
    while (head1 && head2)
        if (head1->data < head2->data)
            insert_after1(head1, head2);
        else 
            if (nacolo == head1)
            {
                node *tmp = head2->next;
                head2->next = head1;
                head1 = head2;
                head2 = tmp;
            }
            else
            {
                node *tmp = head2->next->next;
                head2->next = head1;
                nacolo->next = head2;
                head2 = tmp;
                nacolo = nacolo->next;
            }
}

// int main(){
//     node *head = nullptr;

//     push_back(head, "a");
//     push_back(head, "b");
//     push_back(head, "c");
//     assert(3 == length(head));
//     output(head);
//     merge_sorted(head, head);
//     insert_after(head, "c", "d");
//     node *other_head = split(head, "c");
//     insert_after(other_head, "d", "e");
//     merge_sorted(other_head, head);
//     assert(nullptr == head);
//     assert(0 == length(head));
//     assert(5 == length(other_head));
//     remove_after(other_head, "c");
//     pop_back(other_head);
//     assert(3 == length(other_head));
//     output(other_head);
// }
