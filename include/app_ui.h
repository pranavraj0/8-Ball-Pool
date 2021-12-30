#pragma once

#include "cinder/gl/gl.h"
#include "ball.h"
#include "table.h"
#include "pocket.h"
#include "vector"
#include "pool_balls.h"
#include "cue.h"
#include "display.h"

namespace pool {

using std::vector;

class AppUI {
 public:
  AppUI(const double& window_width, 
        const double& window_length);
  
  /**
   * Draws all aspects of pool game.
   */
  void Draw();

  /**
   * Updates state of game. 
   */
  void AdvanceOneFrame();

  /**
   * Updates positions of balls.
   * @param ball; ball to be updated
   */
  void UpdateBall(Ball& ball);
  
  /**
   * Collides ball with another.
   * @param to_collide; ball to be collided
   */
  void CollideBalls(Ball& to_collide);

  /**
   * Reduces velocity of all balls after each turn. Basically friction. 
   */
  void ReduceVelocity();

  /**
   * Sets solid and stripes for players
   * @param ball; first ball hit in
   */
  void SetSolidsAndStripes(const Ball& ball);

  /**
   * Handles collision with cue
   */
  void HandleCueCollision();

  /**
   * Handles when ball is scored
   * @param ball; ball scored
   * @param current_index; index in vector of ball
   */
  void HandleScoredBall(Ball& ball, const int& current_index);

  /**
   * Handles switching turns after every round
   */
  void HandleSwitchingTurns();
  
  /**
   * Designates pointer to cue ball.
   */
  void DesignateCueBall();

  /**
   * Creates and sets pockets of game
   */
  void CreatePockets();

  /**
   * Creates set of balls with position using text file.
   * @param ball_data; text file path
   */
  void CreateBalls(const std::string& ball_data);

  /**
   * Checks whether balls are moving or not.
   * @return; whether moving
   */
  bool AreBallsStill() const;
  
  /**
   * Makes cue follow mouse
   * @param coords; coords of mouse
   */
  void Follow(const vec2& coords);
  
  /**
   * Tells whether mouse coordinates are within pool table
   * @param coords; mouse
   * @return; whether mouse is in table
   */
  bool AreCoordinatesInWindow(const vec2& coords) const;
  
  /**
   * Powers up cue stick.
   */
  void PowerUp();
  
  /**
   * Resets cue stick power.
   */
  void ResetPower();
  
  /**
   * Shoots cue ball.
   */
  void Shoot();
  
  void CreateIndicator();
  
  void DrawVelocityLine(const Ball& ball);
  
  void DrawIndicator();
  
  void AdjustForWalls();
  
  //Getter
  vector<Pocket> GetPockets() const;
 private:
  //Width of UI
  double width_;
  //Length of UI
  double length_;
  //Length, width, and margin of table
  double table_length_;
  double table_width_;
  double table_margin_;

  //Processed balls to be used on table.
  vector<Ball> processed_;
  //Pockets in table
  vector<Pocket> pockets_;
  //Pointer to cue ball
  Ball *cue_ball_;
  //Table to be played on
  Table table_;
  //Display for first and second players
  BallDisplay first_player_;
  BallDisplay second_player_;
  //Cue used
  Cue cue_;
  //Angle of cue
  double angle;
  //Current mouse coordinates
  vec2 current_coords_;
  //Total pixels pulled back when pulling cue back
  int pixels_pulled;

  //Whether ball was shot
  bool shot_;
  //Tells how many shots were shot
  int shot_counter_;
  //Whether cue was hit into pocket
  bool cue_hit_;

  //Max number of balls
  const int max_size_ = 16;
  //Current number of balls on table
  int current_size_;
  //Previous number of balls on table
  int previous_size_;
  //Number of balls pocketed in 1 turn
  int balls_removed_;

  //Whether first player turn
  bool first_player_turn_;
  //Whether first or second player are stripes or solids
  bool first_player_stripes_;
  bool second_player_stripes_;
  //Vector of balls which are scored by first and second players
  vector<Ball> first_player_scored_;
  vector<Ball> second_player_scored_;
  //Vector of all scored balls
  vector<Ball> scored_;
};

} //namespace pool