# g++ 01_hello_SDL.cpp -w -lSDL2 -o 01_hello_SDL

main: main.cpp
	g++ main.cpp lib/framebuf/framebuf.cpp -Wall -lSDL2 -o main

run: main
	./main

clean:
	rm main
