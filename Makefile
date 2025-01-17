NOMBREPROYECTO=EraseUnCombate

$(NOMBREPROYECTO):
ifeq ($(OS),Windows_NT)
	g++ -Wall -pipe -O0 *.cpp -g -o $(NOMBREPROYECTO).exe -I C:/SFML-3.0.0/include -L C:/SFML-3.0.0/lib -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio
else
	g++ -Wall -pipe -O0 *.cpp -g -o $(NOMBREPROYECTO).out -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio
endif

run:
ifeq ($(OS),Windows_NT)
	.\$(NOMBREPROYECTO).exe
else
	./$(NOMBREPROYECTO).out
endif

rerun:
	make -B
	make run

debug:
ifeq ($(OS),Windows_NT)
	gdb .\$(NOMBREPROYECTO).exe
else
	gdb ./$(NOMBREPROYECTO).out
endif