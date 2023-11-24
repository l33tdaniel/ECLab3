main: main.cpp
	g++ -o output main.cpp

clean: 
	@rm -f output

build-run:
	@g++ -o output main.cpp
	@./output