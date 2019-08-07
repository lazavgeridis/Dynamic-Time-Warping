CC = gcc
CFLAGS = -Wall -g

dtwrec: dtw.o dtw_utils.o
	$(CC) -o dtwrec dtw.o dtw_utils.o -DREC $(CFLAGS)

dtwdp: dtw.o dtw_utils.o
	$(CC) -o dtwdp dtw.o dtw_utils.o $(CFLAGS)

dtw.o: dtw.c
	$(CC) -c dtw.c $(CFLAGS)

dtw_utils.o: dtw_utils.c
	$(CC) -c dtw_utils.c $(CFLAGS)


clean:
	rm dtwrec dtwdp dtw.o dtw_utils.o
