CFLAGS += -std=gnu11 -g
EXES = main
OBJS = main.o

all: $(EXES)

main:   main.o

clean:
	rm -f $(EXES) $(OBJS)
	rm -rf $(LIBS)
tidy:
	rm -f $(OBJS)