CC = gcc
LDFLAGS = -lraylib -lm
CFLAGS = -I$(IDIR) -Wall

TARGET = praseodymium

IDIR = include
SDIR = src
ODIR = obj

OBJS = $(patsubst $(SDIR)/%.c,$(ODIR)/%.o,$(wildcard $(SDIR)/*.c))

.PHONY: build clean run

$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) -c -o $@ $< $(LDFLAGS) $(CFLAGS)

build: $(OBJS)
	$(CC) -o $(TARGET) $^ $(LDFLAGS) $(CFLAGS)

clean:
	rm $(ODIR)/*.o

run: build
	./praseodymium
