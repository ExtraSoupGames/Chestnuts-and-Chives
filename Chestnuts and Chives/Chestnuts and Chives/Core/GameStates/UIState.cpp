#include "UIState.h"

bool UIState::DoElementsOverlap()
{
    throw new exception("Not implemented");
}

bool UIState::IsAllSpaceFilled()
{
    throw new exception("Not implemented");
}

void UIState::Render(Renderer* renderer)
{
    for (int i = 0; i < elements.size(); i++) {
        elements.at(i)->Render(renderer);
    }
}
