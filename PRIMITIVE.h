#ifndef PRIMITIVE_H
#define PRIMITIVE_H
#include <RAY.h>
class PRIMITIVE;
struct IntersectInfo
{
  IntersectInfo():
    t(-1),
    intersectObj(NULL)
  {}
  VEC3F point;
  VEC3F normal;
  VEC3F direction;
  float t;
  PRIMITIVE* intersectObj;
  
  VEC3F getFrontFacingNormal(const RAY& ray, const VEC3F normal) {
	VEC3F FFN;
  	VEC3F totalRay = ray.origin() + t*ray.direction();
	if (totalRay * normal > 0)
		FFN = -1*normal;
	else
	    FFN = normal;
	return FFN;
	}
};
class PRIMITIVE
{
public:
  virtual ~PRIMITIVE() {} //virtual destructor
  //tests for an intersection between ray and primitive
  virtual bool intersect(const RAY& ray, IntersectInfo& info) = 0; 
  //finds normal
  virtual VEC3F normal(const VEC3F& point) = 0;
  //jitters a point out
  virtual VEC3F jitterOut(const VEC3F& point) = 0;
  //jitters a point in
  virtual VEC3F jitterIn(const VEC3F& point) = 0;
  //returns the color of the primitive
  inline VEC3F& color() {return _color; }
  void setColor(VEC3F color) {_color = color;}
  //make the primitive into a mirror
  void isMirror() { mirror = true; glass = false;}
  //make the primitive into not a mirror
  void isNotMirror() { mirror = false; }
  //check and see if primitive is a mirror
  bool isAMirror() { return mirror; }
  //make the primitive into glass
  void isGlass() { glass = true; mirror = false;}
  //make the primitive into not a glass
  void isNotGlass() { glass = false; }
  //check to see if primitive is made of glass
  bool isAGlass() { return glass; }
  void isBoth() {mirror=true; glass = true;}
  void isNeither() {mirror=false; glass=false;};
private:
  VEC3F _color;
  bool mirror;
  bool glass;
};
#endif
