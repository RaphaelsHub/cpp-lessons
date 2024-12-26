#pragma once

#include <iostream>
#include <string>
#include <stack>
#include <assert.h>

using namespace std;

struct Node
{
    char ch{0};
    Node *left_{nullptr};
    Node *right_{nullptr};
};

bool isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int priority(char opernd)
{
    if (opernd == '+' || opernd == '-')
        return 1;
    if (opernd == '*' || opernd == '/')
        return 2;
    return 0;
}

string infixToPostfix(string infix)
{
    stack<char> stack;

    string postfix = "";

    for (size_t i = 0; infix[i] != '\0'; ++i)
    {
        if (infix[i] >= '0' && infix[i] <= '9')
            postfix += infix[i];

        else if (infix[i] == '(')
            stack.push(infix[i]);

        else if (infix[i] == ')')
        {
            postfix += stack.top();
            stack.pop();
            stack.pop();
        }
        else
        {
            while (!stack.empty() && priority(infix[i]) <= priority(stack.top()))
            {
                postfix += stack.top();
                stack.pop();
            }
            stack.push(infix[i]);
        }
    }

    while (!stack.empty())
    {
        postfix += stack.top();
        stack.pop();
    }

    return postfix;
}

Node *makeTree(string postfix)
{
    if (postfix.length() == 0)
        return nullptr;

    stack<Node *> stackTree;

    for (char c : postfix)
    {
        if (isOperator(c))
        {  
            Node *Tree_right = stackTree.top();
            stackTree.pop();
            Node *Tree_left = stackTree.top();
            stackTree.pop();

            Node *newNode = new Node{c, Tree_left, Tree_right};

            stackTree.push(newNode);
        }
        else
            stackTree.push(new Node{c, nullptr, nullptr});
    }

    return stackTree.top();
}

void clear(Node *&root)
{
    if (root != nullptr)
    {
        clear(root->left_);
        clear(root->right_);
        delete root;
        root = nullptr;
    }
}

void output(Node *root)
{
    if (root == nullptr)
        return;

    output(root->left_);
    output(root->right_);
    cout << root->ch;
}

int evaluate(Node *root)
{
    if (!root->left_ && !root->right_)
        return (root->ch) - 48;

    int left_val = evaluate(root->left_);
    int right_val = evaluate(root->right_);

    switch (root->ch)
    {
    case '+':
        return left_val + right_val;
    case '-':
        return left_val - right_val;
    case '*':
        return left_val * right_val;
    case '/':
        return left_val / right_val;
    };
}

// int main()
// {
//     int result =4;
//     string expression = "(1+1)*(1/1)*(1+1)+(1*1)+(1/1)-(1+1)"; // Наше выржение и всего тут 11 операций, вложенность скобок 2 и больше
//     string postfix = infixToPostfix(expression); //Перевод из инфикса в постфикс для удобства 
//     Node *root = makeTree(postfix); //создании дерева
//     assert(result == (evaluate(root))); 
//     output(root);
//     clear(root);
// }
