all: compile link

compile:
	g++ -I include -c src/main.cpp 
	mv *.o ./out
link:
	g++ out/main.o -o out/main -Llib -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system
run:
	out/main
clean:
	rm out/*.o
	find ./out -maxdepth 1 -type f -executable -delete