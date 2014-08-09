#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include <RAY.h>
#include <SPHERE.h>
#include <LIGHT.h>
#include <TRIANGLE.h>
#include <math.h>
using namespace::std;
class SCENE
{
public:
  SCENE() {}
  ~SCENE() {
    for(unsigned int x = 0; x < _primitives.size(); x++)
      delete _primitives[x];
    for(unsigned int x = 0; x < _lights.size(); x++)
      delete _lights[x];
  }
  
  void setup() {
	alphaAir = 1.0;
	alphaGlass = 1.5;  
	
	//add primitives to the scene
	SPHERE* sphere1 = new SPHERE(VEC3F(3.5, 0, -10), 3);
    sphere1->color() = normalize(VEC3F(.25, .25, 1));
    sphere1->isMirror();
    _primitives.push_back(sphere1);
	  
    SPHERE* sphere0 = new SPHERE(VEC3F(-3.5, 0, -10), 3);
    sphere0->color() = VEC3F(1, 0.25, 0.25);
    sphere0->isBoth();
	_primitives.push_back(sphere0);
	
	TRIANGLE* triangle = new TRIANGLE (VEC3F(5,-3,-10),VEC3F (5,1,-10),VEC3F (1,-3,-12));   
	triangle->color() = normalize(VEC3F (.0,0,.6));
	//triangle->isMirror();
	_primitives.push_back(triangle);
    
   
	SPHERE* sphere2 = new SPHERE(VEC3F(0, -1000, -10), 997);
	sphere2->color() = normalize(VEC3F(1, .3, 1));
	_primitives.push_back(sphere2);	

   //_primitives.push_back(sphere2);
    
    for (int m=-20;m<-20+(20-1)*2; m+=2) {
		for (int n = -2; n<-2+(10-1)*2;) {
			SPHERE* newSphere = new SPHERE(VEC3F((float)m, (float)n, -20.0),1);
			newSphere->color()=VEC3F(.25,.45,1);
			_primitives.push_back(newSphere);
			n+=2;
		}
	}

	LIGHT* light0 = new LIGHT(VEC3F(10, 3, -5), VEC3F(1));
	_lights.push_back(light0);

    LIGHT* light1 = new LIGHT(VEC3F(-10, 3, -7.5), VEC3F(0.5, .25, .25));
    _lights.push_back(light1);
    
    LIGHT* light3 = new LIGHT(VEC3F(0, 3, -1), VEC3F(1));
	_lights.push_back(light3);
	
	    LIGHT* light4 = new LIGHT(VEC3F(0, 3, -1), VEC3F(1));
	_lights.push_back(light4);
	
	    LIGHT* light5 = new LIGHT(VEC3F(0, 3, -1), VEC3F(1));
	_lights.push_back(light5);
	
	    LIGHT* light2 = new LIGHT(VEC3F(0, 3, -1), VEC3F(1));
	_lights.push_back(light2);
  }
  
  void setup2() {
	alphaAir = 1.0;
	alphaGlass = 1.5;  
	
	//add primitives to the scene
	SPHERE* sphere1 = new SPHERE(VEC3F(0, 0, -10), 2);
    sphere1->color() = VEC3F(0, 0, 1);
    sphere1->isGlass();
	//sphere1->isMirror();
    _primitives.push_back(sphere1);
    
    SPHERE* sphere3 = new SPHERE(VEC3F(4.5, 0, -10), 2);
    sphere3->color() = VEC3F(1, 0, 0);
    sphere3->isMirror();
	_primitives.push_back(sphere3);
   
	//SPHERE* sphere2 = new SPHERE(VEC3F(0, -1000, -10), 997);
	//sphere2->color() = VEC3F(1,1,0);
	//_primitives.push_back(sphere2);	
    VEC3F coleur;
    for (int m=-20;m<-20+(20-1)*2; m+=2) {
		for (int n = -2; n<-2+(10-1)*2;) {
			if (m*n%8==0)
				coleur = VEC3F(1,1,1);
			else
				coleur = VEC3F(0,1,0);
			SPHERE* newSphere = new SPHERE(VEC3F((float)m, (float)n, -20.0),1);
			newSphere->color()=coleur;
			_primitives.push_back(newSphere);
			n+=2;
		}
	}

	LIGHT* light0 = new LIGHT(VEC3F(10, 3, -5), VEC3F(1));
	_lights.push_back(light0);

    LIGHT* light1 = new LIGHT(VEC3F(-10, 3, -7.5), VEC3F(0.5, .25, .25));
    _lights.push_back(light1);
  }
  
  //check to see if primitives are casting shadow
  bool inshaddow(const LIGHT* light, const IntersectInfo& intersectInfo) {
	//if there is no intersection, return false
	if (intersectInfo.intersectObj == NULL)
		return false;
    VEC3F origin = intersectInfo.intersectObj->jitterOut(intersectInfo.point);
    RAY shadowRay(origin, light->position() - origin);
    IntersectInfo newInfo;
    for(unsigned int x = 0; x < _primitives.size(); x++){
      if(_primitives[x]->intersect(shadowRay, newInfo))
        return true;
    }
    return false;
  }
  
  //check to see if ray intersects a primitive
  IntersectInfo intersect(const RAY& ray){
    IntersectInfo intersectInfo; //make intersectInfo object
	//loop through array of primitives
    for(int x = (_primitives.size()-1); x>=0; x--){    
      _primitives[x]->intersect(ray, intersectInfo);
	  //check to see whether ray intersects any of the primitives, return the intersectInfo
    }
    return intersectInfo; 
  }
  
	//computes reflection intersection information for ray and current intersection information
  IntersectInfo computeReflectionRay(RAY& ray, IntersectInfo& intersectInfo) {	  
	VEC3F d = ray.direction();
	VEC3F n = intersectInfo.normal;
	d.normalize();
	n.normalize();
	VEC3F r = d - 2 * (d * n) * n;
	r.normalize();
	RAY reflectionEyeRay(intersectInfo.point, r);
	IntersectInfo intersectInfo2 = intersect(reflectionEyeRay);
	return intersectInfo2;
  }
  
  //caculates number of intersections between ray and primitive
  int getNumIntersections(bool goingIn, VEC3F d, VEC3F n) {
	 float alpha1, alpha2;
	  if (goingIn) {
		alpha1 = alphaAir;
		alpha2 = alphaGlass;
	  }
	  else {
		alpha1 = alphaGlass;
		alpha2 = alphaAir;  
	  }
	  float disc = sqrt(1 - (alpha1 * alpha1 * (1 - ((d*n)*(d*n)))/(alpha2*alpha2)));
	  if (disc > 0 )
		return 2;
	  else if (disc == 0)
		return 1;
	  else 
		return 0;
  }
  
  //computes refraction intersection information for ray and current information
  IntersectInfo computeRefractionRay(const RAY& ray, const IntersectInfo& intersectInfo) {
	VEC3F d = ray.direction();
	VEC3F n = intersectInfo.normal;
	d.normalize();
	n.normalize(); 
	   
	VEC3F d2Direction= (alphaAir*(d - n * (d * n))/alphaGlass) - 
		n*sqrt(1 - (alphaAir * alphaAir * (1 - ((d*n)*(d*n)))/(alphaGlass*alphaGlass)));
	d2Direction=normalize(d2Direction);
	VEC3F d2Origin= intersectInfo.point;
	d2Origin = intersectInfo.intersectObj->jitterIn(d2Origin);
	RAY d2(d2Origin, d2Direction);
	
	IntersectInfo intersection2 = intersect(d2); 
	
	d = d2.direction();
	n = intersection2.normal*-1;
	d.normalize();
	n.normalize();
	
	VEC3F d3Direction= (alphaGlass*(d - n * (d * n))/alphaAir) - 
		n*sqrt(1 - (alphaGlass * alphaGlass * (1 - ((d*n)*(d*n))))/(alphaAir*alphaAir));
	d3Direction=normalize(d3Direction);
	VEC3F d3Origin = intersection2.point;	
	d3Origin = intersection2.intersectObj->jitterOut(d3Origin);
	RAY d3 (d3Origin, d3Direction);
	
	IntersectInfo intersection3 = intersect (d3);
	
	return intersection3;
  }
  
  float schlickConstant0(bool goingIn) {
	float n1, n2;
	if (goingIn) {
		n1=alphaAir;
		n2=alphaGlass;
		}
	else {
		n2=alphaAir;
		n1=alphaGlass;
	}
	float ratio = (n1-n2)/(n1+n2);
	return ratio*ratio;
  }
  
  float schlickConstantTheta(float schlick0, float cosTheta) {
	  float schlickTheta = schlick0 + (1-schlick0)*(float)pow(1-(double)cosTheta,5);
	  return schlickTheta;
  }
   
  //computes color for given ray
  VEC3F computeColor(RAY& ray, int& k) {
    VEC3F res = VEC3F(0.0,0.0,0.0);
    IntersectInfo intersectInfo = intersect(ray);
    if(intersectInfo.t < 0)
      return res;
    bool mirror = intersectInfo.intersectObj->isAMirror();
    bool glass = intersectInfo.intersectObj->isAGlass();
    RAY Ray = ray;
    VEC3F objectColor = intersectInfo.intersectObj->color();
	//cout<<"hello: "<<objectColor<<endl;
	return objectColor;
	//if (intersectInfo.intersectObj) 
		//return intersectInfo.intersectObj->color();
	if (glass) { 
		intersectInfo =computeRefractionRay(ray, intersectInfo);
		RAY RAy(intersectInfo.point, intersectInfo.direction);
		Ray=RAy;
		if (intersectInfo.intersectObj)
			objectColor = intersectInfo.intersectObj->color();
		res = getColor(intersectInfo, Ray, objectColor);
		if(!mirror) {
			//res.normalize();
			//return res;
			}
		else {
			VEC3F d = ray.direction();
			VEC3F n = intersectInfo.normal;
			d.normalize();
			n.normalize();
			//int numIntersections =getNumIntersections(true,d,n);
			VEC3F refrRes = res;
			res = VEC3F(0,0,0);
			//IntersectInfo refrInfo = intersectInfo;
			intersectInfo = intersect(ray);
			intersectInfo= computeReflectionRay(ray, intersectInfo);
			RAY Ray(intersectInfo.point, intersectInfo.direction);
			IntersectInfo reflInfo=intersect(Ray);
			if (reflInfo.intersectObj && reflInfo.intersectObj->isAGlass())
				objectColor = computeColor(Ray, k);
			else if (reflInfo.intersectObj)
				objectColor = intersectInfo.intersectObj->color();
			else
				objectColor = VEC3F(0,0,0);
			res=getColor(intersectInfo,Ray,objectColor);
			VEC3F reflRes = res;
			intersectInfo = intersect(ray);
			
			float cosTheta = d*n;
			float R0 = schlickConstant0(true);
			float RTheta = schlickConstantTheta(R0, cosTheta);
			res = RTheta*reflRes + (1-RTheta)*refrRes;
			//res = VEC3F(.75,.9,0);
			//cout<<"costheta: "<<cosTheta<<endl;
			 //res.normalize();
			return res;
		}
	}
	
	else if (mirror) {
		intersectInfo = computeReflectionRay(ray,intersectInfo);
		RAY RAy(intersectInfo.point,intersectInfo.direction);
		Ray = RAy;
		//if (k<2) {
		IntersectInfo intersectInfo2 = intersect(RAy);
		if (intersectInfo2.intersectObj && intersectInfo2.intersectObj->isAGlass())
			objectColor = computeColor(RAy,k);
		else if (intersectInfo2.intersectObj)
			objectColor = intersectInfo.intersectObj->color();
		else
			objectColor = VEC3F (0,0,0);
	    res = getColor(intersectInfo, Ray, objectColor);
		  //res.normalize();
	    return res;
		//}
	}
	
	//*for(unsigned int y = 0; y < _lights.size(); y++){
		//if(inshaddow(_lights[y], intersectInfo)) {
			//continue;
		//}	

	  res += getColor(intersectInfo, Ray, objectColor);
	  //res.normalize();
	 // cout<<"color: "<<res<<endl;
    return res;
  }
  
  VEC3F getColor(IntersectInfo intersectInfo, RAY Ray, VEC3F objectColor) {
	  VEC3F res;
	  //return VEC3F(0,0,1);
	  for(unsigned int y = 0; y < _lights.size(); y++){
		if(inshaddow(_lights[y], intersectInfo)) {
			continue;
		}
	    if (!intersectInfo.intersectObj)
		  return (VEC3F(0,0,0));
	    VEC3F diffuseLightColor = _lights[y]->diffuse(intersectInfo.point, intersectInfo.normal);
	    VEC3F specularLightColor = _lights[y]->specular(intersectInfo.point, Ray.direction(), intersectInfo.normal, 10);
	    res += mulVec(objectColor/*intersectInfo.intersectObj->color()*/, diffuseLightColor + specularLightColor);
	 }
	  return res;
  }

private:
  vector<PRIMITIVE*> _primitives;
  vector<LIGHT*> _lights;
  float alphaAir;
  float alphaGlass;
};
#endif
