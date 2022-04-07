#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <stdio.h>
#include <string>
#include <windows.h>
#include "matrix.h"

typedef float** d_mat;

//��������� �������� ������� nXn
void create_mat(d_mat(&mat), long size) {
	for (int i = 0; i < size; i++)
		mat[i] = new float[size];
	//�������������� 0
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			mat[i][j] = 0;
}

//��������� ������ �� �����
void read_f_mat(FILE* fin, d_mat(&a), long size) {
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			fscanf(fin, "%f", (&a[i][j]));
}

//������� � �������� �-��
void clean_mat(d_mat(&mat), long size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
			mat[i][j] = 0;
		delete[] mat[i];
	}
	delete[] mat;
	mat = 0;
}

//��������� ������ ������� � ����
void write_f_mat(FILE* fout, d_mat(&a), long size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			fprintf(fout, "%f", a[i][j]);
			fprintf(fout, "%c", ' ');
		}
		fprintf(fout, "%c", '\n');
	}
	fprintf(fout, "%c", '\n');
}

//��������� ������ 2 ������ � ������� �������
void swap(d_mat(&mat), long size, int i, int i1) {
	int x;
	for (int j = 0; j < size; j++) {
		x = mat[i][j];
		mat[i][j] = mat[i1][j];
		mat[i1][j] = x;
	}
}

//��������� ������������ ������� �� ����� q
void mult_numXmat(d_mat a, long size, long q, d_mat(&b)) {
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			b[i][j] = a[i][j] * q;
}

//��������� ����� ������
void sum_mat(d_mat a, d_mat b, long size, d_mat(&c)) {
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			c[i][j] = a[i][j] + b[i][j];
}

//��������� ������������ ������� �� ������� (����������)
void mult_matXmat(d_mat a, d_mat b, long size, d_mat(&c)) {
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			for (int h = 0; h < size; h++)
				c[i][j] += a[i][h] * b[h][j];
}

//��������� ���������������� ���������� ������� 
void mat_transp(d_mat a, long size, d_mat(&c)) {
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			c[j][i] = a[i][j];
}

//��������� ������� ��������� �������
void create_unit_mat(d_mat(&e), long(&size)) {
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (i == j)
				e[i][j] = 1;
			else
				e[i][j] = 0;
}

//��������� ������� ��������� ������� ���� ��������� �������� � ������� 
int find_nozero_element_mat(d_mat(&mat), long size, int i, int j) {
	for (int i1 = i + 1; i1 < size; i1++)
		if (mat[i1][j] != 0)
			return i1;
	return -1;
}

//��������� ������ ��� ������ (���� �� ������ ��� ����� ��� �����, ����� ������� ������ �� ��������)
void step_gause(d_mat(&mat), long size, int i, int j) {
	float k;
	for (int h = i + 1; h < size; h++)
		if (mat[h][j] != 0) {
			k = mat[h][j] / mat[i][j];
			for (int l = j; l < size; l++)
				mat[h][l] -= k * mat[i][l];
		}
}

//��������� ������ ������� �����������
void make_triangle_mat(d_mat(&mat), long size) {
	int i1;
	for (int i = 0; i < size; i++) {
		//������� ���������� �������
		if (mat[i][i] != 0)
			step_gause(mat, size, i, i);
		else {
			//���� ���������� ������� 0, �� �������� �������� ��� ������ � �����-�� ������ ��� �� �� 0
			i1 = find_nozero_element_mat(mat, size, i, i);
			if (i1 != -1) {
				swap(mat, size, i, i1);
				step_gause(mat, size, i, i);
			}
		}
	}
}

//��������� �������� ������������ � ������������ �������
float count_det_A(d_mat(&mat), long size) {
	float det = 1;
	for (int i = 0; i < size; i++)
		det *= mat[i][i];
	return det;
}

//��������� ������� �������������� ����������� �� i ������ � j �������
void find_alg_dop(d_mat new_A, long size, int x, int y, d_mat(&alg_dop)) {
	int  x1, y1;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (x != i && y != j) {
				x1 = i;
				y1 = j;
				//���������� ������ ����������� ������� ��������� ������� � ������  
				if (i > x) x1--;
				if (j > y) y1--;
				alg_dop[x1][y1] = new_A[i][j];
			}
}

//��������� ������� �������� ������� (���� ��� ����������)
void find_reverse_mat(d_mat new_A, long size, d_mat(&reverse_A)) {
	if (size > 1) {
		double det_A;
		d_mat A = new float* [size], alg_dop = new float* [size - 1], reverse_A_T = new float* [size];

		create_mat(A, size);
		create_mat(reverse_A_T, size);
		create_mat(alg_dop, size - 1);

		mult_numXmat(new_A, size, 1, A);
		make_triangle_mat(A, size);
		det_A = count_det_A(A, size);

		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++) {
				//������� ���������������  ���������� 
				find_alg_dop(new_A, size, i, j, alg_dop);

				//������� ��  ������������ � ����������� � ������ i,  j (���� ������� �� �������� (i+j))
				make_triangle_mat(alg_dop, size - 1);
				reverse_A_T[i][j] = count_det_A(alg_dop, size - 1) / det_A;
				if ((i + j) % 2 == 1)
					reverse_A_T[i][j] *= -1;
			}

		//���������� ��������������� ��� �������
		mat_transp(reverse_A_T, size, reverse_A);

		clean_mat(A, size);
		clean_mat(reverse_A_T, size);
		clean_mat(alg_dop, size - 1);
	}
	else
		reverse_A[0][0] = 1 / new_A[0][0];
}

//��������� ���� ������������ ������� ������� ������ � ������� ��� � ����
void gause(FILE* fout, d_mat A, long size) {
	d_mat dop_A = new float* [size];
	create_mat(dop_A, size);

	//��������� ���:
	fprintf(fout, "\n��������� ���::\n");
	write_f_mat(fout, A, size);

	mult_numXmat(A, size, 1, dop_A);
	make_triangle_mat(dop_A, size);

	//����������� ���:
	fprintf(fout, "\n����������� ���:\n");
	write_f_mat(fout, dop_A, size);

	fprintf(fout, "\n������������ � - �� A\':\n");
	fprintf(fout, "%f", count_det_A(dop_A, size));
	fprintf(fout, "\n");
}

//���������� ���� ���� ��� ����� ����� (� ������� ���� �����) ��� ������ ������� ������� X
int solve_mat_equation(FILE* fout, d_mat A, d_mat B, long size, float b, d_mat(&X)) {
	d_mat new_A = new float* [size], e = new float* [size], dop_mat = new float* [size];
	create_mat(e, size);
	create_unit_mat(e, size);
	create_mat(new_A, size);
	create_mat(dop_mat, size);

	//�������� ��������� � ���� X*A'=B (�������� ���������) 
	mult_numXmat(e, size, b, e);
	sum_mat(A, e, size, new_A);

	//��������� ���������� ����� ������� � �, ��� ��� ��� �������� ������������
	//��� ����� ������� ������� �����������, ��� ������ �������� 
	mult_numXmat(new_A, size, 1, dop_mat);

	//���������, ��� ���� ������ ���������
	make_triangle_mat(dop_mat, size);

	if (count_det_A(dop_mat, size) == 0)
		return -1;
	else {
		//������� �������� �������
		d_mat reverse_A = new float* [size];
		create_mat(reverse_A, size);
		find_reverse_mat(new_A, size, reverse_A);

		//�������� �-��
		fprintf(fout, "\nA'+2:\n");
		write_f_mat(fout, new_A, size);

		//�������� �-��
		fprintf(fout, "\n�������� �-�� ��� A'+2:\n");
		write_f_mat(fout, reverse_A, size);

		//�������� ������� �������
		mult_matXmat(B, reverse_A, size, X);

		clean_mat(reverse_A, size);
	}

	clean_mat(e, size);
	clean_mat(new_A, size);
	clean_mat(dop_mat, size);

	return 1;
}

//��������� ������� f(A)=2x^2-7x-1
void f_A(FILE* fout, d_mat(&a), long size, d_mat(&b)) {
	d_mat e = new float* [size], minus_e = new float* [size], x1 = new float* [size], x2 = new float* [size], rez = new float* [size];
	create_mat(e, size);
	create_mat(minus_e, size);
	create_mat(x1, size);
	create_mat(x2, size);
	create_mat(rez, size);

	//������� ��������� ������� � ����� ���������
	create_unit_mat(e, size);
	mult_numXmat(e, size, -1, minus_e);

	fprintf(fout, "\nf(x):\n");

	//�^2
	mult_matXmat(a, a, size, x2);
	fprintf(fout, "\nx^2:\n");
	write_f_mat(fout, x2, size);
	//2x^2
	mult_numXmat(x2, size, 2, x1);
	fprintf(fout, "\n2x^2:\n");
	write_f_mat(fout, x1, size);
	//-7x
	mult_numXmat(a, size, -7, x2);
	fprintf(fout, "\n-7x:\n");
	write_f_mat(fout, x2, size);
	//2x^2-7x
	sum_mat(x1, x2, size, rez);
	fprintf(fout, "\n2x^2-7x:\n");
	write_f_mat(fout, rez, size);
	//f(x)=2x^2-7x-1
	sum_mat(rez, minus_e, size, b);
	fprintf(fout, "\nf(x)=2x^2-7x-1:\n");
	write_f_mat(fout, b, size);

	clean_mat(e, size);
	clean_mat(minus_e, size);
	clean_mat(x1, size);
	clean_mat(x2, size);
	clean_mat(rez, size);
}

//��������� ������� g(A)=2*x^2-x
void g_A(FILE* fout, d_mat(&a), long size, d_mat(&b)) {
	d_mat  x1 = new float* [size], x2 = new float* [size];
	create_mat(x1, size);
	create_mat(x2, size);

	fprintf(fout, "\ng(x):\n");

	//x^2
	mult_matXmat(a, a, size, x2);
	fprintf(fout, "\nx^2:\n");
	write_f_mat(fout, x2, size);
	//2x^2
	mult_numXmat(x2, size, 2, x1);
	fprintf(fout, "\n2x^2:\n");
	write_f_mat(fout, x1, size);
	//-x
	mult_numXmat(a, size, -1, x2);
	fprintf(fout, "\n-x:\n");
	write_f_mat(fout, x2, size);
	//g(x)=2x^2-x
	sum_mat(x1, x2, size, b);
	fprintf(fout, "\ng(x)=2x^2-x:\n");
	write_f_mat(fout, b, size);

	clean_mat(x1, size);
	clean_mat(x2, size);
}

//��������� ������� f(A)*g(A)
d_mat f_A_x_g_A(FILE* fout, d_mat A, long size) {

	d_mat fA = new float* [size], gA = new float* [size], rez = new float* [size];
	create_mat(fA, size);
	create_mat(gA, size);
	create_mat(rez, size);

	f_A(fout, A, size, fA);
	g_A(fout, A, size, gA);

	mult_matXmat(fA, gA, size, rez);
	fprintf(fout, "\nf(x)*g(x):\n");
	write_f_mat(fout, rez, size);
	clean_mat(fA, size);
	clean_mat(gA, size);

	return rez;
}

//��������� ������� ������ � ��������� ���� X * A + coeff * X = B
void matrix_equation(FILE* fout, d_mat A, d_mat B, long size, float coeff) {
	//������� ������� 
	d_mat X = new float* [size];
	create_mat(X, size);

	if (solve_mat_equation(fout, A, B, size, coeff, X) == -1)
		fprintf(fout, "%s", "� ��������� ��������� ��� �������");
	else {
		fprintf(fout, "\nX:\n");
		write_f_mat(fout, X, size);
	}

	//������ �� ����� �������
	clean_mat(X, size);
}