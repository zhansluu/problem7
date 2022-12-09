
#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include "iterators.h"

class Stack : public single_linked_list
{
public:
    Stack() : top(nullptr) {};          // Конструктор по умолчанию

    Stack(Stack&& s) : top(s.top) { s.top = nullptr; }  //Конструктор перемещения

    Stack(const Stack& s) : top(new node) //Конструктор копирования
    {
        node* t = s.top;
        node** n = &top;

        while (t != nullptr)
        {
            *n = new node;

            (*n)->data = t->data;
            (*n)->next = nullptr;
            n = &((*n)->next);
            t = t->next;
        }
    }

    ~Stack()
    {
        while (!this->Pop(nullptr));
    }

    void Free()
    {
        while (!this->Pop(nullptr));
    }

    const_iterator cbegin() const override { return const_iterator(top); };
    const_iterator cend() const override { return const_iterator(); };
    iterator begin() override { return iterator(top); };
    iterator end() override { return iterator(); };

    Stack& operator = (const Stack& s)
    {
        if (this == &s) return *this;

        Free(); //очистить стек без удаления

        node* t = s.top;
        node** n = &top;

        while (t != nullptr)
        {
            *n = new node;

            (*n)->data = t->data;
            (*n)->next = nullptr;
            n = &((*n)->next);
            t = t->next;
        }
        return *this;
    }

    Stack& operator = (Stack&& s)
    {
        node* t = s.top;
        node** n = &top;

        while (t != nullptr)
        {
            *n = new node;

            (*n)->data = t->data;
            (*n)->next = nullptr;
            n = &((*n)->next);
            t = t->next;
        }
        return *this;
    }

    single_linked_list& operator = (const single_linked_list& s) override
    {
        if (&s == this) return *this;
        const Stack& stackk = dynamic_cast<const Stack&>(s);
        node* t = stackk.top;
        node** n = &top;

        while (t != nullptr)
        {
            *n = new node;

            (*n)->data = t->data;
            (*n)->next = nullptr;
            n = &((*n)->next);
            t = t->next;
        }
        return *this;
    }

    int Push(const int e) override
    {
        node* n = new node;//выделение памяти на новый узел

        n->data = e; //заполнение узла
        n->next = top; //в новом узле указатель на соседа устанавливается на узел в голове в старом
        top = n; //указатель на вершину переносится на новый элемент

        return 0;
    }

    int Pop(int* e) override
    {
        struct node* t = top; //запоминаем указатель на узел в вершине
        if (!t) return 1;

        if (e)
            *e = t->data; //прочитываем данные из вершины, если указатель е не nullptr
        top = top->next; // указатель вершины переносится на следующий элемент, изымая элемент из списка

        delete t;
        return 0;
    }

    bool IsEmpty() const override
    {
        return top == nullptr;
    }

    enum ERR_CODE { OUT_OF_RANGE };

    const int& GetFront() const override
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
        struct node* tmp = top;
        s_size++;

        while (tmp->next != nullptr)
        {
            tmp = tmp->next;
            s_size++;
        }
        return s_size;
    }
protected:
    void Print(std::ostream& stream) const override
    {
        struct node* tmp = top;
        stream << tmp->data << ' ';

        while (tmp->next != nullptr)
        {
            tmp = tmp->next;
            stream << tmp->data << ' ';
        }
        stream << std::endl;
    }
private:
    node* top; //указатель на вершину стека
};


#endif // STACK_H_INCLUDED
