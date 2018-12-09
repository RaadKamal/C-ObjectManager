all:main0 main1 main2 main3 main4

ObjectManager.o: ObjectManager.c ObjectManager.h 
	clang -Wall ObjectManager.c -o ObjectManager.o -c -g  


main0: main0.c ObjectManager.h ObjectManager.o
	clang -Wall main0.c ObjectManager.o -o main0
main1: main1.c ObjectManager.h ObjectManager.o
	clang -Wall main1.c ObjectManager.o -o main1
main2: main2.c ObjectManager.h ObjectManager.o 
	clang -Wall main2.c ObjectManager.o -o main2 -g
main3: main3.c ObjectManager.h ObjectManager.o
	clang -Wall main3.c ObjectManager.o -o main3
main4: main4.c ObjectManager.h ObjectManager.o
	clang -Wall main4.c ObjectManager.o -o main4
clean:
	rm -f ObjectManager.o main0 main1 main2 main3 main4

