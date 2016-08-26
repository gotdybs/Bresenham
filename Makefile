#
# Dennis Bounded
# CS3600 Computer Graphics
# Raster Project
# March 18, 2016
# Needed to add -Wno-deprecated flag
# had to ignore  deprecated warning
# in order for to compile

# Object file list
OBJS = Point.o bresenham.o

# Executable Name
EXENAME = bresenham

# Macros
CC = g++
CCOPTS = -c -g -O0 -Wall -Wno-deprecated
LINK = g++
LINKOPTS = -o

all : $(EXENAME)

# OS X or Linux
OS = $(shell uname -s)

ifeq ($(OS), Darwin)
	LIBS = -framework OpenGL -framework GLUT
else
	LIBS = -lGL -lGLU -glut
endif

# LINK OBJECT FILES
$(EXENAME) : $(OBJS)
	$(LINK) $(LINKOPTS) $(EXENAME) $(OBJS) $(LIBS)

# COMPILE OBJECT FILES
bresenham.o : bresenham.cpp Point.h
	$(CC) $(CCOPTS) bresenham.cpp 

Point.o : Point.cpp Point.h
	$(CC) $(CCOPTS) Point.cpp
clean :
	rm -f *.o $(EXENAME)
