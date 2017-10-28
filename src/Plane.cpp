#include "simple_ray.h"
#include <math.h>
using namespace std;

Plane::plane();
Plane::plane(1,pointPlane,normalPlane,shininess_Plane) : Object(1,Plane){
point=pointPlane;
normalToPlane=normalPlane.Normalize();
shininess=shininess_Plane;
}
Plane::computeNormal(Vector3f point,Vector3f normalPlane)
{
//no chane in normal of plane
return 0;
}
Plane::computeShade(Vector3f point,Vector3f normalPlan,Light light,Camera camera, Vector3f rayDir,Color colorPlan)
{
Color ambient_Product=Color(*(light.coeff_ambi.r)*(*(light.int_ambi.r)),*(light.coeff_ambi.g)*(*(light.int_ambi.g)),*(light.coeff_ambi.b)*(*(light.int_ambi.b)));

Color diffuse_Product=Color(*(light.coeff_diff.r)*(*(light.int_diff.r)),*(light.coeff_diff.g)*(*(light.int_diff.g)),*(light.coeff_diff.b)*(*(light.int_diff.b)));

Color specular_Product=Color(*(light.coeff_spec.r)*(*(light.int_spec.r)),*(light.coeff_spec.g)*(*(light.int_spec.g)),*(light.coeff_spec.b)*(*(light.int_spec.b)));



Vector3f L=Vector3f(*(light.dir.x)-*(point.x),*(light.dir.y)-*(point.y),*(light.dir.z)-*(point.z));//light direction

Vector3f V=Vector3f(*(camera.eyePosition.x)-*(point.x),*(camera.eyePosition.y)-*(point.y),*(camera.eyePosition.z)-*(point.z));//view direction

L.Normalize();
V.Normalize();
float IdotN=L.x*(*normalPlan.x)+L.y*(*normalPlan.y)+L.z*(*normalPlan.z);//dot product betwen incident light and normal

IdotN=min(max(0,IdotN),1);

Vector3f diffuse=Vector3f(IdotN*diffuse_Product.r,IdotN*diffuse_Product.g,IdotN*diffuse_Product.b);

Vector3f ambient=Vector3f(ambient_Product.x,ambient_Product.y,ambient_Product.z);

//already direction of reflection
rayDir.Normalize();
float VdotR=rayDir.x*V.x+rayDir.y*V.y+rayDir.z*V.z;

VdotR=pow(VdotR,shininess);
Vector3f specular=Vector3f(VdotR*specular_Product.r,VdotR*specular_Product.g,VdotR*specular_Product.b);
*colorPlan=Color(diffuse.x+ambient.x+specular.x,diffuse.y+ambient.y+specular.y,diffuse.z+ambient.z+specular.z);

return 0;
}
