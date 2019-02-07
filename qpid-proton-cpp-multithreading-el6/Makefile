.PHONY: test-container
test-container:
	sudo docker build -t test .
	sudo docker run test

.PHONY: debug-container
debug-container:
	sudo docker build -t test .
	sudo docker run -it test /bin/bash

.PHONY: test
test: client
	./test.sh

client: client.cpp
	g++ -Os -g -std=c++0x -lqpid-proton-cpp -lpthread $< -o $@

clean:
	rm -f client
