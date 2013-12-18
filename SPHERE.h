#ifndef SPHERE_H
#define SPHERE_H
#include <PRIMITIVE.h>
class SPHERE: public PRIMITIVE
{
public:
  SPHERE(const VEC3F& c = 0.f, float r = 1):
    _center(c), _radius(r) { isNotMirror(); isNotGlass();}

  virtual ~SPHERE() {}
  
  //called to test for intersection between ray and sphere; 
  virtual bool intersect(const RAY& ray, IntersectInfo& info) {
	bool boo=false;
    VEC3F origin_minus_center = ray.origin() - _center;
    float a = 1.f;
    float b = 2 * (ray.direction() * origin_minus_center);
    float c = origin_minus_center * origin_minus_center - _radius * _radius;
    float delta = b*b - 4 * a * c;
    if(delta < 0){
      return false;
    }
    float delta_root = sqrt(delta);
    float x1 = (-b - delta_root) / (2 * a);
    float x2 = (-b + delta_root) / (2 * a);
    float t;
    if (info.intersectObj==NULL) 
		t = 10000000;
	else
		t=info.t;
    
    
    if (1<x1) {
		if (28<x1)
			;//b=false;
		else //x1 is less that 10000000
			if (x1 < t) {
				boo=true;
				t=x1;
			}
				
	}
	else
		;//b=false;
    
    if (1<x2) {
		if (28<x1)
			;//b=false;
		else //x1 is less that 10000000
			if (x2 < t) {
				
				boo=true;
				t=x2;
			}
	}
	else
		;
		
	if (boo && t > 0) {
		info.t = t;
        info.point = ray.origin() + (info.t * ray.direction());
        info.normal = normal(info.point);
        info.intersectObj = this;
        info.direction=ray.direction();
	}
    return boo;
  }
  
  //returns normal vector to sphere at point
  virtual VEC3F normal(const VEC3F& point) {
    return normalize(point - _center);
  }
  
  //returns point moved 0.05 in direction of normal vector
  VEC3F jitterOut(const VEC3F& point) {
    return point + 0.05f * normalize(point - _center);
  }
  
  //returns point moved 0.01 in direction opposite of normal vector
  VEC3F jitterIn(const VEC3F& point) {
    return point - 0.01f * normalize(point - _center);
  }

private:
  VEC3F _center;
  float _radius;
};
#endif
