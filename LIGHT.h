#ifndef LIGHT_H
#define LIGHT_H
#include <cmath>
#include <VEC3F.h>
class LIGHT
{
public:
  LIGHT(const VEC3F& p = 0.f, const VEC3F& c = 1):
    _position(p),
    _color(c)
  {

  }
  VEC3F diffuse(const VEC3F& point, const VEC3F& normal)
  {
	//cout<<" d ";
    VEC3F lightDir = normalize(_position - point);
    float ratio = fmax(0.f, lightDir * normal);
    return _color * ratio;
  }
  
  VEC3F specular(const VEC3F& point, const VEC3F& rayDir, const VEC3F& normal, float phong)
  {
	VEC3F l = _position-point;
	VEC3F v = rayDir-point;
	l.normalize();
	v.normalize();
	VEC3F h = (v+l)/((v+l).getMagnitude());
	//cout<<" s ";
    VEC3F lightDir = normalize(_position - point);
    VEC3F reflectDir = normalize(-lightDir + 2 * (normal * lightDir) * normal);
    //float s = fmax(0.f, reflectDir * (-rayDir));
	float s = fmax(0.f, normal*h);
    return _color * powf(s, phong);
  }
  
  inline const VEC3F& position() const { return _position; }
  inline VEC3F& position() { return _position; }
private:
  VEC3F _position;
  VEC3F _color;
};
#endif
