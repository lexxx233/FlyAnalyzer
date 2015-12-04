CC=	g++
CFLAGS=	-g -std=c++11 `pkg-config --cflags opencv`  
AOBJS=	image.o ientropy.o
PROG=	flynotyper
LIBS=	-L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc

all:$(PROG)
       
flynotyper: flynotyper.cpp $(AOBJS)
	$(CC) $(CFLAGS) -o $@ $^  $(LIBS)

%.o : %.cpp %.h
	$(CC) -c $(CFLAGS) $< -o $@  

clean:
	rm -f *.o $(PROG)
	
