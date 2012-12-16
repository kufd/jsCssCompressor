#include <iostream>
#include <string>
#include "../compressor.class.h"

using namespace std;

int main()
{

	Compressor compresor;

	compresor.addJs("1.txt");
	compresor.addJs("2.txt");
	compresor.addJs("3.txt");

	//compresor.addCss("/ddd.css");
	//compresor.addCss("/ddd1.css");

	//cout<<compresor.getCss()<<endl;
	cout<<compresor.getJs()<<endl;

}



