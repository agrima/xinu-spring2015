/* nthroot.c - nthroot */

#include <math.h>

#define EPSILON 0.000001

/*------------------------------------------------------------------------
 * delta_x_k - compute the value of delta x for Newton's method
 *------------------------------------------------------------------------
 */
double delta_x_k(
	 double x_k, 	/* Current x_k value	*/
	 int n, 		/* n - root				*/
	 double a		/* base value			*/
	)
{
	return ((a / pow(x_k, n-1)) - x_k) / n;
}


/*------------------------------------------------------------------------
 * nthroot - compute the nth root of an input 'a'
 *------------------------------------------------------------------------
 */
double	nthroot(
	 double		a,	/* base value			*/
	 int		n	/* root value			*/
	)
{
	double x_k = 1.0;
	double d_x_k = delta_x_k(x_k, n, a);

	while(fabs(d_x_k) > EPSILON) {
		x_k += d_x_k;
		d_x_k = delta_x_k(x_k, n, a);
	}

	return x_k;
}
