GENERATES = range actual_1.txt actual_2.txt

all: range
	cc -g range.c -o range

test-%: range
	gdb --batch --quiet range -x scenario_$*.gdb | grep @@@ > actual_$*.txt
	cmp expected_$*.txt actual_$*.txt

test: test-1 test-2

clean:
	rm -f $(GENERATES)
