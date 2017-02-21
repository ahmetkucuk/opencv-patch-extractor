
OBJS = display_image.cpp FileReader.cpp
DEBUG = -g
CFLAGS = -Wall $(DEBUG)
LFLAGS = -Wall $(DEBUG)
CC = g++
CV1 = -ggdb `pkg-config --cflags opencv`
CV2 = -L/usr/lib64/ -I/usr/local/include -lm `pkg-config --libs opencv`

roi : $(OBJS)
	$(CC) $(CV1) $(CFLAGS) display_image.cpp FileReader.cpp Event.cpp -o roi $(CV2)




