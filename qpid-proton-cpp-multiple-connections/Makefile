CCFLAGS := -g -Os -std=c++11 -lstdc++ -lpthread -lqpid-proton-cpp
SOURCES := $(shell find . -name \*.cpp)
TARGETS := ${SOURCES:./%.cpp=build/%}

.PHONY: build
build: ${TARGETS}

.PHONY: clean
clean:
	rm -rf build

# Requires brokers at localhost:5673 and localhost:5674
.PHONY: test
test:
	build/send //localhost:5673 //localhost:5674 q1 m1
	build/receive //localhost:5673 //localhost:5674 q1 1

build/%: %.cpp
	@mkdir -p ${@D}
	${CXX} $< -o $@ ${CCFLAGS}

