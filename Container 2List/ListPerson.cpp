#pragma once
#include <iostream>
#include "List.cpp"
#include <fstream>
#include <string>
#include "stdlib.h"


class ListPerson;

struct Date{
	int m_year;
	int m_month;
	int m_day;
	std::string m_date;

	Date(int year = 0, int month = 0, int day = 0):
	m_year(year), m_month(month), m_day(day)
	{
		m_date = std::to_string(day) + "." 
			   + std::to_string(month) + "." + std::to_string(year);
	}
	Date(const std::string & date)
	{
		if (date.length() == 10)
		{
			m_date = date;
			m_day   = atoi(date.substr(0,2).c_str());
			m_month = atoi(date.substr(3,2).c_str());
			m_year  = atoi(date.substr(6,4).c_str());
		}
	}
};

struct Person
{
	Person(std::string name = "",
			const int & growth = 0,
			const Date & date = Date()):
	m_name(name),
	m_growth(growth),
	m_dateBirthDay(date)
	{
	}
	std::string m_name;
	int m_growth;
	Date m_dateBirthDay;
};

class ListPerson: public List< Person > {

	ListPerson & ListPerson::operator=(ListPerson & list)
	{
		(*this).clear();
		this->m_size = list.m_size;
		this->m_head = list.m_head;
		this->m_tail = list.m_tail;
		return *this;
	}
public:
	void write_all()
	{
		std::cout<<std::endl;
		std::cout<<"WRITE"<<std::endl;
		Node *nodeList = getHead(),
			 *m_tail = getTail();
		while(nodeList != m_tail->m_next)
		{
			Person data = nodeList->m_data;
			std::string str_data = data.m_name + ' ';
			std::cout<<str_data.c_str()<<data.m_growth<<" "
				<<data.m_dateBirthDay.m_date<<std::endl;
			nodeList = nodeList->m_next;
		}
	}
	void write_all_reverse()
	{
		std::cout<<"WRITE REVERSE"<<std::endl;
		Node *nodeList = getTail(),
			 *m_head = getHead();
		
		while(nodeList != m_head->m_prev)
		{
			Person data = nodeList->m_data;
			std::string str_data = data.m_name + ' ';
			std::cout<<str_data.c_str()<<data.m_growth<<" "
				<<data.m_dateBirthDay.m_date<<std::endl;
			nodeList = nodeList->m_prev;
		}
	}
	void pop_name(const std::string & name)
	{
		Node *nodeList = getHead(),
			 *m_tail = getTail();
		std::string m_name;
		while(nodeList != m_tail->m_next)
		{
			m_name = nodeList->m_data.m_name;
			if ( m_name == name )
			{
				
				Node *node = nodeList->m_prev;
				node->m_next = nodeList->m_next;
				node->m_next->m_prev = node;

				delete nodeList;

				decSize();

				nodeList = node;
			}
			nodeList = nodeList->m_next;
		}
	}

	void sort_name() 
	{
		std::cout<<std::endl;
		std::cout<<"Sotring!"<<std::endl;
		ListPerson *out = new ListPerson;
		Node *sorted, *sortTail;
		Node *unsorted, *unsTail;
		
		(*out).push_front(pop_front());
		unsTail  = getTail();
		unsorted = getHead();
		while (unsorted != unsTail->m_next) {
			sorted = (*out).getHead();
			sortTail = (*out).getTail();
			while ( (sorted != sortTail->m_next) && 
					cmp(unsorted->m_data.m_name, sorted->m_data.m_name)) 
				sorted = sorted->m_next;
			if (sorted != sortTail->m_next) 
				(*out).push_elem(sorted, unsorted->m_data);
			else 
				(*out).push_back(unsorted->m_data);
			unsorted = unsorted->m_next;
		}

		*this = *out;
	}	

	void write_in_file(const std::string & filename)
	{
		std::cout<<std::endl;
		std::cout<<"WRITE in FILE"<<std::endl;
		Node *nodeList = getHead(),
			 *m_tail = getTail();
		std::string input;
		Person child;
		while (nodeList != m_tail->m_next)
		{
			child = nodeList->m_data;
			input += child.m_name + " " + std::to_string(child.m_growth) 
				  + " " + child.m_dateBirthDay.m_date + "\n";
			nodeList = nodeList->m_next;
		}
		std::ofstream out(filename);
		out << input;
		out.close();
	}
	
	ListPerson & read_from_file(const std::string & filename)
	{
		std::cout<<std::endl;
		std::cout<<"READ"<<std::endl;
		ListPerson list;
		Person *child;
		int boundString, bound, boundDate;

		
		std::ifstream in(filename);
		std::string s((std::istreambuf_iterator<char>(in)), 
					   std::istreambuf_iterator<char>());
		in.close();

		while ((boundString = s.find("\n")) != std::string::npos)
		{
			std::string str = s.substr(0, boundString);
			bound = str.find(" ");
			boundDate = str.substr(bound + 1).find(" ");
			Date dateBirthDay(str.substr(bound+boundDate+2).c_str());
			child = new Person( str.substr(0, bound), 
					atoi(str.substr(bound+1, bound+boundDate).c_str()),
					dateBirthDay.m_date );
			(*this).push_back(*child);
			s = s.substr(boundString + 1);
		}
		return *this;
	}
	
private:
	int cmp(const std::string &unsort, const std::string &sort)
	{
		return unsort > sort;
	}
};