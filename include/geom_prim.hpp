#ifndef GEOM_PRIM_HPP
#define GEOM_PRIM_HPP

#include "cum/geomprim_ifc.hpp"
#include "hui/geomprim.hpp"

namespace graphics {

    class GeomPrimBack : public hui::GeomPrimBackend {
        public:
            virtual hui::GeomPrim* CreateGeomPrim(size_t geomPrimType, dr4::Window* dr4Window) override;

            virtual const std::string &GetName() const override {return kName;};
            virtual const std::string &GetDescription() const override {return kDescription;};
            virtual const cum::PluginVersion &GetVersion() const override {return kVersion;};

            virtual std::vector<std::string> GetDependencies() const override {return {};};
            virtual bool IsCompatibleWith(const Plugin& other) const override {return true;};

            const cum::PluginVersion kVersion = {1, 4, 88};
            const std::string kName = "DenGeomPrimBackend";
            const std::string kDescription =
                "This plugin provides opportunity for creating and drawing geometric primitives\n";
    };

    class Rectangle : public hui::GeomPrim {
        private:
            const dr4::Color kBorderColor = {dr4::Color::ColorMaxValue, 0, 0};
            dr4::Vec2f pos_;

        public:
            virtual hui::EventResult OnMouseMove(const hui::Event& evt)    override;
            virtual hui::EventResult OnMouseDown(const hui::Event& evt)    override;
            virtual hui::EventResult OnMouseRelease(const hui::Event& evt) override;

            virtual void DrawOn(dr4::Texture& texture) const override;

            virtual void SetPos(dr4::Vec2f pos) override;

            virtual dr4::Vec2f GetPos() const override;
    };

};

#endif // GEOM_PRIM_HPP
