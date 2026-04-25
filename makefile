addressbook.exe : main.o populate.o file.o contact.o
	gcc -o addressbook.exe main.o populate.o file.o contact.o
	
main.o : main.c
	gcc -c main.c
populate.o : populate.c
	gcc -c populate.c
file.o : file.c
	gcc -c file.c
contact.o : contact.c
	gcc -c contact.c
clean:
	rm *.exe *.o
