#include "simple_ray.h"
#include <math.h>
using namespace std;

Ray::Ray();
Ray::Ray(Vector3f point, Vector3f dir, double lambda){
point=point;
dir=dir;
lambda=lambda;
}
Ray::intersect(Object * obj, Vector3f * poi)
{
return 0;//
}
