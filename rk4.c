#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include "error.h"

double f(double x, double y); //derivative
double runge_kutta(double x, double y, double h); //calculate y by fourth order runge-kutta method

int main()
{
	double x0 = 0, y0 = 0;
	double *x1 = NULL, *x2 = NULL, *y1 = NULL, *y2 = NULL;
	double b, h;
	double e = 1, r, r1 = 10, r2 = 5;
	int e_out, i, n, n_iter = 0;
	printf("y'=e^x-y^2\ny(%.3lf)=%.3lf\n", x0, y0);
	//enter input data
	do
	{
		printf("end of the integration interval (>0) -> ");
		scanf("%lf", &b);
		printf("initial length of subintervals -> ");
		scanf("%lf", &h);
		printf("desired accuracy (number of digits after the decimal point) -> ");
		scanf("%d", &e_out);
	} while (b <= 0 || (x0 + h) > b);
	//calculate accuracy
	for (i = 0; i < e_out; i++)
	{
		e /= 10;
	}
	//calculate initial number of subintervals
	n = (b - x0) / h;
	x2 = (double*)malloc((n + 1) * sizeof(double));
	y2 = (double*)malloc((n + 1) * sizeof(double));
	if (!x2 || !y2)
	{
		error(2);
	}
	//calculate х and у
	x2[0] = x0;
	y2[0] = y0;
	for (i = 1; i <= n; i++)
	{
		x2[i] = x0 + i * h;
		y2[i] = runge_kutta(x2[i - 1], y2[i - 1], h);
	}
	printf("\nTHE FOURTH ORDER RUNGE-KUTTA METHOD\n");
	//until the desired accuracy is reached and calculation error stops decreasing
	while (r2 >= e && r1 > r2)
	{
		n_iter++;
		free(x1);
		free(y1);
		x1 = x2;
		y1 = y2;
		r1 = r2;
		//double number of subintervals
		n *= 2;
		//calculate length of subintervals
		h = (b - x0) / n;
		x2 = (double*)malloc((n + 1) * sizeof(double));
		y2 = (double*)malloc((n + 1) * sizeof(double));
		if (!x2 || !y2)
		{
			error(2);
		}
		//calculate х and у
		x2[0] = x0;
		y2[0] = y0;
		for (i = 1; i <= n; i++)
		{
			x2[i] = x0 + i * h;
			y2[i] = runge_kutta(x2[i - 1], y2[i - 1], h);
		}
		r2 = 0;
		for (i = 2; i <= n; i +=2)
		{
			//calculate error using runge's rule
			r = fabs(y2[i] - y1[i / 2]) / 15;
			//memorize max error for this iteration
			if (r > r2)
			{
				r2 = r;
			}
		}
	}
	//print results
	if (r1 < r2)
	{
		printf("\nthe desired accuracy wasn't reached\nthe best approximate solution:\n");
	}
	else
	{
		printf("\napproximate solution that satisfies the desired accuracy:\n");
	}
	for (i = 0; i <= n / 2; i++)
	{
		printf("x = %.*lf, y = %.*lf\n", e_out, x1[i], e_out, y1[i]);
	}
	printf("\ncalculation error: %.3lg\nnumber of iterations: %d\nnumber of subintervals: %d\n", r2, n_iter, n / 2);
	free(x1);
	free(y1);
	free(x2);
	free(y2);
	return 0;
}

double f(double x, double y)
{
	return exp(x) - pow(y, 2);
}

double runge_kutta(double x, double y, double h)
{
	double *k = NULL, y1;
	k = (double*)malloc(4 * sizeof(double));
	if (!k)
	{
		error(2);
	}
	//calculate coefficients
	k[0] = f(x, y);
	k[1] = f(x + h / 2, y + h / 2 * k[0]);
	k[2] = f(x + h / 2, y + h / 2 * k[1]);
	k[3] = f(x + h, y + h * k[2]);
	//calculate у1
	y1 = y + h / 6 * (k[0] + 2 * k[1] + 2 * k[2] + k[3]);
	free(k);
	return y1;
}
