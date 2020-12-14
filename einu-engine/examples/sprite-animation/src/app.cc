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

#include <iostream>
#include <random>

#include "einu-engine/common/sys_movement.h"
#include "einu-engine/common/sys_time.h"
#include "einu-engine/core/einu_engine.h"
#include "einu-engine/core/entity_view.h"
#include "einu-engine/graphics/cmp_camera.h"
#include "einu-engine/graphics/sys_render.h"
#include "einu-engine/graphics/sys_resource.h"
#include "einu-engine/graphics/sys_sprite_render.h"
#include "einu-engine/window/sys_window.h"

namespace sprite_animation {

void App::Run() {
  using namespace einu;  // NOLINT

  using ComponentList = XnentList<window::cmp::Window, graphics::cmp::Sprite,
                                  cmp::Transform, cmp::Movement>;
  using SinglenentList = XnentList<graphics::sgl::GLResourceTable,
                                   graphics::sgl::SpriteBatch, sgl::Time>;
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

  auto& time = ett_mgr->AddSinglenent<sgl::Time>();

  auto& resource_table =
      ett_mgr->AddSinglenent<graphics::sgl::GLResourceTable>();

  window::sys::Init();

  window::sys::Create(win_comp);
  window::sys::MakeContextCurrent(win_comp);

  graphics::sys::LoadGL(win_comp);

  auto vao = graphics::sys::Create<graphics::ResourceType::VertexArray>(
      resource_table, "vao");
  auto vbo1 = graphics::sys::Create<graphics::ResourceType::VertexBuffer>(
      resource_table, "vbo1");
  auto vbo2 = graphics::sys::Create<graphics::ResourceType::VertexBuffer>(
      resource_table, "vbo2");
  graphics::sys::Create<graphics::ResourceType::VertexShader>(
      resource_table, "vshader", "shaders/sprite_vertex_shader.glsl");
  graphics::sys::Create<graphics::ResourceType::FragmentShader>(
      resource_table, "fshader", "shaders/sprite_fragment_shader.glsl");
  graphics::sys::Create<graphics::ResourceType::ShaderProgram>(
      resource_table, "program", "vshader", "fshader");
  graphics::sys::Create<graphics::ResourceType::Texture>(
      resource_table, "white-triangle", "assets/white-triangle.png");
  graphics::sys::CreateSprite(resource_table, "sprite", "program",
                              "white-triangle");
  graphics::sys::Create<graphics::ResourceType::Sampler>(resource_table,
                                                         "sampler");

  auto& sprite_batch = ett_mgr->AddSinglenent<graphics::sgl::SpriteBatch>();
  graphics::sys::InitSpriteBatch(resource_table, sprite_batch, "vao", "vbo1",
                                 "vbo2", "sampler");

  std::random_device device;
  std::mt19937 generator(device());
  std::uniform_int_distribution<int> distribution_x(0, 1920);
  std::uniform_int_distribution<int> distribution_y(0, 1080);
  std::uniform_real_distribution<float> distribution_rotate(0, 360);

  for (std::size_t i = 0; i != 1000; ++i) {
    auto ett = ett_mgr->CreateEntity();
    auto& sprite = ett_mgr->AddComponent<graphics::cmp::Sprite>(ett);
    sprite.sprite_name = "sprite";
    auto& transform = ett_mgr->AddComponent<cmp::Transform>(ett);
    transform.SetPosition(
        glm::vec3(distribution_x(generator), distribution_y(generator), 0));
    transform.SetRotation(glm::quat(
        glm::vec3(0, 0, glm::radians(distribution_rotate(generator)))));
    transform.SetScale(glm::vec3(0.05f, 0.1f, 1.f));
    auto& movement = ett_mgr->AddComponent<cmp::Movement>(ett);
    movement.direction = glm::vec3(1, 0, 0);
    movement.speed = 10.f;
  }

  auto& s = ett_mgr->GetComponent<graphics::cmp::Sprite>(1);

  auto ett_view = EntityView<
      XnentList<cmp::Transform, graphics::cmp::Sprite, cmp::Movement>>{};

  auto proj = graphics::Projection{
      graphics::Projection::Type::Orthographic,
      graphics::Projection::OrthographicAttrib{0, 1920, 0, 1080}};

  auto cam_mat =
      graphics::ProjectionMatrix(proj) * graphics::ViewMatrix(graphics::View{});

  sys::InitTime(time);
  while (!win_comp.shouldClose) {
    graphics::sys::Clear();

    sys::UpdateTime(time);
    std::cout << "ft: " << sgl::DeltaSeconds(time) << std::endl;

    ett_view.View(*ett_mgr);
    for (auto&& [transform, sprite, movement] : ett_view.Components()) {
      sys::Move(transform, movement, time);
      graphics::sys::PrepareSpriteBatch(resource_table, sprite_batch, sprite,
                                        transform);
    }
    graphics::sys::RenderSpriteBatch(sprite_batch, cam_mat);
    graphics::sys::ClearSpriteBatch(sprite_batch);

    window::sys::PoolEvents(win_comp);
    window::sys::SwapBuffer(win_comp);
  }

  // graphics::sys::Destroy<graphics::ResourceType::ShaderProgram>(resource_table,
  //                                                              "program");
  // graphics::sys::Destroy<graphics::ResourceType::FragmentShader>(resource_table,
  //                                                               "fshader");
  // graphics::sys::Destroy<graphics::ResourceType::VertexShader>(resource_table,
  //                                                             "vshader");
  // graphics::sys::Destroy<graphics::ResourceType::VertexArray>(resource_table,
  //                                                            "vao");
}

}  // namespace sprite_animation
