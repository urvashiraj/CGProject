#include "simple_ray.h"

#include <iostream>
using namespace std;
Vector3f centerSphere;
Vector3f  pointPlane;
double shininess_Plane,shininess_Sphere,radiusSphere;
Vector3f normalPlane;
Light light;
Camera camera;
Image image;
void init()
{

light.dir.x=100.0f;
light.dir.y=300.0f;
light.dir.z=0.0f;
light.int_ambi=Color(1.0f,0.0f,1.0f);
light.int_diff=Color(1.0f,1.0f,0.0f);
light.int_spec=Color(1.0f,0.0f,1.0f);
light.coeff_ambi=Color(0.4f,0.4f,0.2f);
light.coeff_diff=Color(0.3f,0.4f,0.4f);
light.coeff_spec=Color(0.2f,0.4f,1.0f);

camera.eyePosition=(100.0f,0.0f,0.0f);
camera.lookAt=Vector3f(0.0f,0.0f,0.0f);
camera.upVector=Vector3f(0.0f,1.0f,0.0f);
camera.aspectRatio=1.0;
camera.FOV=60.0;

image.imageWidth=512;
image.imageHeight=512;

pointPlane=Vector3f(10.0f,5.0f,15.0f);

normalPlane=Vector3f(5.0f,3.0f,2.0f);//TODO correct normal value

shininess_Plane=100.0;
centerSphere=Vector3f(5.0f,30.0f,40.0f);
shininess_Sphere=70.0;
radiusSphere=40.0;
}
int main()
{
	init();
	Sphere sphere(2,centerSphere,radiusSphere,shininess_Sphere);
	Plane plane(1,&pointPlane,&normalPlane,shininess_Plane);
cout<<sphere.center.x;
	return 0;
}
