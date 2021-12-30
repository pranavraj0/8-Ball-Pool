#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "app_ui.h"

namespace pool {

class PoolApp : public ci::app::App {
 public:
  PoolApp();

  void draw() override;

  void update() override;

  void mouseMove(ci::app::MouseEvent event) override;

  void keyDown(ci::app::KeyEvent event) override;

  void mouseDown(ci::app::MouseEvent event) override;

  //Constants
  const double kWindowWidth = 1400;
  const double KWindowLength = 800;
  const double kMargin = 100;
 private:
  AppUI ui_;
};

} //namespace pool