COMPILE_OPTS = -std=c++11 -c -O2
COMPILER = c++
COMPILE = $(COMPILER) $(COMPILE_OPTS)

LIBS = channel.o node.o simulator.o
LINK = c++

%.o : %.cpp
	$(COMPILE) $<

CSMASimulator : main.o $(LIBS)
	$(LINK) -o $@ $^

clean :
	rm -rf *.o CSMASimulator
