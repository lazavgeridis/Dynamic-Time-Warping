/* dtw_utils.c */

#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) ( ( (a) > (b) ) ? (a) : (b) )
#define MIN(a,b) ( ( (a) < (b) ) ? (a) : (b) )


double min(double x, double y, double z) /* find the minimum out of 3 numbers(double) */
{
    double arr[3], min;

    arr[0] = x;
    arr[1] = y;
    arr[2] = z;
    min = arr[0]; /* we initialize min to the 1st element of the array */

    for(int i = 1; i < 3; i++)
        if(arr[i] < min)  /* if we find an array element which is smaller than the current min */
            min = arr[i]; /*  min becomes equal to this element */

    return min;
}


void arraymin(double *array, int length, double *min, int *th_min) /* find array min and its index */
{
     *min = array[0]; /* minimum becomes equal to the first element of the array */
     *th_min = 0; /* location of minimum becomes 0 */

     for(int i = 1; i < length; i++) 
        if(array[i] < *min) { /* if we find an array element which is smaller than the current min */
             *min = array[i]; /* min becomes equal to this element */
             *th_min = i; /*  and its location changes too */
        }
}


double dtwrec(double *pd, double *pe, int len1, int len2, double window)
{
    double *pA, *pB, dtw;
    const double infinity = 1.0 / 0.0;
    int a, b;

    a = len1 - 1;
    b = len2 - 1;
    pA = &pd[a];
    pB = &pe[b];

    if(len1 != 1 && len2 !=1) { /* i>1,j>1 */

        if(window == infinity || abs(a - b) <= window)
            dtw = ( (*pA - *pB) * (*pA - *pB) ) + min(dtwrec(pd, pe, len1 - 1, len2, window), dtwrec(pd, pe, len1, len2 - 1, window), \
			    									dtwrec(pd, pe, len1 - 1, len2 - 1, window));
        else if(abs(a - b) > window)
            dtw = infinity + min(dtwrec(pd, pe, len1 - 1, len2, window), dtwrec(pd, pe, len1, len2 - 1, window), \
			    									dtwrec(pd, pe, len1 - 1, len2 - 1, window));
    }
    if(len1 != 1 && len2 == 1) { /* i>1,j=1 */

            if(window == infinity || abs(a - b) <= window)
                dtw = ( (*pA - *pB) * (*pA - *pB) ) + dtwrec(pd, pe, len1 - 1, len2, window);
            else if(abs(a - b) > window)
                dtw = infinity + dtwrec(pd, pe, len1 - 1, len2, window);
    }
    if(len1 == 1 && len2 != 1) {  /* i=1,j>1 */

            if(window == infinity || abs(a - b) <= window)
                dtw = ( (*pA - *pB) * (*pA - *pB) ) + dtwrec(pd, pe, len1, len2 - 1, window);
            else if(abs(a - b) > window)
                dtw = infinity + dtwrec(pd, pe, len1, len2 - 1, window);
    }
    if(len1 == 1 && len2 == 1) /* i=j=1 */
                dtw = ( (*pA - *pB) * (*pA - *pB) );

    return dtw;
}


double dtwdp(double *pd, double *pe, int len, double window)
{
    double dtw[len][len];
    const double infinity = 1.0 / 0.0;
    int i, j;


    if(window == infinity) {

    	/* initialization of the matrix */
    	dtw[0][0] = (pd[0] - pe[0]) * (pd[0] - pe[0]); /* i=1,j=1 */

    	for(i = 1; i < len; i++) { /* initialize first column(i>1, j=1) */
    	    if(window == infinity || abs(i) <= window)
    	        dtw[i][0] = ( (pd[i] - pe[0]) * (pd[i] - pe[0]) ) + dtw[i-1][0];
    	    else if(abs(i) > window)
    	        dtw[i][0] = infinity + dtw[i-1][0];
    	}

    	for(j = 1; j < len; j++) { /* initialize first row(i=1, j>1) */
    	    if(window == infinity || abs(-j) <= window)
    	        dtw[0][j] = ( (pd[0] - pe[j]) * (pd[0] - pe[j]) ) + dtw[0][j-1];
    	    else if(abs(-j) > window)
    	        dtw[0][j] = infinity + dtw[0][j-1];
    	}
    	/* end of initialization */

    	/* now we basically apply the dtw formula */
    	for(i = 1; i < len; i++) { /* i>1,j>1 */
    	        for(j = 1; j < len; j++) {
    	            if(window == infinity || abs(i-j) <= window)
    	                dtw[i][j] = ( (pd[i] - pe[j]) * (pd[i] - pe[j]) ) + min(dtw[i-1][j], dtw[i][j-1], dtw[i-1][j-1]);
    	            else if(abs(i-j) > window)
    	                dtw[i][j] = infinity + min(dtw[i-1][j], dtw[i][j-1], dtw[i-1][j-1]);
    	        }
    	}
    }
    else { /* window has an arithmetic value -> in this case the algorithm has time complexity O(cN) */
	    int w = (int)window; /* window size */

	    dtw[0][0] = (pd[0] - pe[0]) * (pd[0] - pe[0]);
  	    for(i = 1; i <= w; i++)
  		dtw[i][0] = ( (pd[i] - pe[0]) * (pd[i] - pe[0]) ) + dtw[i-1][0];
  	    for(j = 1; j <= w; j++)
  		dtw[0][j] = ( (pd[0] - pe[j]) * (pd[0] - pe[j]) ) + dtw[0][j-1];

  	    dtw[w+1][0] = infinity;
  	    dtw[0][w+1] = infinity;

	    for(i = w + 2, j = 1; i < len; i++, j++)
  		dtw[i][j] = infinity;

	    for(j = w + 2, i = 1; j < len; j++, i++)
  		dtw[i][j] = infinity;

  	    for(i = 1; i < len; i++)
  		for(j = MAX(1, i - w); j <= MIN(len - 1, i + w); j++)
  			dtw[i][j] = ( (pd[i] - pe[j]) * (pd[i] - pe[j]) ) + min(dtw[i-1][j], dtw[i][j-1], dtw[i-1][j-1]);
    }

    return dtw[len - 1][len - 1];
}
