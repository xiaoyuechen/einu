#pragma once

#include <array>
#include <bitset>
#include <tuple>

#include "einu-engine/core/i_component.h"
#include "einu-engine/input/input_def.h"

namespace einu {
namespace comp {

struct Input : public Xnent {
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
  MouseButtonBufferMap mouse_button_buffer_map;
  KeyboardKeyBufferMap keyboard_key_buffer_map;
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
    return mouse_button_buffer_map[static_cast<MouseButtonBufferMap::size_type>(
        button)];
  }

  BoolBuffer& GetMouseButtonBuffer(MouseButton button) noexcept {
    return mouse_button_buffer_map[static_cast<MouseButtonBufferMap::size_type>(
        button)];
  }

  const BoolBuffer& GetKeyboadKeyBuffer(KeyboardKey key) const noexcept {
    return keyboard_key_buffer_map[static_cast<KeyboardKeyBufferMap::size_type>(
        key)];
  }

  BoolBuffer& GetKeyboadKeyBuffer(KeyboardKey key) noexcept {
    return keyboard_key_buffer_map[static_cast<KeyboardKeyBufferMap::size_type>(
        key)];
  }
};

}  // namespace comp
}  // namespace einu