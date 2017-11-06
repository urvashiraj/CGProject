
#include "simple_ray.h"

#include <iostream>

void init()
{
  //level of reflection
 Scene::level=0;
  //Background
  Scene::bgcolor = Color(.39,.78,1.0);
  //Scene::bgcolor = Color(0.0);

  //Light
  Scene::light.dir = Vector3f(-50.0,0.0,70.0).Normalize();
  Scene::light.int_ambi=Color(1.0);
  Scene::light.int_diff=Color(1.0);
  Scene::light.int_spec=Color(1.0);
  Scene::light.coeff_ambi=Color(0.1);
  Scene::light.coeff_diff=Color(0.7);
  Scene::light.coeff_spec=Color(0.6);
//  Scene::light.brightness=1.0; //initialize brightness of light

  //Camera
  Scene::camera.eye=Vector3f(70.0f,0.0f,0.0f);
  Scene::camera.look=Vector3f(0.0);
  Scene::camera.up=Vector3f(0.0f,1.0f,0.0f);
  Scene::camera.aspect=1.0;
  Scene::camera.fov=40.0;

  //Image
  Scene::image = Image(512,512,"test.png");

  //Objects
  Scene::objects.push_back(
    new Sphere(1,Color(1.0,0.0,0.0),70.0,0.8,Vector3f(0.0,0.0,10.0),30.0)
  );

  Scene::objects.push_back(
    new Plane(
      2,Color(1.0,0.0,1.0),60.0,0.6,Vector3f(0.0,-50.0,0.0),Vector3f(0.0,1.0,0.0))
    );

  Scene::objects.push_back(
    new Triangle(
      3,Color(0.0,0.0,0.0),70.0,0.8,Vector3f(5,-50.0,69.0),Vector3f(5.0,-27.0,20.0),Vector3f(5.0,-22.0,47.0),Vector3f(0.0,-8.0,10.0)
    )
	);
  Scene::objects.push_back(
    new Sphere(1,Color(0.4,1.0,0.0),70.0,0.8,Vector3f(25.0,0.0,-10.0),5.0)
  );
  
Scene::objects.push_back(
    new Sphere(1,Color(0.0,0.0,1.0),70.0,0.8,Vector3f(5.0,-5.0,-5.0),25.0)
  );

/*Scene::objects.push_back(
    new Cone(5,Color(1.0,1.0,0.6),70.0,0.8,Vector3f(0.0,0.0,-15.0),Vector3f(0.0,1.0,0.0),1.0,35.0)
  );*/
//0 0 0 0 1 0 1 1 0.2 0.8 0.8 0



  //pointPlane=Vector3f(10.0f,5.0f,15.0f);
  //normalPlane=Vector3f(5.0f,3.0f,2.0f);//TODO correct normal value
  //shininess_Plane=100.0;
  //centerSphere=Vector3f(5.0f,30.0f,40.0f);
  //shininess_Sphere=70.0;
  //radiusSphere=40.0;

  return;

}

void finalize()
{
  Scene::image.png.close();
  //TBD deallocate objects in scene
  return;
}

int main (int argc, char const* argv[])
{
  Ray ray;
  Color raycolor;
  bool collide;

  Vector3f sx = Vector3f(0.0,0.0,0.0);
  Vector3f sy = Vector3f(0.0,0.0,0.0);
  Vector3f firstray = Vector3f(0.0,0.0,0.0);

  //Initialize scene
	init();

  //Generate first ray
  Scene::camera.getFirstRay(Scene::image,sx,sy,firstray);
  int supersample_factor=6;
 double opacity=(double)1.0/(supersample_factor*supersample_factor);
  //Loop through image
  for (int y = 0; y < Scene::image.height; y += 1)
  {
    for (int x = 0; x < Scene::image.width; x += 1)
    {
      //A new ray from the camera
	double r=0.0,g=0.0,b=0.0;
		
		for(int v=0;v<supersample_factor-1;v++)//supersample_factor=2;
		{
		 for(int u=0;u<supersample_factor-1;u++)
		  {
		  double fx=double(x)+double(u)/double(supersample_factor);
		  double fy=double(y)+double(v)/double(supersample_factor);
		   ray = Ray(
				Scene::camera.eye,
				(firstray + (sx*fx) - (sy*fy)).Normalize()
			      );
		  
			 collide = false; 
		      ray.intersect(-1,collide,raycolor);
		      if(collide)
			{
			//r+=raycolor.r;g+=raycolor.g;b+=raycolor.b;
			//raycolor.r=r;raycolor.g=g;raycolor.b=b;
			// Scene::image.updatePixel(x,Scene::image.height - y,raycolor);
			Scene::image.updatePixel(x,Scene::image.height - y,opacity,raycolor);	
			}
		       
		      else
			{
			//r=r+Scene::bgcolor.r;g=g+Scene::bgcolor.g;b=b+Scene::bgcolor.b;
			Scene::image.updatePixel(x,Scene::image.height - y,opacity,Scene::bgcolor);
			//cout<<Scene::bgcolor.r<<" "<<Scene::bgcolor.g<<" "<<Scene::bgcolor.b<<endl;
			//Scene::bgcolor.r=r;Scene::bgcolor.g=g;Scene::bgcolor.b=b;	
		
			}
			

		   }		
		
		}
     	
		   

    
        
    }
  }

  //Write image to file
  Scene::image.writeToFile();

  //Finalize scene
  finalize();

	return 0;
}
