#include <iostream>
#include <string>
#include "../compressor.class.h"

using namespace std;

int main()
{

	Compressor compresor;

	compresor.addJs("/ddd.js");
	compresor.addJs("/ddd1.js");

	compresor.addCss("/ddd.css");
	compresor.addCss("/ddd1.css");

	cout<<compresor.getCss()<<endl;
	cout<<compresor.getJs()<<endl;

}



