#ifndef _SIMPLE_RAY_H__
#define _SIMPLE_RAY_H__

#include <vector>
#include <string>
#include <cmath>

#include "pngwriter.h"
#include "math_utils.h"

#define FAR_AWAY  1e10
#define MAXLEVEL 10

using namespace std;

typedef enum{
  PLANE = 1,
  SPHERE = 2,
  TRIANGLE=3,
  BOX=4,
  CONE=5
}OBJ_TYPE;

class Image{

  public:
  double width;
  double height;
  string filename;
  pngwriter png;

  Image(){}
  Image(double _w, double _h, string _name) {
    width = _w;
    height = _h;
    filename = _name;
    png = pngwriter((int)_w,(int)_h,0,_name.c_str());
  }

  int updatePixel(int, int, double, const Color&);
  int writeToFile();
};

class Camera{

  public:
  Vector3f eye;
  Vector3f look;
  Vector3f up;

  double aspect;
  double fov;
  
  Camera(){}
  Camera(Vector3f _e, Vector3f _l, Vector3f _u, double _fov, double _ar ) 
  {
    eye = _e;
    look = _l;
    up = _u;
    aspect = _ar;
    fov = _fov;  
  }

  int getFirstRay(const Image&, Vector3f&, Vector3f&, Vector3f&);
};


class Ray {

  public:
  Vector3f point;
  Vector3f dir;
	
  Ray(){}
  Ray(Vector3f _c, Vector3f _d){
	  point=_c;
	  dir=_d;
	}

  int intersect(int, bool&, Color&);  
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

class Object{

  public:
  int id;
  OBJ_TYPE type;

  Color color;
  double shininess;
  double reflectivity;

  Object(){}
  Object(int _id, OBJ_TYPE _type, Color _c,double _s,double _r) {
    id = _id; 
    type = _type;
    color = _c;
    shininess = _s;
    reflectivity= _r;
  }

  virtual int computeRayIntersection(const Ray& ray, double &lambda);
  virtual int computeNormal(const Vector3f&, Vector3f&);
  virtual int computeShade(
    const Light&, const Vector3f&, const Vector3f&, 
    const Vector3f&, Color&, double&, double&
  );

};

class Sphere : public Object{

  public:
  Vector3f center;
  double radius;

  Sphere(){}
  Sphere(int _id, Color _co, double _s,double _re, Vector3f _ce, double _r) : Object(_id,SPHERE,_co,_s,_re) {
    center = _ce;
    radius = _r;
  }

  int computeRayIntersection(const Ray& ray, double &lambda);
  int computeNormal(const Vector3f&, Vector3f&);
  int computeShade(
    const Light&, const Vector3f&, const Vector3f&, 
    const Vector3f&, Color&, double&, double&
  );

};

class Plane : public Object {

  public:

  Vector3f point;
  Vector3f normal;

  Plane(){}
  Plane(int _id, Color _c, double _s,double _r, Vector3f _p, Vector3f _n): Object(_id,PLANE,_c,_s,_r){
    point = _p;
    normal = _n.Normalize();
  }

  int computeRayIntersection(const Ray& ray, double &lambda);
  int computeNormal(const Vector3f&, Vector3f&);
  int computeShade(
    const Light&, const Vector3f&, const Vector3f&, 
    const Vector3f&, Color&, double&, double&
  );


};


class Triangle : public Object {

  public:

  Vector3f vertex1;Vector3f vertex2;Vector3f vertex3;
  Vector3f normal;Vector3f point;
 // double planeConstant;//,edgeConstant1,edgeContant2,edgeConstant3;

  Triangle(){}
  Triangle(int _id, Color _c, double _s,double _r, Vector3f _p1, Vector3f _p2, Vector3f _p3, Vector3f _p4): Object(_id,TRIANGLE,_c,_s,_r){
   vertex1=_p1;
   vertex2=_p2;
   vertex3=_p3;
   point=_p4;
  int res= computeNormal(point,normal);
  }

  int computeRayIntersection(const Ray& ray, double &lambda);
  int computeNormal(const Vector3f&, Vector3f&);
  
  int computeShade(
    const Light&, const Vector3f&, const Vector3f&, 
    const Vector3f&, Color&, double&, double&
  );


};


class Box : public Object {

  public:

  Vector3f center;
 	double length,width,height;
Vector3f normal;
int sidehit;//for normal computation
 // double planeConstant;//,edgeConstant1,edgeContant2,edgeConstant3;

  Box(){}
  Box(int _id, Color _co, double _s,double _r, Vector3f _c, double _l, double _w, double _h): Object(_id,BOX,_co,_s,_r){
   center=_c;
   length=_l;
   width=_w;
   height=_h;
  }

  int computeRayIntersection(const Ray& ray, double &lambda);
  int computeNormal(const Vector3f&, Vector3f&);
  
  int computeShade(
    const Light&, const Vector3f&, const Vector3f&, 
    const Vector3f&, Color&, double&
  );


};

class Cone : public Object {

public:

	double radius, height, alpha;
	Vector3f upVector;
	Vector3f center;
	Cone(){}
	
	Cone(int _id, Color _co, double _s,double _r, Vector3f _c, Vector3f _up,double _a, double _h): Object(_id,BOX,_co,_s,_r){
	center=_c;
	upVector=_up;
	alpha=_a;
	height=_h;
  }

  int computeRayIntersection(const Ray& ray, double &lambda);
  int computeNormal(const Vector3f&, Vector3f&);
  
  int computeShade(
    const Light&, const Vector3f&, const Vector3f&, 
    const Vector3f&, Color&, double&
  );

};

class Scene {

  public:
  static vector<Object*> objects;
  
  static Color bgcolor;
  static Light light;
  static Camera camera;
  static Image image;
};

#endif /* __SIMPLE_RAY_H__ */

