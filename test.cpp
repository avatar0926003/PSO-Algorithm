#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

double Ackley(int n, double* x)
/*
-Dimension: n arbitrary
- Domain: | x_i | <= 30.0
- Minimum 0 at x_i = 0.0
*/
{
	int i;
	double t, s1, s2;
	s1 = s2 = 0.0;
	for (i = 0; i < n; i++) {
		t = x[i];
		s1 += t * t;
		s2 += cos(2.0 * M_PI * x[i]);
	}   
	return -20.0 * exp(-0.2 * sqrt(s1 / n)) - exp(s2 / n) + 20.0 + M_E;
}


double Griewank(int n, double* x)
{
	int i;
	double sum = 0;
	double prod = 1;
	for (i = 0; i < n; i++) {
		sum += x[i] * x[i];
		prod *= cos(x[i] / sqrt((double)(i + 1)));//i+1可能不用
	}
	return sum / 4000.0 - prod + 1;
}


double Schwefel(int n, double* x)
/*
- Domain is | x_i | < 500
- Global minimum at fmin = -122569.5 at x_i = 420.9687
*/
{
	int i;
	double sum;
	sum = 0.0;
	for (i = 0; i < n; i++) {
		sum += x[i] * sin(sqrt(abs(x[i])));
	}
	return 418.9829*n-sum;
}

double SumSquares(int n, double* x)
/*
Dimension: n
Domain: | x[i] | <= 10
Global minimum: 0 at x[i] = 0
*/
{
	int i;
	double sum = 0;
	for (i = 0; i < n; i++) {
		sum += i * x[i] * x[i];
	}
	return sum;
}

double Zakharov(int n, double* x)
{
	int i;
	double input, squareSum = 0, sum = 0;
	for (i = 0; i < n; i++) {
		squareSum += x[i] * x[i];
		sum += 0.5 * i * x[i];
	}
	return squareSum + pow(sum, 2) + pow(sum, 4);
}

double Powell(int n, double* x)
{
	int j;
	double sum;
	sum = 0.0;
	for (j = 1; j <= n / 4; j++) {
		sum += pow(x[4 * j - 3 - 1] + 10 * x[4 * j - 2 - 1],2)
			+ 5 * pow(x[4 * j - 1 - 1] - x[4 * j - 1],2)
			+ pow(x[4 * j - 2 - 1] - 2 * x[4 * j - 1 - 1], 4)
			+ 10 * pow(x[4 * j - 3 - 1] - x[4 * j - 1], 4);
	}
	return sum;
}

double Rastrigin(int n, double* x)
/*
- Domain = | x_i | < 5.12
- Global minimum is 0.0 at x_i = 0.00
*/
{
	int i;
	double sum, t;
	if (n > 20) {
		n = 20;
	}
	sum = 0.0;
	for (i = 0; i < n; i++) {
		t = x[i];
		sum += t * t - cos(2.0 * M_PI * x[i]);
		//sum += t * t - 10*cos(2.0 * M_PI * x[i])+10;
	}
	return sum + n * 10;
	//return sum;
}

double Sphere(int n, double* x)
/*
- Domain: | x[i] | < 10
- Global minimum: 0 at x[i] = 0
*/
{
	int i;
	double sum;
	sum = 0.0;
	for (i = 0; i < n; i++) {
		sum += x[i] * x[i];
	}
	return sum;
}


double Rosenbrock(int n, double* x)
{
	double s = 0.0;
	int i;
	for (i = 1; i < n; i++)
		s += 100.0 * pow(x[i] - x[i - 1] * x[i - 1], 2) + pow(x[i - 1] - 1.0, 2);
	return s;
}

double Michalewicz(int n, double* x)
{
	double s = 0.0;
	for (int i = 0; i < n; i++) {
		s += sin(x[i]) * pow(sin(i * x[i] * x[i] / M_PI), 20);
	}
	return -s;
}