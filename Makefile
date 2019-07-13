noheaders=

###### GitHub commiting ..
# https://help.github.com/en/articles/adding-a-file-to-a-repository-using-the-command-line
# 
# 

make:
	gcc RogueLike.c -o $(noheaders) RogueLike.o -lncurses -std=c99

git:
	git add .
	git commit -m "test .."
	git checkout master
	# git fetch origin master
	# git rebase -i origin/master
	# Squash commits, fix up commit messages etc.
	git push origin master

