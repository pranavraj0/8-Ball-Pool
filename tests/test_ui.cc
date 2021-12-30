#include <catch2/catch.hpp>

#include "app_ui.h"
#include "pocket.h"

using pool::AppUI;
using pool::Pocket;
using glm::vec2;
using std::vector;

TEST_CASE("Making sure UI correctly creates pockets") {
  AppUI ui(vec2(0, 0), 200, 100);
  vector<Pocket> pockets = {Pocket(2.5, vec2(57.5, 27.5)),
                            Pocket(2.5, vec2(100, 27.5)),
                            Pocket(2.5, vec2(142.5, 27.5)),
                            Pocket(2.5, vec2(57.5, 72.5)),
                            Pocket(2.5, vec2(100, 72.5)),
                            Pocket(2.5, vec2(142.5, 72.5))};
  for (int i = 0; i < pockets.size(); i++) {
    REQUIRE(pockets[i].GetRadius() == ui.GetPockets()[i].GetRadius());
    REQUIRE(pockets[i].GetPosition() == ui.GetPockets()[i].GetPosition());
  }
}
