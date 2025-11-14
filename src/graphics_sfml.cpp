#include "../include/graphics.hpp"

#include <stdlib.h>
#include <stdexcept>
#include <string.h>
#include <memory>

#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "../geometry/include/vector.hpp"

#include "../include/table_event.hpp"

namespace graphics {

//-----------------FONT---------------------------------------------------------------------------------------

    class FontImpl : public sf::Font {
        public:
            explicit FontImpl()
                :sf::Font() {};

            virtual ~FontImpl() = default;
    };

    Font::~Font() {};

    void Font::LoadFromFile(const std::string& path) {
        if (!(sf::Font::loadFromFile(path))) {
            throw std::runtime_error("No files for font uploading");
        }
    };
    void Font::LoadFromBuffer(const void* buffer, size_t size)  {
        if (!(sf::Font::loadFromMemory(buffer, size))) {
            throw std::runtime_error("No files for font uploading");
        }
    };

    float Font::GetAscent(float fontSize) const {
        return sf::Font::getLineSpacing(fontSize) - sf::Font::getUnderlinePosition(fontSize);
    };
    float Font::GetDescent(float fontSize) const {
        return sf::Font::getUnderlinePosition(fontSize);
    };

//-----------------TEXT---------------------------------------------------------------------------------------

    Text::Text(const std::string& str_text, const std::string& font_file_name, unsigned char height)
        :sf::Text(), font_(), pos_({0, 0}) {
        sf::Text::setString(str_text);
        sf::Text::setCharacterSize(height);
        if (strcmp(font_file_name.c_str(), "") != 0) {
            font_.LoadFromFile(font_file_name);
        }

        sf::Text::setFont(font_);

        text_ = str_text;
        valign_ = dr4::Text::VAlign::TOP;
    }

    Text::Text(const Text& other)
        :sf::Text(other), font_(other.font_) {
        sf::Text::setFont(font_);
        text_ = other.text_;
        valign_ = other.valign_;
    }

    Text::~Text() {}

    void Text::SetText(const std::string& new_text) {
        sf::Text::setString(new_text);
        text_ = new_text;
    }
    void Text::SetColor(dr4::Color color) {
        sf::Text::setFillColor({color.r, color.g, color.b, color.a});
    }
    void Text::SetFontSize(float size) {
        sf::Text::setCharacterSize(size);
    }
    void Text::SetVAlign(dr4::Text::VAlign valign) {
        valign_ = valign;
        ChangeValign();
    }
    void Text::SetFont(const dr4::Font* font) {
        font_ = Font(*(dynamic_cast<const Font*>(font)));
        delete font;
        sf::Text::setFont(font_);
    }

    dr4::Vec2f Text::GetBounds() const {
        auto size = sf::Text::getLocalBounds().getSize();
        return {size.x, size.y};
    }
    const std::string& Text::GetText() const {
        return text_;
    }
    dr4::Color Text::GetColor() const {
        sf::Color color = sf::Text::getFillColor();
        return {color.r, color.g, color.b, color.a};
    }
    float Text::GetFontSize() const {
        return sf::Text::getCharacterSize();
    }
    dr4::Text::VAlign Text::GetVAlign() const {
        return valign_;
    }
    const dr4::Font& Text::GetFont() const {
        return font_;
    }

    void Text::SetPos(dr4::Vec2f pos) {
        pos_ = pos;
        ChangeValign();
    }
    dr4::Vec2f Text::GetPos() const {
        return pos_;
    }

    void Text::DrawOn(dr4::Texture& texture) const {
        auto& my_texture = dynamic_cast<Texture&>(texture);
        my_texture.draw(*this, sf::RenderStates().transform.translate({my_texture.extent_.x, my_texture.extent_.y}));
    }

    void Text::ChangeValign() {
        switch(valign_) {
            case dr4::Text::VAlign::BASELINE : {
                sf::Text::setPosition({pos_.x, pos_.y - sf::Text::getLocalBounds().height
                                                      + font_.getUnderlinePosition(sf::Text::getCharacterSize())});
                return;
            }
            case dr4::Text::VAlign::BOTTOM : {
                sf::Text::setPosition({pos_.x, pos_.y - sf::Text::getLocalBounds().height});
                return;
            }
            case dr4::Text::VAlign::MIDDLE : {
                sf::Text::setPosition({pos_.x, pos_.y - sf::Text::getLocalBounds().height / 2});
                return;
            }
            case dr4::Text::VAlign::TOP : {
                sf::Text::setPosition({pos_.x, pos_.y});
                return;
            }
            default:
                return;
        }
    }

//-----------------LINE---------------------------------------------------------------------------------------

    Line::Line()
        :sf::RectangleShape() {end_changed_ = false;};

    void Line::SetStart(dr4::Vec2f start) {
        start_ = start;
        sf::RectangleShape::setPosition({start_.x, start_.y});
        if (end_changed_) {
            dr4::Vec2f delta = end_ - start_;
            float len = sqrt(delta.x * delta.x + delta.y * delta.y);
            sf::RectangleShape::setSize({len, sf::RectangleShape::getSize().y});
            float angle = asinf32(- delta.y / len);
            sf::RectangleShape::rotate(angle * 180 / M_PI);
        }
    }
    void Line::SetEnd(dr4::Vec2f end) {
        end_changed_ = true;
        end_ = end;
        dr4::Vec2f delta = end_ - start_;
        float len = sqrt(delta.x * delta.x + delta.y * delta.y);
        sf::RectangleShape::setSize({len, sf::RectangleShape::getSize().y});
        float angle = asinf32(- delta.y / len);
        sf::RectangleShape::rotate(angle * 180 / M_PI);
    }
    void Line::SetColor(dr4::Color color) {
        sf::RectangleShape::setFillColor({color.r, color.g, color.b, color.a});
    }
    void Line::SetThickness(float thickness) {
        sf::Vector2f size = sf::RectangleShape::getSize();
        sf::RectangleShape::setSize({size.x, thickness});
    }

    dr4::Vec2f Line::GetStart() const {
        return start_;
    }
    dr4::Vec2f Line::GetEnd() const {
        return end_;
    }
    dr4::Color Line::GetColor() const {
        sf::Color color = sf::RectangleShape::getFillColor();
        return {color.r, color.g, color.b, color.a};
    }
    float Line::GetThickness() const {
        return sf::RectangleShape::getSize().y;
    }

    void Line::DrawOn(dr4::Texture& texture) const {
        auto& my_texture = dynamic_cast<Texture&>(texture);
        my_texture.draw(*this, sf::RenderStates().transform.translate({my_texture.extent_.x, my_texture.extent_.y}));
    }

    void Line::SetPos(dr4::Vec2f pos) {
        SetStart(pos);
    }
    dr4::Vec2f Line::GetPos() const {
        return GetStart();
    }

//-----------------CIRCLE-------------------------------------------------------------------------------------

    Circle::Circle()
        :sf::CircleShape() {}

    void Circle::SetCenter(dr4::Vec2f center) {
        sf::CircleShape::setPosition({center.x - radius_, center.y - radius_});
        center_ = center;
    }
    void Circle::SetRadius(float radius) {
        sf::CircleShape::setRadius(radius);
        radius_ = radius;
        sf::CircleShape::setPosition({center_.x - radius_, center_.y - radius_});
    }
    void Circle::SetFillColor(dr4::Color color) {
        sf::CircleShape::setFillColor({color.r, color.g, color.b, color.a});
    }
    void Circle::SetBorderColor(dr4::Color color) {
        sf::CircleShape::setOutlineColor({color.r, color.g, color.b, color.a});
    }
    void Circle::SetBorderThickness(float thickness) {
        sf::CircleShape::setOutlineThickness(thickness);
    }

    dr4::Vec2f Circle::GetCenter() const {
        return center_;
    }
    float Circle::GetRadius() const {
        return radius_;
    }
    dr4::Color Circle::GetFillColor() const {
        sf::Color color = sf::CircleShape::getFillColor();
        return {color.r, color.g, color.b, color.a};
    }
    float Circle::GetBorderThickness() const {
        return sf::CircleShape::getOutlineThickness();
    }
    dr4::Color Circle::GetBorderColor() const {
        sf::Color color = sf::CircleShape::getOutlineColor();
        return {color.r, color.g, color.b, color.a};
    }

    void Circle::DrawOn(dr4::Texture& texture) const {
        auto& my_texture = dynamic_cast<Texture&>(texture);
        my_texture.draw(*this, sf::RenderStates().transform.translate({my_texture.extent_.x, my_texture.extent_.y}));
    }

    void Circle::SetPos(dr4::Vec2f pos) {
        sf::CircleShape::setPosition({pos.x, pos.y});
        center_ = {pos.x + radius_, pos.y + radius_};
    }
    dr4::Vec2f Circle::GetPos() const {
        return {center_.x - radius_, center_.y - radius_};
    }

//-----------------RECTANGLE SHAPE----------------------------------------------------------------------------

    RectangleShape::RectangleShape()
        :sf::RectangleShape() {}

    RectangleShape::RectangleShape(const RectangleShape& other)
        :sf::RectangleShape(other) {}

    RectangleShape::~RectangleShape() {}

    void RectangleShape::SetSize(dr4::Vec2f size) {
        sf::RectangleShape::setSize({size.x, size.y});
    }
    void RectangleShape::SetFillColor(dr4::Color color) {
        sf::RectangleShape::setFillColor({color.r, color.g, color.b, color.a});
    }
    void RectangleShape::SetBorderThickness(float thickness) {
        sf::RectangleShape::setOutlineThickness(thickness);
    }
    void RectangleShape::SetBorderColor(dr4::Color color) {
        sf::RectangleShape::setOutlineColor({color.r, color.g, color.b, color.a});
    }

    dr4::Vec2f RectangleShape::GetSize() const {
        sf::Vector2f size = sf::RectangleShape::getSize();
        return {size.x, size.y};
    }
    dr4::Color RectangleShape::GetFillColor() const {
        sf::Color color = sf::RectangleShape::getFillColor();
        return {color.r, color.g, color.b, color.a};
    }
    float RectangleShape::GetBorderThickness() const {
        return sf::RectangleShape::getOutlineThickness();
    }
    dr4::Color RectangleShape::GetBorderColor() const {
        sf::Color color = sf::RectangleShape::getOutlineColor();
        return {color.r, color.g, color.b, color.a};
    }

    void RectangleShape::SetRotation(float angle) {
        sf::RectangleShape::setRotation(angle);
    }
    void RectangleShape::Rotate(float angle) {
        sf::RectangleShape::rotate(angle);
    }

    void RectangleShape::SetPos(dr4::Vec2f pos) {
        sf::RectangleShape::setPosition({pos.x, pos.y});
    }
    dr4::Vec2f RectangleShape::GetPos() const {
        sf::Vector2f pos = sf::RectangleShape::getPosition();
        return {pos.x, pos.y};
    }

    void RectangleShape::DrawOn(dr4::Texture& texture) const {
        auto& my_texture = dynamic_cast<Texture&>(texture);
        my_texture.draw(*this, sf::RenderStates().transform.translate({my_texture.extent_.x, my_texture.extent_.y}));
    }

//-----------------IMAGE--------------------------------------------------------------------------------------

    Image::Image(float width, float height)
        :sf::Image() {
        sf::Image::create(width, height);

        width_ = width;
        height_ = height;

        pos_ = {0, 0};
    }

    Image::~Image() {}

    void Image::SetPixel(size_t x, size_t y, dr4::Color color) {
        sf::Image::setPixel(x, y, sf::Color(color.r, color.g, color.b, color.a));
    }

    dr4::Color Image::GetPixel(size_t x, size_t y) const {
        sf::Color color = sf::Image::getPixel(x, y);
        return dr4::Color(color.r, color.g, color.b, color.a);
    }

    void Image::SetSize(dr4::Vec2f size) {
        width_ = size.x;
        height_ = size.y;
        sf::Image::create(width_, height_);
    }
    dr4::Vec2f Image::GetSize() const {
        return dr4::Vec2f(width_, height_);
    }
    float Image::GetWidth() const {
        return width_;
    }
    float Image::GetHeight() const {
        return height_;
    }

    void Image::SetPos(dr4::Vec2f pos) {
        pos_ = pos;
    }
    dr4::Vec2f Image::GetPos() const {
        return pos_;
    }

    void Image::DrawOn(dr4::Texture& texture) const {
        Texture& my_texture = dynamic_cast<Texture&>(texture);
        sf::Texture txtr(my_texture.getTexture());

        txtr.update(*this, pos_.x, pos_.y);
        sf::Sprite sprite(txtr);
        sprite.setPosition({my_texture.extent_.x, my_texture.extent_.y});
        my_texture.draw(sprite);
    }

//-----------------TEXTURE------------------------------------------------------------------------------------

    Texture::Texture(float width, float height)
        :sf::RenderTexture() {
        width_ = (width > kMinWidthTexture) ? width : kMinWidthTexture;
        height_ = (height > kMinWidthTexture) ? height : kMinWidthTexture;
        sf::RenderTexture::create(width_, height_);
        pos_ = {0, 0};
        extent_ = {0, 0};
    }

    Texture::Texture(const Texture& other)
        :sf::RenderTexture() {
        sf::RenderTexture::create(other.width_, other.height_);
        width_ = other.width_;
        height_ = other.height_;
        pos_ = other.pos_;
        extent_ = other.extent_;
    }

    Texture::~Texture() {}

    void Texture::SetSize(dr4::Vec2f size) {
        width_ = size.x;
        height_ = size.y;
        sf::RenderTexture::create(width_, height_);
    }

    dr4::Vec2f Texture::GetSize() const {
        return dr4::Vec2f(width_, height_);
    }

    float Texture::GetWidth() const {
        return width_;
    }

    float Texture::GetHeight() const {
        return height_;
    }

    void Texture::DrawOn(dr4::Texture& texture) const {
        Texture& my_texture = dynamic_cast<Texture&>(texture);
        (const_cast<Texture*>(this))->display();

        sf::Sprite sprite(sf::RenderTexture::getTexture());
        sprite.setPosition({pos_.x + my_texture.extent_.x, pos_.y + my_texture.extent_.y});
        my_texture.draw(sprite);
    }

    void Texture::SetZero(dr4::Vec2f pos) {
        extent_ = pos;
    }
    dr4::Vec2f Texture::GetZero() const {
        return extent_;
    }

    void Texture::SetPos(dr4::Vec2f pos) {
        pos_ = pos;
    }
    dr4::Vec2f Texture::GetPos() const {
        return pos_;
    }

    void Texture::Clear(dr4::Color color) {
        sf::RenderTexture::clear(sf::Color(color.r, color.g, color.b, color.a));
    }

//-----------------RENDER WINDOW------------------------------------------------------------------------------

    RenderWindow::RenderWindow(size_t width, size_t height, const char* window_name)
        :sf::RenderWindow(), title_(window_name) {
        width_ = width;
        height_ = height;
        if (strcmp(window_name, "") != 0) {
            sf::RenderWindow::setTitle(window_name);
        }
    }

    RenderWindow::~RenderWindow() {}

    std::optional<dr4::Event> RenderWindow::PollEvent() {
        static Coordinates old_coors(GetMousePos());

        sf::Event sf_event;
        if (!(sf::RenderWindow::pollEvent(sf_event))) {
            return {};
        }

        dr4::Event event;

        auto event_type_itr = kEventTypeTransformMap.find(sf_event.type);
        if (event_type_itr == kEventTypeTransformMap.end()) {
            event.type = dr4::Event::Type::UNKNOWN;
            return event;
        }

        event.type = event_type_itr->second;

        switch (event.type) {
            case dr4::Event::Type::QUIT : {
                break;
            }
            case dr4::Event::Type::MOUSE_DOWN : case dr4::Event::Type::MOUSE_UP : {
                auto mouse_button_itr = kMouseButtonTransformMap.find(sf_event.mouseButton.button);
                if (mouse_button_itr == kMouseButtonTransformMap.end()) {
                    event.mouseButton.button = dr4::MouseButtonType::UNKNOWN;
                    return event;
                }

                event.mouseButton.button = mouse_button_itr->second;
                Coordinates pos(GetMousePos());
                event.mouseButton.pos = {pos[0], pos[1]};
                break;
            }
            case dr4::Event::Type::MOUSE_MOVE : {
                Coordinates pos(GetMousePos());
                event.mouseMove.pos = {pos[0], pos[1]};
                event.mouseMove.rel = {pos[0] - old_coors[0], pos[1] - old_coors[1]};
                old_coors = pos;
                break;
            }
            case dr4::Event::Type::MOUSE_WHEEL : {
                if (sf_event.mouseWheelScroll.wheel == sf::Mouse::Wheel::HorizontalWheel) {
                    event.mouseWheel.deltaX = sf_event.mouseWheelScroll.delta;
                    event.mouseWheel.deltaY = 0;
                } else {
                    event.mouseWheel.deltaX = 0;
                    event.mouseWheel.deltaY = sf_event.mouseWheelScroll.delta;
                }
                Coordinates pos(GetMousePos());
                event.mouseWheel.pos = {pos[0], pos[1]};
                break;
            }
            case dr4::Event::Type::KEY_DOWN :  case dr4::Event::Type::KEY_UP : {
                event.key.mods = ((sf_event.key.control) ? dr4::KeyMode::KEYMOD_CTRL : 1)
                               | ((sf_event.key.alt)    ? dr4::KeyMode::KEYMOD_ALT   : 1)
                               | ((sf_event.key.shift)  ? dr4::KeyMode::KEYMOD_SHIFT : 1);

                auto key_itr = kKeyCodeTransformMap.find(sf_event.key.scancode);
                if (key_itr == kKeyCodeTransformMap.end()) {
                    event.key.sym = dr4::KeyCode::KEYCODE_UNKNOWN;
                    return event;
                }

                event.key.sym = key_itr->second;
                break;
            }
            case dr4::Event::Type::TEXT_EVENT : {
                memmove(buffer, &(sf_event.text.unicode), sizeof(sf_event.text.unicode));
                buffer[sizeof(sf_event.text.unicode)] = '\0';
                event.text.unicode = buffer;
                break;
            }
            default : {
                event.type = dr4::Event::Type::UNKNOWN;
                break;
            }
        }

        return event;
    }

    float RenderWindow::GetWidth() const {
        return width_;
    };

    float RenderWindow::GetHeight() const {
        return height_;
    };

    dr4::Vec2f RenderWindow::GetSize() const {
        return {width_, height_};
    }

    void RenderWindow::SetSize(dr4::Vec2f size) {
        width_ = size.x;
        height_ = size.y;
        sf::RenderWindow::setSize({(unsigned int)width_, (unsigned int)height_});
        sf::RenderWindow::setView(sf::View({width_ / 2, height_ / 2}, {width_, height_}));
    }

    void RenderWindow::SetTitle(const std::string &title) {
        sf::RenderWindow::setTitle(title);
        title_ = title;
    }

    const std::string &RenderWindow::GetTitle() const {
        return title_;
    }

    dr4::Texture *RenderWindow::CreateTexture() {
        return new Texture(width_, height_);
    }
    dr4::Image *RenderWindow::CreateImage() {
        return new Image(width_, height_);
    }
    dr4::Font *RenderWindow::CreateFont() {
        return new Font();
    }
    dr4::Line *RenderWindow::CreateLine() {
        return new Line();
    }
    dr4::Circle *RenderWindow::CreateCircle() {
        return new Circle();
    }
    dr4::Rectangle *RenderWindow::CreateRectangle() {
        return new RectangleShape();
    }
    dr4::Text *RenderWindow::CreateText() {
        return new Text("", "", 0);
    }

    Coordinates RenderWindow::GetMousePos() const {
        float scale_x = GetWidth() / width_;
        float scale_y = GetHeight() / height_;
        return Coordinates(2, (float)sf::Mouse::getPosition(*this).x / scale_x,
                              (float)sf::Mouse::getPosition(*this).y / scale_y);
    }

    void RenderWindow::Draw(const dr4::Texture &texture) {
        (const_cast<Texture&>(dynamic_cast<const Texture&>(texture))).display();

        sf::Sprite sprite(dynamic_cast<const Texture&>(texture).getTexture());
        sprite.setPosition({0, 0});
        sf::RenderWindow::draw(sprite);
    }

    void RenderWindow::Open() {
        sf::RenderWindow::create(sf::VideoMode(width_, height_), title_);
    }

    void RenderWindow::Display() {
        sf::RenderWindow::display();
    }

    bool RenderWindow::IsOpen() const {
        return sf::RenderWindow::isOpen();
    }

    void RenderWindow::Close() {
        sf::RenderWindow::close();
    }

    void RenderWindow::Clear(dr4::Color color) {
        sf::RenderWindow::clear(sf::Color(color.r, color.g, color.b, color.a));
    }

    double RenderWindow::GetTime() {
        return time(NULL);
    }

    void RenderWindow::StartTextInput() {
        return;
    }
    void RenderWindow::StopTextInput() {
        return;
    }

//------------------------------------------------------------------------------------------------------------

}
