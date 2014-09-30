/**
 * \class  GameStateData
 * \file   GameStateData.h
 * \author Daniel Holmes & Jonathan Gerrand
 * \date   29 September 2014
 * \brief  Abstract-Base class responsible for defining the interface for
 *         handling all game-runtime variables: player score etc.
 */

#ifndef GAMESTATEDATA_H_
#define GAMESTATEDATA_H_

class GameStateData
{
public:
    ///
    virtual void increaseP1Score() = 0;
    ///
    virtual void increaseP2Score() = 0;
    ///
    virtual void setP1Respawn() = 0;
    ///
    virtual void setP2Respawn() = 0;
    ///
    virtual void disableP1Respawn() = 0;
    ///
    virtual void disableP2Respawn() = 0;
    ///
    virtual const bool isP1Respawn() = 0;
    ///
    virtual const bool isP2Respawn() = 0;
    ///
    virtual const bool isGameFinished() = 0;
    ///
    virtual void setGameFinished() = 0;
    ///
    virtual ~GameStateData() {};

private:

};

#endif // GAMESTATEDATA_H_
