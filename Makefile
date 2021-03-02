OBJS := log.o test.o

test:$(OBJS)
	gcc -o test $(OBJS)

test.o:
	gcc -c test.c

log.o:log.h
	gcc -c log.c

clean:
	rm $(OBJS)