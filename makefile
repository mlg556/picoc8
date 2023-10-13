

# windows: g++ -I src/include -L src/lib -o main main.cpp framebuf.cpp -lmingw32 -lSDL2main -lSDL2
# linux: g++ -o main main.cpp framebuf.cpp -lSDL2main -lSDL2

main: main.cpp framebuf.cpp sprite.h
	g++ -I src/include -L src/lib -o main main.cpp framebuf.cpp -lmingw32 -lSDL2main -lSDL2

run: main
	./main

clean:
	rm main
