#include "simple_ray.h"
#include "math_utils.h"
#include <iostream>
using namespace std;

void init()
{
Light light;
Camera camera;
Image image;
light.dir.x=100.0f;
light.dir.y=300.0f;
light.dir.z=0.0f;
light.int_ambi=Vector3f(1.0f,0.0f,1.0f);
light.int_diff=Vector3f(1.0f,1.0f,0.0f);
light.int_spec=Vector3f(1.0f,0.0f,1.0f);
light.coeff_ambi=Vector3f(0.4f,0.4f,0.2f);
light.coeff_diff=Vector3f(0.3f,0.4f,0.4f);
light.coeff_spec=Vector3f(0.2f,0.4f,1.0f);
camera.eyePosition=Vector3f(100.0f,0.0f,0.0f);
camera.lookAt=Vector3f(0.0f,0.0f,0.0f);
camera.upVector=Vector3f(0.0f,1.0f,0.0f);
camera.aspectRatio=1.0;
camera.FOV=60.0;
image.imageWidth=512;
image.imageHeight=512;
Plane plane;
//assign id=1 for plane for now
Vector3f pointPlane=Vector3f(10.0f,5.0f,15.0f);
double shininess_Plane=100.0;
Vector3f normalPlane=Vector3f(5.0f,3.0f,2.0f);//TODO correct normal value
plane(1,pointPlane,normalPlane,shininess);
Sphere sphere;

Vector3f center=Vector3f(5.0f,30.0f,40.0f);
double radius=40.0;
double shininess_Sphere=70.0;
sphere(2,center,radius,shininess_Sphere);

}
int main()
{
	init();
	return 0;
}