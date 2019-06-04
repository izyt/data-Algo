// COMP1521 Final Exam
// Read points and determine bounding box

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

// Data type definitions

// all values are in the range 0..255
typedef unsigned char Byte;

// an (x,y) coordinate
typedef struct {
	Byte x;
	Byte y;
} Coord;

// a colour, given as 3 bytes (r,g,b)
typedef struct {
	Byte r;
	Byte g;
	Byte b;
} Color;

// a Point has a location and a colour
typedef struct {
	Coord coord;  // (x,y) location of Point
	Color color;  // colour of Point
} Point;

void boundingBox(int, Coord *, Coord *);

int main(int argc, char **argv)
{
	// check command-line arguments
	if (argc < 2) {
		fprintf(stderr, "Usage: %s PointsFile\n", argv[0]);
		exit(1);
	}

	// attempt to open specified file
	int in = open(argv[1],O_RDONLY);
	if (in < 0) {
		fprintf(stderr, "Can't read %s\n", argv[1]);
		exit(1);
	}

	// collect coordinates for bounding box
	Coord topLeft, bottomRight;
	boundingBox(in, &topLeft, &bottomRight);

	printf("TL=(%d,%d)  BR=(%d,%d)\n",
		 topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);

	// clean up
	close(in);
	return 0;
}

void boundingBox(int in, Coord *TL, Coord *BR)
{
    Point new;
    Byte top=0, bottom=0, left=0, right=0;
    int counter=0;
	while(read(in, &new, sizeof(Point))!=0){
	    if(counter==0){
	        top = bottom = new.coord.y;
	        left = right = new.coord.x;
	    }else{
	        if(new.coord.y < bottom)bottom = new.coord.y;
	        if(new.coord.y > top)top = new.coord.y;
	        if(new.coord.x <left) left = new.coord.x;
	        if(new.coord.x >right)right = new.coord.x;
	    }
	    counter++;
	}
	
	TL->x = left;
	TL->y = top;
	BR->x = right;
	BR->y = bottom;
}
