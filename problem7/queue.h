#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
#include "iterators.h"

class Queue : public single_linked_list
{
public:
    Queue() : top(nullptr), tail(nullptr) {};          // Конструктор по умолчанию

    Queue(Queue&& q) : top(q.top), tail(q.tail) {}  //Конструктор перемещения

    Queue(const Queue& q) : top(nullptr), tail(nullptr) //Конструктор копирования
    {
        node* t = q.top;
        while (t != nullptr)
        {
            node* n = new node;

            n->data = t->data;
            n->next = nullptr;
            if (q.top == nullptr)
            {
                top = n;
            }
            else tail->next = n;
            tail = n;
            t = t->next;
        }
    }

    ~Queue()
    {
        while (!IsEmpty())
            Pop(nullptr);
    }

    void Free()
    {
        while (!this->Pop(nullptr));
    }

    const_iterator cbegin() const override { return const_iterator(top); };
    const_iterator cend() const override { return const_iterator(); };
    iterator begin() override { return iterator(top); };
    iterator end() override { return iterator(); };

    Queue& operator = (const Queue& s)
    {
        if (this == &s) return *this;

        (*this).Free(); //<=> Free();

        node* t = s.top;

        while (t != nullptr)
        {
            (*this).Push(t->data);
            t = t->next;
        }
        return *this;
    }

    Queue& operator = (const Queue&& q)
    {
        node* t = q.top;

        while (t != nullptr)
        {
            (*this).Push(t->data);
            t = t->next;
        }

        return *this;
    }

    single_linked_list& operator = (const single_linked_list& q) override
    {
        if (&q == this) return *this;
        const Queue& queu = dynamic_cast<const Queue&>(q);
        node* t = queu.top;
        while (t != nullptr)
        {
            node* n = new node;

            n->data = t->data;
            n->next = nullptr;
            if (queu.top == nullptr)
            {
                top = n;
            }
            else tail->next = n;
            tail = n;
            t = t->next;
        }
        return *this;
    }

    int Push(const int e) override
    {
        node* n = new node; //выделение памяти на новый узел

        n->data = e; //заполнение узла
        n->next = nullptr; //в новом узле указатель на соседа устанавливается на nullptr
        if (top == nullptr)
            top = n; //указатель на вершину переносится на новый элемент
        else
            tail->next = n; //указатель на соседа хвоста устанавливается на новый элемент

        tail = n;

        return 0;
    }

    int Pop(int* e) override
    {
        struct node* t = top; //запоминаем указатель на узел в вершине
        if (!t) return 1;

        top = t->next;
        if (e)
            *e = t->data; //прочитываем данные из вершины, если указатель е не nullptr
        delete t;

        if (top == nullptr)
            tail = nullptr;
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
        int q_size = 0;
        if (top == nullptr)
            return 0;
        struct node* tmp = top;
        q_size++;

        while (tmp->next != nullptr)
        {
            tmp = tmp->next;
            q_size++;
        }
        return q_size;
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
    node* top; //указатель на голову очереди
    node* tail; //указатель на хвост очереди

};

#endif // QUEUE_H_INCLUDED

