#ifndef _SIMPLE_RAY_H__
#define _SIMPLE_RAY_H__

#include <vector>
#include <string>
using namespace std;
typedef enum{
  PLANE = 0,
  SPHERE = 1
}OBJ_TYPE;

class Object{

  int id;
  OBJ_TYPE type;

};


class Ray {

  public:
  Vector3f point;
  Vector3f dir;
  double lambda;

  int intersect(Object&, Vector3f&);  
};

class Light {

  public:
  Vector3f dir;
  Color color;

  Color coeff_ambi;
  Color coeff_diff;
  Color coeff_spec;

  Color int_ambi;
  Color int_diff;
  Color int_spec;
 
};

class Scene {

  public:
  static list<Object> sceneObjects;
  static Light light;
  //static Camera camera;
  //static Image image;

};

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
#endif /* __SIMPLE_RAY_H__ */

