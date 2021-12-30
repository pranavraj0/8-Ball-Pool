#include "ball.h"

namespace pool {

//load texture, take file path, draw texture on ball
Ball::Ball() {
  cue_ = false;
  solid_ = false;
  black_ = false;
  number_ = 0;
}

Ball::Ball(const bool& cue, const bool& solid, const bool& black,
           const int& number, const vec2& racking) {
  cue_ = cue;
  solid_ = solid;
  black_ = black;
  number_ = number;
  racking_ = racking;
  position_ = {-1, -1};
  velocity_ = {0, 0};
  image_path_ = "";
  //Sets image path based on whether number ball or cue ball
  if (!IsCue()) {
    image_path_ = "/Users/pranavrajaraman/Cinder/my-projects/final-project-doofnav/images/" + std::to_string(number) + ".png";
  } else {
    image_path_ = "/Users/pranavrajaraman/Cinder/my-projects/final-project-doofnav/images/cue.png";
  }
  //Setup to put image of ball onto balls when displaying
  img_ = ci::loadImage(image_path_);
  texture_ = ci::gl::Texture::create(img_);
}

void Ball::Display() const {
  //Binds texture to ball
  texture_->bind();
  auto shader = ci::gl::ShaderDef().texture(texture_).lambert();
  auto Glsl = ci::gl::getStockShader(shader);
  auto circle = ci::geom::Circle().radius(radius_).center(position_);
  auto mCircle = ci::gl::Batch::create(circle, Glsl);
  ci::gl::enableDepthWrite();
  ci::gl::enableDepthRead();
  //Displays
  mCircle->draw();
}

bool Ball::WillTwoCollide(const Ball& other) const {
  return (glm::distance(position_, other.position_) < radius_ + other.radius_ &&
          glm::distance(position_, other.position_) > 0 &&
          glm::dot((velocity_ - other.velocity_), (position_ - other.position_)) < 0);
}

bool Ball::WillCollideEver(const vector<Ball>& balls) const {
  for (const Ball& ball: balls) {
    if (WillTwoCollide(ball)) {
      return true;
    }
  }
  return false;
}

double Ball::GetVelocityBallCollisionX(const Ball& other) const{
  return (velocity_ - (dot((velocity_ - other.velocity_),
                           (position_ - other.position_))
                       / (length(position_ - other.position_) *
                          length(position_ - other.position_)))
                      * ((position_ - other.position_))).x;
}

double Ball::GetVelocityBallCollisionY(const Ball& other)const {
  return (velocity_ - (dot((velocity_ - other.velocity_),
                           (position_ - other.position_))
                       / (length(position_ - other.position_) *
                          length(position_ - other.position_)))
                      * ((position_ - other.position_))).y;
}

bool Ball::WillBallPocketCollide(const Pocket& pocket) const {
  //If center of ball is within radius of pocket
  if (glm::distance(position_, vec2(pocket.GetX(), pocket.GetY())) < pocket.GetRadius() + (radius_ / 2)) {
    return true;
  }
  return false;
}

//Getters and setters
bool Ball::IsCue() const{
  return cue_;
}

bool Ball::IsSolid() const {
  return solid_;
}

bool Ball::IsBlack() const {
  return black_;
}

double Ball::GetRadius() const {
  return radius_;
}

int Ball::GetNumber() const {
  return number_;
}

vec2 Ball::GetPosition() const {
  return position_;
}

vec2 Ball::GetRacking() const{
  return racking_;
}

void Ball::SetRadius(const double& to_set) {
  radius_ = to_set;
}

void Ball::SetPosition(const vec2& to_be_set) {
  position_ = to_be_set;
}

void Ball::SetRacking(const vec2& to_be_set) {
  racking_ = to_be_set;
}

double Ball::GetXRack() const {
  return racking_.x;
}

double Ball::GetYRack() const {
  return racking_.y;
}

double Ball::GetXPosition() const {
  return position_.x;
}

double Ball::GetYPosition() const {
  return position_.y;
}

double Ball::GetXVelocity() const {
  return velocity_.x;
}

double Ball::GetYVelocity() const {
  return velocity_.y;
}

void Ball::SetVelocity(const vec2& to_set) {
  velocity_ = to_set;
}

} //namespace pool