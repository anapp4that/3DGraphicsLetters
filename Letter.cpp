#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Letter.h"
using namespace std;

/*****************************************************************/
/**************** Letter Class Implementation ********************/
/*****************************************************************/

Letter::Letter(){
  
}

Letter::Letter(string input, vector<int> points){
  this->name = input;
  this->graphPoints = points;
  this->graphPoints3D.reserve(((graphPoints.size()/2)+(graphPoints.size())));
  //determine max x and y values in the vector
  this->maxX = -1;
  this->maxY = -1;
  this->zValue = -1;
  for(int i =0; i < points.size(); i =i+2){
    if(points[i] > maxX){
      this->maxX = points[i];
    }
    if(points[i+1] > maxY){
      this->maxY = points[i+1];
    }
  }
}

//returns the name of the stored character
string Letter::getName(){
  return this->name;
}

//returns the coordinates
vector<int> Letter::getCoordinates(){
  return this->graphPoints;
}

//prints out the values of the graphPoints vector
void Letter::print(bool flag){
  //if print is called with flag being true then print the original grapgh of the letter
  if(flag){
    for(itr= this->graphPoints.begin(); itr != this->graphPoints.end(); itr++){
      cout << "x: " << *itr;
      advance(itr,1);
      cout << "  y: " << *itr << endl;
    }
  }
  else if(!flag){
    for(itr= this->graphPoints3D.begin(); itr != this->graphPoints3D.end(); itr++){
      cout << "x: " << *itr;
      advance(itr,1);
      cout << " y: " << *itr;
      advance(itr,1);
      cout << " z: " << *itr << endl;
    }
  }
}

//scales the letter and prints it
void Letter::scaleAndPrint(int x, int y){

  //use x and y max to calculate our scalar
  float xFactor = (float)x/(this->maxX);
  //cout << "xFactor: " << xFactor << endl;
  float yFactor = (float)y/(this->maxY);
  //cout << "yFactor: " << yFactor << endl;

  for(int i = 0; i < this->graphPoints.size(); i = i+2){
    //iterate through array and scale the coordinates
    cout << "X: " << (this->graphPoints[i])*xFactor << " Y: " << (this->graphPoints[i+1])*yFactor << endl;
  }
}

//scales/extrudes the 3d letter from the 2d graph
void Letter::extrudeTo3D(int x, int y, int z){
  //scale on the xy axis
  float xFactor = (float)x/(this->maxX);
  float yFactor = (float)x/(this->maxY);
  //saves the z scale so when we display the 3d letter we have the width
  this->zValue = z;

  for(itr = this->graphPoints.begin(); itr != this->graphPoints.end(); itr++){
    this->graphPoints3D.push_back((*itr)*xFactor);
    advance(itr,1);
    this->graphPoints3D.push_back((*itr)*yFactor);
    this->graphPoints3D.push_back(z);
  }
}
