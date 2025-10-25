CFLAGS=-Wall
GENERATES=move input_* output_* protected.so
TRASH= *.o

all: move protected.so

protected.so: protected.c
	cc -shared -fPIC $^ -o $@

test_error: move
	@echo "test input 1" > input_1.txt
	@strace -e fault=openat:error=ENOENT -P "input_1.txt" ./move "input_1.txt" "output_1.txt"; \
	if [ $$? -eq 3 ] && [ -f input_1.txt ] && [ ! -f output_1.txt ]; then \
		echo "Test 1 passed"; \
	else \
		echo "Test 1 failed"; \
		exit 1; \
	fi

	@echo "test input 2" > input_2.txt
	@strace -e fault=openat:error=EACCES -P "input_2.txt" ./move "input_2.txt" "output_2.txt"; \
	if [ $$? -eq 3 ] && [ -f input_2.txt ] && [ ! -f output_2.txt ]; then \
		echo "Test 2 passed"; \
	else \
		echo "Test 2 failed"; \
		exit 2; \
	fi

	@echo "test input 3" > input_3.txt
	@strace -e fault=openat:error=ENOSPC -P "output_3.txt" ./move "input_3.txt" "output_3.txt"; \
	if [ $$? -eq 8 ] && [ -f input_3.txt ] && [ ! -f output_3.txt ]; then \
		echo "Test 3 passed"; \
	else \
		echo "Test 3 failed"; \
		exit 3; \
	fi

	@echo "test input 4" > input_4.txt
	@strace -e fault=close:error=EIO -P "input_4.txt" ./move "input_4.txt" "output_4.txt"; \
	if [ $$? -eq 7 ] && [ -f input_4.txt ] && [ ! -f output_4.txt ]; then \
		echo "Test 4 passed"; \
	else \
		echo "Test 4 failed"; \
		exit 4; \
	fi

	@echo "test input 5" > input_5.txt
	@strace -e fault=unlink:error=EACCES -P "input_5.txt" ./move "input_5.txt" "output_5.txt"; \
	if [ $$? -eq 11 ] && [ -f input_5.txt ] && [ -f output_5.txt ]; then \
		echo "Test 5 passed"; \
	else \
		echo "Test 5 failed"; \
		exit 5; \
	fi

test_preload: move protected.so
	@echo "test input protected" > input_PROTECTed.txt
	@LD_PRELOAD=`pwd`/protected.so ./move "input_PROTECTed.txt" "output_PROTECTed.txt" > /dev/null 2>&1 || \
	if [ -f input_PROTECTed.txt ] && [ ! -f output_PROTECTed.txt ]; then \
		echo "test PROTECT passed"; \
	else \
		echo "test PROTECT failed"; \
		exit 1; \
	fi

test: test_error test_preload

clean:
	rm -f $(GENERATES) $(TRASH)
