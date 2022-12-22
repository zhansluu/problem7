/*����������� ��������� (������� � �����������) ��� ������� ���� � �������, � ����� ����������� ������
begin()/end() � cbegin()/cend(), ���������� �������������� ��������� STL.

* �������� ����� print() � operator << �� ������������� ���������.*/
#ifndef ITERATORS_H_INCLUDED
#define ITERATORS_H_INCLUDED

template <class T>
struct node /*���������-����*/
{
  T data; //���� � �������
  struct node<T>* next; //��������� �� ���������
};

template <class T>
class single_linked_list
{
public:
    class iterator;
    class const_iterator // �� ����� ������ ��������, �� ������� �� ���������
    {
    public:
        const_iterator (const node<T>* current_node = nullptr) : current_node(current_node) { }

        /*const_iterator (typename single_linked_list<T>::node<T>* current_node = nullptr)
        {
            this->current_node = current_node;
        }*/

        T operator*() const //�������������� ��������
        {
            return current_node->data;
        }

        const T& operator ->() const
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

        //��������� const � ��-const ����������
        bool operator!=(const iterator& another) const
        {
            return current_node != another.current_node;
        }
        bool operator==(const iterator& another) const //��������� 2 ����������
        {
            return current_node == another.current_node;
        }

        friend iterator;
    private:
        const node<T>* current_node;
    };

    class iterator // ����� ������ ��������, �� ������� �� ���������
    {
    public:
        iterator (node<T>* current_node = nullptr) : current_node(current_node) { }

        T operator*() const //�������������� �������� (����� ���������� ������ �� �������)
        {
            return current_node->data;
        }

        const T& operator ->() const
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

        //��������� const � ��-const ����������
        bool operator!=(const const_iterator& another) const
        {
            return current_node != another.current_node;
        }
        bool operator==(const const_iterator& another) const //��������� 2 ����������
        {
            return current_node == another.current_node;
        }
        friend const_iterator;
    private:
        node<T>* current_node;
    };
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator cend() const = 0;
    virtual const_iterator begin() const = 0;
    virtual const_iterator end() const = 0;
    virtual iterator begin() = 0;
    virtual iterator end() = 0;

    virtual int Push(const T e) = 0;
    virtual int Pop(T *e) = 0;
    virtual const T& GetFront() const = 0;
    virtual bool IsEmpty() const = 0;
    virtual int Size()= 0;
    virtual single_linked_list& operator = (const single_linked_list& List) = 0;
    friend std::ostream& operator << (std::ostream &stream, single_linked_list& l)
    {
        for (const_iterator it = l.cbegin(); it != l.cend(); ++it)
        {
            stream << *it << std::endl;
        }
        return stream;
    }
    friend std::istream& operator >> (std::istream &stream, single_linked_list& l)
    {
        T e;
        stream >> e;
        l.Push(e);
        return stream;
    }

protected:
    node<T>* top; //��������� �� ������� �����
};

#endif // ITERATORS_H_INCLUDED
