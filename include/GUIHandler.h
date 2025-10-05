#pragma once
#include "ScreenDispatcher.h"
#include "Input.h"


class GUIHandler
{



public:
    ENGINE_API GUITextureManager& getTextureManager();

    ENGINE_API ScreenDispatcher& getScreenManager();

    
};
