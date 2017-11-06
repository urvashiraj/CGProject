#include "simple_ray.h"

//
//  Scene
//

//Static object intialization
vector<Object*> Scene::objects;
Light Scene::light;
Camera Scene::camera;
Image Scene::image;
Color Scene::bgcolor;
int Scene::level = 0;
//=============================================================================

//
//  Image
//

int Image::updatePixel(int x, int y, double opacity, const Color &c)
{
  png.plot_blend(x,y,opacity,c.r,c.g,c.b);
  return 0;
}

int Image::writeToFile()
{
  png.write_png();
  return 0;
}


//=============================================================================

//
//  Cone
//
/*
int Cone::computeRayIntersection(const Ray& ray, double &lambda)
{
	/*Vector <double> points;
	double cos2a = cos(alpha)*cos(alpha);
	double sin2a = 1 - cos2a;
	Vector3f pa = center + upVector * height;
	Vector3f va = upVector * -1;
	Vector3f deltaP = (rayOrigin - pa);

	double c1 = ray.dir.Dot(va);
	Vector3f c2 = va * c1;
	double c3 = deltaP.Dot(va);
	Vector3f c4 = va * c3;

	double a = cos2a * (ray.dir - c2).length() - sin2a * c1 * c1;
	double b = 2* cos2a * (ray.dir - c2).Dot(deltaP - c4) - 2 * sin2a * (c1 * c3);
	double c = cos2a * (deltaP - c4).length() - sin2a * (c3 * c3);


	double discriminant = b*b - 4*a*c;
	if (discriminant < 0) return 0;
	else {
		discriminant = sqrt(discriminant);
		double t1 = ((-1 * b) + discriminant) / (2 * a);
		double t2 = ((-1 * b) - discriminant) / (2 * a);
		if(t1>=0){
			if(upVector.dot((ray.point - center) + ray.dir * t1)>0 && upVector.dot((ray.point - pa) + ray.dir * t1)<0)
				points.push_back(t1);
		}
		if(t2>=0)
			if(upVector.dot((ray.point - center) + ray.dir * t2)>0 && upVector.dot((ray.point - pa) + ray.dir * t2)<0)
				points.push_back(t2);
	}

	float denom = ray.dir.Dot(upVector);
	if (denom > 1e-6) {
		Vec3 co = center - rayOrigin;
		double t3 = co.dot(upVector) / denom;
		if(t3 > 0 && (rayDirection * t3 - co).length2() <= radius*radius)
			points.push_back(t3);
	}

	double minT = INFINITY;
	bool flag = false;
	for(int i=0;i<points.size();i++){
		if(minT > points[i] && points[i]>=0) {
			minT = points[i];
			flag = true;
		}
	}
	if(flag)
		lambda=minT/Ird;
	*/
//cout<<"lambda"<<dist<<endl;
/*return 0;
}


int Cone::computeNormal(const Vector3f& point, Vector3f& normal)
{
radius=height*tan(alpha);
Vector3f V;
V.x=point.x-center.x;V.y=point.y-center.y;V.z==point.z-center.z;
V.Normalize();

normal.x=(V.x*height)/radius;normal.y=(V.y*height)/radius;normal.z=(V.z*height)/radius;
normal.Print();
  return 0;
}

int Cone::computeShade(
  const Light &light,
  const Vector3f &raydir,
  const Vector3f &point,  
  const Vector3f &normal,
  Color &shade,
  double &brightness
)
{
  return Object::computeShade(light,raydir,point,normal,shade,brightness);
}
*/
//=============================================================================

//
//  Box
//
/*
int Box::computeRayIntersection(const Ray& ray, double &lambda)
{

return 0;
}


int Box::computeNormal(const Vector3f& point, Vector3f& normal)
{

normal=Vector3f(0.0);
switch(sidehit)
{
case 0: normal.x=1.0;
	break;
case 1: normal.x=-1.0;
	break;
case 2: normal.y=1.0;
	break;
case 3: normal.y=-1.0;
	break;
case 4: normal.z=1.0;
	break;
case 5: normal.z=-1.0;
	break;

}
  return 0;
}

int Box::computeShade(
  const Light &light,
  const Vector3f &raydir,
  const Vector3f &point,  
  const Vector3f &normal,
  Color &shade,
  double &brightness
)
{
  return Object::computeShade(light,raydir,point,normal,shade,brightness);
}
*/

//=============================================================================

//
//  Triangle
//

int Triangle::computeRayIntersection(const Ray& ray, double &lambda)
{
//check if ray and plane parallel
double NdotRayDir=normal.Dot(ray.dir);
//cout<<NdotRayDir;
if(NdotRayDir==0.0)
return 0;
double D=normal.Dot(vertex1);//distance of plan from origin
//cout<<D;
double dist=-((normal.Dot(ray.point)+D)/NdotRayDir);
//cout<<dist;
if(dist<0.0)
return 0;
Vector3f Point;//=Vector3f(ray.point+ray.dir*dist);
Point.x=ray.point.x+ray.dir.x*dist;
Point.y=ray.point.y+ray.dir.y*dist;
Point.z=ray.point.z+ray.dir.z*dist;

Vector3f normPlane;//vector perpendicular to normal plane
Vector3f edge1=Vector3f(vertex2.x-vertex1.x,vertex2.y-vertex1.y,vertex2.z-vertex1.z);
Vector3f edgeConst1=Vector3f(Point.x-vertex1.x,Point.y-vertex1.y,Point.z-vertex1.z);
normPlane=edge1.Cross(edgeConst1);
if(normal.Dot(normPlane)<0)return 0;

Vector3f edge2=Vector3f(vertex3.x-vertex2.x,vertex3.y-vertex2.y,vertex3.z-vertex2.z);
Vector3f edgeConst2=Vector3f(Point.x-vertex2.x,Point.y-vertex2.y,Point.z-vertex2.z);
normPlane=edge2.Cross(edgeConst2);
if(normal.Dot(normPlane)<0)return 0;

Vector3f edge3=Vector3f(vertex1.x-vertex3.x,vertex1.y-vertex3.y,vertex1.z-vertex3.z);
Vector3f edgeConst3=Vector3f(Point.x-vertex3.x,Point.y-vertex3.y,Point.z-vertex3.z);
normPlane=edge3.Cross(edgeConst3);
if(normal.Dot(normPlane)<0)return 0;

lambda=dist;
//cout<<"lambda"<<dist<<endl;
return 0;
}


int Triangle::computeNormal(const Vector3f& point, Vector3f& normal)
{

  //cout <<"sphere compute normal"<<endl;
  Vector3f edge1=Vector3f(vertex2.x-vertex1.x,vertex2.y-vertex1.y,vertex2.z-vertex1.z);
  Vector3f edge2=Vector3f(vertex3.x-vertex1.x,vertex3.y-vertex1.y,vertex3.z-vertex1.z);
  normal= edge1.Cross(edge2);
  normal.Normalize();
	//cout<<"triangle-normal"<<*normal<<endl;
  //point.Print();
  //cout << point.length() << " ";
  //normal.Print();
  //center.Print();
  //cout <<endl;
  return 0;
}

int Triangle::computeShade(
  const Light &light,
  const Vector3f &raydir,
  const Vector3f &point,  
  const Vector3f &normal,
  Color &shade,
  double &brightness,
  double &reflection
)
{
  return Object::computeShade(light,raydir,point,normal,shade,brightness,reflection);
}

//=============================================================================
//
//  Sphere
//

int Sphere::computeRayIntersection(const Ray& ray, double &lambda)
{
  //cout << "SphereRayIntersection" <<endl;

  Vector3f EO = center - ray.point;
  double v = ray.dir.Dot(EO);
  double d = (radius*radius) - (EO.Dot(EO) - v*v);

  if(d > 0.0)
    lambda = v - sqrt(d);

  //ray.point.Print();
  //ray.dir.Print();
  //cout << lambda <<endl;

  return 0;
}

int Sphere::computeNormal(const Vector3f& point, Vector3f& normal)
{

  //cout <<"sphere compute normal"<<endl;
  normal.x = point.x - center.x;
  normal.y = point.y - center.y;
  normal.z = point.z - center.z;
  
  normal.Normalize();
	
  //point.Print();
  //cout << point.length() << " ";
 // normal.Print();
  //center.Print();
  //cout <<endl;
  return 0;
}

int Sphere::computeShade(
  const Light &light,
  const Vector3f &raydir,
  const Vector3f &point,  
  const Vector3f &normal,
  Color &shade,
  double &brightness,
  double &reflection
)
{
  return Object::computeShade(light,raydir,point,normal,shade,brightness,reflection);
}

//=============================================================================

//
//  Plane
//

int Plane::computeRayIntersection(const Ray& ray, double &lambda)
{
  //cout << "PlaneRayIntersection" <<endl;
  double denom =  normal.Dot(ray.dir);

  if(denom == 0.0)
    return 0;
  
  Vector3f num = Vector3f(0.0);
  num.x = point.x - ray.point.x;
  num.y = point.y - ray.point.y;
  num.z = point.z - ray.point.z;

  lambda = normal.Dot(num) / denom;
  lambda = (lambda > 0.0)? lambda : FAR_AWAY;
  
  return 0;
}

int Plane::computeNormal(const Vector3f& point, Vector3f& normal)
{
  return 0;
}

int Plane::computeShade(
  const Light &light,
  const Vector3f &raydir,
  const Vector3f &point,  
  const Vector3f &dummy,
  Color &shade,
  double &brightness,
  double &reflection
)
{
  //Call object shader directly using built in normal

  //normal.Print();
  //cout<<endl;
  return Object::computeShade(light,raydir,point,normal,shade,brightness,reflection);
}

//=============================================================================

//
//  Object
//

int Object::computeRayIntersection(const Ray& ray, double &lambda)
{
  //cout << "ObjectRayIntersection" <<endl;
  return 0;
}

int Object::computeNormal(const Vector3f& point, Vector3f& normal)
{
  //cout <<"Object Normal"<<endl;
  return 0;
}

int Object::computeShade(
  const Light &light,
  const Vector3f &raydir,
  const Vector3f &point,
  const Vector3f &normal, 
  
  Color &shade,
  double &brightness,
  double &reflection
)
{

  double diffuse = 0.0;
  double specular = 0.0;
//Ambient 
shade.r=light.coeff_ambi.r*light.int_ambi.r;shade.g=light.coeff_ambi.g*light.int_ambi.g;shade.b=light.coeff_ambi.b*light.int_ambi.b;
//diffuse
 diffuse = (light.dir * -1.0).Dot(normal);
if(diffuse > 0.0) {
	    diffuse*=brightness;
	    shade.r+=light.coeff_diff.r*light.int_diff.r*diffuse;
	    shade.g+=light.coeff_diff.g*light.int_diff.g*diffuse;
	    shade.b+=light.coeff_diff.b*light.int_diff.b*diffuse;
	     Vector3f half = (raydir*-1.0) + (light.dir*-1.0);
	    half.Normalize();
	    specular = pow(half.Dot(normal),shininess);
		if(specular>0.0){
				specular*=brightness;
				shade.r+=light.coeff_spec.r*light.int_spec.r*specular;
				shade.g+=light.coeff_spec.g*light.int_spec.g*specular;
				shade.b+=light.coeff_spec.b*light.int_spec.b*specular;
				}
	    		

		  }

/*--------------------reflection------------------*/
double k=reflectivity;
if((k>0)&&(Scene::level<MAXLEVEL))
{
	Scene::level++;
	if(reflection>0)
	{
	shade.r+=color.r*k;
	shade.g+=color.g*k;
	shade.b+=color.b*k;
	}
	else
	{
	shade.r+=Scene::bgcolor.r*k;
	shade.g+=Scene::bgcolor.g*k;
	shade.b+=Scene::bgcolor.b*k;
	}
Scene::level--;
}

  return 0;
}

//=============================================================================

//
//  Camera
//

int Camera::getFirstRay(
  const Image& img, 
  Vector3f& sx, 
  Vector3f& sy, 
  Vector3f& firstray
)
{
  Vector3f gaze = Vector3f(0.0,0.0,0.0);
  double dist,mag;

  gaze = look - eye;
  dist = gaze.length();
  gaze.Normalize();

  sx = gaze.Cross(up);
  sy = sx.Cross(gaze);

  dist *= 2.0; 
  mag = dist * tan(ToRadian(fov)) / img.width;
  sx *= mag; 
  mag = dist * tan(ToRadian(fov)) / img.height;
  sy *= mag;

  firstray = look - eye;
  firstray += (sy*(img.height/2.0)) - (sx*(img.width/2.0));
  
  return 0;
}

//=============================================================================

//
//  Ray
//

int Ray::intersect(
  int srcid,
  bool &intersects,
  Color &shade

)
{
  Object *object = NULL;
  double distance = FAR_AWAY;
  double lambda = FAR_AWAY;

  Vector3f normal = Vector3f(0.0);
int count=0;
  vector<Object*>::iterator it = Scene::objects.begin();
  for (;it != Scene::objects.end(); ++it)
  {
	count++;
    if((*it)->id == srcid)
      continue;
//cout<<count<<endl;
    //Check object intersection
    distance = FAR_AWAY;

	
    (*it)->computeRayIntersection(*this,distance);
    /*switch((*it)->type)
    {
      case PLANE: 
        (dynamic_cast<Plane*>(*it))->computeRayIntersection(*this,distance); 
      break;
      case SPHERE: 
        (dynamic_cast<Sphere*>(*it))->computeRayIntersection(*this,distance); 
      break;
    }*/

   
    if(distance < lambda){
      lambda = distance;
      object = (*it);
    } 
 
  }

  if(object == NULL)
    return 0;
  
  intersects = true;

  Vector3f intersect_point = point+(dir*lambda);

Vector3f shadow=Vector3f(Scene::light.dir.x-point.x,Scene::light.dir.y-point.y,Scene::light.dir.z-point.z);
double shadowdist=shadow.length();
;
double brightness;

if(shadowdist<lambda)
brightness=0.0;//if shadow is formed
else brightness=1.0;
  object->computeNormal(intersect_point,normal);
double reflection=0.0;//for multiple reflection
if(intersects)
reflection=lambda;
	//cout<<normal;
  object->computeShade(
    Scene::light,dir,intersect_point,normal,shade,brightness,reflection
  );

  return 0;
}

