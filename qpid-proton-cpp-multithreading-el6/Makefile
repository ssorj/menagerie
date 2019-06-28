.PHONY: test
test:
	sudo docker build -t test .
	sudo docker run --rm test

.PHONY: debug
debug:
	sudo docker build -t test .
	sudo docker run --rm -it test /bin/bash
