#include "WaypointManager.h"



//==============================================
// DELEGATES DECLARATIONS
//==============================================

void objectDeletePathPlanning(EventData eData);



WaypointManager& WaypointManager::getInstance() {
    static WaypointManager instance;
    return instance;
}

void WaypointManager::init() {
    listSubNodes = new std::vector<GameObject::Pointer>;

    EventManager::getInstance().addListener(EventListener {EventType::GameObject_Delete, objectDeletePathPlanning});
}

void WaypointManager::update(float dTime) {
    //I doubt this method should exist in this manager
    //I doubt it too
    //I hope Fran reads this

    for(int i = 0; i < pathPlanningComponentList.size(); i++)
    {
        auto iItemComponent = pathPlanningComponentList[i]->getGameObject().getComponent<IItemComponent>().get();
        if(iItemComponent == nullptr)
        {
            pathPlanningComponentList[i]->update(dTime); 
        }
    }
    
}

void WaypointManager::close() {
    waypointComponentList.clear();
    listSubNodes->clear();
}

IComponent::Pointer WaypointManager::createWaypointComponent(GameObject::Pointer newGameObject, float r, int lvl)
{
    IComponent::Pointer component = std::make_shared<WaypointComponent>(*newGameObject.get(), r, lvl);

    newGameObject.get()->addComponent(component);

    listSubNodes->push_back(newGameObject);
    
    return component;
}

IComponent::Pointer WaypointManager::createPathPlanningComponent(GameObject::Pointer newGameObject)
{
    IComponent::Pointer component = std::make_shared<PathPlanningComponent>(*newGameObject.get());

    newGameObject.get()->addComponent(component);

    pathPlanningComponentList.push_back(component);

    return component;
}


//==============================================
// DELEGATES
//============================================== 


//==============================================
//Constructor and Destructor
//==============================================

WaypointManager::WaypointManager()
{

}

WaypointManager::~WaypointManager()
{
//check how remove vector
    delete listSubNodes;
}

//==============================================
//Getters
//==============================================

std::vector<GameObject::Pointer> WaypointManager::getWaypoints()
{
    return *listSubNodes;
}


////////////////////////////////////////////
//
//      DELEGATES
//
////////////////////////////////////////////


void objectDeletePathPlanning(EventData eData) {

    auto& PathPlanningComponentList = WaypointManager::getInstance().getPathPlanningList();

    for(unsigned int i = 0; i<PathPlanningComponentList.size(); ++i) {
        if(eData.Id == PathPlanningComponentList.at(i).get()->getGameObject().getId()) {
            PathPlanningComponentList.erase(PathPlanningComponentList.begin() + i);
            return;
        }
    }
} 