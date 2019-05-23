run: demoParser.o
	gcc -o run demoParser.o

demoParser.o: demoParser.c
	gcc -c demoParser.c
