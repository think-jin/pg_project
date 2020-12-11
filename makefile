SRCS = 
TARG = 
CC =
OPTS = 
LIBS = 

OBJS =

all:

$(TARG): $(OBJS)

%.o: %.c
	$(cc) $(OPTS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARG)
