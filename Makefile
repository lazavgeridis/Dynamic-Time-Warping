CC = gcc
CFLAGS = -O -Wall -g

distdtwrec: distdtwrec.c
	$(CC) -o distdtwrec distdtwrec.c $(CFLAGS)

distdtwdp: distdtwdp.c
	$(CC) -o distdtwdp distdtwdp.c $(CFLAGS)

distcdtwrec: distcdtw.c
	$(CC) -o distcdtwrec distcdtw.c -DREC $(CFLAGS)

distcdtwdp: distcdtw.c
	$(CC) -o distcdtwdp distcdtw.c  -DREC $(CFLAGS)

dtwrec: dtw.o dtw_utils.o
	$(CC) -o dtwrec dtw.o dtw_utils.o -DREC $(CFLAGS)

dtwdp: dtw.o dtw_utils.o
	$(CC) -o dtwdp dtw.o dtw_utils.o $(CFLAGS)


clean:
	rm distdtwrec distdtwdp distcdtwrec distcdtwdp dtwrec dtwdp dtw.o dtw_utils.o
