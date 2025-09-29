GENERATES = prog README prog-a prog-so liboutput_static.a liboutput.so
TRASH = *.o *~ o.* test_*
LD_LIBRARY_PATH = $(CURDIR)
CFLAGS = -fPIC

all:	README prog prog-a prog-so

liboutput_static.a: liboutput_static.a(fun.o const.o)

liboutput.so: fun.o const.o
	cc -shared $^ -o $@

prog:   const.o fun.o prog.o
	cc $^ -o $@

prog-a: prog.o liboutput_static.a
	cc -L. $< -loutput_static -o $@

prog-so: prog.o liboutput.so
	cc -L. $< -loutput -o $@

README: prog
	./$< 2> $@

fun.o prog.o const.o: outlib.h

test: prog prog-a prog-so
	./prog > test_prog_0_args 2>&1
	./prog-a > test_prog-a_0_args 2>&1
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH) ./prog-so > test_prog-so_0_args 2>&1
	cmp test_prog_0_args test_prog-a_0_args
	cmp test_prog_0_args test_prog-so_0_args
	cmp test_prog-a_0_args test_prog-so_0_args

	./prog test > test_prog_1_args 2>&1
	./prog-a test > test_prog-a_1_args 2>&1
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH) ./prog-so test > test_prog-so_1_args 2>&1
	cmp test_prog_1_args test_prog-a_1_args
	cmp test_prog_1_args test_prog-so_1_args
	cmp test_prog-a_1_args test_prog-so_1_args

	./prog test other_test another_test > test_prog_3_args 2>&1
	./prog-a test other_test another_test > test_prog-a_3_args 2>&1
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH) ./prog-so test other_test another_test > test_prog-so_3_args 2>&1
	cmp test_prog_3_args test_prog-a_3_args
	cmp test_prog_3_args test_prog-so_3_args
	cmp test_prog-a_3_args test_prog-so_3_args

clean:
	rm -f $(TRASH)

distclean:	clean
	rm -rf $(GENERATES)
