
#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include "iterators.h"

class Stack : public single_linked_list
{
public:
    Stack() : top(nullptr) {};          // ����������� �� ���������

    Stack(Stack&& s) : top(s.top) { s.top = nullptr; }  //����������� �����������

    Stack(const Stack& s) : top(new node) //����������� �����������
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

        Free(); //�������� ���� ��� ��������

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
        node* n = new node;//��������� ������ �� ����� ����

        n->data = e; //���������� ����
        n->next = top; //� ����� ���� ��������� �� ������ ��������������� �� ���� � ������ � ������
        top = n; //��������� �� ������� ����������� �� ����� �������

        return 0;
    }

    int Pop(int* e) override
    {
        struct node* t = top; //���������� ��������� �� ���� � �������
        if (!t) return 1;

        if (e)
            *e = t->data; //����������� ������ �� �������, ���� ��������� � �� nullptr
        top = top->next; // ��������� ������� ����������� �� ��������� �������, ������ ������� �� ������

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
    node* top; //��������� �� ������� �����
};


#endif // STACK_H_INCLUDED
