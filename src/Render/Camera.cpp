#include "Camera.h"
#include "../Game/Game.h"
#include "../Manager/Impl/SceneManager.h"
#include "../Manager/Impl/ConfigManager.h"
#include "../Component/Impl/CompTransform.h"

void Camera::DoRender()
{
    CalculateCenterAndBound();
}

void Camera::CalculateCenterAndBound()
{
    // calculate center = player world position
    auto pPlayer = Game::GetManager<SceneManager>()->GetPlayerEntity();
    if (pPlayer == nullptr)
        return;

    auto pPlayerTrans = pPlayer->GetComponent<CompTransform>();
    if (pPlayerTrans == nullptr)
        return;

    _currentCenterInWorldCoord = pPlayerTrans->GetPosition();

    // calculate world coordinate bound
    auto cameraRectSize = Game::GetManager<ConfigManager>()->GetGlobalSetting().cameraRectWorldCoordinateSize;
    _currentLeftTopInWorldCoord = vec2f { 
        _currentCenterInWorldCoord.x - cameraRectSize.x / 2, 
        _currentCenterInWorldCoord.y + cameraRectSize.y / 2 
        };

    _currentRightBottomInWorldCoord = vec2f { 
        _currentCenterInWorldCoord.x + cameraRectSize.x / 2, 
        _currentCenterInWorldCoord.y - cameraRectSize.y / 2 
        };
}