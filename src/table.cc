#include "table.h"

namespace pool {

Table::Table() {
  length_ = 0;
  width_ = 0;
  margin_ = 0;
}

Table::Table(const double& length, const double& width, const double& margin,
             const double& window_length, const double& window_width) {
  length_ = length;
  width_ = width;
  margin_ = margin;
  window_length_ = window_length;
  window_width_ = window_width;
  //Loads texture for margin of table
  margin_image_ = ci::loadImage("/Users/pranavrajaraman/Cinder/my-projects/final-project-doofnav/images/walnut.jpg");
  margin_texture_ = ci::gl::Texture::create(margin_image_);
}


void Table::Display() const {
  // Creates playing surface of table
  ci::gl::color(ci::Color("seagreen"));
  //Finds distance from x and y axes to table
  double x_distance_to_table = (window_width_ - width_) / 2;
  double y_distance_to_table = (window_length_ - length_) / 2;

  vec2 top_left (x_distance_to_table, y_distance_to_table);
  //Draws rectangle exactly at middle of window
  ci::gl::drawSolidRect(
      ci::Rectf(top_left + vec2(margin_, margin_),
                top_left + vec2(margin_, margin_) +
                vec2(width_ - 2 * margin_, length_ - 2 * margin_)));

  //Creating outer margin of table using texture, drawn at middle of window
  margin_texture_->bind();
  auto shader = ci::gl::ShaderDef().texture(margin_texture_).lambert();
  auto Glsl = ci::gl::getStockShader(shader);

  auto square = ci::geom::Rect().rect(
      ci::Rectf(top_left, top_left + vec2(width_, length_)));

  auto mSquare = ci::gl::Batch::create(square, Glsl);
  ci::gl::enableDepthWrite();
  ci::gl::enableDepthRead();
  mSquare->draw();
}

} //namespace pool