#include "simple_ray.h"

#include <iostream>
using namespace std;
Vector3f centerSphere;
Vector3f * pointPlanePtr;
double shininess_Plane,shininess_Sphere,radiusSphere;
Vector3f * normalPlanePtr;
Light * lightPtr;
Camera * cameraPtr;
Image * imagePtr;
void init()
{
Light light;
light.dir.x=100.0f;
light.dir.y=300.0f;
light.dir.z=0.0f;
light.int_ambi=Color(1.0f,0.0f,1.0f);
light.int_diff=Color(1.0f,1.0f,0.0f);
light.int_spec=Color(1.0f,0.0f,1.0f);
light.coeff_ambi=Color(0.4f,0.4f,0.2f);
light.coeff_diff=Color(0.3f,0.4f,0.4f);
light.coeff_spec=Color(0.2f,0.4f,1.0f);
lightPtr=&light;
Camera camera;
camera.eyePosition=(100.0f,0.0f,0.0f);
camera.lookAt=Vector3f(0.0f,0.0f,0.0f);
camera.upVector=Vector3f(0.0f,1.0f,0.0f);
camera.aspectRatio=1.0;
camera.FOV=60.0;
cameraPtr=&camera;
Image image;
image.imageWidth=512;
image.imageHeight=512;
imagePtr=&image;
Vector3f pointPlane=Vector3f(10.0f,5.0f,15.0f);
pointPlanePtr=&pointPlane;
Vector3f normalPlane=Vector3f(5.0f,3.0f,2.0f);//TODO correct normal value
normalPlanePtr=&normalPlane;
shininess_Plane=100.0;
centerSphere=Vector3f(5.0f,30.0f,40.0f);
shininess_Sphere=70.0;
radiusSphere=40.0;
}
int main()
{
	init();
	Sphere sphere(2,centerSphere,radiusSphere,shininess_Sphere);
	Plane plane(1,*pointPlanePtr,*normalPlanePtr,shininess_Plane);
cout<<sphere.center.x;
	return 0;
}
