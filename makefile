FILES := *.o *.gch *.dot *.pdf filtre
COMP := gcc
CFLAGS := -Wall -Wfatal-errors -pedantic -Wextra -Werror

all: ABR.o filtre

filtre: filtrage.c ABR.o
	$(COMP) $(CFLAGS) -o filtre filtrage.c ABR.o

ABR.o: ABR.c ABR.h
	$(COMP) $(CFLAGS) -c ABR.c

clean:
	for file in $(FILES); do \
		if [ -f $$file ]; then \
			rm $$file; \
		fi; \
	done
