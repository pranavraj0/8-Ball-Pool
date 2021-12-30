#pragma once

#include <glm/vec2.hpp>

#include "cinder/gl/gl.h"
#include "vector"
#include "pocket.h"

namespace pool {

using glm::vec2;
using std::vector;

class Ball {
 public:
  Ball();

  Ball(const bool& cue, const bool& solid, const bool& black, const int& number,
       const vec2& racking);

  /**
   * Displays ball using image.
   */
  void Display() const;

  /**
   * Tells whether two balls will collide.
   * @param other; ball to compare to
   * @return; whether collision will occur
   */
  bool WillTwoCollide(const Ball& other) const;

  /**
   * Tells if ball will ever collide with another.
   * @param balls; all balls in game
   * @return; whether collision will occur
   */
  bool WillCollideEver(const vector<Ball>& balls) const;

  /**
   * Gets x component of velocity after collision.
   * @param other; ball to be collided with
   * @return; x component of velocity
   */
  double GetVelocityBallCollisionX(const Ball& other) const;

  /**
   * Gets y component of velocity after collision.
   * @param other; ball to be collided with
   * @return; y component of velocity
   */
  double GetVelocityBallCollisionY(const Ball& other) const;

  /**
   * Tells whether ball will collide with a pocket.
   * @param pocket; pocket to check
   * @return; whether ball will collide
   */
  bool WillBallPocketCollide(const Pocket& pocket) const;

  //Setters for instance variables
  void SetRadius(const double& to_set);

  void SetPosition(const vec2& to_be_set);

  void SetRacking(const vec2& to_be_set);

  void SetVelocity(const vec2& to_set);

  bool IsCue() const;

  bool IsSolid() const;

  bool IsBlack() const;

  double GetRadius() const;

  int GetNumber() const;

  vec2 GetPosition() const;

  vec2 GetRacking() const;

  double GetXRack() const;

  double GetYRack() const;

  double GetXPosition() const;

  double GetYPosition() const;

  double GetXVelocity() const;

  double GetYVelocity() const;
 private:
  //Ball radius
  double radius_;
  bool cue_;
  //Whether ball is solid or stripes
  bool solid_;
  //Whether ball is 8-ball
  bool black_;
  int number_;
  vec2 position_;
  //Position in rack of balls
  vec2 racking_;
  vec2 velocity_;
  //Variables to add images to balls
  std::string image_path_;
  std::shared_ptr<cinder::ImageSource> img_;
  std::shared_ptr<cinder::gl::Texture2d> texture_;
};

} //namespace pool