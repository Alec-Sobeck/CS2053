
#include "player.h"

/**
* Creates a new Entity and assigns it the provided entityID, model, and camera.
* @param entityID an int which must uniquely identify this Entity. It is suggested that this
* be a value generated from {@link #getNextEntityID()}
* @param model a Model that will be used for this entity
* @param camera a Camera that will be used for this entity
*/
Player::Player(Camera camera) : Entity(std::shared_ptr<Model>(nullptr), camera), ammoCount(20), healingItemCount(3)
{
}

Player::~Player()
{
}

