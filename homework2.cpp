#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Letter.h"
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

//global variables
int xangle = 0;
int yangle = 0;
int zangle = 0;
char letter;
Letter E,F,I,H,L;

/*****************************************************************/
/********************** OpenGL Methods ***************************/
/*****************************************************************/

//init function
void init(){
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-50.0, 50.0, -50.0, 50.0, -50.0, 50.0);
  glEnable(GL_DEPTH_TEST);
}

//function to draw the letter
void drawLetter(Letter L){
  float x1, x2, y1, y2, z1, z2;
  float xPrev, yPrev, zPrev;

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glRotatef(xangle, 1.0, 0.0, 0.0);
  glRotatef(yangle, 0.0, 1.0, 0.0);
  glRotatef(zangle, 0.0, 0.0, 1.0);


  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_LINE_LOOP);
      //use the iterator given to us by the letter Class
      //iterate throguh the points and create the letter
    for(L.itr = L.graphPoints3D.begin(); L.itr != L.graphPoints3D.end(); L.itr++){

          if(L.itr == L.graphPoints3D.begin()){//else use the previous x and y
            x1 = *L.itr;
            advance(L.itr,1);
            y1 = *L.itr;
            advance(L.itr,1);
            z1 = *L.itr;
            advance(L.itr,1);
          }
          if(L.itr == L.graphPoints3D.end()){
            x1 = x2;
            y1 = y2;
            z1 = z2;
            L.itr = L.graphPoints3D.begin();
            x2 = *L.itr;
            advance(L.itr,1);
            y2 = *L.itr;
            advance(L.itr,1);
            z2 = *L.itr;

            L.itr = L.graphPoints3D.end();
          }
          else{
            //if not first or last case shift left one
            x1 = x2;
            y1 = y2;
            z1 = z2;

            x2 = *L.itr;
            advance(L.itr,1);
            y2 = *L.itr;
            advance(L.itr,1);
            z2 = *L.itr;
          }
          glVertex3f(x1, y1, 0);
          glVertex3f(x2, y2, 0);
          //glVertex3f(x2, y2, z1);
          //glVertex3f(x1, y1, z2);


    }
  //comment out this loop *****************************************************************************
  //this will give you flat 2d letter that you can spin
    for(L.itr = L.graphPoints3D.begin(); L.itr != L.graphPoints3D.end(); L.itr++){

          if(L.itr == L.graphPoints3D.begin()){//else use the previous x and y
            x1 = *L.itr;
            advance(L.itr,1);
            y1 = *L.itr;
            advance(L.itr,1);
            z1 = *L.itr;
            advance(L.itr,1);
          }
          if(L.itr == L.graphPoints3D.end()){
            x1 = x2;
            y1 = y2;
            z1 = z2;
            L.itr = L.graphPoints3D.begin();
            x2 = *L.itr;
            advance(L.itr,1);
            y2 = *L.itr;
            advance(L.itr,1);
            z2 = *L.itr;

            L.itr = L.graphPoints3D.end();
          }
          else{
            //if not first or last case shift left one
            x1 = x2;
            y1 = y2;
            z1 = z2;

            x2 = *L.itr;
            advance(L.itr,1);
            y2 = *L.itr;
            advance(L.itr,1);
            z2 = *L.itr;
          }
          glVertex3f(x1, y1, L.zValue);
          glVertex3f(x2, y2, L.zValue);
          //glVertex3f(x2, y2, z1);
          //glVertex3f(x1, y1, z2);

    }
    glEnd();


}

//keyboard callback
void keyboard(unsigned char key, int x, int y){
  if(key == 'x'){
      xangle -= 5;
  }
  else if(key == 'X'){
    xangle += 5;
  }
  else if(key == 'y'){
    yangle -= 5;
  }
  else if(key == 'Y'){
    yangle += 5;
  }
  else if(key == 'z'){
    zangle -= 5;
  }
  else if(key == 'Z'){
    zangle += 5;
  }

  //redraw objects
  glutPostRedisplay();
}

Letter switchLetter(){
  switch(letter){
    case 'E':
      return E;
      break;

    case 'F':
      return F;
      break;

    case 'I':
      return I;
      break;

    case 'H':
      return H;
      break;

    case 'L':
      return L;
      break;

    default:
      cout << "uh oh" << endl;
      terminate();
      break;
    }
}

//display callback
void display(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //switch to the correct object to dsiplay
  drawLetter(switchLetter());

  glFlush();

}


/*****************************************************************/
/********************** Input Methods ****************************/
/*****************************************************************/

//get user input
char pickLetter(){
  char temp;

  //Get user choice on what letter to display
  cout << "What letter would you like to display?(E,F,I,H,L) q to quit" << endl;
  cin >> temp;
  temp = toupper(temp);

  //allow user to exit
  if(temp == '0'){
    return 0;
  }

  //if not exit temp and not valid letter loop until accepted
  while(temp != 'L' && temp != 'E' && temp != 'F' &&
      temp != 'I' && temp != 'H'){

        cout << "Incorrect choice, options are E,F,I,H,L     0 to quit" << endl;
        cin  >> temp;
        temp = toupper(temp);

        //if user wants to exit allow it
        if(temp == '0'){
          return 0;
        }
        cout << endl;
  }

  return temp;
}

//get scalars from user, using reference integers to save the input
void getScalars(int &x, int &y, int &z){
  string readIn;
  //ask user what size they want the letter to be displayed
  cout << "What size would you like the letters to be?(q to quit)" << endl
       << "X: ";
  cin >> readIn;

  if(readIn == "q"){
    terminate();
  }

  x = atoi(readIn.c_str());
  cout << "Y: ";
  cin >> readIn;

  if(readIn == "q"){
    terminate();
  }

  y = atoi(readIn.c_str());

  cout << "Z: ";
  cin >> readIn;

  if(readIn == "q"){
    terminate();
  }

  z = atoi(readIn.c_str());
}

/*****************************************************************/
/************************ Main Method ****************************/
/*****************************************************************/

int main(int argc, char *argv[]){
  int xScaleValue, yScaleValue, zScaleValue;

  //init all letter ojects
  //eventually replace with file reading loop to remove hard coding

  int eCoords[] = {0,0,0,10,8,10,8,8,2,8,2,6,8,6,8,4,2,4,2,2,8,2,8,0};
  vector<int> etempCoords (eCoords,eCoords+sizeof(eCoords)/sizeof(eCoords[0]));
  E = Letter("E", etempCoords);

  int FCoords[] = {0,0,0,10,8,10,8,8,2,8,2,6,8,6,8,4,2,4,0,4};
  vector<int> ftempCoords (FCoords,FCoords+sizeof(FCoords)/sizeof(FCoords[0]));
  F = Letter("F", ftempCoords);

  int iCoords[] = {0,0,0,2,2,2,2,8,0,8,0,10,6,10,6,8,4,8,4,2,6,2,6,0};
  vector<int> itempCoords (iCoords,iCoords+sizeof(iCoords)/sizeof(iCoords[0]));
  I = Letter("I", itempCoords);

  int hCoords[] =  {0,0,0,9,2,9,2,6,6,6,6,9,8,9,0,8,6,0,6,4,6,6,2,6,2,4,2,0};
  vector<int> htempCoords (hCoords,hCoords+sizeof(hCoords)/sizeof(hCoords[0]));
  H = Letter("H", htempCoords);

  int lCoords[] = {0,0,0,8,2,8,2,2,6,2,6,0};
  vector<int> ltempCoords (lCoords,lCoords+sizeof(lCoords)/sizeof(lCoords[0]));
  L = Letter("L",ltempCoords);



  //debugging with simple 1x1 square
  int squareCoords[] = {0,0,0,1,1,1,1,0};
  vector<int> squareVector (squareCoords,squareCoords+sizeof(squareCoords)/sizeof(squareCoords[0]));
  Letter square = Letter("Square", squareVector);



  //get the letter to display
  letter = pickLetter();
  //get the scalars from user
  getScalars(xScaleValue, yScaleValue, zScaleValue);
  //display selected/scaled letters
  switch(letter){

    case 'E':
      //.scaleAndPrint(xScaleValue, yScaleValue);
      E.extrudeTo3D(xScaleValue, yScaleValue, zScaleValue);
      break;

    case 'F':
      F.extrudeTo3D(xScaleValue, yScaleValue, zScaleValue);
      break;

    case 'I':
      I.extrudeTo3D(xScaleValue, yScaleValue, zScaleValue);
      break;

    case 'H':
      H.extrudeTo3D(xScaleValue, yScaleValue, zScaleValue);
      break;

    case 'L':
      L.extrudeTo3D(xScaleValue, yScaleValue, zScaleValue);
      break;

    default:
      cout << "An unexpected error has occured, program terminating." << endl;
      terminate();
      break;
  }

  //Create OpenGL window
  glutInit(&argc,argv);
  glutInitWindowSize(500,500);
  glutInitWindowPosition(250,250);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH );
  glutCreateWindow("Letter");
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  init();
  glutMainLoop();


}
