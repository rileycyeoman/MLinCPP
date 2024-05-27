CFLAGS = -Wno-implicit-function-declaration

all: final

final: data.o data_handler.o
	gcc $(CFLAGS) data.o data_handler.o -o final
	chmod +x final
data.o: data.cpp
	gcc $(CFLAGS) -c data.cc data.hpp

data_handler.o: data_handler.cc data_handler.hpp
	gcc $(CFLAGS) -c data_handler.cc

clean: 
	echo "Removing everything but source files"
	rm data.o data_handler.o final