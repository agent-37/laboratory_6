#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <stdio.h>
#include <string>
#include <windows.h>
#include "matrix.h"

using namespace std;

#define FNAME_LEN 200

int main(int argc, char* argv[])
{
	//локализация русских букв
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char fname_in[FNAME_LEN], fname_out[FNAME_LEN];
	FILE* fin;
	FILE* fout;

	//проверяем на коректность файлы заданные командной строкой
	if ((fin = fopen(argv[1], "r")) == NULL || (fout = fopen(argv[2], "w")) == NULL) {
		cout << "Не удалось открыть файлы\n";
		cout << "Введите файл для чтения: ";
		cin >> fname_in;
		cout << "\nВведите файл для вывода: ";
		cin >> fname_out;

		while ((fin = fopen(fname_in, "r")) == NULL || (fout = fopen(fname_out, "w")) == NULL) {
			cout << "\nНе удалось открыть файлы\n";
			cout << "Введите файл для чтения: ";
			cin >> fname_in;
			cout << "\nВведите файл для вывода: ";
			cin >> fname_out;
		}
	}

	long size = 0;
	float coeff;
	fscanf(fin, "%li", &size);
	fscanf(fin, "%f", &coeff);

	if (size > 0) {
		d_mat A = new float* [size], B = new float* [size], E = new float* [size];
		d_mat res_A = new float* [size], res_B = new float* [size];
		d_mat dop_mat_0 = new float* [size], dop_mat_1 = new float* [size], dop_mat_2 = new float* [size];
		create_mat(A, size);
		create_mat(B, size);
		create_mat(res_A, size);
		create_mat(res_B, size);
		create_mat(dop_mat_1, size);
		create_mat(dop_mat_2, size);
		create_mat(dop_mat_0, size);
		read_f_mat(fin, A, size);
		read_f_mat(fin, B, size);

		//находим A'=f(A+3)*g(A+3)
		create_mat(E, size);
		create_unit_mat(E, size);
		mult_numXmat(E, size, 3, dop_mat_0);
		sum_mat(A, dop_mat_0, size, dop_mat_1);
		//A+3
		fprintf(fout, "\nA+3:\n");
		write_f_mat(fout, dop_mat_1, size);
		res_A = f_A_x_g_A(fout, dop_mat_1, size);

		//A'
		fprintf(fout, "\nA':\n");
		write_f_mat(fout, res_A, size);

		//Находим B'=f(B*A)*g(B*A)
		mult_matXmat(B, A, size, dop_mat_2);
		//B*A
		fprintf(fout, "\nB*A:\n");
		write_f_mat(fout, dop_mat_2, size);
		res_B = f_A_x_g_A(fout, dop_mat_2, size);

		//B'
		fprintf(fout, "\nB':\n");
		write_f_mat(fout, res_B, size);

		clean_mat(dop_mat_0, size);
		clean_mat(dop_mat_1, size);
		clean_mat(dop_mat_2, size);
		clean_mat(A, size);
		clean_mat(B, size);

		//Находим определитель матрицы A' приведением ее к треугольному виду
		gause(fout, res_A, size);

		//X * A' + 2X = B' находим X
		matrix_equation(fout, res_A, res_B, size, coeff);
		clean_mat(res_A, size);
		clean_mat(res_B, size);
		clean_mat(E, size);
	}
	else
		fprintf(fout, "%s", "Введен неправильный параметр size");

	fclose(fin);
	fclose(fout);
}
//132