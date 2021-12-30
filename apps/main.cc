

#include <glm/vec2.hpp>

#include "cue.h"

using glm::vec2;
using pool::Collision;
using pool::NewCue;
int main () {
  vec2 po {533.125, 410.5};
  vec2 point = NewCue().RotatePoint(po, vec2(551.25, 400), -30);
  std::cout<<point<<std::endl;
  std::cout<<po<<std::endl;

  vec2 npoint = NewCue().RotatePoint(vec2(5, 5), vec2(10, 5), -90);
  std::cout<<npoint<<std::endl;
  
}
