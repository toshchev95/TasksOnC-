#pragma once
#include <iostream>
#include "ListPerson.cpp"
#include "List.cpp"

static int NUMBER_CHILDS = 0;//2;
const std::string filename = "input.txt";
const std::string filename_ = "input_.txt";
//typedef List<Person>::Node Node;
/*
Andy 19 13.05.1994
Dandy 23 17.10.1992
Drew 21 02.01.1995
Merry 80 05.12.1946
kok 32 20.06.1984
Mario 9 12.12.2005

*/
int main(){
	try
	{
		ListPerson list;
		Person *child;
		std::string name, date;
		int age;

		list.read_from_file(filename_);
		//list.write_all();
		for (int i = 0; i < NUMBER_CHILDS; i++)
		{
			std::cin>>name>>age>>date;
			child = new Person(name, age, Date(date));
			list.push_back(*child);
		}


		
		child = new Person("Andrey", 21, Date("13.09.1995"));
		list.push_index((*child), 4);
		list.write_all();
		list.pop_index(2);
		list.write_all();
		list.write_in_file(filename);
		list.clear();

		list.read_from_file(filename);
		list.write_all_reverse();
		list.pop_name("Andrey");
		list.write_all();
		list.sort_name();
		list.write_all();
		std::cout<<std::endl;
	}
	catch(...)
	{
		std::cout<<"Exception"<<std::endl;
	}
	
	return 0;
}