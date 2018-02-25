#include "SensorManager.h"

//==============================================
// DELEGATES DECLARATIONS
//==============================================

void objectDeleteMSensor(EventData data);
void objectDeleteVSensor(EventData data);

SensorManager& SensorManager::getInstance() {
    static SensorManager instance;
    return instance;
}

void SensorManager::init() {

    EventManager::getInstance().addListener(EventListener {EventType::GameObject_Delete, objectDeleteVSensor});
    EventManager::getInstance().addListener(EventListener {EventType::GameObject_Delete, objectDeleteMSensor});

    distanceLoD = 100;

}

void SensorManager::update() {
    //This should call every time to all the sensors to update them.
    //Actually we dont have Environment, so we can't get the objects
    //from the map to be seen

    auto player = InputManager::getInstance().getComponent().get()->getGameObject();
    auto posPlayer = player.getTransformData().position;

    //Clean the list
    worldObjects.clear();

    fillWorldObjects();

    //CALCULATE LOD VISION SENSOR
    for(unsigned int i=0; i<sensorComponentList.size(); ++i)
    {
        auto AIObject = sensorComponentList[i]->getGameObject();
        auto posAI = AIObject.getTransformData().position; 

        auto distPlayerAI = (posPlayer.x - posAI.x) * (posPlayer.x - posAI.x) +
                            (posPlayer.y - posAI.y) * (posPlayer.y - posAI.y) +
                            (posPlayer.z - posAI.z) * (posPlayer.z - posAI.z);

        //IF DISTANCE PLAYER-AI IS BIGER THAN DISTANCELOD, NOT UPDATE
        if(distPlayerAI <= distanceLoD*distanceLoD)
        {
            auto sensor = std::dynamic_pointer_cast<VSensorComponent>(sensorComponentList[i]).get();
            updateVisionSensor(sensor);
        }
    }

    //CALCULATE LOD MAP SENSOR
    for(unsigned int i=0; i<sensorMComponentList.size(); ++i)
    {
        auto AIObject = sensorMComponentList[i]->getGameObject();
        auto posAI = AIObject.getTransformData().position; 

        auto distPlayerAI = (posPlayer.x - posAI.x) * (posPlayer.x - posAI.x) +
                            (posPlayer.y - posAI.y) * (posPlayer.y - posAI.y) +
                            (posPlayer.z - posAI.z) * (posPlayer.z - posAI.z);
                            
        //IF DISTANCE PLAYER-AI IS BIGER THAN DISTANCELOD, NOT UPDATE
        if(distPlayerAI <= distanceLoD*distanceLoD)
        {
            auto sensor = std::dynamic_pointer_cast<MSensorComponent>(sensorMComponentList[i]).get();
            updateMapSensor(sensor);
        }
    }

}

void SensorManager::close() {
    sensorComponentList.clear();
    sensorMComponentList.clear();
    worldObjects.clear();
}



//COMPONENT CREATORS
IComponent::Pointer SensorManager::createVSensorComponent(GameObject& newGameObject, float angV, float angI, float md, float ml){

    IComponent::Pointer component = std::make_shared<VSensorComponent>(newGameObject, angV, angI, md, ml);

    newGameObject.addComponent(component);

    EventData data;
    data.Component = component;

    SensorManager::getInstance().getComponentList().push_back(data.Component);
    data.Component.get()->init();

    EventManager::getInstance().addEvent(Event {EventType::VSensorComponent_Create, data});

    return component;
}

IComponent::Pointer SensorManager::createMSensorComponent(GameObject& newGameObject, float angV, float angI){

    IComponent::Pointer component = std::make_shared<MSensorComponent>(newGameObject, angV, angI);

    newGameObject.addComponent(component);

    EventData data;
    data.Component = component;

    SensorManager::getInstance().getMComponentList().push_back(data.Component);
    data.Component.get()->init();

    EventManager::getInstance().addEvent(Event {EventType::MSensorComponent_Create, data});

    return component;
}

//==============================================
// DELEGATES
//============================================== 

void objectDeleteVSensor(EventData eData) {

    auto& vSensorList = SensorManager::getInstance().getComponentList();

    for(unsigned int i = 0; i<vSensorList.size(); ++i) {
        if(eData.Id == vSensorList[i].get()->getGameObject().getId()) {
            vSensorList.erase(vSensorList.begin() + i);
            return;
        }
    }
}

void objectDeleteMSensor(EventData eData) {

    auto& MSensorList = SensorManager::getInstance().getMComponentList();

    for(unsigned int i = 0; i<MSensorList.size(); ++i) {
        if(eData.Id == MSensorList[i].get()->getGameObject().getId()) {
            MSensorList.erase(MSensorList.begin() + i);
            return;
        }
    }
}


//==============================================
// FILL LIST OF WORLD OBJECTS
//============================================== 

void SensorManager::fillWorldObjects()
{
    auto collisionList =  PhysicsManager::getInstance().getCollisionComponentList();
    for(unsigned int i = 0; i < collisionList.size(); ++i){
        if(collisionList[i] != nullptr)
        {
            worldObjects.push_back(std::dynamic_pointer_cast<CollisionComponent>(collisionList[i]).get()->getGameObject());
        }   
    }
}

//==============================================
// UPDATE VISION SENSOR
//============================================== 

void SensorManager::updateVisionSensor(VSensorComponent* sensor)
{
    if(sensor != nullptr)
    {
        sensor->updateSeenObjects(worldObjects);
    }
}

//==============================================
// UPDATE MAP SENSOR
//============================================== 

void SensorManager::updateMapSensor(MSensorComponent* sensor)
{
    if(sensor != nullptr)
    {
        sensor->updateMapCollisions();
    }
}