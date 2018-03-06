#include "MultiMatchState.h"

//Additional functions
void createPlayer();

void MultiMatchState::init() {

    audioManager    = &AudioManager::getInstance();     //Initialize true audio manager
    eventManager    = &EventManager::getInstance();     //Initilize event manager
    renderManager   = &RenderManager::getInstance();    //First we initialize renderManager, who creates a device and passes this reference to the inputManager
    inputManager    = &InputManager::getInstance();     //Once we've initialized the renderManager, we can do the same with our inputManager
    objectManager   = &ObjectManager::getInstance();    //Initialize object manager
    waypointManager = &WaypointManager::getInstance();  //Initialize Waypoint Manager
    sensorManager   = &SensorManager::getInstance();    //Initialize Sensor manager
    physicsManager  = &PhysicsManager::getInstance();   //Initialize physics manager
    itemManager     = &ItemManager::getInstance();      //Initialize Sensor manager
    scoreManager    = &ScoreManager::getInstance();     //Initialize Score Manager
    networkManager  = &NetworkManager::getInstance();   //Initialize Sensor manager
    debugManager    = &DebugManager::getInstance();     //Initialize Debug manager
    
    Game::getInstance().setAccumulatedTime(0);
}

void MultiMatchState::update(float &accumulatedTime) {

    //No gelding
    inputManager->update();
    networkManager->update();
    debugManager->update();
    renderManager->update(accumulatedTime);
    
    //If time surpassed the loopTime
    if(accumulatedTime > loopTime){
        //Update managers
        updateManagers(accumulatedTime);
        Game::getInstance().setStay(objectManager->getGameRunning());
        accumulatedTime = 0;
    }

    //Always interpolate
    interpolate(accumulatedTime);

    //Event manager has to be the last to be updated
    eventManager->update();
}

void MultiMatchState::updateManagers(float dTime){
    
    scoreManager->update();

    audioManager->update();
}

void MultiMatchState::draw() {
    renderManager->draw();
}

void MultiMatchState::interpolate(float &accumulatedTime) {
    //Update each position in Render Manager
    for(unsigned int i=0; i<physicsManager->getMovingCharacterList().size(); ++i){
        //Interpolate every moving object
        RenderManager::getInstance().getRenderFacade()->updateObjectTransform(
                physicsManager->getMovingCharacterList()[i].moveComponent.get()->getGameObject().getId(), 
                physicsManager->getMovingCharacterList()[i].moveComponent.get()->getGameObject().getTransformData()
        );
    }

    //Update camera position
    renderManager->getRenderFacade()->interpolateCamera(accumulatedTime, loopTime);
}


void MultiMatchState::close() {

}