GENERATES=labyrinth labyrinth_0 labyrinth_1 labyrinth_2 labyrinth_0.c labyrinth_1.c labyrinth_2.c

all: labyrinth labyrinth_0 labyrinth_1 labyrinth_2

labyrinth_%: labyrinth_%.c
	cc -o $@ $<

labyrinth_0.c: labyrinth.c labyrinth_0.patch
	patch -o $@ $< labyrinth_0.patch

labyrinth_1.c: labyrinth_0.c labyrinth_1.patch
	patch -o $@ $< labyrinth_1.patch

labyrinth_2.c: labyrinth_1.c labyrinth_2.patch
	patch -o $@ $< labyrinth_2.patch

run: labyrinth labyrinth_0 labyrinth_1 labyrinth_2
	./labyrinth
	./labyrinth_0 10
	./labyrinth_1 '-+' 4
	./labyrinth_2 45 '01' 7

clean:
	rm $(GENERATES)
