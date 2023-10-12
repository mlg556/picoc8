# g++ 01_hello_SDL.cpp -w -lSDL2 -o 01_hello_SDL

# windows: g++ -I src/include -L src/lib -o main main.cpp framebuf.cpp -lmingw32 -lSDL2main -lSDL2
# linux: g++ -o main main.cpp framebuf.cpp

main: main.cpp framebuf.cpp sprite.h
	g++ -o main main.cpp framebuf.cpp -lSDL2main -lSDL2

run: main
	./main

clean:
	rm main
