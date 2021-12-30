#include "app_ui.h"
#include "ui.h"

namespace pool {

AppUI::AppUI(const double& window_width,
             const double& window_length)
    : width_(window_width),
      length_(window_length) {
  //Standard to make it fit well in window and look good
  table_width_ = width_ / 2;
  table_length_ = (.6 * table_width_);
  table_margin_ = (table_length_ / 8);

  //Creates pockets
  CreatePockets();
  //Creates balls
  CreateBalls("/Users/pranavrajaraman/Cinder/my-projects/final-project-"
              "doofnav/data/ball_data.txt");
  DesignateCueBall();
  table_ = Table(table_length_, table_width_, table_margin_, length_, width_);
  first_player_ = BallDisplay(vec2(355.25, 650),
                              7, 10.5);
  second_player_ = BallDisplay(vec2(903, 650), 
                               7, 10.5);
  cue_ = Cue(table_length_ / 1.5, table_length_ / 40);
  cue_.SetStartingPosition(vec2(cue_ball_->GetXPosition(), 
                                cue_ball_->GetYPosition()), 
                           cue_ball_->GetRadius());
  pixels_pulled = 0;
  
  shot_ = false;
  shot_counter_ = 0;
  cue_hit_ = false;

  current_size_ = max_size_;
  previous_size_ = max_size_;
  balls_removed_ = 0;
  
  first_player_turn_ = true;
  first_player_stripes_ = false;
  second_player_stripes_ = false;
}

void AppUI::Draw() {
  //Displaying player's side for next week
  if (first_player_stripes_ || second_player_stripes_) {
    UI().DisplayStripes(vec2(25, 100), first_player_stripes_, 1);
    UI().DisplayStripes(vec2(700, 100), second_player_stripes_, 2);
  }
  //Creates indicator from cue to show where ball will go
  if (AreBallsStill()) {
    CreateIndicator();
  }
  //Displays ball display for both players
  first_player_.Display();
  second_player_.Display();
  
  //Goes through each pocket and displays
  for (const Pocket& pocket: pockets_) {
    pocket.Display();
  }
  
  //Displays balls
  for (const Ball& ball: processed_) {
    ball.Display();
  }
  
  //After each turn, resets cue stick position to align with cue ball
  //Only displays if balls aren't moving
  if (AreBallsStill()) {
    if (shot_) {
      cue_.SetCuePositionWithAngle(vec2(cue_ball_->GetXPosition(),
                                        cue_ball_->GetYPosition()), 
                                   cue_ball_->GetRadius(), angle);
      shot_ = false;
    }
    cue_.Display();
  }
  table_.Display();
}

void AppUI::AdvanceOneFrame() {
  //Either collides or updates all balls
  for (int i = 0; i < processed_.size(); i++) {
    if (processed_[i].WillCollideEver(processed_)) {
      CollideBalls(processed_[i]);
    } else {
      UpdateBall(processed_[i]);
    }
    //Velocity is reduced for every ball.
    ReduceVelocity();
    
    for (const Pocket& pocket: pockets_) {
      //If any balls will collide with pocket...
      if (processed_[i].WillBallPocketCollide(pocket)) {
        //If first ball scored, sets first and second player sides
        if (processed_.size() == max_size_) {
          SetSolidsAndStripes(processed_[i]);
        }
        //If ball to be scored is cue, handles that.
        if (processed_[i].IsCue()) {
          HandleCueCollision();
          //If 8 ball, should either win or lose game.
        } else if (processed_[i].IsBlack()) {
          if (first_player_turn_) {
            if (first_player_scored_.size() != 7) {
              //you lose
              //display message
              //end game
            } else {
              //win; end game
            }
          } else {
            if (second_player_scored_.size() != 7) {
              //you lose.
            } else {
              //win
            }
          }
        } else {
          //Otherwise, handles normal ball scored
          HandleScoredBall(processed_[i], i);
        }
      }
    }
    //After, switches turns based on what occurred in round
    HandleSwitchingTurns();
  }
}

void AppUI::UpdateBall(Ball& ball) {
  //Gets position and velocity
  vec2 position = vec2(ball.GetXPosition(), ball.GetYPosition());
  vec2 velocity = vec2(ball.GetXVelocity(), ball.GetYVelocity());
  double radius = ball.GetRadius();
  //Checks if balls will collide with walls
  if ((position.x + radius >= 997.5 && velocity.x > 0) ||
      (position.x - radius <= 402.5 && velocity.x < 0)) {
    //Negates velocity in direction of wall
    velocity = vec2(-velocity.x, velocity.y);
  } else if ((position.y + radius >= 557.5 && velocity.y > 0) ||
             (position.y - radius <= 242.5 && velocity.y < 0)) {
    //Negates velocity in direction of wall
    velocity = vec2(velocity.x, -velocity.y);
  }
  //Sets new position and velocity and updates
  ball.SetVelocity(velocity);
  ball.SetPosition(position + velocity);
}

void AppUI::CollideBalls(Ball& to_collide) {
  for (Ball &ball : processed_) {
    //checks if collision is possible
    if (to_collide.WillTwoCollide(ball)) {
      //only updates velocities
      vec2 new_velocity_first = vec2(to_collide.GetVelocityBallCollisionX(ball), 
                                     to_collide.GetVelocityBallCollisionY(ball));
      vec2 new_velocity_other = vec2(ball.GetVelocityBallCollisionX(to_collide), 
                                     ball.GetVelocityBallCollisionY(to_collide));
      to_collide.SetVelocity(new_velocity_first);
      ball.SetVelocity(new_velocity_other);
    }
  }
}

void AppUI::ReduceVelocity() {
  for (Ball& ball: processed_) {
    //Reduces velocity
    ball.SetVelocity({.999 * ball.GetXVelocity(), .999 * ball.GetYVelocity()});
    //Sometimes balls don't stop so...
    if (abs(ball.GetXVelocity()) < .15 && abs(ball.GetYVelocity()) < .15) {
      ball.SetVelocity({0, 0});
    }
  }
}

void AppUI::SetSolidsAndStripes(const Ball& ball) {
  //If a number ball...
  if (!ball.IsCue() && !ball.IsBlack()) {
    if (ball.IsSolid()) {
      if (first_player_turn_) {
        second_player_stripes_ = true;
      } else {
        first_player_stripes_ = true;
      }
    } else {
      if (first_player_turn_) {
        first_player_stripes_ = true;
      } else {
        second_player_stripes_ = true;
      }
    }
  }
}

void AppUI::HandleCueCollision() {
  //Sets cue velocity, then resets position of cueball and cue.
  cue_hit_ = true;
  cue_ball_->SetVelocity({0, 0});
  cue_ball_->SetPosition(vec2(350 + table_margin_ + 
                                  (table_width_ - 2 * table_margin_) / 4, 400));
  cue_.SetCuePositionWithAngle(vec2(350 + table_margin_ + 
                                    (table_width_ - 2 * table_margin_) / 4), 
                               cue_ball_->GetRadius(), angle);
}

void AppUI::HandleScoredBall(Ball& ball, const int& current_index) {
  //When ball is scored, based on situation, adds to proper vector.
  if (first_player_stripes_) {
    if (ball.IsSolid()) {
      second_player_.Update(ball);
      scored_.push_back(ball);
      second_player_scored_.push_back(std::move(ball));
    } else {
      first_player_.Update(ball);
      scored_.push_back(ball);
      first_player_scored_.push_back(std::move(ball));
    }
  } else {
    if (ball.IsSolid()) {
      first_player_.Update(ball);
      scored_.push_back(ball);
      first_player_scored_.push_back(std::move(ball));
    } else {
      second_player_.Update(ball);
      scored_.push_back(ball);
      second_player_scored_.push_back(std::move(ball));
    }
  }
  //Removes scored balls from the main vector of balls
  processed_.erase(processed_.begin() + current_index);
  current_size_--;
  balls_removed_++;
}

void AppUI::HandleSwitchingTurns() {
  //If shot has occurred
  if (shot_counter_ > 0) {
    //If balls not moving
    if (AreBallsStill()) {
      //If balls are actually scored
      if (balls_removed_ > 0) {
        //If cue hit, switches turns
        if (cue_hit_) {
          first_player_turn_ = !first_player_turn_;
          cue_hit_ = false;
          //Checks first ball scored by player and if its their color, turn stays
          //If opposite color, turn switches
        } else if (first_player_turn_) {
          if (first_player_stripes_) {
            if (scored_[scored_.size() - balls_removed_].IsSolid()) {
              first_player_turn_ = !first_player_turn_;
            } else {
              previous_size_ -= balls_removed_;
            }
          } else {
            if (scored_[scored_.size() - balls_removed_].IsSolid()) {
              previous_size_ -= balls_removed_;
            } else {
              first_player_turn_ = !first_player_turn_;
            }
          }
        } else if (!first_player_turn_) {
          if (first_player_stripes_) {
            if (scored_[scored_.size() - balls_removed_].IsSolid()) {
              previous_size_ -= balls_removed_;
            } else {
              first_player_turn_ = !first_player_turn_;
            }
          } else {
            if (scored_[scored_.size() - balls_removed_].IsSolid()) {
              first_player_turn_ = !first_player_turn_;
            } else {
              previous_size_ -= balls_removed_;
            }
          }
        }
        //If none of the above occurs, switches turns
      } else {
        first_player_turn_ = !first_player_turn_;
      }
      //Resets counters
      shot_counter_ = 0;
      balls_removed_ = 0;
    }
  }
}

void AppUI::DesignateCueBall() {
  //Sets pointer to cue ball
  for (Ball& ball: processed_) {
    if (ball.IsCue()) {
      cue_ball_ = &ball;
    }
  }
}

void AppUI::CreatePockets() {
  //Assigns radius based on table.
  double radius = table_margin_ / 3;
  //Top left corner for top three pockets
  vec2 top_left = vec2(table_width_ / 2, (length_ - table_length_) / 2) + 
                  vec2(table_margin_, table_margin_);
  //Creates top three
  for (int i = 0; i < 3; i++) {
    Pocket pocket(radius, top_left);
    pockets_.push_back(pocket);
    top_left += vec2((table_width_ - 2 * table_margin_) / 2, 0);
  }
  //Top left corner for bottom three pockets
  //Creates bottom three
  top_left = vec2(table_width_ / 2, (length_ - ((length_ - table_length_) 
                                                / 2) - 2 * table_margin_)) + 
             vec2(table_margin_, table_margin_);
  for (int i = 0; i < 3; i++) {
    Pocket pocket(radius, top_left);
    pockets_.push_back(pocket);
    top_left += vec2((table_width_ - 2 * table_margin_) / 2, 0);
  }
}

void AppUI::CreateBalls(const std::string& ball_data) {
  std::ifstream input_file(ball_data);
  std::string line;
  std::vector<std::string> current_ball;
  std::vector<std::vector<std::string>> all_balls;
  vector<Ball> balls;
  //Adds strings with ball info to current ball
  while (getline(input_file, line)) {
      current_ball.push_back(line);
      if (current_ball.size() == 6) {
        //Once info is in one vector, clears it and moves to next ball.
        all_balls.push_back(current_ball);
        current_ball.clear();
      }
  }
  //Goes through each vector of strings and creates ball objects
  for (const vector<std::string>& ball: all_balls) {
    bool cue = false;
    if (ball[0] == "true") {
      cue = true;
    }
    bool solid = false;
    if (ball[1] == "true") {
      solid = true;
    }
    bool black = false;
    if (ball[2] == "true") {
      black = true;
    }
    int number = std::stoi(ball[3]);
    vec2 racking = vec2(std::stoi(ball[4]), std::stoi(ball[5]));
    Ball to_add(cue, solid, black, number, racking);
    balls.push_back(to_add);
  }
  //Doesn't carry on variables for some reason
  //Creates set of pool balls, which processes and adds position to each ball
  PoolBalls create(balls, table_width_, 
                   table_length_, table_margin_, width_, length_);
  processed_ = create.GetProcessed();
}

bool AppUI::AreBallsStill() const {
  //Checks if all balls are stilll.
  for (const Ball& ball: processed_) {
    if (vec2(ball.GetXVelocity(), ball.GetYVelocity()) != vec2(0, 0)) {
      return false;
    }
  }
  return true;
}

void AppUI::Follow(const vec2& coords) {
  //If mouse is in table...
  if (AreCoordinatesInWindow(coords)) {
    //Adjusts cue according to angle.
    double y = (cue_ball_->GetYPosition() - coords.y);
    double x = (cue_ball_->GetXPosition() - coords.x);
    angle =  (atan2(y, x) - M_PI);
    cue_.SetPosition(vec2(cue_ball_->GetXPosition(), cue_ball_->GetYPosition()), angle);
    current_coords_ = coords;
  }
}

bool AppUI::AreCoordinatesInWindow(const vec2& coords) const{
  double to_table = (width_ - table_width_) / 2;
  double to_top = (length_ - table_length_) / 2;
  if (coords.x >= to_table && coords.x <= to_table + table_width_) {
    if (coords.y >= to_top && coords.y <= to_top + table_length_) {
      return true;
    }
  }
  return false;
}

void AppUI::PowerUp() {
  //Powers up cue stick
  if (pixels_pulled < 50) {
    cue_.PullBack(5);
    pixels_pulled +=5;
  }
}

void AppUI::ResetPower() {
  //Resets power on cue
  if (pixels_pulled > 0) {
    cue_.PullBack(-pixels_pulled);
    pixels_pulled = 0;
    cue_.SetVelocity({0, 0});
  }
}

void AppUI::Shoot() {
  //Resets power and shoots cue ball
  if (pixels_pulled > 0) {
    cue_.PullBack(-pixels_pulled);
    pixels_pulled = 0;
    shot_ = true;
    cue_ball_->SetVelocity(vec2(cue_.GetXVelocity(), -cue_.GetYVelocity()));
    cue_.SetVelocity({0, 0});
    shot_counter_++;
  }
}

void AppUI::CreateIndicator() {
  //Uses last saved mouse coordinates and adjusts them if they reach beyond the wall.
  AdjustForWalls();
  for (const Ball& ball: processed_) {
    //If indicator ball is close enough to another ball..
    if (!ball.IsCue()) {
      if (glm::distance(vec2(ball.GetXPosition(), ball.GetYPosition()), current_coords_) < 22) {
        //Adjusts current coordinates to not be inside other ball's radius.
        while (glm::distance(vec2(ball.GetXPosition(), ball.GetYPosition()), current_coords_) < 21) {
          double new_x = current_coords_.x - (sin((M_PI / 2) + angle));
          double new_y = current_coords_.y + (sin(-angle));
          current_coords_ = vec2(new_x, new_y);
        }
        //Draws line velocity of ball.
        DrawVelocityLine(ball);
      }
    }
  }
  //Draws line showing path of ball.
  DrawIndicator();
}

void AppUI::AdjustForWalls() {
  double x_distance = ((width_ - table_width_) / 2) + table_margin_;
  double y_distance = ((length_ - table_length_) / 2) + table_margin_;
  double radius = cue_ball_->GetRadius();
  //Takes current coordinates, and puts it within wall
  if (current_coords_.x > width_ - x_distance - radius) {
    current_coords_.x = width_ - x_distance - radius;
  }
  if (current_coords_.x < x_distance + radius) {
    current_coords_.x = x_distance - radius;
  }
  if (current_coords_.y < y_distance + radius) {
    current_coords_.y = y_distance + radius;
  }
  if (current_coords_.y > length_ - y_distance - radius) {
    current_coords_.y = length_ - y_distance - radius;
  }
}

void AppUI::DrawVelocityLine(const Ball& ball) {
  //Finds velocity after collision, and draws velocity indicator
  vec2 vel = vec2{5 * cos(-angle),  -5 * sin(-angle)};
  Ball helper = Ball();
  helper.SetPosition(current_coords_);
  helper.SetVelocity(vel);
  double ball_vel_x = ball.GetVelocityBallCollisionX(helper);
  double ball_vel_y = ball.GetVelocityBallCollisionY(helper);
  vec2 ball_indicator = vec2(ball.GetXPosition(), ball.GetYPosition()) + vec2(ball_vel_x, ball_vel_y);
  ci::gl::color(ci::Color("white"));
  ci::gl::drawLine(current_coords_, ball_indicator);
}

void AppUI::DrawIndicator() {
  //Draws regular indicator
  ci::gl::color(ci::Color("white"));
  ci::gl::drawLine(vec2(cue_ball_->GetXPosition(), cue_ball_->GetYPosition()), current_coords_);
  ci::gl::drawStrokedCircle(current_coords_, cue_ball_->GetRadius());
}

//Getter
vector<Pocket> AppUI::GetPockets() const {
  return pockets_;
}

} // namespace pool