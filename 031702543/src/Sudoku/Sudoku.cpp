// Sudoku.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#pragma warning(disable:4996)
using namespace std;

int num, gsiz, glen, gwid, single_bor[100][100], out_bor[10][100][100];
bool check(int x,int y,int i) //判断在(x,y)处数字i在同一行、列、宫是否唯一
{
	int l, w;
	for (l = 0; l < gsiz; l++) //按列检查同一行是否有重复
	{
		if (l != y&&single_bor[x][l] == i)
			return false;
	}
	for (w = 0; w < gsiz; w++)//按行检查同一列是否有重复
	{
		if (w != x&&single_bor[w][y] == i)
			return false;
	}
	if (glen != gsiz) //如果有宫
	{
		for (l = (x / glen)*glen; l < (x /glen)*glen +glen; l++) 
		{
			for (w = (y /gwid)*gwid; w < (y /gwid)*gwid +gwid; w++)
			{
				if (single_bor[l][w] == i)
				{
					if (l == x&&w == y)
						continue;
					else
						return false;
				}
			}
		}
	}
	return true;
}

bool DSF(int depth) //利用递归分别探求每个格子填入哪个数字
{
	//single_bor[0][0] = 1;
	int i, x, y;
	if (depth >= gsiz*gsiz)
		return true;
	x = depth / gsiz, y = depth % gsiz;
	if (single_bor[x][y] != 0)//（x,y)已赋值
		return DSF(depth + 1);
	else
	{
		for (i = 1; i <= gsiz; i++)
		{		
			if (check(x, y, i))
			{
				single_bor[x][y] = i;
				//cout << i << "填入" << depth << "\n"; 
				if (DSF(depth + 1))
					return true;
			}
			single_bor[x][y] = 0;
		}	
	}
	return false;
}
int main(int argc,char *argv[])
{
	int  i, j, k;
	int InputFile=0, OutputFile=0;
	string m = "-m",in = "-i", out = "-o",  n = "-n";
	if ( argc > 0 && argv != NULL)
	{
		for (i = 0; i < argc; i++)
		{
			
			if (argv[i] == in)
				InputFile = i + 1;
			if (argv[i] == out)
				OutputFile = i + 1;
			if(argv[i]==m)
				gsiz = atoi(argv[i + 1]);
			if(argv[i]==n)
				num = atoi(argv[i + 1]);
		}
	}
	else
	{
		cout << "未输入参数" << endl;
	}

	if (gsiz % 3 == 0)	
		glen = gsiz / 3,gwid = gsiz / glen;			
	else if (gsiz % 2 == 0)
		glen = gsiz / 2,gwid = gsiz / glen;		
	else
		glen = gsiz, gwid = gsiz;
		
	FILE* afile;
	afile = fopen(argv[InputFile], "r");
	if (afile == NULL)
	{
		cout << "cannot find input file" << endl;
		return 0;
	}
	for (i = 0; i < num; i++)
	{
		for(j = 0; j < gsiz; j++)
			for(k = 0;  k< gsiz; k++)
				fscanf(afile, "%d", &single_bor[j][k]);
		DSF(0);
		for (j = 0; j < gsiz; j++)
			for (k = 0; k < gsiz; k++)
				out_bor[i][j][k] = single_bor[j][k];
	}
	fclose(afile);
	
	afile = fopen(argv[OutputFile], "w");
	for (i = 0; i < num; i++)
	{
		for (j = 0; j < gsiz; j++)
		{
			for (k = 0; k < gsiz; k++)
			{
				fprintf(afile, "%d", out_bor[i][j][k]);
				if (k != gsiz - 1)				
					fprintf(afile, " ");			
			}
			if (j != gsiz - 1)			
				fprintf(afile, "\n");		
		}
		if (i != num - 1)	
			fprintf(afile, "\n\n");
					
	}
	fclose(afile);
    return 0;
}

