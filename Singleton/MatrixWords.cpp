#pragma once
//!!! - right
//#include "MatrixWords.h"
#include <iostream>
using namespace std;
#include <list>
#include <string>
#include <sstream>
#include <mutex>
#include <vector>
//  

/*
–еализуйте класс на —++ представл€ющий собой матрицу N на M (N,M <= 10000) из €чеек 
хран€щих набор строк, в программе должен создаватьс€ только один экземпл€р класса.

¬ классе должны быть реализованы методы позвол€ющие:

- добавить в любую €чейку слово (количество вызовов <=1000)

- вывести дл€ €чейки слова хран€щиес€ в ней

- вывести дл€ всех €чеек слова хран€щиес€ в них

*/

class MatrixWords{

	MatrixWords(int n, int m):m_(m), n_(n)
	{
		matListOfString = new list<string>*[n];
		for (int i = 0; i < n; i++)
			matListOfString[i] = new list<string>[m];
	}
	
	MatrixWords() {}
	MatrixWords& operator= (MatrixWords& other){}
public:
	
	static MatrixWords& Instance(int n, int m) {

		if(!p_instance)     
		{
			std::lock_guard<std::mutex> lock(mutLock);
			if (!p_instance)
				p_instance = new MatrixWords(n, m);
		}
		return *p_instance;
	}
	
	void push_index2d(int xCell, int yCell, const std::string& data)
	{
		matListOfString[xCell][yCell].push_back(data);
	}
	void pop_index2d(int xCell, int yCell)
	{
		list<string> listString = matListOfString[xCell][yCell];
		std::vector<std::string>  sArr;
		for (list<string>::iterator it = listString.begin();
			it != listString.end(); it++)
		{
			sArr = split((*it), ' ');
			for (std::vector<std::string>::const_iterator i = sArr.begin(); 
				 i != sArr.end(); ++i)
				std::cout << *i << ' ';
			std::cout<<'\n';
		}
	}

	void pop_cells()
	{
		for (int i = 0; i < n_; i++)
		{
			for (int j = 0; j < m_; j++)
				pop_index2d(i, j);
		}
	}
protected:
	MatrixWords( const MatrixWords& other)
	{
		n_ = other.n_;
		m_ = other.m_;
		matListOfString = other.matListOfString;
		p_instance = other.p_instance;
	}
	
	~MatrixWords()
	{
		for (int i = 0; i < n_; i++)
			delete[] matListOfString[i];
		delete[] matListOfString;
	}
private:
	void split(const std::string &s, char delim, std::vector<std::string> &elems) {
		std::stringstream ss;
		ss.str(s);
		std::string item;
		while (std::getline(ss, item, delim)) {
			elems.push_back(item);
		}
	}

	std::vector<std::string> split(const std::string &s, char delim) {
		std::vector<std::string> elems;
		split(s, delim, elems);
		return elems;
	}

private:
	static std::mutex mutLock;
	static MatrixWords* p_instance;
	int m_,n_;
	std::list<std::string>** matListOfString;
};


//!!! - right
/*
	MatrixWords::MatrixWords(int n, int m):m_(m), n_(n)
	{
		matListOfString = new list<string>*[n];
		for (int i = 0; i < n; i++)
			matListOfString[i] = new list<string>[m];
	}
	
	MatrixWords::MatrixWords() {}
	MatrixWords& MatrixWords::operator= (MatrixWords& other){return *this;}
	
	MatrixWords& MatrixWords::Instance(int n, int m) {
		if(!p_instance)     
		{
			p_instance = new MatrixWords(n, m);
		}
		return *p_instance;
	}
	
	void MatrixWords::push_index2d(int xCell, int yCell, const std::string& data)
	{
		matListOfString[xCell][yCell].push_back(data);
	}
	void MatrixWords::pop_index2d(int xCell, int yCell)
	{
		list<string> listString = matListOfString[xCell][yCell];
		std::vector<std::string>  sArr;
		for (list<string>::iterator it = listString.begin();
			it != listString.end(); it++)
		{
			sArr = split((*it), ' ');
			for (std::vector<std::string>::const_iterator i = sArr.begin(); 
				 i != sArr.end(); ++i)
				std::cout << *i << ' ';
			std::cout<<'\n';
		}
	}

	void MatrixWords::pop_cells()
	{
		for (int i = 0; i < n_; i++)
		{
			for (int j = 0; j < m_; j++)
				pop_index2d(i, j);
		}
	}

	MatrixWords::MatrixWords( const MatrixWords& other)
	{
		n_ = other.n_;
		m_ = other.m_;
		matListOfString = other.matListOfString;
		p_instance = other.p_instance;
	}
	
	MatrixWords::~MatrixWords()
	{
		for (int i = 0; i < n_; i++)
			delete[] matListOfString[i];
		delete[] matListOfString;
	}

	void MatrixWords::split(const std::string &s, char delim, std::vector<std::string> &elems) {
		std::stringstream ss;
		ss.str(s);
		std::string item;
		while (std::getline(ss, item, delim)) {
			elems.push_back(item);
		}
	}

	std::vector<std::string> MatrixWords::split(const std::string &s, char delim) {
		std::vector<std::string> elems;
		split(s, delim, elems);
		return elems;
	}

	*/