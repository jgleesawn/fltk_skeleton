#include <GL/glew.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <vector>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

#include <FL/Fl_Gl_Window.H>
//#include <FL/gl.h>

//#include "visualengine.h"
//#include "object.h"

void Help();

class MyWindow : public Fl_Gl_Window {
	void draw();
	int handle(int);
	
	//bool valid();
	bool v;
	int basex, basey, curx, cury;
	int numv;	//number of vertices.  Used for num passed in to avoid re-compile.
	
//	std::vector<Object> objects;
//	VisualEngine ve;
	
public:
//last int added for passing number of vertices in.
	MyWindow(int X, int Y, int W, int H, const char *L, int);
	void InitGL();

	void Pstep();
	void Vstep();
};

typedef void (*func_ptr)(void *);
void ccallback(void *);

MyWindow::MyWindow(int X, int Y, int W, int H, const char *L, int num)
		: Fl_Gl_Window(X, Y, W, H, L), basex(0), basey(0), curx(-2), cury(2), v(false),numv(num) {
			Help(); 
			Fl::add_timeout(1.0/10.0, (func_ptr)ccallback, this);
}

void MyWindow::draw() {
	if( !valid() ) {
		GLenum err = glewInit(); 
		if (err != GLEW_OK) 
			exit(1);
		if (!GLEW_VERSION_3_3)
			exit(1);
//		ve.Init();
//		objects.push_back(Object(&pe,numv)); //Requires glewInit to be run.
	}
	Vstep();

	glDrawBuffer(GL_BACK);
}

void MyWindow::Vstep() {
//	for( std::vector<Object>::iterator it = objects.begin(); it != objects.end(); it++) {
//		ve.Draw(*it);
//	}
}
void MyWindow::Pstep() {
//	for( std::vector<Object>::iterator it = objects.begin(); it != objects.end(); it++) {
//		pe.Step(*it);
//	}
}

void ccallback(void * this_ptr) {
	MyWindow * t = (MyWindow *)this_ptr;
	//for( int i=0; i<2; i++)
		t->Pstep();

	((MyWindow *)this_ptr)->redraw();
	
	Fl::repeat_timeout(1.0/10.0, (func_ptr)ccallback, this_ptr);
}


int MyWindow::handle(int event) {
	int ekey;
	char text[2];
	switch(event) {
		case FL_KEYBOARD:
			ekey = Fl::event_key();
			strcpy(text,Fl::event_text());
			if( ekey == 65362 ) {
			}
			if( ekey == 65364 ) {
			}
			if( ekey == 65361 ) {
			}
			if( ekey == 65363 ) {
			}
			redraw();
//			fprintf(stderr,"%i\n",Fl::event_key());
//			fprintf(stderr,"%i %i",basex,basey);
//Escape Key
			if( ekey == 65307 )
				exit(0);
//Zoom-in wrt scaling
			if( strcmp(text,"z") == 0 ) {
			}
			if( strcmp(text,"x") == 0 ) {
			}
			if( strcmp(text,"q") == 0 ) {
			}
			if( strcmp(text,"e") == 0 ) {
			}
		break;
		default:
		break;
	}
}

int main(int argc, char **argv) {
	int num = 1024;
	if(argc > 1){
		num = atoi(argv[1]);
	}
	MyWindow *window = new MyWindow(20,40,300,180,"Hellow, World!", num);
//	Fl_Box *box = new Fl_Box(20,40,260,100,"Hello, World!");
	window->show(argc, argv);
	return Fl::run();
}

void Help() {
	printf("Escape to quit.\n");
	printf("q Zooms in.(Scales frustum up)\n");
	printf("e Zooms out.(Scales frustum down)\n");
	printf("z Increases z.\n");
	printf("x Decreases z.\n");
	printf("ArrowKeys Pan.\n");
	printf("Escape to quit.\n");
}
