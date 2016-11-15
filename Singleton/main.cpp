#include "MatrixWords.cpp"

MatrixWords * MatrixWords::p_instance = 0;

void test(MatrixWords& element)
{
	element.push_index2d(1,1, "adfasdfasdfasdf\n");
	element.pop_index2d(1,1);
	std::cout<<"\n";
	element.push_index2d(1,1, "123413241234134 1341234 12341243\n");

	element.pop_cells();
}

int main(){
	try 
	{
		MatrixWords& s = MatrixWords::Instance(2, 2);
		MatrixWords& s1 = MatrixWords::Instance(3, 2);
		MatrixWords b();

		if (&s != &s1)
			throw int();
		else
			throw char();
	}
	catch(int x){
		std::cout<<"Exception MatrixWords"<<std::endl;
	}
	catch(...){
		try
		{
			std::cout<<"Exception"<<std::endl;
			MatrixWords& s = MatrixWords::Instance(1, 1);
			test(s);
		}
		catch(...)
		{}
	}
	system("pause");
	return 0;
}