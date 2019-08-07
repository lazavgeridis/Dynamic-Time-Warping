

## Time-Series Classification with Dtw

Assume we have 2 time-series *A* and *B*. *A* has *ai* elements (1 <= i <= n) and *B* has *bj* elements (1 <= j <= m). Assuming that *d(ai,bj)* = *(ai-bj)^2* and that *min{x,y,z}* is the minimum of *x,y* and *z* the **_dtw_** formula is the following:

![Screenshot](dtw_formula.png)


## Description

- The program can receive a user-defined non negative integer via the command line, which represents the "window" for the computation of the **dtw distaces**. If such an argument is not provided, we assume that a constraint/"window" does not exist(or equivalently the "window" is equal to infinity).

- The input of the program is the following: Initially, the number of time-series of a known class(**training set**) and their length is given in a single line(stdin).   
