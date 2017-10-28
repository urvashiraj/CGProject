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
Plane::computeShade(Vector3f point,Vector3f normalPlan,Light light, Vector3f rayDir,Color colorPlane)
{
Color ambient_Product=Color(*(light.coeff_ambi.r)*(*(light.int_ambi.r)),*(light.coeff_ambi.g)*(*(light.int_ambi.g)),*(light.coeff_ambi.b)*(*(light.int_ambi.b)));

Color diffuse_Product=Color(*(light.coeff_diff.r)*(*(light.int_diff.r)),*(light.coeff_diff.g)*(*(light.int_diff.g)),*(light.coeff_diff.b)*(*(light.int_diff.b)));

Color specular_Product=Color(*(light.coeff_spec.r)*(*(light.int_spec.r)),*(light.coeff_spec.g)*(*(light.int_spec.g)),*(light.coeff_spec.b)*(*(light.int_spec.b)));



Vector3f L=Vector3f(*(rayDir.x)-*(point.x),*(rayDir.y)-*(point.y),*(rayDir.z)-*(point.z));//ray direction
Vector3f V=Vector3f(*(light.dir.x)-*(point.x),*(light.dir.y)-*(point.y),*(light.dir.z)-*(point.z));//light direction
L.Normalize();
V.Normalize();
float LdotN=L.x*(*normalPlan.x)+L.y*(*normalPlan.y)+L.z*(*normalPlan.z);//dot product betwen incident ray and normal

LdotN=min(max(0,LdotN),1);

Vector3f diffuse=Vector3f(LdotN*diffuse_Product.r,LdotN*diffuse_Product.g,LdotN*diffuse_Product.b);

Vector3f ambient=Vector3f(ambient_Product.x,ambient_Product.y,ambient_Product.z);//ambient contribution

//calculate reflection ray :calculated from intersection ray and normal
float k=-2*((*(rayDir.x))*(*(normalPlan.x))+(*(rayDir.y))*(*(normalPlan.y))+(*(rayDir.z))*(*(normalPlan.z)));
Vector3f reflectionRay;
reflectionRay.x=k*(*normalPlan.x)+(*rayDir.x);
reflectionRay.y=k*(*normalPlan.y)+(*rayDir.y);
reflectionRay.z=k*(*normalPlan.z)+(*rayDir.z);
reflectionRay.Normalize();
//already direction of reflection

float VdotR=reflectionRay.x*V.x+reflectionRay.y*V.y+reflectionRay.z*V.z;
Vector3f specular=Vector3f(0.0f,0.0f,0.0f);
if(VdotR>0)
{
VdotR=pow(VdotR,shininess);
specular=Vector3f(VdotR*specular_Product.r,VdotR*specular_Product.g,VdotR*specular_Product.b);
}

*colorPlane=Color(diffuse.x+ambient.x+specular.x,diffuse.y+ambient.y+specular.y,diffuse.z+ambient.z+specular.z);

return 0;
}
