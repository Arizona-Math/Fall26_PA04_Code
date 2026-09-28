CXX = g++
CPPFLAGS = -Iinclude
CXXFLAGS = -O2 -std=c++17 -Wall -Wextra -Wpedantic
AR = ar

.PHONY: all test submission clean
all: build/liblinsys.a build/demo

build:
	mkdir -p $@

build/linsys.o: src/linsys.cpp include/linsys.h | build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

build/liblinsys.a: build/linsys.o
	$(AR) rcs $@ $<

build/demo: examples/demo.cpp build/liblinsys.a include/linsys.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< build/liblinsys.a -o $@

build/check: tests/check.cpp build/liblinsys.a include/linsys.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< build/liblinsys.a -o $@

test: build/check
	./build/check

# Only the student's implementation is submitted; the grader supplies the API.
submission: | build
	python3 -m zipfile -c build/pa04-submission.zip src/linsys.cpp

clean:
	rm -rf build
