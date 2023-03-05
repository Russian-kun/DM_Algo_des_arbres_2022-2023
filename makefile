FILES := *.o *.out vgcore.* *.gch *.dot *.pdf filtre
COMP := gcc
CFLAGS := -Wall -Wfatal-errors -pedantic -Wextra -Werror -g
all: ABR.o filtre

filtre: filtrage.c ABR.o
	$(COMP) $(CFLAGS) -o filtre filtrage.c ABR.o

ABR.o: ABR.c ABR.h
	$(COMP) $(CFLAGS) -c ABR.c

debug:
	make clean
	make all
	valgrind --leak-check=full --show-leak-kinds=all ./filtre ./test/texte1.txt ./test/filtre1.txt -v

clean:
	for file in $(FILES); do \
		if [ -f $$file ]; then \
			rm $$file; \
		fi; \
	done
