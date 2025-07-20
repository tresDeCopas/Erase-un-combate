EraseUnCombate:
ifeq ($(OS),Windows_NT)
	g++ -Wall -pipe -O3 *.cpp -g -o EraseUnCombate.exe -I C:\SFML-2.6.1\include -L C:\SFML-2.6.1\lib -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio
else
	g++ -Wall -pipe -O3 *.cpp -g -o EraseUnCombate.out -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio
endif

run:
ifeq ($(OS),Windows_NT)
	.\EraseUnCombate.exe
else
	./EraseUnCombate.out
endif

rerun:
	make -B
	make run

debug:
ifeq ($(OS),Windows_NT)
	gdb .\EraseUnCombate.exe
else
	gdb ./EraseUnCombate.out
endif