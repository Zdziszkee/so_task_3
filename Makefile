#ROZSZEZENIA
.SUFFIXES: .c .o .x

#KATALOG
DIR = `basename $(CURDIR)`

#NAZWY PLIKOW
NAME1 = a
NAME2 = b
NAME3 = c

#PROGRAMY WYKONAWCZE
EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x
EXEC3 = $(NAME3).x

#PLIKI PO KOMPILACJI
OBJS1 = $(NAME1).o
OBJS2 = $(NAME2).o
OBJS3 = $(NAME3).o 
# KOMPILATOR I LINKER 
CO = gcc
LD = $(CO)

#FLAGI KOMPILATORA I LINKERA
CFLAGS = -Wall -std=c99 -pedantic -O -fPIC 
LFLAGS = -Wall -std=c99 -pedantic -O

#REGULA WZORCOWA
%.o: %.c
	$(CO) $(CFLAGS) -c $<

#REGULY ZALEZNOSCI
.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3)

$(EXEC1): $(OBJS1)
	$(LD) -o $@ $(LFLAGS) $^
$(EXEC2): $(OBJS2)
	$(LD) -o $@ $(LFLAGS) $^
$(EXEC3): $(OBJS3)
	$(LD) -o $@ $(LFLAGS) $^

#KOMPILOWANIE PROGRAMOW
compile1: $(EXEC1) 
compile2: $(EXEC2) 	
compile3: $(EXEC3) 

#CLEANER
.PHONY: clean tar
clean: 
	rm -f *.o  *~ *.a *.so *.x core core* a.out;

#ARCHIWIZACJA I KOMPRESJA
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )