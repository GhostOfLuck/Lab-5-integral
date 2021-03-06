#include "pch.h"
#include "pch.h"
#include <iostream>
#include<iomanip>
#include <cmath>
using namespace std;
double first_func(double x)
{
	return (x*x*x*exp(2 * x));
}
double second_func(double x)
{
	return 1 / (1 + sqrt(x));
}
double third_func(double x)
{
	return 1 / ((x + 1)*(sqrt(x*x + 1)));
}
double integral_mid(double(*func)(double), double b, double a, double ebs, double pribl2, int &k)
{
	double pribl1;
	double h = b - a;
	for (double x = a; x <= b; x += h)
	{
		pribl2 += func(x);
	}
	do {
		pribl1 = pribl2;
		k *= 2;
		h = (b - a) / k;
		pribl2 = 0;
		for (double x = a; x <= b; x += h)
		{
			pribl2 += func(x);
		}
		pribl2 *= h;
	} while (fabs(pribl1 - pribl2) > ebs);
	return pribl2;
}
double sim(double(*func)(double), double a, double b, double eps, double value_first, int &steps)
{
	double value_last = eps + 1;
	int n = 4;
	do
	{
		double h, sum2 = 0, sum4 = 0, summa = 0;
		h = (b - a) / (2.0 * (double)n);
		for (int i = 1; i <= 2 * n - 1; i += 2)
		{
			sum2 += func(a + h * (i + 1));
			sum4 += func(a + h * i);
		}
		summa = func(a) + 4 * sum4 + 2 * sum2 - func(b);
		value_last = value_first;
		value_first = (h / 3)*summa;
		steps = n;
		n *= 2;

	} while (fabs(value_first - value_last) > eps);
	return (-1)*value_first;
}
int main()
{
	double ebs, pribl2 = 0, value_first = 0;
	int k = 1, steps = 0;
	setlocale(LC_ALL, ".1251");
	cout << "Введите значение e (где 0<e<10^(-k)) : " << endl;
	cin >> ebs;
	if ((ebs > 1) || (ebs <= 0.00000001))
	{
		cout << "Значение е не соответсвует ограничениям. Попробуйте снова.";
		return 0;
	}
	double y_mid1 = integral_mid(first_func, 0.8, 0.0, ebs, pribl2, k);
	cout << "Интеграл равен (по методу средних прямоугольников): " << y_mid1 << ". Вычисленно за данное количество шагов: " << k << endl;
	double y_mid2 = integral_mid(second_func, 1.8, 0.0, ebs, pribl2, k);
	cout << "Интеграл равен (по методу средних прямоугольников): " << y_mid2 << ". Вычисленно за данное количество шагов: " << k << endl;
	double y_mid3 = integral_mid(third_func, 0.3, 0.0, ebs, pribl2, k);
	cout << "Интеграл равен (по методу средних прямоугольников): " << y_mid3 << ". Вычисленно за данное количество шагов: " << k << endl;
	double y_sim1 = sim(first_func, 0.8, 0.0, ebs, value_first, steps);
	cout << "Интеграл равен (по методу Симпсона): " << y_sim1 << ". Вычисленно за данное количество шагов: " << steps << endl;
	double y_sim2 = sim(second_func, 1.8, 0.0, ebs, value_first, steps);
	cout << "Интеграл равен (по методу Симпсона): " << y_sim2 << ". Вычисленно за данное количество шагов: " << steps << endl;
	double y_sim3 = sim(third_func, 0.3, 0.0, ebs, value_first, steps);
	cout << "Интеграл равен (по методу Симпсона): " << y_sim3 << ". Вычисленно за данное количество шагов: " << steps << endl;
	system("pause");
	return 0;
}