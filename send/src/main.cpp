
#include "simple_ray.h"

#include <ctime>
#include <iostream>

#include <omp.h>
#include <sys/time.h>

void init()
{
  //level of reflection
 Scene::level=0;
  //Background
  Scene::bgcolor = Color(.39,.78,1.0);
  //Scene::bgcolor = Color(0.0);

  //Light
  Scene::light.dir = Vector3f(10.0,40.0,-70.0).Normalize();
  Scene::light.pos=Vector3f(-100.0,0.0,30.0);
  Scene::light.int_ambi=Color(1.0);
  Scene::light.int_diff=Color(1.0);
  Scene::light.int_spec=Color(1.0);
  Scene::light.coeff_ambi=Color(0.1);
  Scene::light.coeff_diff=Color(0.4);
  Scene::light.coeff_spec=Color(0.8);
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
    new Sphere(1,Color(0.0,1.0,0.0),70.0,0.8,0.6,Vector3f(0.0,5.0,10.0),20.0)
  );

  Scene::objects.push_back(
    new Plane(
      2,Color(1.0,1.0,1.0),60.0,0.3,0.6,Vector3f(0.0,-50.0,0.0),Vector3f(0.0,1.0,0.0))
    );

 Scene::objects.push_back(
    new Triangle(
      3,Color(1.0,0.0,0.0),70.0,0.8,0.6,Vector3f(5,-50.0,69.0),Vector3f(5.0,-27.0,20.0),Vector3f(5.0,-22.0,47.0),Vector3f(0.0,-8.0,10.0)
    )
	);
  Scene::objects.push_back(
    new Sphere(1,Color(0.0,1.0,0.0),70.0,0.8,0.6,Vector3f(25.0,0.0,-20.0),5.0)
  );

Scene::objects.push_back(
    new Sphere(1,Color(1.0,.0,0.7),70.0,0.8,0.6,Vector3f(10.0,10.0,-40.0),5.0)
  );
  
/*  Scene::objects.push_back(
    new Sphere(1,Color(0.0,0.0,1.0),70.0,0.8,Vector3f(5.0,-5.0,-5.0),10.0)
  );

Scene::objects.push_back(
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
  int x,y,u,v;

  Vector3f sx = Vector3f(0.0,0.0,0.0);
  Vector3f sy = Vector3f(0.0,0.0,0.0);
  Vector3f firstray = Vector3f(0.0,0.0,0.0);

  struct timeval start = {0};
  struct timeval end = {0};


  //Initialize scene
	init();

  //Generate first ray
  Scene::camera.getFirstRay(Scene::image,sx,sy,firstray);

  //Set number of omp threads
  omp_set_dynamic(0);
  omp_set_num_threads((argc > 1)?atoi(argv[1]):1);

  gettimeofday(&start,NULL);
  //Loop through image

  int width = Scene::image.width;
  int height = Scene::image.height;

  #pragma omp parallel for default(none) \
   shared(sx,sy,firstray,width,height) private(y,x,v,u)
  for (y = 0; y < height; y += 1)
  {
    for (x = 0; x < width; x += 1)
    {
      //A new ray from the camera
	    double r=0.0,g=0.0,b=0.0;
      int supersample_factor = 5;
      double opacity=(double)1.0/(supersample_factor*supersample_factor);
      Ray ray;
      Color raycolor;
      bool collide;

		  for(v = 0; v < supersample_factor-1; v++) {
		  for(u = 0; u < supersample_factor-1; u++)
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
          Scene::image.updatePixel(x,Scene::image.height - y,opacity,raycolor);			       
        else
          Scene::image.updatePixel(x,Scene::image.height - y,opacity,Scene::bgcolor);
        
      }}        
    }//*/
  }

  gettimeofday(&end,NULL);

  //Write image to file
  Scene::image.writeToFile();

  //Finalize scene
  finalize();

  //Report timing
  cout << "Total time to render (msec): " <<
    (double)(end.tv_sec-start.tv_sec)*1e3 + 
    (double)(end.tv_usec-start.tv_usec)*1e-3 
        << endl;

	return 0;
}
