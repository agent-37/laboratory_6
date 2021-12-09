//Лаба  №6 выполнил Маслеников Иван
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <tchar.h>
#include <windows.h>
#include <stdio.h>
#include <string>
#include "matrix.h"
using namespace std;
#define FNAME_LEN 200

int main(long argc, char* argv[])
{

	long long i;
	char fname_in[FNAME_LEN], fname_out[FNAME_LEN];
	FILE* fin;
	FILE* fout;
	//проверяем на коректность файлы заданные коандной строкой
	if ((fin = fopen(argv[1], "rt")) == NULL || (fout = fopen(argv[2], "w")) == NULL) {
		cout << "Не удалось открыть файлы" << endl;
		cin >> fname_in;
		cin >> fname_out;
		while ((fin = fopen(fname_in, "rt")) == NULL || (fout = fopen(fname_out, "w")) == NULL)
		{
			cout << "Не удалось открыть файлы" << endl;
			cin >> fname_in >> fname_out;
		}
	}

	matrix_equation(fin, fout);

	fclose(fin);
	fclose(fout);
}

