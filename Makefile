all: main.cpp; clang++ -Wall -std=c++11 -o Gravity main.cpp Cat.cpp Game.cpp Particle.cpp Point.cpp `pkg-config --cflags sdl2` `pkg-config --libs sdl2`

commit:	main.cpp; git add --all; git commit -m "made progress"; git push origin master