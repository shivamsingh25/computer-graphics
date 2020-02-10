// Computer Graphics
// Assignment 03
// Emoticon + Translation + Rotation + Animation
// Apple's Zany Face
// Shivam Singh - AU17B1021

#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <process.h>
#include <graphics.h>

// Global varibles for function to coordinate with each other for animation.
float animateStatus = 0, status_x, status_y;

// DDA line drawing algorithm function
void DDAline(float X0, float Y0, float X1, float Y1, int color)
{
	int i;
	// calculate dx & dy
	int dx = X1 - X0;
	int dy = Y1 - Y0;

	// calculate p required for generating pixels
	int p = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

	float Xinc = dx / (float)p;
	float Yinc = dy / (float)p;

	// Put pixel for each step
	float X = X0;
	float Y = Y0;
	for (i = 0; i <= p; i++)
	{

		putpixel(X, Y, color); // Plot
		X += Xinc;
		Y += Yinc;
	}
}


// User defined Bresenham circle drawing function
void bresenhamCircle(int x, int y, int r, int color){
    int xnext, ynext, p;
	p=(3-(2*r));  // Calculate Decision factor

	ynext=r; // initialize ynext with r

	for(xnext=0;xnext<=ynext;xnext++)
	{
		putpixel((xnext+x),(ynext+y),color);					//Octant1
		putpixel((xnext+x),(((-1)*ynext+y)),color);			//Octant7
		putpixel((((-1)*xnext+x)),(((-1)*ynext+y)),color);		//Octant5
		putpixel((((-1)*xnext+x)),(ynext+y),color);			//Octant3

		putpixel((ynext+x),(xnext+y),color);					//Octant2
		putpixel((((-1)*ynext+x)),(xnext+y),color);			//Octant8
		putpixel((((-1)*ynext+x)),(((-1)*xnext+y)),color);		//Octant6
		putpixel((ynext+x),(((-1)*xnext+y)),color);			//Octant4

		if(p < 0){
			p=p+(4*xnext)+6;
		}else{
			ynext--;
			p = p-(4*ynext)+(4*xnext)+10;
		}
	}
}

// User defined Flood fill function 4 pixels
int floodFIll4UserDefined(int x, int y, int oldcolor, int newcolor)
{
	// Change old fill color to new fill color
	if (getpixel(x, y) == oldcolor)
	{
		putpixel(x, y, newcolor);
		//printf("%d - %d", x, y);
		// Recursively call function to fill neighbour pixels
		floodFIll4UserDefined(x, y + 1, oldcolor, newcolor);
		floodFIll4UserDefined(x - 1, y, oldcolor, newcolor);
		floodFIll4UserDefined(x, y - 1, oldcolor, newcolor);
		floodFIll4UserDefined(x + 1, y, oldcolor, newcolor);
	}
	return 0;
}

// User defined Boundary fill function 4 pixels
int boundaryFill4UserDefined(int x, int y, int boundarycolor, int newcolor)
{
	// fill until boundary is reached
	if (getpixel(x, y) != boundarycolor && getpixel(x, y) != newcolor)
	{
		putpixel(x, y, newcolor);
		//printf("%d - %d", x, y);
		// Recursively call function to fill neighbour pixels
		boundaryFill4UserDefined(x, y + 1, boundarycolor, newcolor);
		boundaryFill4UserDefined(x - 1, y, boundarycolor, newcolor);
		boundaryFill4UserDefined(x, y - 1, boundarycolor, newcolor);
		boundaryFill4UserDefined(x + 1, y, boundarycolor, newcolor);
	}
	return 0;
}


// Function to rotate emoticon
void rotateZany(int r)
{
	// Different variables to store calculated coordinates change of different shapes and angles 
	int resr;
	float rr;
	float leftEye_x1, leftEye_x2, leftEye_y1, leftEye_y2, rightEye_x1, rightEye_x2, rightEye_y1, rightEye_y2; // Eye Coordinates
	float mouthCurve_x1, mouthCurve_y1, upperLip_x1, upperLip_x2, upperLip_y1, upperLip_y2,
		teeth_x1, teeth_x2, teeth_y1, teeth_y2, tongue_x, tongue_y, leftTongue_x1, leftTongue_y1,
		leftTongue_x2, leftTongue_y2, rightTongue_x1, rightTongue_y1, rightTongue_x2, rightTongue_y2,
		topTongue_x1, topTongue_x2, topTongue_y1, topTongue_y2;

	float x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18,
		y1, y2, y3, y4, y5, y6, y7, y8, y9, y10, y11, y12, y13, y14, y15, y16, y17, y18;

	leftEye_x1 = 305;
	leftEye_y1 = 238;
	leftEye_x2 = 305;
	leftEye_y2 = 239;

	rightEye_x1 = 326;
	rightEye_y1 = 228;
	rightEye_x2 = 324;
	rightEye_y2 = 225;

	mouthCurve_x1 = (getmaxx() / 2);
	mouthCurve_y1 = (getmaxy() / 2);

	upperLip_x1 = 304;
	upperLip_y1 = 255;
	upperLip_x2 = 342;
	upperLip_y2 = 234;

	teeth_x1 = 308;
	teeth_y1 = 258;
	teeth_x2 = 341;
	teeth_y2 = 240;

	tongue_x = 320;
	tongue_y = 263;

	leftTongue_x1 = 312;
	leftTongue_y1 = 257;
	leftTongue_x2 = 312;
	leftTongue_y2 = 263;
	rightTongue_x1 = 328;
	rightTongue_y1 = 249;
	rightTongue_x2 = 328;
	rightTongue_y2 = 263;
	topTongue_x1 = 312;
	topTongue_y1 = 257;
	topTongue_x2 = 328;
	topTongue_y2 = 249;

	if (r < 0)
	{
		resr = 360 - r;
		rr = resr * (M_PI / 180);
	}
	else
	{
		rr = r * (M_PI / 180);
	}

	// calculate change in coordinates of different shapes (starting and ending points) with respect to user given angle.

	x1 = (leftEye_x1 - getmaxx() / 2) * cos(rr) + (leftEye_y1 - getmaxy() / 2) * sin(rr);
	y1 = (leftEye_y1 - getmaxy() / 2) * cos(rr) - (leftEye_x1 - getmaxx() / 2) * sin(rr);
	x2 = (leftEye_x2 - getmaxx() / 2) * cos(rr) + (leftEye_y2 - getmaxy() / 2) * sin(rr);
	y2 = (leftEye_y2 - getmaxy() / 2) * cos(rr) - (leftEye_x2 - getmaxx() / 2) * sin(rr);
	x3 = (rightEye_x1 - getmaxx() / 2) * cos(rr) + (rightEye_y1 - getmaxy() / 2) * sin(rr);
	y3 = (rightEye_y1 - getmaxy() / 2) * cos(rr) - (rightEye_x1 - getmaxx() / 2) * sin(rr);
	x4 = (rightEye_x2 - getmaxx() / 2) * cos(rr) + (rightEye_y2 - getmaxy() / 2) * sin(rr);
	y4 = (rightEye_y2 - getmaxy() / 2) * cos(rr) - (rightEye_x2 - getmaxx() / 2) * sin(rr);
	x5 = (mouthCurve_x1 - cos(rr) + (mouthCurve_y1 - getmaxy() / 2) * sin(rr));
	y5 = (mouthCurve_y1 - getmaxy() / 2) * cos(rr) - (mouthCurve_x1 - getmaxx() / 2) * sin(rr);
	x6 = (upperLip_x1 - getmaxx() / 2) * cos(rr) + (upperLip_y1 - getmaxy() / 2) * sin(rr);
	y6 = (upperLip_y1 - getmaxy() / 2) * cos(rr) - (upperLip_x1 - getmaxx() / 2) * sin(rr);
	x7 = (upperLip_x2 - getmaxx() / 2) * cos(rr) + (upperLip_y2 - getmaxy() / 2) * sin(rr);
	y7 = (upperLip_y2 - getmaxy() / 2) * cos(rr) - (upperLip_x2 - getmaxx() / 2) * sin(rr);
	x8 = (teeth_x1 - getmaxx() / 2) * cos(rr) + (teeth_y1 - getmaxy() / 2) * sin(rr);
	y8 = (teeth_y1 - getmaxy() / 2) * cos(rr) - (teeth_x1 - getmaxx() / 2) * sin(rr);
	x9 = (teeth_x2 - getmaxx() / 2) * cos(rr) + (teeth_y2 - getmaxy() / 2) * sin(rr);
	y9 = (teeth_y2 - getmaxy() / 2) * cos(rr) - (teeth_x2 - getmaxx() / 2) * sin(rr);
	x10 = (tongue_x - getmaxx() / 2) * cos(rr) + (tongue_y - getmaxy() / 2) * sin(rr);
	y10 = (tongue_y - getmaxy() / 2) * cos(rr) - (tongue_x - getmaxx() / 2) * sin(rr);
	x11 = (leftTongue_x1 - getmaxx() / 2) * cos(rr) + (leftTongue_y1 - getmaxy() / 2) * sin(rr);
	y11 = (leftTongue_y1 - getmaxy() / 2) * cos(rr) - (leftTongue_x1 - getmaxx() / 2) * sin(rr);
	x12 = (leftTongue_x2 - getmaxx() / 2) * cos(rr) + (leftTongue_y2 - getmaxy() / 2) * sin(rr);
	y12 = (leftTongue_y2 - getmaxy() / 2) * cos(rr) - (leftTongue_x2 - getmaxx() / 2) * sin(rr);
	x13 = (rightTongue_x1 - getmaxx() / 2) * cos(rr) + (rightTongue_y1 - getmaxy() / 2) * sin(rr);
	y13 = (rightTongue_y1 - getmaxy() / 2) * cos(rr) - (rightTongue_x1 - getmaxx() / 2) * sin(rr);
	x14 = (rightTongue_x2 - getmaxx() / 2) * cos(rr) + (rightTongue_y2 - getmaxy() / 2) * sin(rr);
	y14 = (rightTongue_y2 - getmaxy() / 2) * cos(rr) - (rightTongue_x2 - getmaxx() / 2) * sin(rr);
	x15 = (topTongue_x1 - getmaxx() / 2) * cos(rr) + (topTongue_y1 - getmaxy() / 2) * sin(rr);
	y15 = (topTongue_y1 - getmaxy() / 2) * cos(rr) - (topTongue_x1 - getmaxx() / 2) * sin(rr);
	x16 = (topTongue_x2 - getmaxx() / 2) * cos(rr) + (topTongue_y2 - getmaxy() / 2) * sin(rr);
	y16 = (topTongue_y2 - getmaxy() / 2) * cos(rr) - (topTongue_x2 - getmaxx() / 2) * sin(rr);

	// Used only for animation of rotating eyes.
	if(animateStatus == 1){
			// Left eye
			setcolor(WHITE);
			circle(status_x + x1 + getmaxx() / 2, y1 + getmaxy() / 2, 6);
			floodFIll4UserDefined(status_x + x1 + getmaxx() / 2, y1 + getmaxy() / 2, getpixel(status_x + x1 + getmaxx() / 2, y1 + getmaxy() / 2), WHITE);

			setcolor(BLACK);
			circle(status_x + x2 + getmaxx() / 2, y2 + getmaxy() / 2, 2); // Eye ball
			floodFIll4UserDefined(status_x + x2 + getmaxx() / 2, y2 + getmaxy() / 2, getpixel(status_x + x2 + getmaxx() / 2, y2 + getmaxy() / 2), BLACK);

			// Right eye
			setcolor(WHITE);
			circle(status_x + x3 + getmaxx() / 2, y3 + getmaxy() / 2, 10);
			floodFIll4UserDefined(status_x + x3 + getmaxx() / 2, y3 + getmaxy() / 2, getpixel(status_x + x3 + getmaxx() / 2, y3 + getmaxy() / 2), WHITE);
			setcolor(BLACK);
			circle(status_x + x4 + getmaxx() / 2, y4 + getmaxy() / 2, 4); // Eye ball
			floodFIll4UserDefined(status_x + x4 + getmaxx() / 2, y4 + getmaxy() / 2, getpixel(status_x + x4 + getmaxx() / 2, y4 + getmaxy() / 2), BLACK);
	}else{

	// Plot rotation of emoticon at user given angle.

	setcolor(YELLOW);
	circle((getmaxx() / 2), (getmaxy() / 2), 30); // Face
	setfillstyle(1, YELLOW);
	floodfill((getmaxx() / 2), (getmaxy() / 2), YELLOW);

	// Left eye
	setcolor(WHITE);
	circle(x1 + getmaxx() / 2, y1 + getmaxy() / 2, 6);
	setfillstyle(1, WHITE);
	floodfill(x1 + getmaxx() / 2, y1 + getmaxy() / 2, WHITE);
	setcolor(BLACK);
	circle(x2 + getmaxx() / 2, y2 + getmaxy() / 2, 2); // Eye ball
	floodFIll4UserDefined(x2 + getmaxx() / 2, y2 + getmaxy() / 2, getpixel(x2 + getmaxx() / 2, y2 + getmaxy() / 2), BLACK);

	// Right eye
	setcolor(WHITE);
	circle(x3 + getmaxx() / 2, y3 + getmaxy() / 2, 10);
	floodfill(x3 + getmaxx() / 2, y3 + getmaxy() / 2, WHITE);
	setcolor(BLACK);
	circle(x4 + getmaxx() / 2, y4 + getmaxy() / 2, 4); // Eye ball
	floodFIll4UserDefined(x4 + getmaxx() / 2, y4 + getmaxy() / 2, getpixel(x4 + getmaxx() / 2, y4 + getmaxy() / 2), BLACK);

	// Mouth
	arc(x5, y5 + getmaxy() / 2, 225 + r, 10 + r, 23); // mouth curve
	line(x6 + getmaxx() / 2, y6 + getmaxy() / 2, x7 + getmaxx() / 2, y7 + getmaxy() / 2); // Upper lip
	line(x8 + getmaxx() / 2, y8 + getmaxy() / 2, x9 + getmaxx() / 2, y9 + getmaxy() / 2); // Teeth

	// Fill inner mouth area on specific angles to avoid fill lag on other angles.
	if(r == 0 || r == 360){
		floodFIll4UserDefined(320, 260, getpixel(320, 260), BLACK);
		floodFIll4UserDefined(306, 257, getpixel(306, 257), WHITE);
	}
	if(r == 90){
		floodFIll4UserDefined(10 + (x8+x9)/2 + getmaxx() / 2, getmaxy() / 2, getpixel(10 + (x8+x9)/2 + getmaxx() / 2, getmaxy() / 2), BLACK);
	}
	if(r == 180){
		floodFIll4UserDefined((x8+x9)/2 + getmaxx() / 2, (y8 + getmaxy() / 2), getpixel((x8+x9)/2 + getmaxx() / 2, (y8 + getmaxy() / 2)), BLACK);
	}
	if(r == 270){
		floodFIll4UserDefined(((x8+x9)/2 + getmaxx() / 2) - 5, 20 + y8 + getmaxy() / 2, getpixel(((x8+x9)/2 + getmaxx() / 2) - 5, 20 + y8 + getmaxy() / 2), BLACK);
	}

	setcolor(RED);
	arc(x10 + getmaxx() / 2, y10 + getmaxy() / 2, 180 + r, 360 + r, 8); // Tongue Tip curve
	line(x11 + getmaxx() / 2, y11 + getmaxy() / 2, x12 + getmaxx() / 2, y12 + getmaxy() / 2); // left tongue line
	line(x13 + getmaxx() / 2, y13 + getmaxy() / 2, x14 + getmaxx() / 2, y14 + getmaxy() / 2); // right tongue line
	line(x15 + getmaxx() / 2, y15 + getmaxy() / 2, x16 + getmaxx() / 2, y16 + getmaxy() / 2); // Top tongue line
	boundaryFill4UserDefined(x10 + getmaxx() / 2, y10 + getmaxy() / 2, RED, RED);	// Boundary Fill tongue
	
	}																
}

// Function on plot face of emoji that is the base of emoticon.
void face(screenx, screeny, x, y){
	setcolor(YELLOW);
	circle((screenx / 2) + x, (screeny / 2) + y, 30); // Face
	//floodFIll4UserDefined((screenx / 2) + x, (screeny / 2) + y, getpixel((screenx / 2) + x, (screeny / 2) + y), YELLOW);
	setfillstyle(1, YELLOW);
	floodfill((screenx / 2) + x, (screeny / 2) + y, YELLOW);
}

// Function to plot mouth part of the emoticon without tongue
void mouth(screenx, screeny, x, y){
	// Mouth
	arc((screenx / 2) + x, (screeny / 2) + y, 225, 10, 23); // mouth curve
	line(304 + x, 255 + y, 342 + x, 234 + y);				// Upper lip
	line(308 + x, 258 + y, 341 + x, 240 + y);				// Teeth
	floodFIll4UserDefined(320 + x, 260 + y, getpixel(320 + x, 260 + y), BLACK);
	floodFIll4UserDefined(306 + x, 257 + y, getpixel(306 + x, 257 + y), WHITE);
}

void builtInZany(screenx, screeny, x, y)
{

	//   Using user defined flood fill function (4 pixels) as
	//   system's flood fill function are not suitable for curves (8 pixels)

	face(screenx, screeny, x, y);

	// Left eye
	setcolor(WHITE);
	circle(305 + x, 238 + y, 6);
	setfillstyle(1, WHITE);
	floodfill(305 + x, 238 + y, WHITE);
	setcolor(BLACK);
	circle(305 + x, 239 + y, 2); // Eye ball
	floodFIll4UserDefined(305 + x, 239 + y, getpixel(305 + x, 239 + y), BLACK);

	// Right eye
	setcolor(WHITE);
	circle(326 + x, 228 + y, 10);
	floodfill(326 + x, 228 + y, WHITE);
	setcolor(BLACK);
	circle(324 + x, 225 + y, 4); // Eye ball
	floodFIll4UserDefined(324 + x, 225 + y, getpixel(324 + x, 225 + y), BLACK);

	mouth(screenx, screeny, x, y);

	// Tongue
	setcolor(RED);
	arc(320 + x, 263 + y, 180, 360, 8);		  // Tongue Tip curve
	line(312 + x, 257 + y, 312 + x, 263 + y); // left tongue line
	line(328 + x, 249 + y, 328 + x, 263 + y); // right tongue line
	line(312 + x, 257 + y, 328 + x, 249 + y); // Top tongue line
	boundaryFill4UserDefined(320 + x, 258 + y, RED, RED);
	setcolor(BROWN);
	line(320 + x, 256 + y, 320 + x, 265 + y); // Tongue middle line
											  // Ellipse aren't good for long slant tongue
											  // Uncomment below line to see.
											  //ellipse(322, 245, 210, 355, 10, 25);
}

void scaleZany(int screenx, int screeny, float scale)
{
	printf("\n-> Original (on bottom right) vs scaled\n-> Press any key to continue");

	/*
		Using user defined flood fill function (4 pixels) as
		system's flood fill function are not suitable for curves (8 pixels)
	*/

	// Filling only for scale factor above 0.6 and 1.2 to avoid fill lag.

	setcolor(YELLOW);
	circle((screenx / 2) * scale, (screeny / 2) * scale, 30 * scale); // Face
	if (scale > 0.7 && scale < 1.2)
	{
		floodFIll4UserDefined((screenx / 2) * scale, (screeny / 2) * scale, getpixel((screenx / 2) * scale, (screeny / 2) * scale), YELLOW);
	}
	else
	{
		printf("\n-> Filling is available only for scale factor between 0.6 and 1.2 to avoid fill lag.");
	}

	// Left eye
	setcolor(WHITE);
	circle(305 * scale, 238 * scale, 6 * scale);
	if (scale > 0.7 && scale < 1.2)
	{
		floodfill(305 * scale, 238 * scale, WHITE);
	}
	setcolor(BLACK);
	circle(305 * scale, 239 * scale, 2 * scale); // Eye ball
	if (scale > 0.7 && scale < 1.2)
	{
		floodFIll4UserDefined(305 * scale, 239 * scale, getpixel(305 * scale, 239 * scale), BLACK);
	}

	// Right eye
	setcolor(WHITE);
	circle(326 * scale, 228 * scale, 10 * scale);
	if (scale > 0.7 && scale < 1.2)
	{
		floodfill(326 * scale, 228 * scale, WHITE);
	}
	setcolor(BLACK);
	circle(324 * scale, 225 * scale, 4 * scale); // Eye ball
	if (scale > 0.7 && scale < 1.2)
	{
		floodFIll4UserDefined(324 * scale, 225 * scale, getpixel(324 * scale, 225 * scale), BLACK);
	}

	// Mouth
	arc((screenx / 2) * scale, (screeny / 2) * scale, 225, 10, 23 * scale); // mouth curve
	line(304 * scale, 255 * scale, 342 * scale, 234 * scale);				// Upper lip
	line(308 * scale, 258 * scale, 341 * scale, 240 * scale);				// Teeth
	if (scale > 0.7 && scale < 1.2)
	{
		floodFIll4UserDefined(320 * scale, 260 * scale, getpixel(320 * scale, 260 * scale), BLACK);
		floodFIll4UserDefined(306 * scale, 257 * scale, getpixel(306 * scale, 257 * scale), WHITE);
	}
	setcolor(RED);
	arc(320 * scale, 263 * scale, 180, 360, 8 * scale);		  // Tongue Tip curve
	line(312 * scale, 257 * scale, 312 * scale, 263 * scale); // left tongue line
	line(328 * scale, 249 * scale, 328 * scale, 263 * scale); // right tongue line
	line(312 * scale, 257 * scale, 328 * scale, 249 * scale); // Top tongue line
	if (scale > 0.7 && scale < 1.2)
	{
		boundaryFill4UserDefined(320 * scale, 258 * scale, RED, RED);
	}
	setcolor(BROWN);
	line(320 * scale, 256 * scale, 320 * scale, 265 * scale); // Tongue middle line
}

int animateZany(screenx, screeny){
	int x, y = 110;
	// Special trigger variable to use above dependency emoticon functions
	animateStatus = 1;

	// Rotate from x to center of screen -> animation of rotation of emoticon with base face and eyes.
	for(x = 220; x >= 0; x -= 20){
		y +=20;
		status_x = x;
		cleardevice();
		face(screenx, screeny, x, 0);
		rotateZany(y);
		delay(70);
	}

	// Open mouth once reached center.
	mouth(screenx, screeny, 0, 0);
	delay(200);

	// Tongue
	setcolor(RED);
	line(312, 257, 328, 249); // Top tongue line

	// Short tongue -> gives effect of tongue been taken out
	line(312, 257, 312, 260); // left tongue line
	line(328, 249, 328 , 262); // right tongue line
	arc(320, 257, 180, 360, 8);		  // Tongue Tip curve
	boundaryFill4UserDefined(320, 256 , RED, RED);

	delay(200);

	// Enlarge the tongue -> gives effect of tongue been taken out
	arc(320, 263, 180, 360, 8);		  // Tongue Tip curve
	line(312, 257, 312, 263); // left tongue line
	line(328, 249, 328 , 263); // right tongue line
	boundaryFill4UserDefined(320, 266 , RED, RED);
	setcolor(BROWN);
	line(320, 256, 320, 265); // Tongue middle line

	printf("\n\n\n-> Press any key to continue.");

	animateStatus = 0;
	return 0;
}

// Includes Transition + Rotation + Animation MENU
int transitionZany(screenx, screeny)
{
	int x, y, c;
	float scale;
animateMenu:
	clrscr();
	cleardevice();
	printf("\n\n\tZany Face Transformation:\n\n\t\t1. Translate\n\n\t\t2. Rotate\n\n\t\t3. Scale\n\n\t\t4. Animate\n\n\t\t5. Go back to main menu.\n\n\tYour Choice(1/2/3/4/5): ");
	scanf("%d", &c);
	clrscr();
	cleardevice();
	// Menu Driven transition application.
	switch (c)
	{
	case 1:
		printf("\n\n-> Enter Tranlate coordinates:\n\tX:");
		scanf("%d", &x);
		printf("\n\tY:");
		scanf("%d", &y);
		printf("\n\n-> The Emoticon has been \n    shifted/ translated from the\n    center origin to (%d, %d).", x, y);
		line((screenx/2),0,(screenx/2),screeny);
		line(0,(screeny/2),screenx,(screeny/2));
		builtInZany(screenx, screeny, x, y);
		break;
	case 2:
		getAngle:
		printf("\n\n\tEnter Rotation Angle: ");
		scanf("%d", &y);
		if(y > 360 || y < 0){
			clrscr();
			cleardevice();
			printf("\n\tInvalid Angle.. !! Please use any angle between 0 to 360. ");
			goto getAngle;
		}
		rotateZany(y);
		break;
	case 3:
		printf("\n\n\tEnter Scaling Factor (0.7 - 1.2): ");
		scanf("%f", &scale);
		builtInZany(screenx, screeny, 220, 190);
		scaleZany(screenx, screeny, scale);
		break;
	case 4: animateZany(screenx, screeny);break;
	case 5:
		return 0;
	default:
		goto animateMenu;
	}
	getch();
	goto animateMenu;
}

void algorithmsZany(screenx, screeny){
	printf("\n\n-> Zany Face: Using Bresenham's Circle algorithm & DDA line algorithm\n\n-> Press any key to continue");

	bresenhamCircle(screenx/2, screeny/2, 30, YELLOW); // Face
	floodFIll4UserDefined(screenx/2, screeny/2, getpixel(screenx/2, screeny/2), YELLOW);

	// Left eye
	bresenhamCircle(305, 238, 6, WHITE);
	floodFIll4UserDefined(305, 238, getpixel(305, 238), WHITE);
	bresenhamCircle(305, 239, 2, BLACK); // Eye ball
	floodFIll4UserDefined(305, 239, getpixel(305, 239), BLACK);


	// Right eye
	bresenhamCircle(326, 228, 10, WHITE);
	floodfill(326, 228, WHITE);
	bresenhamCircle(324, 225, 4, BLACK); // Eye ball
	floodFIll4UserDefined(324, 225, getpixel(324, 225), BLACK);

	// Mouth
	setcolor(BLACK);
	arc(screenx/2, screeny/2, 225, 10, 23); // mouth curve
	DDAline(304, 255, 342, 234, BLACK); // Upper lip
	DDAline(308, 258, 341, 240, BLACK); // Teeth
	floodFIll4UserDefined(320, 260, getpixel(320, 260), BLACK);
	floodFIll4UserDefined(306, 257, getpixel(306, 257), WHITE);
	setcolor(RED);
	arc(320, 263, 180, 360, 8); // Tongue Tip curve
	DDAline(312, 257, 312, 263, RED); // left tongue line
	DDAline(328, 249, 328, 263, RED); // right tongue line
	DDAline(312, 257, 328, 249, RED); // Top tongue line
	boundaryFill4UserDefined(320, 258, RED, RED);
	DDAline(320, 256, 320, 265, BROWN); // Tongue middle line
}

void main()
{
	int gd = DETECT, gm, screenx, screeny, choice;
	clrscr();
	initgraph(&gd, &gm, "C:\TURBOC3\BGI");
	screenx = getmaxx();
	screeny = getmaxy();
menu:
	clrscr();
	cleardevice();
	printf("Screen Resolution: %d x %d \n\nZany Face:", screenx, screeny);
	//	printf("\n\nA smiley making a silly face. A yellow face with a big grin and wide, white eyes, one larger than the other and in a wild, cockeyed expression. Many platforms, including Apple, depict its tongue stuck out and head tilted; others feature a full-toothed grin, giving it a more unhinged appearance. Commonly represents such activities as acting goofy, having fun, and partying as well as various senses of slang terms like crazy, usually in a positive manner. May convey a spirit of wackiness more generally. \n\nZany Face was approved as part of Unicode 10.0 in 2017 under the name “Grinning Face With One Large and One Small Eye” and added to Emoji 5.0 in 2017. ");
	//	printf("\n\nUnicode code: Grinning Face With One Large and One Small Eye");
	printf("\n\n\tChoose method to generate Zany face: \n\n\t\t1. Using C's Built in graphics functions.\n\n\t\t2. Using Algorithms\n\n\t\t3. Transformation\n\n\t\t4. Exit\n\n\tYour Choice (1/2/3): ");
	scanf("%d", &choice);

	clrscr();
	cleardevice();
	// Menu driven emoticon generation.
	switch (choice)
	{
	case 1:
		printf("\n\nZany Face: Using C's built in graphics functions\n\n-> Press any key to continue");
		builtInZany(screenx, screeny, 0, 0);
		break;
	case 2: 
		algorithmsZany(screenx, screeny);
		break;
	case 3:
		transitionZany(screenx, screeny);
		goto menu;
	case 4:
		exit(1);
	default:
		goto menu;
	}
	getch();
	goto menu;
}
