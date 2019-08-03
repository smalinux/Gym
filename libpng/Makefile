headers=  -lncurses -lpanel -lform -lmenu

all:
	touch main.c
	gcc main.c -o main -lz -lpng16 -std=c99
	./main sd.png ssd.png
	eog ssd.png

clean:
	rm *.o