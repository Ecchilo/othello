othello : adapter.o
	cc -o othello adapter.o

adapter.o : adapter.c
	cc -c adapter.c

engine : engine.o engine_core.o engine_io.o
	cc -o engine engine.o engine_core.o engine_io.o

engine.o : engine.c engine_core.h engine_io.h
	cc -c engine.c

engine_core.o : engine_core.c engine_core.c
	cc -c engine_core.c

engine_io.o : engine_io.c engine_core.h engine_io.h
	cc -c engine_io.c

clean :
	rm adapter.o engine.o engine_core.o engine_io.o


