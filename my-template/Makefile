.PHONY: clean 

CXX=g++
RM=rm -f
CPPFLAGS=-Wall -std=c++11

SRCS=my-template.cpp
OBJS=my-template.o

all: my-template

$(OBJS): $(SRCS)
	$(CXX) $(CPPFLAGS) -c $(SRCS)

my-template: $(OBJS)
	$(CXX) $(OBJS) -o my-template

clean:
	$(RM) *.o my-template
