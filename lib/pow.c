/* pow.c - pow */

#include <math.h>

/*------------------------------------------------------------------------
 * pow - compute the a raised to the power of n
 *------------------------------------------------------------------------
 */
double	pow(
	 double		a,					/* base value					*/
	 int		n					/* power value					*/
	)
{
	double temp;

	if(a == 0) {
		return 0;
	}

	if(a < 0 || a == NAN) {
		return NAN;
	}

	if(n == 0) {
		return 1;
	}
	
	temp = pow(a, n/2);
	if(n % 2 == 0) {
		return temp*temp;
	} else {
		if(n > 0) {
			return a * temp * temp;
		} else {
			return (temp * temp) / a;
		}
	}

	return NAN;
}
