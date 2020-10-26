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
// along with this program.  If not, see
// <https://www.gnu.org/licenses/>.

#include "sprite-animation/app.h"

#include <einu-engine/core/einu_engine.h>
#include <einu-engine/core/entity_view.h>
#include <einu-engine/graphics/sys_render.h>
#include <einu-engine/graphics/sys_resource.h>
#include <einu-engine/graphics/sys_sprite_render.h>
#include <einu-engine/window/sys_window.h>

#include <iostream>

namespace sprite_animation {

void App::Run() {
  using namespace einu;  // NOLINT

  using ComponentList = XnentList<window::cmp::Window, graphics::cmp::Sprite,
                                  common::cmp::Transform>;
  using SinglenentList =
      XnentList<graphics::sgl::ResourceTable, graphics::sgl::SpriteBatch>;
  using NeedList = NeedList<ComponentList, SinglenentList>;
  using EnginePolicy = EnginePolicy<NeedList>;
  using Engine = EinuEngine<EnginePolicy>;

  Engine engine;

  auto eid_pool = engine.CreateEIDPool();
  auto comp_pool = engine.CreateComponentPool();
  auto sgln_pool = engine.CreateSinglenentPool();
  auto ett_mgr = engine.CreateEntityManager();
  ett_mgr->SetEIDPool(*eid_pool);
  ett_mgr->SetComponentPool(*comp_pool);
  ett_mgr->SetSinglenentPool(*sgln_pool);

  auto eid = ett_mgr->CreateEntity();
  auto& win_comp = ett_mgr->AddComponent<window::cmp::Window>(eid);

  auto& resource_table = ett_mgr->AddSinglenent<graphics::sgl::ResourceTable>();

  window::sys::Init();

  window::sys::Create(win_comp);
  window::sys::MakeContextCurrent(win_comp);

  graphics::sys::LoadGL();

  graphics::sys::Create<graphics::ResourceType::VertexArray>(resource_table,
                                                             "vao");
  graphics::sys::Create<graphics::ResourceType::VertexBuffer>(resource_table,
                                                              "vbo1");
  graphics::sys::Create<graphics::ResourceType::VertexBuffer>(resource_table,
                                                              "vbo2");
  graphics::sys::Create<graphics::ResourceType::VertexShader>(
      resource_table, "vshader", "shaders/sprite_vertex_shader.glsl");
  graphics::sys::Create<graphics::ResourceType::FragmentShader>(
      resource_table, "fshader", "shaders/sprite_fragment_shader.glsl");
  graphics::sys::Create<graphics::ResourceType::ShaderProgram>(
      resource_table, "program", "vshader", "fshader");
  graphics::sys::Create<graphics::ResourceType::Texture>(
      resource_table, "white-triangle", "assets/white-triangle.png");

  using ResourceKey = graphics::sgl::ResourceTable::Key;

  auto shader = resource_table.table.at(
      ResourceKey{graphics::ResourceType::ShaderProgram, "program"});

  auto wtri_tex = resource_table.table.at(
      ResourceKey{graphics::ResourceType::Texture, "white-triangle"});

  auto& sprite_batch = ett_mgr->AddSinglenent<graphics::sgl::SpriteBatch>();
  graphics::sys::InitSpriteBatch(
      sprite_batch,
      resource_table.table.at(
          ResourceKey(graphics::ResourceType::VertexArray, "vao")),
      resource_table.table.at(
          ResourceKey(graphics::ResourceType::VertexBuffer, "vbo1")),
      resource_table.table.at(
          ResourceKey(graphics::ResourceType::VertexBuffer, "vbo2")));
  for (std::size_t i = 0; i != 100; ++i) {
    auto ett = ett_mgr->CreateEntity();
    auto& sprite = ett_mgr->AddComponent<graphics::cmp::Sprite>(ett);
    sprite.shader = shader;
    sprite.texture = wtri_tex;
    ett_mgr->AddComponent<common::cmp::Transform>(ett);
  }

  auto& s = ett_mgr->GetComponent<graphics::cmp::Sprite>(1);

  auto view =
      EntityView<XnentList<common::cmp::Transform, graphics::cmp::Sprite>>{};
  view.View(*ett_mgr);

  for (auto eid : view.EIDs()) {
    auto shader = ett_mgr->GetComponent<graphics::cmp::Sprite>(eid).shader;
    std::cout << eid << "<shader>: " << shader << std::endl;
  }

  for (auto&& [transform, sprite] : view.Components()) {
    int i = 0;
  }

  while (!win_comp.shouldClose) {
    for (auto&& [transform, sprite] : view.Components()) {
      graphics::sys::PrepareSpriteBatch(sprite_batch, sprite, transform);
    }
    graphics::sys::RenderSpriteBatch(sprite_batch, glm::mat4{});

    window::sys::PoolEvents(win_comp);
    window::sys::SwapBuffer(win_comp);
  }

  graphics::sys::Destroy<graphics::ResourceType::ShaderProgram>(resource_table,
                                                                "program");
  graphics::sys::Destroy<graphics::ResourceType::FragmentShader>(resource_table,
                                                                 "fshader");
  graphics::sys::Destroy<graphics::ResourceType::VertexShader>(resource_table,
                                                               "vshader");
  graphics::sys::Destroy<graphics::ResourceType::VertexArray>(resource_table,
                                                              "vao");
}

}  // namespace sprite_animation
