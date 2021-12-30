#pragma once

#include "cinder/gl/gl.h"
#include "vector"
#include <glm/vec2.hpp>

namespace pool {

using glm::vec2;

class Table {
 public:
  Table();

  /**
   * Constructor which takes length, width, and margin for table
   * @param length 
   * @param width 
   * @param margin 
   */
  Table(const double& length, const double& width, const double& margin,
        const double& window_length, const double& window_width);

  /**
   * Displays table
   */
  void Display() const;
 private:
  double window_length_;
  double window_width_;
  double length_;
  double width_;
  double margin_;

  //Variables used to bind texture to table
  std::shared_ptr<cinder::ImageSource> margin_image_;
  std::shared_ptr<cinder::gl::Texture2d> margin_texture_;
};

} //namespace pool