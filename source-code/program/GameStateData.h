//! An Abstract-based class providing an interface for game state data containing classes
/*! This class is used as a interface-parent for a classes which will hold game data (score etc)
    for the game. It defines an array of pure virtual getters and setters which can
    be implemented in various ways for versitiliy.
    \file       GameStateData.h
    \author     Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date       29 September 2014
 */

#ifndef GAMESTATEDATA_H_
#define GAMESTATEDATA_H_

class GameStateData
{
public:
    /// Increment player 1's score by one
    virtual void increaseP1Score() = 0;
    /// Increment player 2's score by one
    virtual void increaseP2Score() = 0;
    /// Retrieve player 1's score
    virtual const int getP1Score() = 0;
    /// Retrieve player 2's score
    virtual const int getP2Score() = 0;
    /// Allow P1 to be respawed again
    virtual void setP1Respawn() = 0;
    /// Allow P2 to be respawned again
    virtual void setP2Respawn() = 0;
    /// Disallow P1 to be respawned
    virtual void disableP1Respawn() = 0;
    /// Disallow P2 to be respawned again
    virtual void disableP2Respawn() = 0;
    /// Chech to see if P1 can be respawned
    virtual const bool isP1Respawn() = 0;
    /// Check to see if P2 can be respawned
    virtual const bool isP2Respawn() = 0;
    /// Check to see if the game has reached an end state
    virtual const bool isGameFinished() = 0;
    /// Set the game to a finnished state
    virtual void setGameFinished() = 0;
    /// Update the game time for rendering
    virtual void setGameTime(const float game_time) = 0;
    /// Provide the current game time
    virtual const float getGameTime() = 0;
    /// Destructor
    virtual ~GameStateData() {};

private:

};

#endif // GAMESTATEDATA_H_
