EraseUnCombate:
ifeq ($(OS),Windows_NT)
	g++ -Wall *.cpp -g -o EraseUnCombate.exe -I C:\SFML-2.6.1\include -L C:\SFML-2.6.1\lib -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio
else
	ifeq ($(OS),Linux)
		g++ -Wall *.cpp -g -o EraseUnCombate.out -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio
	endif
endif

run:
ifeq ($(OS),Windows_NT)
	.\EraseUnCombate.exe
else
	ifeq ($(OS),Linux)
		./EraseUnCombate.out
	endif
endif

rerun:
	make -B
	make run

debug:
ifeq ($(OS),Windows_NT)
	gdb .\EraseUnCombate.exe
else
	ifeq ($(OS),Linux)
		gdb ./EraseUnCombate.out
	endif
endif