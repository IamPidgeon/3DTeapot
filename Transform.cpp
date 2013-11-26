// Transform.cpp: implementation of the Transform class.


#include "Transform.h"

//Please implement the following functions:

// Helper rotation function. 
mat3 Transform::rotate(const float degrees, const vec3& axis) {
  float radians = degrees * M_PI / 180.0f;
  mat3 identMat(1.0);
  mat3 r1 = mat3(axis.x*axis.x, axis.x*axis.y, axis.x*axis.z, axis.x*axis.y, axis.y*axis.y, axis.y*axis.z, axis.x*axis.z, axis.y*axis.z, axis.z*axis.z);
  mat3 r2 = mat3(0.0, axis.z, -axis.y, -axis.z, 0.0, axis.x, axis.y, -axis.x, 0.0);
  mat3 R = cos(radians)*identMat + (1.0-cos(radians))*r1 + sin(radians)*r2;
  //  (1 0 0)			      (xˆ2  xy  xz)		    (0  -z  y)
  //  (0 1 0)	+ (1-cosϴ)(xy  yˆ2  yz) + sinϴ(z   0 -x)
  //  (0 0 1)			      (xz  yz  zˆ2)		    (-y  x  0)
  return R;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  eye = rotate(degrees, up) * eye;
  
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
  vec3 newAxis = glm::cross(eye, up);
  newAxis = glm::normalize(newAxis);
  mat3 R = rotate(degrees, newAxis);
  eye = R * eye;
  up = R * up;
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  vec3 u,v,w;
  w = glm::normalize(eye);
  u = glm::normalize(glm::cross(up,w));
  v = glm::cross(w,u);
  
  mat4 M = mat4(u.x,v.x,w.x,0,u.y,v.y,w.y,0,u.z,v.z,w.z, 0,(-u.x*eye.x-u.y*eye.y-u.z*eye.z), (-v.x*eye.x-v.y*eye.y-v.z*eye.z), (-w.x*eye.x-w.y*eye.y-w.z*eye.z), 1);
  
  return M;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
