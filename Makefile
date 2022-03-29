all:
	g++ RoundRobinSimulator.cpp -o RRsim
	make help
run:
	./RRsim
clean:
	rm -v RRsim
help:
	$(warning For custom execution with file input use ./RRsim < input)