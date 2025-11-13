#ifndef DR4_BACKEND
#define DR4_BACKEND

#include "cum/dr4_ifc.hpp"
#include "cum/plugin.hpp"

namespace graphics {

    class Backend : public dr4::DR4Backend {
        public:
            virtual dr4::Window *CreateWindow() override;
            inline virtual ~Backend() {};

            virtual const std::string &GetName() const override;
            virtual const std::string &GetDescription() const override;
            virtual const cum::PluginVersion &GetVersion() const override;

            virtual std::vector<std::string> GetDependencies() const override;
            virtual bool IsCompatibleWith(const Plugin& other) const override;
    };

    std::string const kBackendName = "DenDR4Backend";

    std::string const kDescription =
    "\t It's a plugin with implementation of methods\n"
    "from standard namespace, dr4. It could be used \n"
    "for working with graphics and windows.\n";

    cum::PluginVersion const kVersion = {1, 4, 88};
};

#endif // DR4_BACKEND
