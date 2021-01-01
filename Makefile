headers=  -lncurses -lpanel -lform -lmenu

###### GitHub commiting ..
# https://help.github.com/en/articles/adding-a-file-to-a-repository-using-the-command-line
#
#

all:
		gcc -o RogueLike RogueLike.c $(headers) -std=c99

clean:
	rm RogueLike
