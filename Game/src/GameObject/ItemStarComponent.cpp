#include "ItemStarComponent.h"



ItemStarComponent::ItemStarComponent(GameObject& newGameObject, GameObject& obj) : IItemComponent(newGameObject), player(obj)
{
    speed = 350.f;
    consTime = 8.f;
    decTime = 0.5f;
}

ItemStarComponent::~ItemStarComponent()
{

}

void ItemStarComponent::init()
{
    player.getComponent<MoveComponent>()->changeMaxSpeedOverTime(speed, consTime, decTime);
}

void ItemStarComponent::update(float dTime)
{
    
}

void ItemStarComponent::close()
{
    
} 
 
