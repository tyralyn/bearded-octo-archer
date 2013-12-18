#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <PRIMITIVE.h>


class TRIANGLE: public PRIMITIVE
{
public:
  TRIANGLE(const VEC3F& c = 0.f, const VEC3F& d = 0.f, const VEC3F& e = 0.f){
	vertices[0]=c;
	vertices[1]=d;
	vertices[2]=e;
	//orientTriangle();
	isNotMirror();
	isNotGlass();
  }
  virtual ~TRIANGLE() {}

  /*void orientTriangle() {
	VEC3F vector1 = vertices[1]-vertices[0];
	VEC3F vector2 = vertices[2]-vertices[0];
	VEC3F normal = cross (vector1, vector2);
	
	  
  }*/

  //finds normalized normal vector at point vertices[0]
  VEC3F getNormal() {
	  VEC3F vector1 = vertices[1]-vertices[0];
	  VEC3F vector2 = vertices[2]-vertices[0];
	  VEC3F normal = cross (vector1, vector2);
	  return normal;
  }
  
  //finds normal point on triangle at point a
   virtual VEC3F normal(const VEC3F& a) {
	  VEC3F vector1 = vertices[1]-a;
	  VEC3F vector2 = vertices[2]-a;
	  VEC3F normal = cross (vector1, vector2);
	  return normal;
  }

  //gets normal value at point pb given points pa, pc, pb
  VEC3F getNormal(VEC3F pa, VEC3F pb, VEC3F pc) {
	  VEC3F vector1 = pa-pb;
	  VEC3F vector2 = pc-pb;
	  VEC3F normal = cross(vector1, vector2);
	return normal ;
  }

  //tests to see whether a point is in triangle given the point and its normal
  bool inTriangle(VEC3F point,VEC3F normal) {
	for (int i=0; i<3;i++) {
	  VEC3F crossP=getNormal(vertices[(i+1)%3],vertices[i%3],point);
	  float f = crossP*normal;
	  if (f<0)
		return false;
	}
	return true;
  }

  //test to see whether ray intersects with triangle
  virtual bool intersect(const RAY& ray, IntersectInfo& info) {
	//check to see where ray intersects plane
	VEC3F point_p = vertices[0]; //get any point of the plane
	VEC3F Normal = normal(point_p); //get direction of normal at that point
	VEC3F normal = info.getFrontFacingNormal( ray, Normal);
	float t= (-(ray.origin()-point_p)*normal)/(ray.direction()*normal);
	VEC3F rayPlaneIntersection = ray.origin()+t*ray.direction();
	bool b = inTriangle(rayPlaneIntersection, normal);
	if (!b)
		return false;
	if (info.intersectObj==NULL)
		t=1000000000;
		
	if (info.t > t) {
		info.t=t;
		info.point = rayPlaneIntersection;
		info.normal = normal;
		info.intersectObj=this;
		info.direction=ray.direction();
		return true;
	}
	return false;
  }

  //returns point moved 0.01 in direction of normal
  VEC3F jitterOut(const VEC3F& point) {
    return point + 0.05f * normalize(normal(point));
  }
  
  //returns point moved 0.01 in direction opposite of normal
    VEC3F jitterIn(const VEC3F& point) {
    return point - 0.01f * normalize(normal(point));
  }

private:
  VEC3F vertices[3];
};
#endif
