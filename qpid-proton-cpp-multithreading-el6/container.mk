CCFLAGS := -Os -g -std=c++0x -lstdc++ -lpthread -lqpid-proton-cpp
SOURCES := $(shell find . -name \*.cpp)
TARGETS := ${SOURCES:./%.cpp=build/%}

.PHONY: test
test: build
	./test.sh

.PHONY: build
build: ${TARGETS}

.PHONY: clean
clean:
	rm -rf build

build/%: %.cpp
	@mkdir -p ${@D}
	${CXX} $< -o $@ ${CCFLAGS}
