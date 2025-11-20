#ifndef DR4_BACKEND
#define DR4_BACKEND

#include "cum/ifc/dr4.hpp"

namespace graphics {

    std::string const kBackendName = "DenDR4Backend";

    std::string const kDescription =
    "\t It's a plugin with implementation of methods\n"
    "from standard namespace, dr4. It could be used \n";

    class Backend : public cum::DR4BackendPlugin {
        public:
            virtual dr4::Window *CreateWindow() override;
            inline virtual ~Backend() {};

            virtual std::string_view GetIdentifier() const {return kBackendName;};
            virtual std::string_view GetName() const {return kBackendName;};
            virtual std::string_view GetDescription() const {return kDescription;};

            virtual std::vector<std::string_view> GetDependencies() const {return {};};
            virtual std::vector<std::string_view> GetConflicts() const {return {};};

            virtual void AfterLoad() {};
    };

};

#endif // DR4_BACKEND
