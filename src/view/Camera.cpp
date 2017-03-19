#include "../view/Camera.h"
#include "../player/Player.h"
#include "../view/Window.h"
#include "../player/Marine.h"

Camera::Camera(float w, float h) {
    viewport = {0, 0, 0, 0};
    setViewSize(w, h);
}

Camera::~Camera() {

}

// Move camera to player
void Camera::move(float x, float y) {
    viewport.x = ( x + MARINE_HEIGHT / 2 ) - viewport.w / 2;
    viewport.y = ( y + MARINE_WIDTH / 2 ) - viewport.h / 2;
}

// Set camera width and height
void Camera::setViewSize(float w, float h) {
    viewport.w = w;
    viewport.h = h;
}
