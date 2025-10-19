CFLAGS=-Wall -O0 -g
GENERATES=esub
TRASH=actual_* expected_*

all: esub

test: esub
	echo "myawesometest" | sed -E "s/awesome/AWESOME/" > expected_1.txt
	./esub "awesome" "AWESOME" "myawesometest" > actual_1.txt
	cmp expected_1.txt actual_1.txt
	echo "myawesometest" | sed -E "s/awe(so)me/\1_\1/" > expected_2.txt
	./esub "awe(so)me" "\1_\1" "myawesometest" > actual_2.txt
	cmp expected_2.txt actual_2.txt
	date | sed -E "s/([[:digit:]]+)(.*)([[:digit:]]+)/<1=\1><2=\2><3=\3>/" > expected_3.txt
	./esub "([[:digit:]]+)(.*)([[:digit:]]+)" "<1=\1><2=\2><3=\3>"  "`date`" > actual_3.txt
	cmp expected_3.txt actual_3.txt

clean:
	rm -f $(GENERATES) $(TRASH)
