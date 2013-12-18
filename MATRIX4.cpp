#include "MATRIX4.h"

MATRIX4 operator * (const MATRIX4 &Left, const MATRIX4 &Right){
  MATRIX4 result;
  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
      result[i][j] = Left[i][0] * Right[0][j] + Left[i][1] * Right[1][j]
                   + Left[i][2] * Right[2][j] + Left[i][3] * Right[3][j];
  return result;
}
MATRIX4 MATRIX4::I()
{ 
  MATRIX4 I;
  I[0][0] = I[1][1] = I[2][2] = I[3][3] = 1;
  return I;
}

MATRIX4 MATRIX4::Scaling(const VEC3F &s)
{
  MATRIX4 S;
  S[0][0] = s[0];
  S[1][1] = s[1];
  S[2][2] = s[2];
  S[3][3] = 1;
  return S;
}
MATRIX4 MATRIX4::Scaling(Real s)
{
  return MATRIX4::Scaling(VEC3F(s));
}
MATRIX4 MATRIX4::Translation(const VEC3F &pos)
{
  MATRIX4 T;
  T[0][0] = T[1][1] = T[2][2] = T[3][3] = 1;
  T[0][3] = pos[0];
  T[1][3] = pos[1];
  T[2][3] = pos[2];
  return T;
}
MATRIX4 MATRIX4::Rotation(const VEC3F &axis, Real angle)
{
  Real c = cos(angle);
  Real s = sin(angle);
  Real t = 1.0f - c;

  VEC3F normalizedAxis = normalize(axis);
  Real x = normalizedAxis[0];
  Real y = normalizedAxis[1];
  Real z = normalizedAxis[2];

  MATRIX4 R;
  // from wiki
  R[0][0] = c + t * x * x;
  R[1][0] = y * x * t + z * s;
  R[2][0] = z * x * t - y * s;
  R[3][0] = 0;

  R[0][1] = x * y * t - z * s;
  R[1][1] = c + y * y  * t;
  R[2][1] = z * y * t + x * s;
  R[3][1] = 0;

  R[0][2] = x * z * t + y * s;
  R[1][2] = y * z * t - x * s;
  R[2][2] = c + z * z * t;
  R[3][2] = 0;

  R[0][3] = 0;
  R[1][3] = 0;
  R[2][3] = 0;
  R[3][3] = 1;
  return R;
}

MATRIX4 MATRIX4::Rotation(const VEC3F &basis1, const VEC3F &basis2, const VEC3F &basis3)
{
  return MATRIX4(basis1, basis2, basis3);
}
MATRIX4 MATRIX4::RotationX(Real theta)
{
  MATRIX4 R;
  R[0][0] = R[3][3] = 1;
  Real c = cos(theta);
  Real s = sin(theta);
  R[1][1] = R[2][2] = c;
  R[1][2] = -s;
  R[2][1] = s;
  return R;
}
MATRIX4 MATRIX4::RotationY(Real theta)
{
  MATRIX4 R;
  R[1][1] = R[3][3] = 1;
  Real c = cos(theta);
  Real s = sin(theta);
  R[0][0] = R[2][2] = c;
  R[0][2] = s;
  R[2][0] = -s;
  return R;
}
MATRIX4 MATRIX4::RotationZ(Real theta)
{
  MATRIX4 R;
  R[2][2] = R[3][3] = 1;
  Real c = cos(theta);
  Real s = sin(theta);
  R[0][0] = R[1][1] = c;
  R[0][1] = -s;
  R[1][0] = s;
  return R;
}

MATRIX4 MATRIX4::LookAt(const VEC3F &Eye, const VEC3F &At, const VEC3F &Up)
{
  // gaze
  VEC3F g = At - Eye;
  // our new 'z'
  VEC3F w = normalize(-g);
  VEC3F u = normalize(cross(Up, w));
  VEC3F v = cross(w, u);
  MATRIX4 R = MATRIX4::Rotation(u, v, w);
  MATRIX4 T = MATRIX4::Translation(-Eye);

  return R * T;
}
MATRIX4 MATRIX4::Perspective(Real FOV, Real Aspect, Real ZNear, Real ZFar){
  MATRIX4 M;
  Real FOVRadiant = FOV / 180 * M_PI;
  Real tanHalfFov = tan(FOVRadiant / 2);
  Real fH = tanHalfFov * ZNear;
  Real fW = fH * Aspect;
  M[0][0] = ZNear / fW;
  M[1][1] = ZNear / fH;
  M[2][2] = (ZNear + ZFar) / (ZNear - ZFar);
  M[3][2] = -1;
  M[2][3] = 2 * ZFar * ZNear / (ZNear - ZFar);

  return M;
}
MATRIX4 MATRIX4::Viewport(Real Width, Real Height)
{
  MATRIX4 M;
  M[0][0] = Width / 2;
  M[1][1] = Height / 2;
  M[2][2] = M[3][3] = 1;
  M[0][3] = (Width - 1) / 2;
  M[1][3] = (Height - 1) / 2;
  return M;
}
