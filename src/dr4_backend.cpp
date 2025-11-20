#include "../include/dr4_backend.hpp"
#include "../include/graphics.hpp"
#include "../mipt-ded-zemax/include/cum/manager.hpp"

extern "C" cum::Plugin* CREATE_PLUGIN_FUNC_NAME() {
    return new graphics::Backend();
}

dr4::Window *graphics::Backend::CreateWindow() {
    return new graphics::RenderWindow();
}
