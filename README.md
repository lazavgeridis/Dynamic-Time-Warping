

## Time-Series Classification with Dtw

Assume we have 2 time-series *A* and *B*. *A* has *ai* elements (1 <= i <= n) and *B* has *bj* elements (1 <= j <= m). Assuming that *d(ai,bj)* = *(ai-bj)^2* and that *min{x,y,z}* is the minimum of *x,y* and *z* the **_dtw_** formula is the following:

![Screenshot](dtw_formula.png)


## Description

- The program can receive a user-defined non negative integer via the command line, which represents the "window" for the computation of the **dtw distaces**. If such an argument is not provided, we assume that a constraint/"window" does not exist(or equivalently the "window" is equal to infinity).

- The input of the program is the following: Initially, the number of time-series of a known class(**training set**) and their length is given in a single line(stdin). In the following lines, the actual time-series data is given. Specifically, this includes, firstly, the class of the time-series and then, the elements of the time-series. Similarly, the data of the **test set** is given next. In a single line we provide the number of time-series in the test-set and the length of each one. Then, in the following lines we give, firstly, the class of each time-series, which will be only used during the evaluation of the dtw classification process. After that, the elements of the test-set time-series follow. Note that the length of the time-series in the test-set must be equal to the length of the time-series in the training-set. If such a requirement is not satisfied, then the program must teminate. 
