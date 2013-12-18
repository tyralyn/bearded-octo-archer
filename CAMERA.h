#ifndef CAMERA_H
#define CAMERA_H
#include <MATRIX4.h>

class CAMERA
{
public:
  CAMERA()
  {
    _eye = VEC3F();
    _lookAt = VEC3F(0, 0, -1);
    _up = VEC3F(0, 1, 0);
    _nearPlane = 1;
    _fov = 65.0 / 180 * M_PI;

    VEC3F g = _lookAt - _eye;
    VEC3F w = normalize(-g);
    VEC3F u = normalize(cross(_up, w));
    VEC3F v = cross(w, u);
    MATRIX4 R = MATRIX4::Rotation(u, v, w);
    MATRIX4 T = MATRIX4::Translation(_eye);
    _reverseModelView = T * R.transpose();
  }
  void setAspect(float ratio)
  {
    _aspect = ratio;

    Real tanHalfFov = tan(_fov / 2);
    _top = tanHalfFov * _nearPlane;
    _bottom = -_top;
    _left = -_top * ratio;
    _right = -_left;
  }
  VEC3F pixelToWorldCoordinates(float x, float y)
  {
    VEC3F pixel_position(_left + (_right - _left) * x, _bottom + (_top - _bottom) * y, -_nearPlane);
    return _reverseModelView.transformPoint(pixel_position);
  }
  inline VEC3F& eye() { return _eye; }
  ~CAMERA()
  {

  }
private:
  VEC3F _eye;
  VEC3F _lookAt;
  VEC3F _up;
  float _nearPlane;
  float _fov;
  float _aspect;
  float _left;
  float _right;
  float _top;
  float _bottom;
  MATRIX4 _reverseModelView;
};
#endif