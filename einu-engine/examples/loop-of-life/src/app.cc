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

#include "src/app.h"

#include <einu-engine/common/sys_movement.h>
#include <einu-engine/common/sys_time.h>
#include <einu-engine/core/einu_engine.h>
#include <einu-engine/core/entity_view.h>
#include <einu-engine/graphics/cmp_camera.h>
#include <einu-engine/graphics/sys_render.h>
#include <einu-engine/graphics/sys_resource.h>
#include <einu-engine/graphics/sys_sprite_render.h>
#include <einu-engine/window/sys_window.h>

#include <iostream>
#include <random>

#include "src/bt_agent.h"
#include "src/engine_policy.h"
#include "src/sys_agent_create.h"
#include "src/sys_destroy.h"
#include "src/sys_lose_health.h"
#include "src/sys_movement.h"
#include "src/sys_rotate.h"
#include "src/sys_sense.h"
#include "src/sys_world_state.h"

namespace lol {

void App::Run() {
  Engine engine;

  auto eid_pool = engine.CreateEIDPool();
  auto comp_pool = engine.CreateComponentPool();
  auto sgln_pool = engine.CreateSinglenentPool();
  auto ett_mgr = engine.CreateEntityManager();
  ett_mgr->SetEIDPool(*eid_pool);
  ett_mgr->SetComponentPool(*comp_pool);
  ett_mgr->SetSinglenentPool(*sgln_pool);

  auto eid = ett_mgr->CreateEntity();
  auto& win = ett_mgr->AddComponent<einu::window::cmp::Window>(eid);
  win.title = "Loop of Life";
  win.size.width = 1080;
  win.size.height = 720;

  auto& time = ett_mgr->AddSinglenent<einu::sgl::Time>();
  auto& world_state = ett_mgr->AddSinglenent<sgl::WorldState>();
  world_state.grid = sgl::WorldState::Grid(glm::uvec2{160, 90});
  world_state.world_size = glm::vec2{win.size.width, win.size.height};

  auto& resource_table =
      ett_mgr->AddSinglenent<einu::graphics::sgl::GLResourceTable>();

  auto& sprite_batch =
      ett_mgr->AddSinglenent<einu::graphics::sgl::SpriteBatch>();

  {
    using namespace einu::window::sys;  // NOLINT
    Init();
    Create(win);
  }

  { einu::sys::InitTime(time); }

  {
    using namespace einu::graphics::sys;  // NOLINT
    using ResourceType = einu::graphics::ResourceType;

    LoadGL(win);

    auto vao = Create<ResourceType::VertexArray>(resource_table, "vao");
    auto vbo1 = Create<ResourceType::VertexBuffer>(resource_table, "vbo1");
    auto vbo2 = Create<ResourceType::VertexBuffer>(resource_table, "vbo2");
    Create<ResourceType::VertexShader>(resource_table, "vshader",
                                       "shaders/sprite_vertex_shader.glsl");
    Create<ResourceType::FragmentShader>(resource_table, "fshader",
                                         "shaders/sprite_fragment_shader.glsl");
    Create<ResourceType::ShaderProgram>(resource_table, "program", "vshader",
                                        "fshader");
    Create<ResourceType::Texture>(resource_table, "white-triangle",
                                  "assets/white-triangle.png");
    Create<ResourceType::Sampler>(resource_table, "sampler");

    auto& tex_info = resource_table.tex_info_table.at("white-triangle");

    CreateSprite(resource_table, sys::kSheepSpriteName, "program",
                 "white-triangle");
    auto& sheep_sprite = resource_table.sprite_table.at(sys::kSheepSpriteName);
    for (auto&& vert : sheep_sprite.verts) {
      vert.pos.x -= static_cast<float>(tex_info.size.x) / 2;
    }

    einu::graphics::sys::CreateSprite(resource_table, sys::kWolfSpriteName,
                                      "program", "white-triangle");
    auto& wolf_sprite = resource_table.sprite_table.at(sys::kWolfSpriteName);
    for (auto&& vert : wolf_sprite.verts) {
      vert.pos.x -= static_cast<float>(tex_info.size.x) / 2;
    }
  }

  einu::graphics::sys::InitSpriteBatch(resource_table, sprite_batch, "vao",
                                       "vbo1", "vbo2", "sampler");

  {
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<int> distribution_x(0, win.size.width);
    std::uniform_int_distribution<int> distribution_y(0, win.size.height);
    std::uniform_real_distribution<float> distribution_rotate(0, 360);

    for (std::size_t i = 0; i != 100; ++i) {
      auto transform = einu::Transform{};
      transform.SetPosition(
          glm::vec3(distribution_x(generator), distribution_y(generator), 0));
      transform.SetRotation(glm::quat(
          glm::vec3(0, 0, glm::radians(distribution_rotate(generator)))));
      transform.SetScale(glm::vec3(0.02f, 0.05f, 1.f));
      sys::CreateSheep(*ett_mgr, transform);
    }

    for (std::size_t i = 0; i != 10; ++i) {
      auto transform = einu::Transform{};
      transform.SetPosition(
          glm::vec3(distribution_x(generator), distribution_y(generator), 0));
      transform.SetRotation(glm::quat(
          glm::vec3(0, 0, glm::radians(distribution_rotate(generator)))));
      transform.SetScale(glm::vec3(0.04f, 0.10f, 1.f));
      sys::CreateWolf(*ett_mgr, transform);
    }
  }

  auto proj = einu::graphics::Projection{
      einu::graphics::Projection::Type::Orthographic,
      einu::graphics::Projection::OrthographicAttrib{
          -160, 160.f + win.size.width, -90, 90.f + win.size.height}};

  auto cam_mat = einu::graphics::ProjectionMatrix(proj) *
                 einu::graphics::ViewMatrix(einu::graphics::View{});

  auto cell_buffer = sys::CellBuffer{};

  einu::ai::bt::ArgPack sheep_bt_args;
  auto sheep_bt = ai::bt::BuildSheepBT(*ett_mgr);

  auto destroy_view = einu::EntityView<einu::XnentList<const cmp::Health>>{};

  auto forget_view = einu::EntityView<einu::XnentList<cmp::Memory>>{};

  auto ett_view = einu::EntityView<einu::XnentList<
      einu::cmp::Transform, einu::graphics::cmp::Sprite, einu::cmp::Movement,
      einu::ai::cmp::Destination, cmp::Agent>>{};

  auto health_loss_view =
      einu::EntityView<einu::XnentList<const cmp::HealthLoss, cmp::Health>>{};

  auto move_view = einu::EntityView<
      einu::XnentList<einu::cmp::Transform, einu::cmp::Movement>>{};

  auto sheep_view = einu::EntityView<einu::XnentList<
      einu::cmp::Transform, einu::graphics::cmp::Sprite, einu::cmp::Movement,
      einu::ai::cmp::Destination, cmp::Agent, cmp::Eat, cmp::Evade, cmp::Health,
      cmp::HealthLoss, cmp::Hunger, cmp::Hunt, cmp::Memory, cmp::Panick,
      cmp::Sense, cmp::Wander>>{};

  auto sprite_render_view = einu::EntityView<
      einu::XnentList<einu::cmp::Transform, einu::graphics::cmp::Sprite>>{};

  while (!win.shouldClose) {
    einu::window::sys::PoolEvents(win);
    einu::graphics::sys::Clear();

    einu::sys::UpdateTime(time);
    std::cout << "ft: " << einu::sgl::DeltaSeconds(time) << std::endl;

    ett_view.View(*ett_mgr);

    sys::ClearWorldState(world_state);
    for (auto [comp_it, eid_it] =
             std::tuple{ett_view.Components().begin(), ett_view.EIDs().begin()};
         comp_it != ett_view.Components().end(); ++comp_it, ++eid_it) {
      auto&& [transform, sprite, movement, dest, agent] = *comp_it;
      sys::UpdateWorldState(world_state, transform, agent, *eid_it);
    }

    forget_view.View(*ett_mgr);
    for (auto&& [memory] : forget_view.Components()) {
      sys::Forget(memory);
    }

    sheep_view.View(*ett_mgr);
    for (auto [comp_it, eid_it] = std::tuple{sheep_view.Components().begin(),
                                             sheep_view.EIDs().begin()};
         comp_it != sheep_view.Components().end(); ++comp_it, ++eid_it) {
      auto& comps = *comp_it;
      sys::Sense(world_state, cell_buffer, std::get<cmp::Sense&>(comps),
                 std::get<einu::cmp::Transform&>(comps),
                 std::get<cmp::Memory&>(comps), *eid_it);
      sheep_bt_args.Set(*eid_it, *comp_it);
      sheep_bt.Run(sheep_bt_args);
    }

    health_loss_view.View(*ett_mgr);
    for (auto&& [health_loss, health] : health_loss_view.Components()) {
      sys::LoseHealth(time, health_loss, health);
    }

    // move and rotate
    move_view.View(*ett_mgr);
    for (auto&& [transform, movement] : move_view.Components()) {
      sys::Move(time, world_state, transform, movement);
      sys::Rotate(transform, movement);
    }

    // entity destruction
    destroy_view.View(*ett_mgr);
    for (auto [comp, eid] = std::make_tuple(destroy_view.Components().begin(),
                                            destroy_view.EIDs().begin());
         comp != destroy_view.Components().end(); ++comp, ++eid) {
      auto& [health] = *comp;
      sys::Destroy(*ett_mgr, health, *eid);
    }

    // render sprites
    sprite_render_view.View(*ett_mgr);
    einu::graphics::sys::ClearSpriteBatch(sprite_batch);
    for (auto&& [transform, sprite] : sprite_render_view.Components()) {
      einu::graphics::sys::PrepareSpriteBatch(resource_table, sprite_batch,
                                              sprite, transform);
    }
    einu::graphics::sys::RenderSpriteBatch(sprite_batch, cam_mat);

    einu::window::sys::SwapBuffer(win);
  }
}

}  // namespace lol
