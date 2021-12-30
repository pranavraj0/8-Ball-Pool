#include "ui.h"

namespace pool {

UI::UI() {

}

void UI::DisplayStripes(const glm::vec2& position, const bool& stripes,
                              const int& player_num) {
  ci::gl::color(ci::Color("black"));
  //std::cout<<position<<std::endl;
  //Draws strings dependent on whether player is solids or stripes
  if (stripes) {
    ci::gl::drawStringCentered("Player " + std::to_string(player_num) + ": Stripes", position);
  } else {
    ci::gl::drawStringCentered("Player " + std::to_string(player_num) + ": Solids", position);
  }
}

void UI::DisplayTurns(const glm::vec2& position, const bool& first_player) {

}

} //namespace pool

