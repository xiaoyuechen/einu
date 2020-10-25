// Copyright (C) 2020  Xiaoyue Chen
//
// This file is part of EINU Engine.
// See <https://github.com/xiaoyuechen/einu.git>.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <glad/glad.h>
#define STBI_NO_STDIO
#define STBI_NO_LINEAR
#define STBI_NO_HDR
#define STBI_ONLY_PNG
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <fstream>
#include <sstream>

#include "einu-engine/graphics/graphics_error.h"
#include "einu-engine/graphics/sys_resource.h"

namespace einu {
namespace graphics {
namespace sys {

namespace {
class Image {
  uint8_t* image_ = nullptr;
  int width_ = 0, height_ = 0, components_ = 0;

 public:
  explicit Image(const char* file_name);
  Image(const Image&) = delete;
  ~Image();

  int Width() const { return width_; }
  int Height() const { return height_; }
  int Components() const { return components_; }
  uint8_t* Data() const { return image_; }
};

Image::Image(const char* file_name) {
  auto file = std::ifstream(file_name, std::ios_base::binary);
  if (!file.is_open()) {
    throw GraphicsError{"Failed to open image file"};
  }
  auto buffer = std::stringstream{};
  buffer << file.rdbuf();
  auto content = buffer.str();
  auto cstr = content.c_str();

  const auto data = reinterpret_cast<const uint8_t*>(content.data());
  auto size = static_cast<int>(content.size());
  // flip to match openGL texture coords
  stbi_set_flip_vertically_on_load(true);
  image_ = stbi_load_from_memory(data, size, &width_, &height_, &components_,
                                 STBI_rgb_alpha);
  if (!image_) {
    throw GraphicsError{"could not read image"};
  }
}

Image::~Image() { stbi_image_free(image_); }

}  // namespace

template <>
void Create<ResourceType::Texture, const char*>(
    sgln::ResourceTable& resource_table, const char* name,
    const char* file_name) {
  auto img = Image(file_name);
  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.Width(), img.Height(), 0, GL_RGBA,
               GL_UNSIGNED_BYTE, img.Data());
  resource_table.table.emplace(std::make_pair(ResourceType::Texture, name),
                               texture);
  resource_table.texture_info_table.emplace(
      name, TextureInfo{img.Width(), img.Height()});
}

template <>
void Destroy<ResourceType::Texture>(sgln::ResourceTable& resource_table,
                                    const char* name) {
  auto it =
      resource_table.table.find(std::make_pair(ResourceType::Texture, name));
  auto texture = it->second;
  glDeleteTextures(1, &texture);
  resource_table.table.erase(it);
  resource_table.texture_info_table.erase(name);
}

}  // namespace sys
}  // namespace graphics
}  // namespace einu
