/**
 * \class  Turret
 * \file   Turret.h
 * \author Daniel Holmes & Jonathan Gerrand
 * \date   2 September 2014
 * \brief  Child composition class for all turrnet objects
 */

 #ifndef TURRET_H_
 #define TURRET_H_

 //Includes
 #include "Collidable.h"
 #include "Trackable.h"
 #include "Orientation.h"
 #include "Structures.h"
 #include "SpriteDimensions.h"

 //Throw exception defenitions
 class InvalidConstructorArgumentsTurret{};

class Turret: virtual public Collidable, public Trackable
{
public:

    ///Constructor
    Turret(float positionX, float positionY, float rotation);
    ///Provide type
    virtual const entity_type& getType() const;
    ///Determine the life state of the Turrent
    virtual const bool isDeleted();
    ///Retrieve the entity's x Position
    virtual const float getDrawPositionX();
    ///Retrieve the entity's y Position
    virtual const float getDrawPositionY();
    ///Retrieve the entity's Position
    virtual const float getDrawRotation();
      ///Get bounding box of entity
    virtual const rect_corners& getBoundingBox();
    ///Set blocked state of entity
    virtual const int setBlocked();
    ///Unset the blocked state of the entity
    virtual void setUnblocked();
    ///Set collision state of entity
    virtual void setCollided();
     ///Get the current x co-ordinates of Trackable object
    virtual const float getPositionX();
    ///Get the current y co-ordinates of Trackable object
    virtual const float getPositionY();
    ///Get the current orientation of Trackable object
    virtual const float getOrientation();
    ///Get the bounding box relevant for line-of-fire detection
    virtual const rect_corners& getTrackingBoundingBox();
    ///Rotates the Turret by its set value
    void rotateTurret();
    ///Destructor
    virtual ~Turret();

private:

    ///Collision state of the Turrent Entity: 1 for collided, 0 for not
    bool _collidedStatus;
    ///The angle of rotation for the Turrnet entity
    float _rotation;
    ///Co-ordinate system for the Turrnet
    Orientation _turret;
    ///Enumeration type defining the turrnet
    entity_type _type;
    ///Turrent Sprite Dimensions
    SpriteDimensions _sprite_dimensions;
    ///Default value for rotation rate
    const float _rotation_rate;

};

 #endif // TURRENT_H_
