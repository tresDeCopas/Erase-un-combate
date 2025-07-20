# Nombre del ejecutable
TARGET = EraseUnCombate

# Extensiones según SO
EXT_WIN = .exe
EXT_NOWIN = .out

# Archivos fuente
SRCS = Animacion.cpp AnimacionConGravedad.cpp AnimacionPorFrames.cpp Bitacora.cpp Combate.cpp ContenedorDeEfectos.cpp ContenedorDePersonajes.cpp GestorDeControles.cpp Hitbox.cpp main.cpp Personaje.cpp ReproductorDeMusica.cpp Utilidades.cpp VentanaPrincipal.cpp

# Archivos objeto (obtenidos automáticamente a partir de los fuente)
OBJS = $(SRCS:.cpp=.o)

# Compilador y opciones de compilación
CXX = g++
CXXFLAGS_WIN = -O3 -pipe -I C:\SFML-2.6.1\include -L C:\SFML-2.6.1\lib -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio
CXXFLAGS_NOWIN = -O3 -pipe -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio

# Regla para generar el ejecutablE
$(TARGET): $(OBJS)
ifeq ($(OS),Windows_NT)
	$(CXX) -o $(TARGET)$(EXT_WIN) $(OBJS) $(CXXFLAGS_WIN)
else
	$(CXX) -o $(TARGET)$(EXT_NOWIN) $(OBJS) $(CXXFLAGS_NOWIN)
endif

# Regla para compilar archivos .cpp a .o (al poner aquí Constantes.hpp tarda 341 horas más si
# cambias Constantes.hpp porque no he encontrado otra forma de hacerlo pero da igual jejej)
%.o: %.cpp Constantes.hpp
ifeq ($(OS),Windows_NT)
	$(CXX) $(CXXFLAGS_WIN) -c $< -o $@
else
	$(CXX) $(CXXFLAGS_NOWIN) -c $< -o $@
endif

# Regla para limpiar archivos generados
clean:
ifeq ($(OS),Windows_NT)
	echo "No sé cómo se borra en Windows xdd"
else
	rm -f $(OBJS) $(TARGET)$(EXT_NOWIN)
endif

# Regla para ejecutar el programa
run:
ifeq ($(OS),Windows_NT)
	.\$(TARGET)$(EXT_WIN)
else
	./$(TARGET)$(EXT_NOWIN)
endif

# Regla para compilar y ejecutar de una
rerun:
	make all
	make run

# Regla para iniciar una sesión de depuración con gdb
gdb:
ifeq ($(OS),Windows_NT)
	gdb .\$(TARGET)$(EXT_WIN)
else
	gdb ./$(TARGET)$(EXT_NOWIN)
endif

# Regla para compilar en paralelo
.PHONY: all clean

all: $(TARGET)