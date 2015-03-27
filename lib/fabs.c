/* fabs.c - fabs */

#include <math.h>

/*------------------------------------------------------------------------
 * fabs - compute the floating point absolute value of a number
 *------------------------------------------------------------------------
 */
double		fabs(
		double	x						/* base value					*/
	)
{
	if(x == NAN) {
		return NAN;
	}

	if(x < 0) {
		x = -x;
	}
	return x;
}
