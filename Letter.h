#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

/*****************************************************************/
/******************** Letter Class Header ************************/
/*****************************************************************/
class Letter{

  public:
    Letter();
    Letter(string , vector<int>);
    string getName();
    vector<int> getCoordinates();
    void print(bool);//method to print content of point vector
    void scaleAndPrint(int, int);
    void extrudeTo3D(int, int, int);//takes the 2d vector, and given a y size creates a 3d object
    vector<int>::iterator itr;
    //prevents us from needing to store an array with z=0 values
    vector<int> graphPoints; // the points that consist of its graph
    vector<int> graphPoints3D; //points extruded to make a 3d object
    int zValue;//keeps track of the z value

  private:
    // name of the letter, allows for characters that have
    string name;//more than single character names (like &)
    int maxX, maxY;


};
