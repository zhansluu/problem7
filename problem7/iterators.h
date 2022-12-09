/*����������� ��������� (������� � �����������) ��� ������� ���� � �������, � ����� ����������� ������
begin()/end() � cbegin()/cend(), ���������� �������������� ��������� STL.

* �������� ����� print() � operator << �� ������������� ���������.*/
#ifndef ITERATORS_H_INCLUDED
#define ITERATORS_H_INCLUDED

typedef struct node /*���������-����*/
{
    int data; //���� � �������
    struct node* next; //��������� �� ���������
} node;

class single_linked_list
{
public:
    class const_iterator // �� ����� ������ ��������, �� ������� �� ���������
    {
    public:
        const_iterator(const node* current_node = nullptr) : current_node(current_node) { }

        int operator*() const //�������������� ��������
        {
            return current_node->data;
        }

        const int& operator ->() const
        {
            return current_node->data;
        }

        const_iterator& operator++() // ��������� � ��������� ������
        {
            current_node = current_node->next;
            return *this;
        }

        const_iterator operator++(int)
        {
            const_iterator i = *this;
            current_node = current_node->next;
            return i;
        }

        //��������� 2 ����������
        bool operator!=(const const_iterator& another) const
        {
            return current_node != another.current_node;
        }
        bool operator==(const const_iterator& another) const //��������� 2 ����������
        {
            return current_node == another.current_node;
        }

    private:
        const node* current_node;
    };

    class iterator // ����� ������ ��������, �� ������� �� ���������
    {
    public:
        iterator(node* current_node = nullptr) : current_node(current_node) { }

        int operator*() const //�������������� �������� (����� ���������� ������ �� �������)
        {
            return current_node->data;
        }

        const int& operator ->() const
        {
            return current_node->data;
        }

        iterator& operator++() // ��������� � ��������� ������
        {
            current_node = current_node->next;
            return *this;
        }

        iterator operator++(int)
        {
            iterator i = *this;
            current_node = current_node->next;
            return i;
        }

        //��������� 2 ����������
        bool operator!=(const iterator& another) const
        {
            return current_node != another.current_node;
        }
        bool operator==(const iterator& another) const //��������� 2 ����������
        {
            return current_node == another.current_node;
        }

    private:
        node* current_node;
    };
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator cend() const = 0;
    virtual iterator begin() = 0;
    virtual iterator end() = 0;

    virtual int Push(const int e) = 0;
    virtual int Pop(int* e) = 0;
    virtual const int& GetFront() const = 0;
    virtual bool IsEmpty() const = 0;
    virtual int Size() = 0;
    virtual single_linked_list& operator = (const single_linked_list& List) = 0;
    friend std::ostream& operator << (std::ostream& stream, single_linked_list& l)
    {
        for (const_iterator it = l.cbegin(); it != l.cend(); ++it)
        {
            stream << *it << std::endl;
        }
        return stream;
    }
    friend std::istream& operator >> (std::istream& stream, single_linked_list& l)
    {
        int e;
        stream >> e;
        l.Push(e);
        return stream;
    }

protected:
    virtual void Print(std::ostream& stream) const = 0;
    node* top; //��������� �� ������� �����
};

#endif // ITERATORS_H_INCLUDED

