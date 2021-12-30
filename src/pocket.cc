#include "pocket.h"

namespace pool {

Pocket::Pocket(const double& radius, const vec2& position) {
  radius_ = radius;
  position_ = position;
}

void Pocket::Display() const {
  ci::gl::color(ci::Color("black"));
  ci::gl::drawSolidCircle(position_, radius_);
}

vec2 Pocket::GetPosition() const {
  return position_;
}

double Pocket::GetRadius() const {
  return radius_;
}

double pool::Pocket::GetX() const {
  return position_.x;
}

double pool::Pocket::GetY() const {
  return position_.y;
}

} //namespace pool

