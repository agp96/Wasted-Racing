#include "ResourceManager.h"

TResourceMesh* ResourceManager::getResourceMesh(const char* n)
{
    unsigned int i;
    TResourceMesh* res=NULL;
    bool found = false;

    //First we look in memory loaded resources
    for(i=0; i<meshes.size() && found == false; i++)
    {
        if(strcmp(n, meshes[i]->getName()) == 0)
        {
            found = true;
            res=meshes[i];
        }
    }
    //If it's not loaded, we create a new resource and try to load it
    if(found == false)
    {
        res = new TResourceMesh();

        res->setName(n);
        if(res->loadResource())
        {
            meshes.push_back(res);
        }
    }
    
    return res;
}

TResourceMaterial* ResourceManager::getResourceMaterial(const char* n)
{
    unsigned int i;
    TResourceMaterial* res=NULL;
    bool found = false;

    //First we look in memory loaded resources
    for(i=0; i<materials.size() && found == false; i++)
    {
        if(strcmp(n, materials[i]->getName()) == 0)
        {
            found = true;
            res=materials[i];
        }
    }
    //If it's not loaded, we create a new resource and try to load it
    if(found == false)
    {
        res = new TResourceMaterial();

        res->setName(n);
        if(res->loadResource())
        {
            materials.push_back(res);
        }
    }
    
    return res;
}


TResourceTexture* ResourceManager::getResourceTexture(const char* n)
{
    unsigned int i;
    TResourceTexture* res=NULL;
    bool found = false;

    //First we look in memory loaded resources
    for(i=0; i<textures.size() && found == false; i++)
    {
        if(strcmp(n, textures[i]->getName()) == 0)
        {
            found = true;
            res=textures[i];
        }
    }
    //If it's not loaded, we create a new resource and try to load it
    if(found == false)
    {
        res = new TResourceTexture();

        res->setName(n);
        if(res->loadResource())
        {
            textures.push_back(res);
        }
    }
    
    return res;
}

TResourceShader* ResourceManager::getResourceShader(const char* n, GLenum e)
{
    unsigned int i;
    TResourceShader* res=NULL;
    bool found = false;

    //First we look in memory loaded resources
    for(i=0; i<shaders.size() && found == false; i++)
    {
        if(strcmp(n, shaders[i]->getName()) == 0)
        {
            found = true;
            res=shaders[i];
        }
    }
    //If it's not loaded, we create a new resource and try to load it
    if(found == false)
    {
        res = new TResourceShader(type);

        res->setName(n);
        res->setShaderType(e);
        if(res->loadResource())
        {
            shaders.push_back(res);
        }
    }
    
    return res;
}

TResourceOBJ* ResourceManager::getResourceOBJ(const char* n)
{
    unsigned int i;
    TResourceOBJ* res=NULL;
    bool found = false;

    //First we look in memory loaded resources
    for(i=0; i<objs.size() && found == false; i++)
    {
        if(strcmp(n, objs[i]->getName()) == 0)
        {
            found = true;
            res=objs[i];
        }
    }
    //If it's not loaded, we create a new resource and try to load it
    if(found == false)
    {
        res = new TResourceOBJ();

        res->setName(n);
        if(res->loadResource())
        {
            objs.push_back(res);
        }
    }
    
    return res;
}