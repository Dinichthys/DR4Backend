#include "../include/dr4_backend.hpp"
#include "../include/graphics.hpp"

extern "C" dr4::DR4Backend* DR4_BACKEND_FUNCTION() {
    return new graphics::Backend();
}

const std::string &graphics::Backend::GetName() const {
    return graphics::kBackendName;
}

dr4::Window *graphics::Backend::CreateWindow() {
    return new graphics::RenderWindow();
}

const std::string &graphics::Backend::GetDescription() const {
    return graphics::kDescription;
}

const cum::PluginVersion &graphics::Backend::GetVersion() const {
    return graphics::kVersion;
}

std::vector<std::string> graphics::Backend::GetDependencies() const {
    return {};
}

bool graphics::Backend::IsCompatibleWith(const cum::Plugin&) const {
    return true;
}
