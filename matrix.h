
#ifndef _MATRIX_H_
#define _MATRIX_H_
typedef float** d_mat;
//процедура  создания матрицы nXn
void create_mat(d_mat(&fA), long n);

//процедура  чтения из файла
void read_f_mat(FILE* fin, d_mat(&a), long n);

//процедура записи матрицы в файл
void write_f_mat(FILE* fout, d_mat(&a), long n);

//процедура меняет 2 строки в матрице местами
void swap(d_mat(&mat), long n, int i, int i1);

//процедура произведения матрицы на число q
void mult_numXmat(d_mat a, long n, long q, d_mat(&b));

//процедура суммы матриц
void sum_mat(d_mat a, d_mat b, long n, d_mat(&c));

//процедура произведения матрицы на матрицу (квадратных)
void mult_matXmat(d_mat a, d_mat b, long n, d_mat(&c));

//процедура транспонировании квадратной матрицы 
void mat_transp(d_mat a, long n, d_mat(&c));

//процедура создает единичную матрицу
void create_unit_mat(d_mat(&e), long(&n));

//процедура находит ненулевой элемент ниже заданного элемента в столбце 
int find_nozero_element_mat(d_mat(&mat), long n, int i, int j);

//процедура делает шаг гаусса (если не знаешь что такое шаг гауса, лучше почитай теорию по матрицам)
void step_gause(d_mat(&mat), long n, int i, int j);

//процедура делает матрицу треугольной
void make_triangle_mat(d_mat(&mat), long n);

//процедура считатет определитель  у треугольноый матрицы
float count_det_A(d_mat(&mat), long n);

//процедура находит алгеоброичекое дополнеиние по i строке и j столбцу
void find_alg_dop(d_mat new_A, long n, int x, int y, d_mat(&alg_dop));

//процедура находит обратную матрицу (если она существует)
void find_reverse_mat(d_mat new_A, long n, d_mat(&reverse_A));

//процедура ищет определитель матрицы методом гаусса и выводи его в файл
void gause(FILE* fin, FILE* fout);

//возврощает флаг того что можно найти (и находит если можно) или нельзя искомую матрицу X
int solve_mat_equation(d_mat A, d_mat C, long n, long b, d_mat(&X));

//процедура считает f(A)=2x^2-7x-1
void f_A(FILE* fout, d_mat(&a), long n, d_mat(&b));

//процедура считает g(A)=2*x^2-x
void g_A(FILE* fout, d_mat(&a), long n, d_mat(&b));

//процедура считает f(A)*g(A)
void f_A_x_g_A(FILE* fin, FILE* fout);

//процедура находи корень у уравнения вида X * A + b * X = C
void matrix_equation(FILE* fin, FILE* fout);
#endif // _MATRIX_H_