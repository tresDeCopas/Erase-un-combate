EraseUnCombate:
ifeq ($(OS),Windows_NT)
	g++ *.cpp -o EraseUnCombate.exe -I C:\SFML-2.6.1\include -L C:\SFML-2.6.1\lib -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio
else
	ifeq ($(OS),Linux)
		g++ *.cpp -o EraseUnCombate -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio
	endif
endif