src=src/*.cpp src/*.c
output=bin/prog
libs=-lGL -lGLEW -lglfw -lassimp 
debug=1
all:
	clear
	rm -rf bin/*
	g++ $(src) -o ${output} ${libs}
run:
	clear
	./$(output) $(debug)