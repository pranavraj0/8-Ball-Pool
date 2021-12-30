#pragma once

#include <glm/vec2.hpp>
#include "cinder/gl/gl.h"
#include "vector"
#include "ball.h"

namespace pool {

using glm::vec2;
using std::vector;

class UI {
 public:
  UI();

  /**
   * Draws whether player has solids or stripes.
   * @param position; position string should be at
   * @param shaded; whether player 
   * @param player_num; player's number
   */
  static void DisplayStripes(const vec2& position, const bool& stripes, 
                             const int& player_num);

  /**
   * Displays current turn of game.
   * @param position; position string should be at
   * @param first_player; whether player is the first player or not
   */
  static void DisplayTurns(const vec2& position, const bool& first_player);
};

} //namespace pool