OBJS := log.o test.o
CLAGS := -g
LINKS := -lpthread

test:$(OBJS)
	gcc -o test $(OBJS) $(LINKS)

test.o:
	gcc $(CLAGS) -c test.c

log.o:log.h
	gcc $(CLAGS) -c log.c

clean:
	rm $(OBJS)