#include "Camera.h"
#include "../Game/Game.h"
#include "../Manager/Impl/SceneManager.h"
#include "../Manager/Impl/ConfigManager.h"
#include "../Component/Impl/CompTransform.h"

void Camera::DoRender()
{
    SetCurrentScreenSize();

    CalculateCenterAndBound();

    std::vector<CompRender*> allRenderNeedDraw;
    CullScene(allRenderNeedDraw);

    RenderScene(allRenderNeedDraw);
}

void Camera::SetCurrentScreenSize()
{
    _currentScreenSize = VecConvert<unsigned int, float>(Game::GetWindow()->getSize());
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
    _currentLeftBottomInWorldCoord = _currentCenterInWorldCoord - cameraRectSize / 2.0f;
    _currentRightTopInWorldCoord = _currentCenterInWorldCoord + cameraRectSize / 2.0f;
}

void Camera::CullScene(std::vector<CompRender*>& resultVec)
{
    SceneManager* pSceneMgr = Game::GetManager<SceneManager>();
    auto& allEntitiesMap =pSceneMgr ->GetSceneEntities();
    auto windowSize = Game::GetWindow()->getSize();
    for (auto& [guid, pEntity]: allEntitiesMap)
    {
        auto pRender = pEntity->GetComponent<CompRender>();
        if (pRender == nullptr)
            continue;

        auto pTransform = pEntity->GetComponent<CompTransform>();
        if (pTransform == nullptr)
            continue;

        vec2f entityCenterWorldCoord = pTransform->GetPosition();
        vec2f entityCenterScreenCoord = WorldCoordToScreenCoord(entityCenterWorldCoord);
        pRender->SetSfmlDrawableScreenCoordinate(entityCenterScreenCoord);

        vec2f entityRenderSizeScreenCoord = pRender->GetRenderSizeInScreenCoordinate();

        vec2f entityRenderBottomRightScreenCoord = entityCenterScreenCoord + entityRenderSizeScreenCoord / 2.0f;
        if (entityRenderBottomRightScreenCoord.x < 0 || entityRenderBottomRightScreenCoord.y < 0)
            continue;

        vec2f entityRenderTopLeftScreenCoord = entityCenterScreenCoord - entityRenderSizeScreenCoord / 2.0f;
        if (entityRenderTopLeftScreenCoord.x > windowSize.x || entityRenderTopLeftScreenCoord.y > windowSize.y)
            continue;

        resultVec.push_back(pRender);
    }
}

void Camera::RenderScene(const std::vector<CompRender*>& renderVec)
{
    auto pWindow = Game::GetWindow();
    for (auto pRender: renderVec)
    {
        if (pRender == nullptr)
            continue;

        auto pSfmlDrawable = pRender->GetSfmlDrawable();
        if (pSfmlDrawable == nullptr)
            continue;

        pWindow->draw(*pSfmlDrawable);
    }
}

vec2f Camera::WorldCoordToScreenCoord(const vec2f& worldPos)
{
    // move left bottom wolrd coordinate to original coordinate
    vec2f worldPosWhenLeftBottomIsOrigin = worldPos - _currentLeftBottomInWorldCoord;

    // move left top world coordinate to original coordinate (which is same with screen coordinate)
    auto cameraRectSize = Game::GetManager<ConfigManager>()->GetGlobalSetting().cameraRectWorldCoordinateSize;
    vec2f worldPosWhenLeftTopIsOrigin = vec2f {
        worldPosWhenLeftBottomIsOrigin.x,
        cameraRectSize.y - worldPosWhenLeftBottomIsOrigin.y
    };

    // convert to scrren coordinate
    vec2f screenCoordinate = vec2f {
        (worldPosWhenLeftTopIsOrigin.x / cameraRectSize.x) * _currentScreenSize.x,
        (worldPosWhenLeftTopIsOrigin.y / cameraRectSize.y) * _currentScreenSize.y,
    };

    return screenCoordinate;
}