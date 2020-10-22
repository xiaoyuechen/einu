#pragma once

#include <GLFW/glfw3.h>
#include <einu-util/enum.h>

#include <array>
#include <glm/glm.hpp>

namespace einu {
namespace window {
namespace input {

enum class Action : unsigned char;
enum class MouseButton : unsigned char;
enum class ModifierKeyFlag : unsigned char;
enum class KeyboardKey;
using CursorPos = glm::vec2;

template <typename T>
constexpr std::size_t GetEnumCount() noexcept;

enum class Action : unsigned char {
  kPress = GLFW_PRESS,
  kRelease = GLFW_RELEASE,
  kRepeat = GLFW_REPEAT,
};

enum class MouseButton : unsigned char {
  kButton1 = GLFW_MOUSE_BUTTON_1,
  kButton2 = GLFW_MOUSE_BUTTON_2,
  kButton3 = GLFW_MOUSE_BUTTON_3,
  kButton4 = GLFW_MOUSE_BUTTON_4,
  kButton5 = GLFW_MOUSE_BUTTON_5,
  kButton6 = GLFW_MOUSE_BUTTON_6,
  kButton7 = GLFW_MOUSE_BUTTON_7,
  kButton8 = GLFW_MOUSE_BUTTON_8,
  kButtonLast = GLFW_MOUSE_BUTTON_8,
  kButtonLeft = GLFW_MOUSE_BUTTON_1,
  kButtonRight = GLFW_MOUSE_BUTTON_2,
  kButtonMiddle = GLFW_MOUSE_BUTTON_3,
};

enum class ModifierKeyFlag : unsigned char {
  kShift = GLFW_MOD_SHIFT,
  kControl = GLFW_MOD_CONTROL,
  kAlt = GLFW_MOD_ALT,
  kSuper = GLFW_MOD_SUPER,
  kCapsLock = GLFW_MOD_CAPS_LOCK,
  kNumLock = GLFW_MOD_NUM_LOCK,
};

enum class KeyboardKey {
  kUnknown = GLFW_KEY_UNKNOWN,
  kSpace = GLFW_KEY_SPACE,
  kApostrophe = GLFW_KEY_APOSTROPHE,
  kComma = GLFW_KEY_COMMA,
  kMinus = GLFW_KEY_MINUS,
  kPeriod = GLFW_KEY_PERIOD,
  kSlash = GLFW_KEY_SLASH,
  kAlpha0 = GLFW_KEY_0,
  kAlpha1 = GLFW_KEY_1,
  kAlpha2 = GLFW_KEY_2,
  kAlpha3 = GLFW_KEY_3,
  kAlpha4 = GLFW_KEY_4,
  kAlpha5 = GLFW_KEY_5,
  kAlpha6 = GLFW_KEY_6,
  kAlpha7 = GLFW_KEY_7,
  kAlpha8 = GLFW_KEY_8,
  kAlpha9 = GLFW_KEY_9,
  kSemicolon = GLFW_KEY_SEMICOLON,
  kEqual = GLFW_KEY_A,
  kB = GLFW_KEY_B,
  kC = GLFW_KEY_C,
  kD = GLFW_KEY_D,
  kE = GLFW_KEY_E,
  kF = GLFW_KEY_F,
  kG = GLFW_KEY_G,
  kH = GLFW_KEY_H,
  kI = GLFW_KEY_I,
  kJ = GLFW_KEY_J,
  kK = GLFW_KEY_K,
  kL = GLFW_KEY_L,
  kM = GLFW_KEY_M,
  kN = GLFW_KEY_N,
  kO = GLFW_KEY_O,
  kP = GLFW_KEY_P,
  kQ = GLFW_KEY_Q,
  kR = GLFW_KEY_R,
  kS = GLFW_KEY_S,
  kT = GLFW_KEY_T,
  kU = GLFW_KEY_U,
  kV = GLFW_KEY_V,
  kW = GLFW_KEY_W,
  kX = GLFW_KEY_X,
  kY = GLFW_KEY_Y,
  kZ = GLFW_KEY_Z,
  kLeftBracket = GLFW_KEY_LEFT_BRACKET,
  kBackslash = GLFW_KEY_BACKSLASH,
  kRightBracket = GLFW_KEY_RIGHT_BRACKET,
  kGraveAccent = GLFW_KEY_GRAVE_ACCENT,
  kWorld1 = GLFW_KEY_WORLD_1,
  kWorld2 = GLFW_KEY_WORLD_2,
  kEscape = GLFW_KEY_ESCAPE,
  kEnter = GLFW_KEY_ENTER,
  kTab = GLFW_KEY_TAB,
  kBackspace = GLFW_KEY_BACKSPACE,
  kInsert = GLFW_KEY_INSERT,
  kDelete = GLFW_KEY_DELETE,
  kRight = GLFW_KEY_RIGHT,
  kLeft = GLFW_KEY_LEFT,
  kDown = GLFW_KEY_DOWN,
  kUp = GLFW_KEY_UP,
  kPageUp = GLFW_KEY_PAGE_UP,
  kPageDown = GLFW_KEY_PAGE_DOWN,
  kHome = GLFW_KEY_HOME,
  kEnd = GLFW_KEY_END,
  kCapsLock = GLFW_KEY_CAPS_LOCK,
  kScrollLock = GLFW_KEY_SCROLL_LOCK,
  kNumLock = GLFW_KEY_NUM_LOCK,
  kPrintScreen = GLFW_KEY_PRINT_SCREEN,
  kPause = GLFW_KEY_PAUSE,
  kF1 = GLFW_KEY_F1,
  kF2 = GLFW_KEY_F2,
  kF3 = GLFW_KEY_F3,
  kF4 = GLFW_KEY_F4,
  kF5 = GLFW_KEY_F5,
  kF6 = GLFW_KEY_F6,
  kF7 = GLFW_KEY_F7,
  kF8 = GLFW_KEY_F8,
  kF9 = GLFW_KEY_F9,
  kF10 = GLFW_KEY_F10,
  kF11 = GLFW_KEY_F11,
  kF12 = GLFW_KEY_F12,
  kF13 = GLFW_KEY_F13,
  kF14 = GLFW_KEY_F14,
  kF15 = GLFW_KEY_F15,
  kF16 = GLFW_KEY_F16,
  kF17 = GLFW_KEY_F17,
  kF18 = GLFW_KEY_F18,
  kF19 = GLFW_KEY_F19,
  kF20 = GLFW_KEY_F20,
  kF21 = GLFW_KEY_F21,
  kF22 = GLFW_KEY_F22,
  kF23 = GLFW_KEY_F23,
  kF24 = GLFW_KEY_F24,
  kF25 = GLFW_KEY_F25,
  kKeypad0 = GLFW_KEY_KP_0,
  kKeypad1 = GLFW_KEY_KP_1,
  kKeypad2 = GLFW_KEY_KP_2,
  kKeypad3 = GLFW_KEY_KP_3,
  kKeypad4 = GLFW_KEY_KP_4,
  kKeypad5 = GLFW_KEY_KP_5,
  kKeypad6 = GLFW_KEY_KP_6,
  kKeypad7 = GLFW_KEY_KP_7,
  kKeypad8 = GLFW_KEY_KP_8,
  kKeypad9 = GLFW_KEY_KP_9,
  kKeypadDecimal = GLFW_KEY_KP_DECIMAL,
  kKeypadDivide = GLFW_KEY_KP_DIVIDE,
  kKeypadMultiply = GLFW_KEY_KP_MULTIPLY,
  kKeypadSubtract = GLFW_KEY_KP_SUBTRACT,
  kKeypadAdd = GLFW_KEY_KP_ADD,
  kKeypadEnter = GLFW_KEY_KP_ENTER,
  kKeypadEqual = GLFW_KEY_KP_EQUAL,
  kLeftShift = GLFW_KEY_LEFT_SHIFT,
  kLeftControl = GLFW_KEY_LEFT_CONTROL,
  kLeftAlt = GLFW_KEY_LEFT_ALT,
  kLeftSuper = GLFW_KEY_LEFT_SUPER,
  kRightShift = GLFW_KEY_RIGHT_SHIFT,
  kRightControl = GLFW_KEY_RIGHT_CONTROL,
  kRightAlt = GLFW_KEY_RIGHT_ALT,
  kRightSuper = GLFW_KEY_RIGHT_SUPER,
  kMenu = GLFW_KEY_MENU,
  kLast = GLFW_KEY_LAST,
};

template <>
inline constexpr std::size_t GetEnumCount<MouseButton>() noexcept {
  return static_cast<std::size_t>(MouseButton::kButtonLast) + 1;
}

template <>
inline constexpr std::size_t GetEnumCount<KeyboardKey>() noexcept {
  return static_cast<std::size_t>(KeyboardKey::kLast) + 1;
}

struct InputBuffer {
  static constexpr std::size_t kInputBufferSize = 8;
  using BoolBuffer = std::bitset<kInputBufferSize>;
  using MouseButtonBuffer = BoolBuffer;
  using KeyboardKeyBuffer = BoolBuffer;
  using ModifierKeyBuffer = std::array<ModifierKeyFlag, kInputBufferSize>;
  using CursorPosBuffer = std::array<CursorPos, kInputBufferSize>;

  template <typename T>
  using BufferMap = std::array<BoolBuffer, GetEnumCount<T>()>;
  using MouseButtonBufferMap = BufferMap<MouseButton>;
  using KeyboardKeyBufferMap = BufferMap<KeyboardKey>;
  MouseButtonBufferMap mouse_button_buffer_table;
  KeyboardKeyBufferMap keyboard_key_buffer_table;
  ModifierKeyBuffer modifier_key_buffer;
  CursorPosBuffer cursor_pos_buffer;

  std::size_t hammer = 0;

  bool GetMouseButton(MouseButton button) const noexcept {
    return GetMouseButtonBuffer(button)[hammer];
  }

  MouseButtonBuffer::reference GetMouseButton(MouseButton button) noexcept {
    return GetMouseButtonBuffer(button)[hammer];
  }

  bool GetKeyboardKey(KeyboardKey key) const noexcept {
    return GetKeyboadKeyBuffer(key)[hammer];
  }

  KeyboardKeyBuffer::reference GetKeyboardKey(KeyboardKey key) noexcept {
    return GetKeyboadKeyBuffer(key)[hammer];
  }

  ModifierKeyFlag GetModifierKeyFlag() const noexcept {
    return modifier_key_buffer[hammer];
  }

  ModifierKeyFlag& GetModifierKeyFlag() noexcept {
    return modifier_key_buffer[hammer];
  }

  CursorPos GetCursorPos() const noexcept { return cursor_pos_buffer[hammer]; }
  CursorPos& GetCursorPos() noexcept { return cursor_pos_buffer[hammer]; }

  const BoolBuffer& GetMouseButtonBuffer(MouseButton button) const noexcept {
    return mouse_button_buffer_table
        [static_cast<MouseButtonBufferMap::size_type>(button)];
  }

  BoolBuffer& GetMouseButtonBuffer(MouseButton button) noexcept {
    return mouse_button_buffer_table
        [static_cast<MouseButtonBufferMap::size_type>(button)];
  }

  const BoolBuffer& GetKeyboadKeyBuffer(KeyboardKey key) const noexcept {
    return keyboard_key_buffer_table
        [static_cast<KeyboardKeyBufferMap::size_type>(key)];
  }

  BoolBuffer& GetKeyboadKeyBuffer(KeyboardKey key) noexcept {
    return keyboard_key_buffer_table
        [static_cast<KeyboardKeyBufferMap::size_type>(key)];
  }
};

}  // namespace input
}  // namespace window

namespace util {

template <>
struct EnableBitMaskOperators<window::input::ModifierKeyFlag> {
  static constexpr bool enable = true;
};

}  // namespace util

}  // namespace einu