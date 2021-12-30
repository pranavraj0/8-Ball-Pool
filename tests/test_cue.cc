#include <catch2/catch.hpp>

#include "cue.h"

using pool::Cue;
using glm::vec2;

TEST_CASE("Finding coordinates") {
  Cue cue(vec2(10, 10), 50, 10);
  SECTION("Outside of cue") {
    REQUIRE(vec2(0, 0) == cue.FindCoordinates(vec2(200, 200)));
  }
  SECTION("Inside cue") {
    REQUIRE(vec2(26, 20) == cue.FindCoordinates(vec2(26, 15)));
  }
}

TEST_CASE("Setting drag coordinates") {
  Cue cue(vec2(10, 10), 50, 10);
  cue.SetDrag(vec2(40, 15));
  SECTION("Checking coordinates") {
    REQUIRE(vec2(40, 20) == cue.GetDragCoordinates());
  }
  SECTION("Checking that distances to ends of cue are correct") {
    REQUIRE(30 == cue.GetXDistance());
    REQUIRE(10 == cue.GetYDistance());
  }
}

TEST_CASE("Checking that cue pulls back and forth properly") {
  Cue cue(vec2(10, 10), 50, 10);
  cue.SetDrag(vec2(40, 15));
  cue.PullBack(vec2(26, 15));
  SECTION("Checking that top left and bottom right properly update") {
    REQUIRE(vec2(-4, 10) == cue.GetTopLeft());
    REQUIRE(vec2(46, 20) == cue.GetBottomRight());
  }
}