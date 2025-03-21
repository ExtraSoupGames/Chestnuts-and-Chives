#include "UIState.h"

UIState::~UIState()
{
    for (auto p : elements) {
        delete p;
    }
}

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
    screenScaling = renderer->GetScreenScalingFactor();
    for (int i = 0; i < elements.size(); i++) {
        elements.at(i)->Render(renderer);
    }
}

void UIState::ManageInput(SDL_Event* e)
{
    if (e->type == SDL_EVENT_MOUSE_MOTION) {
        UIElement* hoveredElement = GetHoveredElement();
        if (hoveredElement == nullptr) {
            return;
        }
        if (hoveredElement->hovered) {
            return;
        }
        hoveredElement->HoverStarted();
        hoveredElement->hovered = true;
    }
    if (e->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        UIElement* hoveredElement = GetHoveredElement();
        if (hoveredElement == nullptr) {
            return;
        }
        hoveredElement->Clicked();
    }
}
UIElement* UIState::GetHoveredElement() {
    float x;
    float y;
    SDL_GetMouseState(&x, &y);
    int mouseX = (int)x;
    int mouseY = (int)y;
    mouseX = mouseX / screenScaling;
    mouseY = mouseY / screenScaling;
    for (UIElement* elem : elements) {
        if (elem->ContainsMouse(mouseX, mouseY)) {
            return elem;
        }
        else {
            if (elem->hovered) {
                elem->HoverEnded();
                elem->hovered = false;
            }
        }
    }
    return nullptr;
}
