# g++ 01_hello_SDL.cpp -w -lSDL2 -o 01_hello_SDL

main: main.cpp framebuf.cpp sprite.h
	g++ -I src/include -L src/lib -o main main.cpp framebuf.cpp -lmingw32 -lSDL2main -lSDL2

run: main
	./main

clean:
	rm main
