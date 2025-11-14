#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <stdlib.h>
#include <string>

#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "dr4/math/color.hpp"
#include "dr4/texture.hpp"
#include "dr4/window.hpp"
#include "dr4/event.hpp"

#include "../geometry/include/vector.hpp"

namespace graphics {

    class Font : public dr4::Font, public sf::Font {
        public:
            Font() = default;

            virtual ~Font();

            virtual void LoadFromFile(const std::string& path) override;
            virtual void LoadFromBuffer(const void* buffer, size_t size) override;

            virtual float GetAscent(float fontSize) const override;
            virtual float GetDescent(float fontSize) const override;
    };

    class Text : public dr4::Text, public sf::Text {
        private:
            Font font_ = {};
            dr4::Text::VAlign valign_;
            std::string text_;

            dr4::Vec2f pos_;

        public:
            explicit Text(const std::string& text, const std::string& font_file_name, unsigned char height);

            explicit Text(const Text& other);

            ~Text();

            virtual void SetText(const std::string& text) override;
            virtual void SetColor(dr4::Color color) override;
            virtual void SetFontSize(float size) override;
            virtual void SetVAlign(dr4::Text::VAlign align) override;
            virtual void SetFont(const dr4::Font* font) override;

            virtual dr4::Vec2f GetBounds() const override;
            virtual const std::string& GetText() const override;
            virtual dr4::Color GetColor() const override;
            virtual float GetFontSize() const override;
            virtual dr4::Text::VAlign GetVAlign() const override;
            virtual const dr4::Font& GetFont() const override;

            virtual void DrawOn(dr4::Texture& texture) const override;

            virtual void SetPos(dr4::Vec2f pos) override;

            virtual dr4::Vec2f GetPos() const override;

            void ChangeValign();
    };

    class Line : public dr4::Line, public sf::RectangleShape {
        private:
            dr4::Vec2f start_;
            dr4::Vec2f end_;

            bool end_changed_;

        public:
            explicit Line();

            virtual void SetStart(dr4::Vec2f start) override;
            virtual void SetEnd(dr4::Vec2f end) override;
            virtual void SetColor(dr4::Color color) override;
            virtual void SetThickness(float thickness) override;

            virtual dr4::Vec2f GetStart() const override;
            virtual dr4::Vec2f GetEnd() const override;
            virtual dr4::Color GetColor() const override;
            virtual float GetThickness() const override;

            virtual void DrawOn(dr4::Texture& texture) const override;

            virtual void SetPos(dr4::Vec2f pos) override;

            virtual dr4::Vec2f GetPos() const override;
    };

    class Circle : public dr4::Circle, public sf::CircleShape {
        private:
            dr4::Vec2f center_;
            float radius_;

        public:
            explicit Circle();

            virtual void SetCenter(dr4::Vec2f center) override;
            virtual void SetRadius(float radius) override;
            virtual void SetFillColor(dr4::Color color) override;
            virtual void SetBorderColor(dr4::Color color) override;
            virtual void SetBorderThickness(float thickness) override;

            virtual dr4::Vec2f GetCenter() const override;
            virtual float GetRadius() const override;
            virtual dr4::Color GetFillColor() const override;
            virtual dr4::Color GetBorderColor() const override;
            virtual float GetBorderThickness() const override;

            virtual void DrawOn(dr4::Texture& texture) const override;

            virtual void SetPos(dr4::Vec2f pos) override;

            virtual dr4::Vec2f GetPos() const override;
    };

    class RectangleShape : public dr4::Rectangle, public sf::RectangleShape {
        public:
            explicit RectangleShape();

            explicit RectangleShape(const RectangleShape& other);

            ~RectangleShape();

            virtual void SetSize(dr4::Vec2f size) override;
            virtual void SetFillColor(dr4::Color color) override;
            virtual void SetBorderThickness(float thickness) override;
            virtual void SetBorderColor(dr4::Color color) override;

            virtual dr4::Vec2f GetSize() const override;
            virtual dr4::Color GetFillColor() const override;
            virtual float GetBorderThickness() const override;
            virtual dr4::Color GetBorderColor() const override;

            void SetRotation(float angle);
            void Rotate(float angle);

            virtual void DrawOn(dr4::Texture& texture) const override;

            virtual void SetPos(dr4::Vec2f pos) override;

            virtual dr4::Vec2f GetPos() const override;
    };

    class Image : public dr4::Image, public sf::Image {
        private:
            float width_;
            float height_;

            dr4::Vec2f pos_;

        public:
            explicit Image(float width, float height);

            virtual ~Image();

            virtual void SetPixel(size_t x, size_t y, dr4::Color color) override;
            virtual dr4::Color GetPixel(size_t x, size_t y) const override;

            virtual void SetSize(dr4::Vec2f size) override;
            virtual dr4::Vec2f GetSize() const override;
            virtual float GetWidth() const override;
            virtual float GetHeight() const override;

            virtual void DrawOn(dr4::Texture& texture) const override;

            virtual void SetPos(dr4::Vec2f pos) override;

            virtual dr4::Vec2f GetPos() const override;
    };

    const float kMinWidthTexture = 10;

    class Texture : public dr4::Texture, public sf::RenderTexture {
        private:
            float width_;
            float height_;

            dr4::Vec2f pos_;

        public:
            dr4::Vec2f extent_;

            explicit Texture(float width, float height);
            explicit Texture(const Texture& other);

            virtual ~Texture();

            virtual void SetSize(dr4::Vec2f size) override;
            virtual dr4::Vec2f GetSize() const override;
            virtual float GetWidth() const override;
            virtual float GetHeight() const override;

            virtual void SetZero(dr4::Vec2f pos) override;
            virtual dr4::Vec2f GetZero() const override;

            virtual void Clear(dr4::Color color) override;

            virtual void DrawOn(dr4::Texture& texture) const override;

            virtual void SetPos(dr4::Vec2f pos) override;

            virtual dr4::Vec2f GetPos() const override;
    };

    const size_t kStartWindowWidth = 720;
    const size_t kStartWindowHeight = 480;

    class RenderWindow : public dr4::Window, public sf::RenderWindow {
        private:
            std::string title_;

            float width_;
            float height_;

            char buffer[sizeof(sf::Uint32) + 1];

        public:
            explicit RenderWindow(size_t width = kStartWindowWidth, size_t height = kStartWindowHeight, const char* window_name = "");

            ~RenderWindow();

            float GetStartWidth() const {return width_;};
            float GetStartHeight() const {return height_;};

            float GetWidth() const;
            float GetHeight() const;

            virtual dr4::Vec2f GetSize() const override;
            virtual void SetSize(dr4::Vec2f size) override;

            virtual void SetTitle(const std::string &title) override;
            virtual const std::string &GetTitle() const override;

            virtual dr4::Texture   *CreateTexture()   override;
            virtual dr4::Image     *CreateImage()     override;
            virtual dr4::Font      *CreateFont()      override;
            virtual dr4::Line      *CreateLine()      override;
            virtual dr4::Circle    *CreateCircle()    override;
            virtual dr4::Rectangle *CreateRectangle() override;
            virtual dr4::Text      *CreateText()      override;

            virtual std::optional<dr4::Event> PollEvent() override;

            Coordinates GetMousePos() const;

            virtual void Draw(const dr4::Texture &texture) override;

            virtual void Display() override;

            virtual bool IsOpen() const override;

            virtual void Open() override;
            virtual void Close() override;

            virtual void Clear(dr4::Color color) override;

            double GetTime() override;
            virtual void StartTextInput() override;
            virtual void StopTextInput() override;
    };

}

#endif // GRAPHICS_HPP
