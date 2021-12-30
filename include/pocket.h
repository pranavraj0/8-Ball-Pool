#pragma once
#include "cinder/gl/gl.h"
#include "vector"

namespace pool {

using glm::vec2;

class Pocket {
 public:
  Pocket(const double& radius, const vec2& position);

  /**
   * Displays table.
   */
  void Display() const;
  
  //Getters
  vec2 GetPosition() const;
  
  double GetRadius() const;
  
  double GetX() const;
  
  double GetY() const;
 private:
  double radius_;
  vec2 position_;
  
};

} //namespace pool