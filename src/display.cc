#include "display.h"


namespace pool {

BallDisplay::BallDisplay() {
  first_position_ = {0, 0};
  num_balls_ = 0;
  radius_ = 0;
  num_displayed_ = 0;
}

BallDisplay::BallDisplay(const glm::vec2& first_ball_position, const int& num_balls,
                         const double& ball_radius) {
  first_position_ = first_ball_position;
  num_balls_ = num_balls;
  radius_ = ball_radius;
  num_displayed_ = 0;
}

void BallDisplay::Display()  {
  vec2 position = first_position_;
  //Displays balls from update, and black circles
  for (int i = 0; i < num_displayed_; i++) {
    scored_[i].SetPosition({position});
    scored_[i].Display();
    position += vec2(2 * radius_, 0);
  }
  for (int i = num_displayed_; i < num_balls_; i++) {
    ci::gl::color(ci::Color("black"));
    ci::gl::drawSolidCircle(position, radius_);
    position += vec2(radius_ * 2, 0);
  }
}

void BallDisplay::Update(const Ball& ball) {
  //Adds scored ball to vector, and updates number displayed
  num_displayed_++;
  scored_.push_back(ball);
}

} //namespace pool


