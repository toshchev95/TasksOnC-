#pragma once
#include <iostream>

template< typename T >
class List;
 
template< typename T >
bool operator==(const List< T > &, const List< T > &);
template< typename T >
bool operator!=(const List< T > &, const List< T > &);
 
template< typename T >
class List
{
public:

    struct Node
    {
        Node(const T &data):
        m_data(data),
		m_next(0),
        m_prev(0)
        {
        }
 
        T m_data;
        Node *m_next;
        Node *m_prev;
    };
 
public:
    List():
    m_head(),
    m_tail(),
    m_size()
    {
    }
 
    List(const List &source):
    m_head(),
    m_tail(),
    m_size()
    {
        Node *i = source.m_head;
 
        while (i != 0)
        {
            push_back(i->m_data);
 
            i = i->m_next;
        }
    }
 
    ~List()
    {
        clear();
    }

    size_t size() const
    {
        return m_size;
    }
 
    bool is_empty() const
    {
        return m_size == 0;
    }
 
    void clear()
    {
        while (m_size != 0)
            pop_back();
    }
 
    void push_back(const T &data)
    {
        Node *add_elem = new Node (data);

        if (m_size == 0)
        {
            m_head = add_elem;
			m_head->m_prev = 0;
        }
        else
        {
            m_tail->m_next = add_elem;
            add_elem->m_prev = m_tail;
        }
 
        m_tail = add_elem;
		m_tail->m_next = 0;
 
        ++m_size;
    }
 
    T pop_back()
    {
        if (m_size == 0)
            return T ();
 
        T ret_elem = m_tail->m_data;
        Node *new_tail = m_head == m_tail ? 0 : m_tail->m_prev;
 
        delete m_tail;
 
        if (m_head == m_tail)
            m_head = 0;
 
        m_tail = new_tail;
 
        --m_size;
 
        return ret_elem;
    }
 
    void push_front(const T &data)
    {
        Node *add_elem = new Node (data);
 
        if (m_size == 0)
        {
            m_tail = add_elem;
			m_tail->m_next = 0;
        }
        else
        {
            m_head->m_prev = add_elem;
            add_elem->m_next = m_head;
        }
 
        m_head = add_elem;
 
        ++m_size;
    }
 
    T pop_front()
    {
        if (m_size == 0)
            return T ();
 
        T ret_elem = m_head->m_data;
        Node *new_head = m_head == m_tail ? 0 : m_head->m_next;
 
        delete m_head;
 
        if (m_head == m_tail)
            m_tail = 0;
 
        m_head = new_head;
		m_head->m_prev = 0;
 
        --m_size;
 
        return ret_elem;
    }
	
	void push_index(const T &data, size_t index)
	{
		std::cout<<"PUSH"<<std::endl;
		Node *add_elem = new Node (data);
		Node *nodeList;
		if (index == 0)
		{
			push_front(data);
			return;
		}
		else if (m_size - 1 == index)
		{
			push_back(data);
			return;
		}
		else if (index > m_size)
			return;

		if (index < (m_size + 1) / 2)
		{
			nodeList = m_head;
			for (size_t i = 0; i < index; i++)
				nodeList = nodeList->m_next;
		}
		else
		{
			nodeList = m_tail;
			for (size_t i = 0; i < m_size - index - 1; i++)
				nodeList = nodeList->m_prev;
		}
		
		add_elem->m_prev = nodeList->m_prev;
		add_elem->m_next = nodeList;
		nodeList->m_prev = add_elem;
		add_elem->m_prev->m_next = add_elem;
        

		++m_size;
	}

	T pop_index(size_t index)
	{
		if (m_size == 0)
            return T ();
		
		if (index == 0)
		{
			pop_front();
			return T ();
		}
		else if (m_size - 1 == index)
		{
			pop_back();
			return T();
		}
		else if (index > m_size)
			return T ();

        T ret_elem;
		Node *nodeList;
		if (index < (m_size + 1) / 2)
		{
			nodeList = m_head;
			for (size_t i = 0; i < index; i++)
				nodeList = nodeList->m_next;
		}
		else
		{
			nodeList = m_tail;
			for (size_t i = 0; i < m_size - index - 1; i++)
				nodeList = nodeList->m_prev;
		}

		ret_elem = nodeList->m_data;

		Node *node = nodeList->m_prev;
		node->m_next = nodeList->m_next;
		node->m_next->m_prev = node;
		delete nodeList;

		--m_size;
		return ret_elem;
	}
	
	void push_elem(Node* elem, T value) 
	{
		if (elem == 0) 
		{
			exit(1);
		}
     
		if (!elem->m_prev) 
		{
			push_front(value);
			return;
		}

		Node *add_elem = new Node(value);
		add_elem->m_prev = elem->m_prev;
		elem->m_prev->m_next = add_elem;
		add_elem->m_next = elem;
		elem->m_prev = add_elem;
 
		++m_size;
	}

    friend bool operator==< >(const List< T > &left, const List< T > &right);
    friend bool operator!=< >(const List< T > &left, const List< T > &right);
 
    List<T> &operator=(const List<T> &source)
    {
        if (this != &source)
        {
            clear();
 
            Node *i = source.m_head;
 
            while (i != source.m_tail)
            {
                push_back(i->m_data);
 
                i = i->m_next;
            }
        }
 
        return *this;
    }
protected:
	Node* getHead()
	{
		return m_head;
	}
	Node* getTail()
	{
		return m_tail;
	}
	size_t getSize()
	{
		return m_size;
	}
	void decSize()
	{
		--m_size;
	}
	void incSize()
	{
		++m_size;
	}
protected:
    Node *m_head;
    Node *m_tail;
    size_t m_size;
};
 
template< typename T >
bool operator==(const List< T > &left, const List< T > &right)
{
    if (left.m_size != right.m_size)
        return false;
 
    List< T >::Node *p_left = left.m_head;
    List< T >::Node *p_right = right.m_head;
 
    while (p_left != left.m_tail)
    {
        if (p_left->m_data != p_right->m_data)
            return false;
 
        p_left = p_left->m_next;
        p_right = p_right->m_next;
    }

    return true;
}
 
template< typename T >
bool operator!=(const List< T > &left, const List< T > &right)
{
    return !(left == right);
}