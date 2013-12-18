#ifndef RAY_H
#define RAY_H
#include <VEC3F.h>
class RAY
{
public:  
  RAY(VEC3F o, VEC3F d):
    _origin(o), _direction(d)
  {
    _direction.normalize();
  }
  RAY();
  inline const VEC3F& origin() const { return _origin; }
  inline const VEC3F& direction() const { return _direction; }
  inline VEC3F& origin() { return _origin; }
  inline VEC3F& direction() { return _direction; }

  
private:
  VEC3F _origin;
  VEC3F _direction;
};

#endif
