#ifndef _SIMPLE_RAY_H__
#define _SIMPLE_RAY_H__

#include <vector>
#include <string>
using namespace std;
class Sphere{

//pointer to light object
public:

Vector3f center;
double radius;
double shininess;

int computeNormal(Vector3f&, Vector3f&);//input:point onsphere //output:normal vector
int computeShade(Vector3f&, Vector3f&, Light&, Vector3f&, Vector3f&);
};

class Plane{

public:

Vector3f point;
Vector3f normalToPlane;
double shininess;

int computeNormal(Vector3f&, Vector3f&);//input:point onsphere //output:normal vector
int computeShade(Vector3f&, Vector3f&, Light&, Vector3f&, Vector3f&);
};
class Camera{
public:
Vector3f eyePosition;
Vector3f lookAt;
Vector3f upVector;

double aspectRatio;
double FOV;
};

class Image{
public:
double imageWidth;
double imageHeight;
string filename;

vector<vector<Vector3f> > buffer;
void initialize();
void writeToFile();
}
#endif 

