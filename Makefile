headers=  -lncurses -lpanel -lform -lmenu

###### GitHub commiting ..
# https://help.github.com/en/articles/adding-a-file-to-a-repository-using-the-command-line
# 
# 

all:
	gcc -o RogueLike.o RogueLike.c $(headers) -std=c99
	gcc -o Ncurses.o Ncurses.c $(headers) -std=c99
	gcc -o mySnake.o mySnake.c $(headers) -std=c99

clean:
	rm *.o