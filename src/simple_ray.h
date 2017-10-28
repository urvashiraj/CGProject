#ifndef _SIMPLE_RAY_H__
#define _SIMPLE_RAY_H__

#include "math_utils.h"

#include <vector>
#include <string>
#include <math.h>

using namespace std;

typedef enum{
  PLANE = 1,
  SPHERE = 2
}OBJ_TYPE;

class Object{

  public:
  int id;
  OBJ_TYPE type;

  Object(){}
  Object(int _id, OBJ_TYPE _type) {
    id = _id; 
    type = _type;
  }

};

class Image{
public:
double imageWidth;
double imageHeight;
string filename;

vector<vector<Vector3f> > buffer;
void initialize();
void writeToFile();
};

class Camera{

  public:
  Vector3f eyePosition;
  Vector3f lookAt;
  Vector3f upVector;

  double aspectRatio;
  double FOV;
  
  Camera(){}

  Camera(Vector3f _e, Vector3f _l, Vector3f _u, double _fov, double _ar ) 
  {
    eyePosition = _e;
    lookAt = _l;
    upVector = _u;
    aspectRatio = _ar;
    FOV = _fov;  
  }

  int getFirstRay(Image&, Vector3f&, Vector3f&, Vector3f&);
};


class Ray {

  public:
  Vector3f point;
  Vector3f dir;
  double lambda;
	
  Ray(){}
  Ray(Vector3f _c, Vector3f _d, double _l){
	point=_c;
	dir=_d;
	lambda=_l;
	}
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

class Sphere : public Object{
//pointer to light object
public:

Vector3f center;
double radius;
double shininess;

  Sphere(){}
  Sphere(int _id, Vector3f _c, double _r, double _s) : Object(_id,SPHERE) {
    center = _c;
    radius = _r;
    shininess = _s;
  }

int computeNormal(Vector3f&, Vector3f&);//input:point onsphere //output:normal vector
int computeShade(Vector3f&, Vector3f&, Light&, Camera&, Vector3f&, Vector3f&);
};

class Plane : public Object {

public:

Vector3f point;
Vector3f normalToPlane;
double shininess;

  Plane(){}
  Plane(int _id, Vector3f _p, Vector3f _n, double _s): Object(_id,PLANE){
    point = _p;
   normalToPlane = _n;
    shininess = _s;    
  }

int computeNormal(Vector3f&, Vector3f&);//input:point onsphere //output:normal vector
int computeShade(Vector3f&, Vector3f&, Light&, Camera&, Vector3f&, Vector3f&);
};


class Scene {

  public:
  //static vector<Object*> sceneObjects;
  //static Light light;
  //static Camera camera;
  //static Image image;
};

//vector<Object*> Scene::sceneObjects;
//Light Scene::light;


#endif /* __SIMPLE_RAY_H__ */




