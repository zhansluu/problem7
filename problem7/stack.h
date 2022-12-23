#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include "iterators.h"

template <class T>
class Stack: public single_linked_list<T>
{
public:
    Stack () : top(nullptr) {};          // Конструктор по умолчанию

    Stack (Stack&& s) : top(s.top) {s.top = nullptr;}  //Конструктор перемещения

    Stack (const Stack& s) : top(nullptr) //Конструктор копирования
    {
        node<T> *t = s.top;
        node<T> **n = &top;

        while (t != nullptr)
        {
            *n = new node<T>;

            (*n)->data = t->data;
            (*n)->next = nullptr;
            n = &((*n)->next);
            t = t->next;
        }
    }

    ~Stack()
    {
        while(!this->Pop());
    }

    void Free()
    {
        while(!this->Pop());
    }

    typename single_linked_list<T>::const_iterator cbegin() const override {return typename single_linked_list<T>::const_iterator (top);};
    typename single_linked_list<T>::const_iterator cend() const override {return nullptr ;};
    typename single_linked_list<T>::const_iterator begin() const override {return typename single_linked_list<T>::const_iterator (top);};
    typename single_linked_list<T>::const_iterator end() const override {return nullptr;};
    typename single_linked_list<T>::iterator begin() override {return typename single_linked_list<T>::iterator(top);};
    typename single_linked_list<T>::iterator end() override {return nullptr;};

    Stack& operator = (const Stack& s)
    {
        if (this == &s) return *this;

        Free(); //очистить стек без удаления

        node<T> *t = s.top;
        node<T> **n = &top;

        while (t != nullptr)
        {
            *n = new node<T>;

            (*n)->data = t->data;
            (*n)->next = nullptr;
            n = &((*n)->next);
            t = t->next;
        }
        return *this;
    }

    Stack& operator = (Stack&& s)
    {
        node<T> *t = s.top;
        node<T> **n = &top;

        while (t != nullptr)
        {
            *n = new node<T>;

            (*n)->data = t->data;
            (*n)->next = nullptr;
            n = &((*n)->next);
            t = t->next;
        }
        return *this;
    }

    single_linked_list<T>& operator = (const single_linked_list<T>& s) override
    {
        if (&s == this) return *this;
        const Stack& stackk = dynamic_cast<const Stack&>(s);
        node<T> *t = stackk.top;
        node<T> **n = &top;

        while (t != nullptr)
        {
            *n = new node<T>;

            (*n)->data = t->data;
            (*n)->next = nullptr;
            n = &((*n)->next);
            t = t->next;
        }
        return *this;
    }
    void Push(T e)
    {
        node<T>* t = new node<T>;

        t->data = e;
        t->next = top;
        top = t;
    }

    T Pop()
    {
        if (!top) throw STACK_UNDERFLOW;

        node<T>* t = top;
        T e = t->data;

        top = t->next;
        delete t;

        return e;
    }
/*
    int Push (const T e) override
    {
        node<T> *n = new node<T> ;//выделение памяти на новый узел

        n->data = e; //заполнение узла
        n->next = top; //в новом узле указатель на соседа устанавливается на узел в голове в старом
        top = n; //указатель на вершину переносится на новый элемент

        return 0;
    }

    int Pop(T *e) override
    {
        struct node<T> *t = top; //запоминаем указатель на узел в вершине
        if (!t) return 1;

        if (e)
            *e = t->data; //прочитываем данные из вершины, если указатель е не nullptr
        top = top->next; // указатель вершины переносится на следующий элемент, изымая элемент из списка

        delete t;
        return 0;
    }
*/
    bool IsEmpty() const override
    {
        return top == nullptr;
    }

    enum ERR_CODE {OUT_OF_RANGE};

    const T& GetFront() const override
    {
        if (this->IsEmpty())
            throw OUT_OF_RANGE;
        return top->data;
    }

    int Size() override
    {
        int s_size = 0;
        if (top == nullptr)
            return 0;
        struct node<T> *tmp = top;
        s_size++;

        while (tmp->next != nullptr)
        {
            tmp = tmp->next;
            s_size++;
        }
        return s_size;
    }
private:
    node<T>* top; //указатель на вершину стека
};


#endif // STACK_H_INCLUDED
