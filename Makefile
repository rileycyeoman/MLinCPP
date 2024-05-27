CFLAGS = -Wno-implicit-function-declaration

all: final

final: data.o data_handler.o
	gcc $(CFLAGS) data.o data_handler.o -o final
	chmod +x final
data.o: data.cpp
	gcc $(CFLAGS) -c data.cpp data.h

data_handler.o: data_handler.cpp data_handler.h
	gcc $(CFLAGS) -c data_handler.cpp

clean: 
	echo "Removing everything but source files"
	rm data.o data_handler.o final