#pragma once

#include <glm/vec2.hpp>
#include "cinder/gl/gl.h"

namespace pool {
using glm::vec2;

class Cue {
 public:
  Cue();

  Cue(const double& width, const double& length);

  /**
   * Displays cue.
   */
  void Display() const;

  /**
   * Sets starting position of cue right behind cue ball.
   * @param cue_position; position of ball
   * @param radius; radius of ball
   */
  void SetStartingPosition(const vec2& cue_position, const double& radius);

  /**
   * Sets position when of cue when following mouse.
   * @param rotation_point; point cue should rotate around 
   * @param angle; angle cue should rotate
   */
  void SetPosition(const vec2& rotation_point, const double& angle);

  /**
   * Rotates a singular point as desired.
   * @param point; point to rotate
   * @param rotation_point; point rotated around
   * @param angle; angle to rotate
   * @return; new rotated point
   */
  static vec2 RotatePoint(vec2 point, vec2 rotation_point, const double& angle);

  /**
   * Pulls cue back certain number of pixels.
   * @param pixels; pixels to pull back
   */
  void PullBack(const double& pixels);

  /**
   * Uses angle of cue to find coordinates to pull cue back to. 
   * @param point; point of cue
   * @param pixels; pixels to pull back cue
   * @return; pulled back point
   */
  vec2 FindNewCoordinatesWithAngle(const vec2& point, const double& pixels) const;

  /**
   * Sets cue position after each turn of the game.
   * @param cue_position; position of cue ball
   * @param radius; radius of ball
   * @param angle; current angle of mouse
   */
  void SetCuePositionWithAngle(const vec2& cue_position, const double& radius, 
                               const double& angle);

  //Getters and setters
  void SetVelocity(const vec2& to_set);

  double GetXVelocity() const;

  double GetYVelocity() const;
 private:
  double width_;
  double length_;
  //Corners of cue
  vec2 top_right_;
  vec2 top_left_;
  vec2 bottom_right_;
  vec2 bottom_left_;
  vec2 velocity_;
  //Current angle which cue last turned to
  double current_angle_;
};

} //namespace pool

//what should classes do??
//manage state or just their object