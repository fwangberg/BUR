CC					= cc
CFLAGS 			= -mmacosx-version-min=10.6 -std=c99 -arch x86_64 -O2 -Wall -Werror
FRAMEWORKS 	= -framework CoreFoundation -framework IOKit

test: smc.c
	${CC} ${CFLAGS} ${FRAMEWORKS} ext/smc.c -o BUR

smc.c: ext/smc.c ext/smc.h

types.h: include/types.h

hello:
	${CC} ${CFLAGS} test.c -o HELLOW.o

clean:
	rm BUR *.o
