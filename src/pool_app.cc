#include "pool_app.h"

namespace pool {

PoolApp::PoolApp() : ui_(kWindowWidth,
                         KWindowLength) {
  ci::app::setWindowSize((int) kWindowWidth,
                         (int) KWindowLength);
}

void PoolApp::draw() {
  // Draws UI
  ci::Color background_color("gray");
  ci::gl::clear(background_color);
  ui_.Draw();
}

void PoolApp::update() {
  ui_.AdvanceOneFrame();
}

void PoolApp::mouseDown(ci::app::MouseEvent event) {
  //Shoots when mouse is clicked
  ui_.Shoot();
}

void PoolApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    //if key pressed is up, velocity increases
    case ci::app::KeyEvent::KEY_LEFT:
      //Left key increases cue stick's power
      ui_.PowerUp();
      break;
      //if key pressed is down, velocity increases
    case ci::app::KeyEvent::KEY_RIGHT:
      //Right key resets cue stick's power without shooting
      ui_.ResetPower();
      break;
  }
}

void PoolApp::mouseMove(ci::app::MouseEvent event) {
  //Whenever the mouse moves, the cue follows the mouse
  ui_.Follow(event.getPos());
}

} //namespace pool