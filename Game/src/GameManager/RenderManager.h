#pragma once

#include "../GameFacade/IRenderFacade.h"
#include "QuadTree.h"
#include <vector>

class RenderManager{

public: 

    //Constructor
    RenderManager() {}

    //Destructor
    ~RenderManager() {
        delete renderFacade;
    }

    //Initialization
    void init(int engine);

    //Update
    void update(float dTime);

    //Draw
    void draw();

    //Shutdown
    void close();

    //Take the vector and split it in a quadTree
    void splitQuadTree();

    //Static class getter
    static RenderManager& getInstance();

    //Component list getter
    std::vector<IComponent::Pointer>& getComponentList() {
        return renderComponentList;
    }

    //QuadTree getter
    QuadTree& getComponentTree() {
        return renderComponentTree;
    }

    //Get render facade functions
    IRenderFacade* getRenderFacade() {
        return renderFacade;
    }

    IComponent::Pointer createObjectRenderComponent(GameObject& newGameObject, ObjectRenderComponent::Shape newShape, const char* newStr);
    IComponent::Pointer createLightRenderComponent(GameObject& newGameObject, LightRenderComponent::Type newType, float newRadius);
    IComponent::Pointer createCameraRenderComponent(GameObject& newGameObject);
    //Create cylinder or cone
    IComponent::Pointer createObjectRenderComponent(GameObject& newGameObject, ObjectRenderComponent::Shape newShape, const char* newStr, float radius, float length, int tesselation, bool transparency);
    //Camera component getter and setter
    IComponent::Pointer getCameraComponent() { return cameraComponent; }
    void setCameraComponent( IComponent::Pointer cam ) { cameraComponent = cam; }

    //==============================================
    // VISUAL INTERFACE
    //==============================================
    
    /////////////
    //  IMAGES
    /////////////

    //Adds a rectangle on the specific point given with the specified image
    int32_t createImage(std::string img, glm::vec2 pos);

    //Delete image specified by its id
    void deleteImage(int32_t id);

    //Delete images specified inside the vector of ids
    void deleteImages(std::vector<int32_t>* ids);

    //Clean images off of the visual interface
    void cleanImages();

    /////////////
    //  COLOR RECTANGLES
    /////////////

    //Add rectangle of the given color and alpha channel, at the specified position with the given size
    int32_t createRectangleColor(glm::vec2 pos, glm::vec2 size, int r = 255, int g = 255, int b = 255, int a = 255);

    //Change color of the rectangle known by the id given
    void changeRectangleColor(int32_t id, int r, int g, int b, int a);
    
    //Deletes the rectangle with the passed id
    void deleteRectangleColor(int32_t id);

    //Clean all rectangles off of the screen
    void cleanRectangles();

    /////////////
    //  TEXT
    /////////////

    //Add specified text in the specified point
    int32_t createText( std::string text, glm::vec2 pos = glm::vec2(0,0), int r = 255, int g = 255, int b = 255, int a = 255, glm::vec2 size = glm::vec2(20,50), std::string fontFile = "");

    //Change the specified text with the given message
    void changeText(int32_t id, std::string text);

   //Changes the font of the game
    void changeFontText(int32_t id, std::string fontFile);

    //Changes the color of the text specified by the id
    void changeColorText(int32_t id, int r, int g, int b, int a);

    //Changes the color of the background of the text specified by the id
    void changeBackgroundColorText(int32_t id, int r, int g, int b, int a);

    //Delete text with the specified id
    void deleteText(int32_t id);

    //Delete texts within the array of idss
    void deleteTexts(std::vector<int32_t>* ids);

    //Erase all text from the screen
    void cleanTexts();

    //Erase all interface elements off of the screen
    void cleanVI();

    //==============================================
    // GETTERS AND SETTERS
    //==============================================
    void setDebugState(bool d){ debugState = d; };
    
    //AI Debug
    void renderAIDebug();
    void updateAIDebug();
    void createRenderNPC(); 
    void deleteRenderNPC(); 
    void createLinesObjects();
    void deleteLinesObjects();

    //Camera Debug
    void renderCameraDebug();
    void updateCameraDebug();
    void createCameraRender();
    void deleteCameraRender();

    //Debug Behaviour
    void renderBattleDebug();
    void updateBattleDebug(float dTime);
    void createBattleRender();
    void deleteBattleRender();
    void setRootBattle(std::string r)                  {          root += " -> "+r;         }
    void setEndRootBattle(bool b)                      {          end = b;                  }
    bool getEndRootBattle()                            {          return end;               }
    void setWaitBattle(bool b)                         {          wait = b;                 }
    bool getWaitBattle()                               {          return wait;              }
    bool getLapBattle()                                {          return lapB;              }
    int getAINumberBattle()                            {          return AIDebugB;         }
    std::vector<GameObject> getAIsBattle()             {          return AIDebugPointB;     }
    
private:
    //==============================================================
    // PRIVATE DATA
    //==============================================================
    //Render facade
    IRenderFacade* renderFacade;

    //Debug state checker
    bool debugState;

    //When we start adding components, we add them in a list,
    //Once we've added them all, we split them in a QuadTree structure
    std::vector<IComponent::Pointer>      renderComponentList;
    QuadTree                              renderComponentTree;

    //Data for the quadTree
    //unsigned int maxObjPerNode;
    //int          updateRange;
    //int          x0, x1, y0, y1; //Map dimensions

    //We store just one camera component, so we can't have more than 1
    IComponent::Pointer cameraComponent;

    //Debug IA
    unsigned int AIDebug = 0;
    bool lap = false;
    std::vector<GameObject> AIDebugPoint;
    GameObject::Pointer marker;
    GameObject::Pointer collisionCylinder;
    GameObject::Pointer visibilityArea;
    GameObject::Pointer visionTriangle;
    std::vector<GameObject::Pointer> linesObjects;
    float moveSeen = 0;
    float maxMoveSeen = 20.0;
    float moveNextPos = 0;
    float maxMoveNextPos = 30.0;
    bool activeDebugAI = false;

    //Debug Camera
    unsigned int AIDebugC = 0;
    bool lapC = false;
    std::vector<GameObject> AIDebugPointC;
    GameObject::Pointer cameraVision;
    bool collisionC = false;
    int aux = 0;
    bool activeDebugCamera = false;

    //Debug Behaviour
    unsigned int AIDebugB = 0;
    bool lapB = false;
    std::vector<GameObject> AIDebugPointB;
    std::string title = "BEHAVIOUR";
    std::string root = "";
    bool end = false;
    bool activeDebugBehaviour = false;
    bool success = false;
    float timeP = 5.0f;
    float maxTimeP = 5.0f;
    bool wait = false;
    

};