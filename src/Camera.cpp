#include "simple_ray.h"
#include <math.h>
#include <iostream>


int Camera::getFirstRay(
  Image& img, Vector3f& sx, Vector3f& sy, Vector3f& firstray
){

  Vector3f gaze = Vector3f(0.0,0.0,0.0);
  Vector3f tmp = Vector3f(0.0,0.0,0.0);
  int i,j;
  double dist,mag;

  gaze += lookAt;
  gaze -= eyePosition;
  gaze.Normalize();
  dist = gaze.length();

  //gaze.Print();

  sx = lookAt.Cross(upVector);
  sy = gaze.Cross(sx);

  //cout <<"la";
  //sy.Print();

  //eyePosition.Print();
  //cout << endl;
  //sy.Print();


  dist *= 2.0; 
  mag = dist * tan(ToRadian(FOV)) / img.imageWidth;
  sx *= mag;

  //cout <<"Mag = "<< mag << endl;
  
  mag = dist * tan(ToRadian(FOV)) / img.imageHeight;
  sy *= mag;

  firstray += lookAt;
  firstray -= eyePosition;
  cout << endl;
  lookAt.Print();
  eyePosition.Print();
  firstray.Print();



  tmp = sy;
  tmp *= img.imageHeight / 2.0;
  firstray += tmp;

  
  
  tmp = sx;
  tmp *= -1.0 * img.imageWidth / 2.0;
  firstray += tmp;

}

