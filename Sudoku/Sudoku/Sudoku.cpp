// Sudoku.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#pragma warning(disable:4996)
using namespace std;

int main()
{
	int num, size, i,j, k;
	int buff[1024];
	
	/*fstream afile;
	afile.open("C:\\Users\\dell\\Desktop\\input.txt", ios::in);
	afile >> buff;
	for (i = 0; i < 5; i++)
		cout << buff[i];*/
	
	FILE* afile;
	afile = fopen("C:\\Users\\dell\\Desktop\\input.txt", "r");
	for (i = 0; i < 5; i++)
		fscanf(afile, "%d", &buff[i]);	
	for (i = 0; i < 5; i++)
		cout << buff[i];

	/*int argc,char *argv[]

	size = atoi(argv[2]);
	num = atoi(argv[4]);

	cout << argc << endl;
	for (i = 0; i < argc; i++)
	{
		n = strlen(argv[i]);
		cout << n << " ";
		cout << argv[i] << endl;
	}*/
		
    return 0;
}

