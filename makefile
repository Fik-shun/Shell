all : bg.o cdir.o echo.o hist.o ls.o mypwd.o others.o pinfo.o shell.o
	gcc $^ -o fksh
bg.o : functions/bg.c
	gcc -c functions/bg.c

cdir.o : functions/cdir.c
	gcc -c functions/cdir.c

echo.o : functions/echo.c
	gcc -c functions/echo.c

hist.o : functions/hist.c
	gcc -c functions/hist.c

ls.o : functions/ls.c
	gcc -c functions/ls.c

mypwd.o : functions/mypwd.c
	gcc -c functions/mypwd.c

others.o : functions/others.c
	gcc -c functions/others.c

pinfo.o : functions/pinfo.c
	gcc -c functions/pinfo.c

shell.o : shell.c
	gcc -c shell.c
clean :
	rm *.o fksh
