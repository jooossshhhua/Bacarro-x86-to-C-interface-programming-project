#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>

extern void daxpy_asm(int n, double a, double x[], double y[], double z[]);

void random_num(int n, double X[], double Y[]) {
	for (int i = 0; i < n; i++) {
		X[i] = ((double)rand());
		Y[i] = ((double)rand());
	}
}
void daxpy_c(int n, double a, double x[], double y[], double z[]) {

	for (int i = 0; i < n; i++) {
		z[i] = (a * x[i]) + y[i];
	}
}
void output(double z[]) {
	for (int i = 0; i < 10; i++) {
		printf("%.2f \n", z[i]);
	}
	printf("\n");
}

int main() {
	srand((unsigned int)time(NULL));
	clock_t start_time, end_time;
	double a = 2.0;
	int n = 1048576; // 2^20
	double* x = (double*)malloc(n * sizeof(double));
	double* y = (double*)malloc(n * sizeof(double));
	double* z = (double*)malloc(n * sizeof(double));
	random_num(n, x, y);

	double time_c = 0.0;
	double ave_time_c = 0.0;
	double total_time_c = 0.0;
	
	for (int i = 0; i < 30; i++) {
		start_time = clock();
		daxpy_c(n, a, x, y, z);
		end_time = clock();
		time_c = (double)(end_time - start_time) / CLOCKS_PER_SEC;
		total_time_c += time_c;

	}
	ave_time_c = total_time_c / 30;

	double time_asm = 0.0;
	double ave_time_asm = 0.0;
	double total_time_asm = 0.0;

	for (int i = 0; i < 30; i++) {
		start_time = clock();
		daxpy_asm(n, a, x, y, z);
		end_time = clock();
		time_asm = (double)(end_time - start_time) / CLOCKS_PER_SEC;
		total_time_asm += time_asm;
	}
	ave_time_asm = time_asm / 30;

	printf("C: Average Execution time is %f seconds\n", ave_time_c);
	output(z);
	printf("\n");

	printf("ASM: Average Execution time is %f seconds\n", ave_time_asm);
	output(z);
	printf("\n");

	free(x);
	free(y);
	free(z);
	return 0;
}