#ifndef _MATRIX_H_
#define _MATRIX_H_

typedef float** d_mat;

//���������  �������� ������� nXn
void create_mat(d_mat(&fA), long n);

//���������  ������ �� �����
void read_f_mat(FILE* fin, d_mat(&a), long n);

//������� � �������� �-��
void clean_mat(d_mat(&mat), long size);

//��������� ������ ������� � ����
void write_f_mat(FILE* fout, d_mat(&a), long n);

//��������� ������ 2 ������ � ������� �������
void swap(d_mat(&mat), long n, int i, int i1);

//��������� ������������ ������� �� ����� q
void mult_numXmat(d_mat a, long n, long q, d_mat(&b));

//��������� ����� ������
void sum_mat(d_mat a, d_mat b, long n, d_mat(&c));

//��������� ������������ ������� �� ������� (����������)
void mult_matXmat(d_mat a, d_mat b, long n, d_mat(&c));

//��������� ���������������� ���������� ������� 
void mat_transp(d_mat a, long n, d_mat(&c));

//��������� ������� ��������� �������
void create_unit_mat(d_mat(&e), long(&n));

//��������� ������� ��������� ������� ���� ��������� �������� � ������� 
int find_nozero_element_mat(d_mat(&mat), long n, int i, int j);

//��������� ������ ��� ������ (���� �� ������ ��� ����� ��� �����, ����� ������� ������ �� ��������)
void step_gause(d_mat(&mat), long n, int i, int j);

//��������� ������ ������� �����������
void make_triangle_mat(d_mat(&mat), long n);

//��������� �������� ������������ � ������������ �������
float count_det_A(d_mat(&mat), long n);

//��������� ������� ������������� ����������� �� i ������ � j �������
void find_alg_dop(d_mat new_A, long n, int x, int y, d_mat(&alg_dop));

//��������� ������� �������� ������� (���� ��� ����������)
void find_reverse_mat(d_mat new_A, long n, d_mat(&reverse_A));

//��������� ���� ������������ ������� ������� ������ � ������� ��� � ����
void gause(FILE* fout, d_mat A, long n);

//���������� ���� ���� ��� ����� ����� (� ������� ���� �����) ��� ������ ������� ������� X
int solve_mat_equation(FILE* fout, d_mat A, d_mat C, long n, long b, d_mat(&X));

//��������� ������� f(A)=2x^2-7x-1
void f_A(FILE* fout, d_mat(&a), long n, d_mat(&b));

//��������� ������� g(A)=2*x^2-x
void g_A(FILE* fout, d_mat(&a), long n, d_mat(&b));

//��������� ������� f(A)*g(A)
d_mat f_A_x_g_A(FILE* fout, d_mat A, long n);

//��������� ������� ������ � ��������� ���� X * A + coeff * X = B
void matrix_equation(FILE* fout, d_mat A, d_mat B, long n, float coeff);

#endif // _MATRIX_H_