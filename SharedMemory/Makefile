all:
	gcc Producer.c -pthread -lrt -o Producer
	gcc Consumer.c -pthread -lrt -o Consumer
run:
	./Producer & ./Consumer &
clean:
	rm -v Producer Consumer