CC					= cc
CFLAGS 			= -mmacosx-version-min=10.6 -std=c99 -arch x86_64 -O2 -Wall -Werror
FRAMEWORKS 	= -framework CoreFoundation -framework IOKit

bur: smc.c hashmap.c
	${CC} ${CFLAGS} ${FRAMEWORKS} bur.c -o BUR

test:
	${CC} ${CFLAGS} ${FRAMEWORKS} test.c -o TEST

smc-read: smc.c
	${CC} ${CFLAGS} ${FRAMEWORKS} ext/smc.c -o SMC-READ

smc.c: ext/smc.c ext/smc.h

hashmap.c: ext/hashmap.c ext/hashmap.h

types.h: include/types.h

hello:
	${CC} ${CFLAGS} test.c -o HELLOW.o

clear:
	clear

clean:
	rm BUR TEST SMC-READ *.o
