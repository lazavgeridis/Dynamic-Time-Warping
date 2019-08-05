/* Time-series classification with dtw - either recursive or dynamic programming version */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "dtw.h"


int main(int argc, char *argv[])
{
    int *class_train, *class_test, num1, num2, len1, len2, cellmin, fails = 0;
    double **train_set, *test_set, *dtwdist, mindtw, sttime, endtime, c;
    const double infinity = 1.0 / 0.0;

    #ifdef REC  

    if(argc > 2) { 
        fprintf(stderr, "Invalid number of arguments\n");
	exit(EXIT_FAILURE);
    }
    else if(argc < 2)  /* if the program was run with no arguements, c=infinity */
        	c = infinity;
    else if(argc == 2)
        	c = atoi(argv[1]); /* if the program was run with exactly 2 arguements, c=arithmetic value of arguement 2 */

    /* Input: training set */
    scanf("%d %d", &num1, &len1); /* store the number of timeseries in the training set and the length of each one */

    class_train = malloc( num1 * sizeof(int) ); /* used to store the class of each timeseries in the training set */
    if(class_train == NULL) {
	    fprintf(stderr, "Memory error!\n");
	    exit(EXIT_FAILURE);
    }

    train_set = malloc( num1 * sizeof(double *) ); /* used to store each timeseries in the training set */
    if(train_set == NULL) {
	    fprintf(stderr, "Memory error!\n");
	    exit(EXIT_FAILURE);
    }
    for(int i = 0; i < num1; i++) {
	    train_set[i] = malloc( len1 * sizeof(double) );
    	    if(train_set[i] == NULL) {
    	        fprintf(stderr, "Memory error!\n");
    	        exit(EXIT_FAILURE);
	    }
    }
    

    for(int i = 0; i < num1; i++)
        for(int j = 0; j < len1; j++)
            if(j == 0) {   /* the first element of each row([i][0]) is the class of the time-series(integer) */
                scanf("%d", &class_train[i]); /* so, store the class of each timeseries in the array allocated earlier */
                scanf("%lf", &train_set[i][j]); /* immediately after follows the first element of the time-series(double) */
            }
            else
                scanf("%lf", &train_set[i][j]); /* on any other case we just fill the array */
    /* End of input: training set */


    /* Input: test set.
     * We basically repeat the same steps
     */
    scanf("%d %d", &num2, &len2); 
    if(len1 != len2) {
	    fprintf(stderr, "Time-series are not the same length\n"); /* in case the length of each time-series in the test set is different */
	    exit(EXIT_FAILURE);
    }

    class_test = malloc( num2 * sizeof(int) ); /* used to store the class of each timeseries in the test set */
    if(class_test == NULL) {
	    fprintf(stderr, "Memory error!\n");
	    exit(EXIT_FAILURE);
    }
    
    test_set = malloc( len2 * sizeof(double) ); /* malloc'd 1d array to store each time-series in the test set(one in each loop) */ 
    if(test_set == NULL) { 
            fprintf(stderr, "Memory Error\n"); 
	    exit(EXIT_FAILURE);
    }

    dtwdist = malloc( num1 * sizeof(double) ); /* dynamically allocated 1d array to keep the dtw distances of the i-th timeseries in the 
						      test set with every timeseries in the training set */

    if(dtwdist == NULL) { 
            fprintf(stderr, "Memory Error\n"); 
	    exit(EXIT_FAILURE);
    }

    sttime = ( (double) clock() ) / CLOCKS_PER_SEC; /* start timer */

    /* the following for loop performs the classification of the time-series in the test set */
    for(int i = 0; i < num2; i++) {  


        scanf("%d", &class_test[i]); /* the first number represents the class of the timeseries */

        for(int j = 0; j < len2; j++)
            scanf("%lf", &test_set[j]); /* the following numbers are the elements of the timeseries */
        for(int k = 0; k < num1; k++)
            dtwdist[k] = dtwrec(train_set[k], test_set, len1, len2, c); /* insert a specific row of the train_set array */

        arraymin(dtwdist, num1, &mindtw, &cellmin); /*  this function finds the minimum element in the array and its location */

        printf("Series %d(class %d) is nearest(distance %f) to Series %d(class %d)\n", i + 1, class_test[i], mindtw, cellmin + 1, \
														class_train[cellmin]);
        if(class_test[i] != class_train[cellmin]) /* check for errors during the classification process */
            fails++;
    }

    endtime = ( (double) clock() ) / CLOCKS_PER_SEC; /* stop timer */

    fprintf(stderr, "Error rate: %.3f\n", (double)fails / num2);
    fprintf(stderr,  "CPU time: %.2f secs\n", endtime - sttime);

    free(test_set); 
    free(dtwdist);
    free(class_train);
    free(class_test);
    for(int i = 0; i < num1; i++)
	    free(train_set[i]);
    free(train_set);
	
    return 0;


    #endif // REC


    #ifndef REC /* if REC was not defined the following source code will be compiled */


    if(argc > 2) { 
        fprintf(stderr, "Invalid number of arguments\n");
	exit(EXIT_FAILURE);
    }
    else if(argc < 2) /* if the program was run with no arguments, c=infinity */
        	c = infinity;
    else if(argc == 2) /* if the program was run with exactly 2 arguments, c=arithmetic value of arguement 2 */
        	c = atoi(argv[1]);


    /* Input: training set */
    scanf("%d %d", &num1, &len1); /* store the number of the training set time-series and the length of each one */

    class_train = malloc( num1 * sizeof(int) );
    if(class_train == NULL) {
	    fprintf(stderr, "Memory error!\n");
	    exit(EXIT_FAILURE);
    }

    train_set = malloc( num1 * sizeof(double *) );
    if(train_set == NULL) {
	    fprintf(stderr, "Memory error!\n");
	    exit(EXIT_FAILURE);
    }

    for(int i = 0; i < num1; i++) {
	    train_set[i] = malloc( len1 * sizeof(double) );
    	    if(train_set[i] == NULL) {
    	        fprintf(stderr, "Memory error!\n");
    	        exit(EXIT_FAILURE);
	    }
    }
    
    for(int i = 0; i < num1; i++)
        for(int j = 0; j < len1; j++)
            if(j == 0) {   /* the first element of each row([i][0]) is the class of the time-series(integer) */
                scanf("%d", &class_train[i]); /* so, store the class of each timeseries in the array allocated earlier */
                scanf("%lf", &train_set[i][j]); /* immediately after follows the first element of the time-series(double) */
            }
            else
                scanf("%lf", &train_set[i][j]); /* on any other case we just fill the array */
    /* End of input: training set */


    /* Input: test set.
     * We basically repeat the same steps
     */
    scanf("%d %d", &num2, &len2); 

    if(len1 != len2) {
	    fprintf(stderr, "Time-series are not the same length\n"); /* in case the length of each time-series in the test set is different */
	    exit(EXIT_FAILURE);
    }

    class_test = malloc( num2 * sizeof(int) );
    if(class_test == NULL) {
	    fprintf(stderr, "Memory error!\n");
	    exit(EXIT_FAILURE);
    }

    test_set = malloc( len2 * sizeof(double) );
    if(test_set == NULL) {
 	    fprintf(stderr, "Memory Error\n");
	    exit(EXIT_FAILURE);
    }

    dtwdist = malloc( num1 * sizeof(double) );
    if(dtwdist == NULL) {
            fprintf(stderr, "Memory Error\n");
	    exit(EXIT_FAILURE);
    }

    sttime = ( (double) clock() ) / CLOCKS_PER_SEC; /* start timer */

    for(int i = 0; i < num2; i++) {

        scanf("%d", &class_test[i]);

        for(int j = 0; j < len2; j++)
            scanf("%lf", &test_set[j]);

        for(int k = 0; k < num1; k++)
            dtwdist[k] = dtwdp(train_set[k], test_set, len1, c);

        arraymin(dtwdist, num1, &mindtw, &cellmin);

        printf("Series %d(class %d) is nearest(distance %f) to Series %d(class %d)\n", i + 1, class_test[i], mindtw, cellmin + 1, \
															class_train[cellmin]);
        if(class_test[i] != class_train[cellmin])
            fails++;
    }

    endtime = ( (double) clock() ) / CLOCKS_PER_SEC; /* stop timer */

    fprintf(stderr, "Error rate: %.3f\n", (double)fails / num2);
    fprintf(stderr, "CPU time: %.2f secs\n", endtime - sttime);

    free(test_set);
    free(dtwdist);
    free(class_train);
    free(class_test);
    for(int i = 0; i < num1; i++)
	    free(train_set[i]);
    free(train_set);

    return 0;

    #endif // REC
}
