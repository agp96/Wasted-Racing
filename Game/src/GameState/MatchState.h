#pragma once

#include "IGameState.h"
#include "../Game.h"
#include "../GameObject/GameObject.h"
#include "../GameObject/RenderComponent/ObjectRenderComponent.h"
#include "../GameObject/InputComponent.h"
#include "../GameObject/PhysicsComponent/MoveComponent.h"
#include "../GameObject/PhysicsComponent/RampComponent.h"
#include "../GameObject/ItemComponent/ItemBoxComponent.h"
#include "../GameObject/AIComponent/WaypointComponent.h"
#include "../GameManager/InputManager.h"
#include "../GameManager/RenderManager.h"
#include "../GameManager/ObjectManager.h"
#include "../GameManager/PhysicsManager.h"
#include "../GameManager/WaypointManager.h"
#include "../GameManager/AIManager.h"
#include "../GameManager/SensorManager.h"
#include "../GameManager/AudioManager.h"
#include "../GameManager/ScoreManager.h"
#include "../GameManager/ItemManager.h"
#include "../GameEvent/EventManager.h"
#include "../GameFacade/AudioFMOD.h"

#include <memory>
#include <iostream>
#include <rapidxml/rapidxml.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>

class Game;
class AIManager;
class ObjectManager;
class ItemManager;
class SensorManager;

class MatchState : public IGameState {

public: 

    //Constructor
    MatchState (){ type = IGameState::MATCH; };

    //Destructor
    virtual ~MatchState() {}

    //Initialization
    virtual void init();

    //Updater
    virtual void update(float &accumulatedTime);

    //Update managers
    void updateManagers(float dTime);

    //Drawer
    virtual void draw();

    //Shutdown
    virtual void close();

    //Static class getter
    static MatchState& getInstance() {
        static MatchState instance;
        return instance;
    };

    //Game ratio
    void setRatio(float r)          {       ratio = r;      }
    float getRatio()                {       return ratio;   }

private:
    
    //==============================================================
    // Private data
    //==============================================================
    //Object manager
    ObjectManager* objectManager;
    //Input manager
    InputManager* inputManager;
    //Render manager
    RenderManager* renderManager;
    //Event manager
    EventManager* eventManager;
    //Physics manager
    PhysicsManager* physicsManager;
    //Waypoint manager
    WaypointManager* waypointManager;
    //Audio Manager
    AudioManager* audioManager;
    //AI manager
    AIManager* aiManager;
    //Sensor manager
    SensorManager* sensorManager;
    //Item manager
    ItemManager* itemManager;
    //Score manager
    ScoreManager* scoreManager;

    //Update's loop time
    const float loopTime = 1.0f/30.0f;

    //Game velocity
    float ratio = 1.0;

};