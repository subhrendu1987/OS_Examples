all:
	gcc send.c -pthread -lrt -o send
	gcc receive.c -pthread -lrt -o receive

run:
	./send & ./receive &
clean:
	rm -v send receive