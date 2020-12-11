SRCS = ootd.c 
TARG = ootd
CC = gcc
OPTS = -Wall -O

OBJS = $(SRCS: .c=.o)

all: $(TARG)

$(TARG): $(OBJS)
	$(CC) -o $(TARG) $(OBJS)

%.o: %.c
	$(cc) $(OPTS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARG)
