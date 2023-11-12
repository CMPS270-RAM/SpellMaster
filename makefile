IDIR =./include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=src/obj

_DEPS = header.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = botEasy.o botMedium.o botHard.o checks.o coinToss.o readFile.o gameDriver.o search.o spellMaster.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

spellMaster: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 


