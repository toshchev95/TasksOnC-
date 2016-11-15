#pragma once
#include <iostream>
using namespace std;
#include <list>
#include <string>
#include <sstream>
#include <vector>

class MatrixWords
{
private:
	MatrixWords();
	MatrixWords(int, int);
	MatrixWords& operator=( MatrixWords& );
public:
	static MatrixWords& Instance(int, int);    
	void push_index2d(int, int, const std::string&);
	void pop_index2d(int, int);
	void pop_cells();
protected:
	MatrixWords( const MatrixWords& );
	~MatrixWords();
private:
	void split(const std::string &s, char, std::vector<std::string> &);
	std::vector<std::string> split(const std::string &, char);


private:
	int m_,n_;
	std::list<std::string>** matListOfString;
	static MatrixWords* p_instance;
};