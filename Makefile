MAIN = app
LIBS = -lSDL2
CFLAGS = -Wall
GCC = gcc $(CFLAGS) -o $@ $^ $(LIBS)


$(MAIN): test.c
	$(GCC)

debug: test.c
	$(GCC) -g

screen: screen.c
	$(GCC)
