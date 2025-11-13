#ifndef TABLE_EVENT_HPP
#define TABLE_EVENT_HPP

#include <map>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "graphics.hpp"

#include "dr4/event.hpp"
#include "dr4/keycodes.hpp"
#include "dr4/mouse_buttons.hpp"

namespace graphics {

    const std::map<sf::Event::EventType, dr4::Event::Type> kEventTypeTransformMap{
        {sf::Event::EventType::Closed,              dr4::Event::Type::QUIT          },
        {sf::Event::EventType::KeyPressed,          dr4::Event::Type::KEY_DOWN      },
        {sf::Event::EventType::KeyReleased,         dr4::Event::Type::KEY_UP        },
        {sf::Event::EventType::MouseButtonPressed,  dr4::Event::Type::MOUSE_DOWN    },
        {sf::Event::EventType::MouseButtonReleased, dr4::Event::Type::MOUSE_UP      },
        {sf::Event::EventType::MouseMoved,          dr4::Event::Type::MOUSE_MOVE    },
        {sf::Event::EventType::MouseWheelScrolled,  dr4::Event::Type::MOUSE_WHEEL   },
        {sf::Event::EventType::TextEntered,         dr4::Event::Type::TEXT_EVENT    },
    };

    const std::map<sf::Mouse::Button, dr4::MouseButtonType> kMouseButtonTransformMap{
        {sf::Mouse::Button::Left,   dr4::MouseButtonType::LEFT  },
        {sf::Mouse::Button::Right,  dr4::MouseButtonType::RIGHT },
        {sf::Mouse::Button::Middle, dr4::MouseButtonType::MIDDLE},
    };

    const std::map<sf::Keyboard::Scan::Scancode, dr4::KeyCode>  kKeyCodeTransformMap{
        {sf::Keyboard::Scan::Scancode::A, dr4::KeyCode::KEYCODE_A},
        {sf::Keyboard::Scan::Scancode::B, dr4::KeyCode::KEYCODE_B},
        {sf::Keyboard::Scan::Scancode::C, dr4::KeyCode::KEYCODE_C},
        {sf::Keyboard::Scan::Scancode::D, dr4::KeyCode::KEYCODE_D},
        {sf::Keyboard::Scan::Scancode::E, dr4::KeyCode::KEYCODE_E},
        {sf::Keyboard::Scan::Scancode::F, dr4::KeyCode::KEYCODE_F},
        {sf::Keyboard::Scan::Scancode::G, dr4::KeyCode::KEYCODE_G},
        {sf::Keyboard::Scan::Scancode::H, dr4::KeyCode::KEYCODE_H},
        {sf::Keyboard::Scan::Scancode::I, dr4::KeyCode::KEYCODE_I},
        {sf::Keyboard::Scan::Scancode::J, dr4::KeyCode::KEYCODE_J},
        {sf::Keyboard::Scan::Scancode::K, dr4::KeyCode::KEYCODE_K},
        {sf::Keyboard::Scan::Scancode::L, dr4::KeyCode::KEYCODE_L},
        {sf::Keyboard::Scan::Scancode::M, dr4::KeyCode::KEYCODE_M},
        {sf::Keyboard::Scan::Scancode::N, dr4::KeyCode::KEYCODE_N},
        {sf::Keyboard::Scan::Scancode::O, dr4::KeyCode::KEYCODE_O},
        {sf::Keyboard::Scan::Scancode::P, dr4::KeyCode::KEYCODE_P},
        {sf::Keyboard::Scan::Scancode::Q, dr4::KeyCode::KEYCODE_Q},
        {sf::Keyboard::Scan::Scancode::R, dr4::KeyCode::KEYCODE_R},
        {sf::Keyboard::Scan::Scancode::S, dr4::KeyCode::KEYCODE_S},
        {sf::Keyboard::Scan::Scancode::T, dr4::KeyCode::KEYCODE_T},
        {sf::Keyboard::Scan::Scancode::U, dr4::KeyCode::KEYCODE_U},
        {sf::Keyboard::Scan::Scancode::V, dr4::KeyCode::KEYCODE_V},
        {sf::Keyboard::Scan::Scancode::W, dr4::KeyCode::KEYCODE_W},
        {sf::Keyboard::Scan::Scancode::X, dr4::KeyCode::KEYCODE_X},
        {sf::Keyboard::Scan::Scancode::Y, dr4::KeyCode::KEYCODE_Y},
        {sf::Keyboard::Scan::Scancode::Z, dr4::KeyCode::KEYCODE_Z},

        {sf::Keyboard::Scan::Scancode::Num0, dr4::KeyCode::KEYCODE_NUM0},
        {sf::Keyboard::Scan::Scancode::Num1, dr4::KeyCode::KEYCODE_NUM1},
        {sf::Keyboard::Scan::Scancode::Num2, dr4::KeyCode::KEYCODE_NUM2},
        {sf::Keyboard::Scan::Scancode::Num3, dr4::KeyCode::KEYCODE_NUM3},
        {sf::Keyboard::Scan::Scancode::Num4, dr4::KeyCode::KEYCODE_NUM4},
        {sf::Keyboard::Scan::Scancode::Num5, dr4::KeyCode::KEYCODE_NUM5},
        {sf::Keyboard::Scan::Scancode::Num6, dr4::KeyCode::KEYCODE_NUM6},
        {sf::Keyboard::Scan::Scancode::Num7, dr4::KeyCode::KEYCODE_NUM7},
        {sf::Keyboard::Scan::Scancode::Num8, dr4::KeyCode::KEYCODE_NUM8},
        {sf::Keyboard::Scan::Scancode::Num9, dr4::KeyCode::KEYCODE_NUM9},

        {sf::Keyboard::Scan::Scancode::Escape,     dr4::KeyCode::KEYCODE_ESCAPE},
        {sf::Keyboard::Scan::Scancode::LControl,   dr4::KeyCode::KEYCODE_LCONTROL},
        {sf::Keyboard::Scan::Scancode::LShift,     dr4::KeyCode::KEYCODE_LSHIFT},
        {sf::Keyboard::Scan::Scancode::LAlt,       dr4::KeyCode::KEYCODE_LALT},
        {sf::Keyboard::Scan::Scancode::LSystem,    dr4::KeyCode::KEYCODE_LSYSTEM},
        {sf::Keyboard::Scan::Scancode::RControl,   dr4::KeyCode::KEYCODE_RCONTROL},
        {sf::Keyboard::Scan::Scancode::RShift,     dr4::KeyCode::KEYCODE_RSHIFT},
        {sf::Keyboard::Scan::Scancode::RAlt,       dr4::KeyCode::KEYCODE_RALT},
        {sf::Keyboard::Scan::Scancode::RSystem,    dr4::KeyCode::KEYCODE_RSYSTEM},
        {sf::Keyboard::Scan::Scancode::Menu,       dr4::KeyCode::KEYCODE_MENU},
        {sf::Keyboard::Scan::Scancode::LBracket,   dr4::KeyCode::KEYCODE_LBRACKET},
        {sf::Keyboard::Scan::Scancode::RBracket,   dr4::KeyCode::KEYCODE_RBRACKET},
        {sf::Keyboard::Scan::Scancode::Semicolon,  dr4::KeyCode::KEYCODE_SEMICOLON},
        {sf::Keyboard::Scan::Scancode::Comma,      dr4::KeyCode::KEYCODE_COMMA},
        {sf::Keyboard::Scan::Scancode::Period,     dr4::KeyCode::KEYCODE_PERIOD},
        {sf::Keyboard::Scan::Scancode::Apostrophe, dr4::KeyCode::KEYCODE_QUOTE},
        {sf::Keyboard::Scan::Scancode::Slash,      dr4::KeyCode::KEYCODE_SLASH},
        {sf::Keyboard::Scan::Scancode::Backslash,  dr4::KeyCode::KEYCODE_BACKSLASH},
        {sf::Keyboard::Scan::Scancode::Grave,      dr4::KeyCode::KEYCODE_TILDE},
        {sf::Keyboard::Scan::Scancode::Equal,      dr4::KeyCode::KEYCODE_EQUAL},
        {sf::Keyboard::Scan::Scancode::Hyphen,     dr4::KeyCode::KEYCODE_HYPHEN},
        {sf::Keyboard::Scan::Scancode::Space,      dr4::KeyCode::KEYCODE_SPACE},
        {sf::Keyboard::Scan::Scancode::Enter,      dr4::KeyCode::KEYCODE_ENTER},
        {sf::Keyboard::Scan::Scancode::Backspace,  dr4::KeyCode::KEYCODE_BACKSPACE},
        {sf::Keyboard::Scan::Scancode::Tab,        dr4::KeyCode::KEYCODE_TAB},
        {sf::Keyboard::Scan::Scancode::PageUp,     dr4::KeyCode::KEYCODE_PAGEUP},
        {sf::Keyboard::Scan::Scancode::PageDown,   dr4::KeyCode::KEYCODE_PAGEDOWN},
        {sf::Keyboard::Scan::Scancode::End,        dr4::KeyCode::KEYCODE_END},
        {sf::Keyboard::Scan::Scancode::Home,       dr4::KeyCode::KEYCODE_HOME},
        {sf::Keyboard::Scan::Scancode::Insert,     dr4::KeyCode::KEYCODE_INSERT},
        {sf::Keyboard::Scan::Scancode::Delete,     dr4::KeyCode::KEYCODE_DELETE},

        {sf::Keyboard::Scan::Scancode::NumpadPlus,     dr4::KeyCode::KEYCODE_ADD},
        {sf::Keyboard::Scan::Scancode::NumpadMinus,    dr4::KeyCode::KEYCODE_SUBTRACT},
        {sf::Keyboard::Scan::Scancode::NumpadMultiply, dr4::KeyCode::KEYCODE_MULTIPLY},
        {sf::Keyboard::Scan::Scancode::NumpadDivide,   dr4::KeyCode::KEYCODE_DIVIDE},

        {sf::Keyboard::Scan::Scancode::Left,  dr4::KeyCode::KEYCODE_LEFT},
        {sf::Keyboard::Scan::Scancode::Right, dr4::KeyCode::KEYCODE_RIGHT},
        {sf::Keyboard::Scan::Scancode::Up,    dr4::KeyCode::KEYCODE_UP},
        {sf::Keyboard::Scan::Scancode::Down,  dr4::KeyCode::KEYCODE_DOWN},

        {sf::Keyboard::Scan::Scancode::Numpad0, dr4::KeyCode::KEYCODE_NUMPAD0},
        {sf::Keyboard::Scan::Scancode::Numpad1, dr4::KeyCode::KEYCODE_NUMPAD1},
        {sf::Keyboard::Scan::Scancode::Numpad2, dr4::KeyCode::KEYCODE_NUMPAD2},
        {sf::Keyboard::Scan::Scancode::Numpad3, dr4::KeyCode::KEYCODE_NUMPAD3},
        {sf::Keyboard::Scan::Scancode::Numpad4, dr4::KeyCode::KEYCODE_NUMPAD4},
        {sf::Keyboard::Scan::Scancode::Numpad5, dr4::KeyCode::KEYCODE_NUMPAD5},
        {sf::Keyboard::Scan::Scancode::Numpad6, dr4::KeyCode::KEYCODE_NUMPAD6},
        {sf::Keyboard::Scan::Scancode::Numpad7, dr4::KeyCode::KEYCODE_NUMPAD7},
        {sf::Keyboard::Scan::Scancode::Numpad8, dr4::KeyCode::KEYCODE_NUMPAD8},
        {sf::Keyboard::Scan::Scancode::Numpad9, dr4::KeyCode::KEYCODE_NUMPAD9},

        {sf::Keyboard::Scan::Scancode::F1, dr4::KeyCode::KEYCODE_F1},
        {sf::Keyboard::Scan::Scancode::F2, dr4::KeyCode::KEYCODE_F2},
        {sf::Keyboard::Scan::Scancode::F3, dr4::KeyCode::KEYCODE_F3},
        {sf::Keyboard::Scan::Scancode::F4, dr4::KeyCode::KEYCODE_F4},
        {sf::Keyboard::Scan::Scancode::F5, dr4::KeyCode::KEYCODE_F5},
        {sf::Keyboard::Scan::Scancode::F6, dr4::KeyCode::KEYCODE_F6},
        {sf::Keyboard::Scan::Scancode::F7, dr4::KeyCode::KEYCODE_F7},
        {sf::Keyboard::Scan::Scancode::F8, dr4::KeyCode::KEYCODE_F8},
        {sf::Keyboard::Scan::Scancode::F9, dr4::KeyCode::KEYCODE_F9},
        {sf::Keyboard::Scan::Scancode::F10, dr4::KeyCode::KEYCODE_F10},
        {sf::Keyboard::Scan::Scancode::F11, dr4::KeyCode::KEYCODE_F11},
        {sf::Keyboard::Scan::Scancode::F12, dr4::KeyCode::KEYCODE_F12},
        {sf::Keyboard::Scan::Scancode::F13, dr4::KeyCode::KEYCODE_F13},
        {sf::Keyboard::Scan::Scancode::F14, dr4::KeyCode::KEYCODE_F14},
        {sf::Keyboard::Scan::Scancode::F15, dr4::KeyCode::KEYCODE_F15},

        {sf::Keyboard::Scan::Scancode::Pause, dr4::KeyCode::KEYCODE_PAUSE},
    };

};

#endif // TABLE_EVENT_HPP
