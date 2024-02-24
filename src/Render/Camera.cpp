#include "Camera.h"

#include <vector>
#include "../Game/Game.h"
#include "../Component/Impl/CompTransform.h"
#include "../Component/Impl/CompRenderer.h"
#include "../Utility/Util.hpp"

void Camera::DoRender()
{
    // 1. Calculate the render bound.
    auto pWindow = Game::GetInstance()->GetWindow();
    vec2f windowSize = VecConvert<unsigned int, float>(pWindow->getSize());
    auto pPlayer = Game::GetInstance()->GetPlayerEntity();
    vec2f playerCoordinate = pPlayer->GetComponent<CompTransform>()->GetPosition();

    vec2f viewPortTopLeftCoordinate = playerCoordinate - (windowSize / 2.0f);
    vec2f viewPortDownRightCoordinate = playerCoordinate + (windowSize / 2.0f);

    // 2. Cull objects
    std::vector<CompRenderer*> allRenderEntities {};
    for (const auto& [id, pEntity]: Game::GetInstance()->GetAllEntities())
    {
        auto pTrans = pEntity->GetComponent<CompTransform>();
        if (pTrans == nullptr)
            continue;

        auto pRender = pEntity->GetComponent<CompRenderer>();
        if (pRender == nullptr)
            continue;

        vec2f entityCoordinate = pTrans->GetPosition();
        vec2f renderRectSize = pRender->GetRenderBound();

        vec2f entityBoundTopLeft = entityCoordinate - (renderRectSize / 2.0f);
        vec2f entityBoundDownRight = entityCoordinate + (renderRectSize / 2.0f);

        bool isOverlapped = Util::IsRectOverlap(viewPortTopLeftCoordinate, viewPortDownRightCoordinate, entityBoundTopLeft, entityBoundDownRight);
        bool isContains = Util::IsRectContains(viewPortTopLeftCoordinate, viewPortDownRightCoordinate, entityBoundTopLeft, entityBoundDownRight);
        if (isOverlapped || isContains)
        {
            // Calculate sprite coordinate in screen
            vec2f spriteScreenPosition = entityCoordinate - viewPortTopLeftCoordinate;
            pRender->GetSprite().setPosition(spriteScreenPosition);

            allRenderEntities.push_back(pRender);
        }
    }

    // 3. Draw 
    for (auto pEntity: allRenderEntities)
    {
        pWindow->draw(pEntity->GetSprite());
    }
}