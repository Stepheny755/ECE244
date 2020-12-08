SRCS = main.cpp big_integer.cpp
INCS = big_integer.h
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

main.exe: $(OBJS)
	g++ -std=c++11 $^ -o $@
%.o:	%.cpp
	g++ -std=c++11 -c -g $< -o $@ 
clean:
	rm -f $(OBJS)  main.exe core
