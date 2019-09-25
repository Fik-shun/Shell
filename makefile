all : bg.o cdir.o echo.o hist.o ls.o mypwd.o others.o pinfo.o shell.o env.o the_jobs.o kill.o fg.o
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

env.o : functions/env.c
	gcc -c functions/env.c

the_jobs.o : functions/the_jobs.c
	gcc -c functions/the_jobs.c

kill.o : functions/kill.c
	gcc -c functions/kill.c	

fg.o : functions/fg.c
	gcc -c functions/fg.c

shell.o : shell.c
	gcc -c shell.c

clean :
	rm *.o fksh
