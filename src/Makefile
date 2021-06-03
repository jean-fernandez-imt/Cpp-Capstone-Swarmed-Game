#EXEC specifies the name of the executable
EXEC = Game-debug

#OBJS specifies which files to compile as part of the project
OBJS = main.o game.o keyboard.o media.o renderer.o snake.o texture.o

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w -ggdb

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image

#This is the target that compiles our executable
${EXEC}: ${OBJS}
	${CC} ${COMPILER_FLAGS} ${LINKER_FLAGS} -o ${EXEC} ${OBJS}

#From here we will compile the objects for the executable
main.o: main.cpp keyboard.h game.h renderer.h media.h texture.h
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c main.cpp

game.o: game.cpp game.h keyboard.h renderer.h snake.h 
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c game.cpp

keyboard.o: keyboard.cpp keyboard.h snake.h 
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c keyboard.cpp

media.o: media.cpp media.h keyboard.h snake.h 
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c media.cpp

renderer.o: renderer.cpp renderer.h texture.h snake.h 
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c renderer.cpp

snake.o: snake.cpp snake.h
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c snake.cpp

texture.o: texture.cpp texture.h
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c texture.cpp

clean:
	rm -f ${EXEC} ${OBJS}