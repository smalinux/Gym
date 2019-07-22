headers=  -lncurses -lpanel -lform -lmenu

###### GitHub commiting ..
# https://help.github.com/en/articles/adding-a-file-to-a-repository-using-the-command-line
# 
# 

make:
	gcc -o RogueLike.o RogueLike.c $(headers) -std=c99
	gcc -o Ncurses.o Ncurses.c $(headers) -std=c99

git:
	git add .
	git commit -m "$m"
	git checkout master
	git fetch origin master
	git rebase -i origin/master
	# Squash commits, fix up commit messages etc.
	git push origin master

