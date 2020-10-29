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

#include <einu-engine/common/random.h>
#include <einu-engine/common/sys_movement.h>
#include <einu-engine/common/sys_time.h>
#include <einu-engine/core/einu_engine.h>
#include <einu-engine/core/entity_view.h>
#include <einu-engine/graphics/cmp_camera.h>
#include <einu-engine/graphics/sys_render.h>
#include <einu-engine/graphics/sys_resource.h>
#include <einu-engine/graphics/sys_sprite_render.h>
#include <einu-engine/window/sys_window.h>

#include <cstdlib>
#include <iostream>
#include <random>

#include "src/engine_policy.h"
#include "src/sys_cell.h"
#include "src/sys_create_entity.h"
#include "src/sys_find_path.h"
#include "src/sys_movement.h"
#include "src/sys_rotate.h"
#include "src/sys_starchaser.h"

namespace astar {

void App::Run() {
  // init engine
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
  win.title = "A*";
  win.size.width = 1080;
  win.size.height = 1080;

  auto& time = ett_mgr->AddSinglenent<einu::sgl::Time>();
  auto& world_state = ett_mgr->AddSinglenent<sgl::WorldState>();
  world_state.grid = sgl::WorldState::Grid(glm::uvec2{12, 12});
  world_state.world_size = glm::vec2{12 * 32, 12 * 32};

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

  // init graphics
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
                                  "assets/white_triangle.png");
    Create<ResourceType::Texture>(resource_table, "white-circle",
                                  "assets/white_circle.png");
    Create<ResourceType::Texture>(resource_table, "white-frame",
                                  "assets/white_frame.png");
    Create<ResourceType::Texture>(resource_table, "white-cross",
                                  "assets/white_cross.png");

    Create<ResourceType::Sampler>(resource_table, "sampler");

    InitSpriteBatch(resource_table, sprite_batch, "vao", "vbo1", "vbo2",
                    "sampler");

    CreateSprite(resource_table, sys::kCellFrameSprite, "program",
                 "white-frame");

    CreateSprite(resource_table, sys::kCellBlockSprite, "program",
                 "white-cross");

    CreateSprite(resource_table, sys::kSpaceshipSprite, "program",
                 "white-circle");

    CreateSprite(resource_table, sys::kTradingPostSprite, "program",
                 "white-circle");

    CreateSprite(resource_table, sys::kStarSprite, "program", "white-circle");

    CreateSprite(resource_table, sys::kStarchaserSprite, "program",
                 "white-triangle");

    auto& triangle_tex_info =
        resource_table.tex_info_table.at("white-triangle");

    auto& starchaser_sprite =
        resource_table.sprite_table.at(sys::kStarchaserSprite);
    for (auto&& vert : starchaser_sprite.verts) {
      vert.pos.x -= static_cast<float>(triangle_tex_info.size.x) / 2.f;
    }
  }

  // init grid
  {
    std::srand(std::time(nullptr));
    for (std::size_t i = 0; i != world_state.grid.GetSize().x; ++i) {
      for (std::size_t j = 0; j != world_state.grid.GetSize().y; ++j) {
        std::uint8_t blocked = std::rand() % 4;
        blocked = blocked > 1 ? 1 : blocked;
        world_state.grid[i][j].state = static_cast<CellState>(blocked);
      }
    }
  }

  // create cells
  {
    auto cell_size = sgl::GetCellSize(world_state);
    auto transform = einu::Transform{};
    sys::CreateCellFrame(*ett_mgr, transform);

    for (std::size_t i = 0; i != world_state.grid.GetSize().x; ++i) {
      for (std::size_t j = 0; j != world_state.grid.GetSize().y; ++j) {
        auto cell_size = sgl::GetCellSize(world_state);
        auto pos = glm::vec3(i * cell_size.x, j * cell_size.y, 0);
        auto transform = einu::Transform{};
        transform.SetPosition(pos);
        world_state.grid[i][j].eid = sys::CreateCellFrame(*ett_mgr, transform);
        sys::CreateCellBlock(*ett_mgr, transform);
      }
    }
  }

  // create trading post
  {
    bool created = false;
    while (!created) {
      auto x = std::rand() % world_state.grid.GetSize().x;
      auto y = std::rand() % world_state.grid.GetSize().y;
      auto& cell = world_state.grid[x][y];
      if (cell.state != CellState::Blocked) {
        auto cell_size = sgl::GetCellSize(world_state);
        auto pos = glm::vec3(cell_size.x * x, cell_size.y * y, 0);
        auto transform = einu::Transform{};
        transform.SetPosition(pos + glm::vec3(3, 3, 0));
        transform.SetScale(glm::vec3(0.2f, 0.2f, 0));
        sys::CreateTradingPost(*ett_mgr, transform);
        created = true;
      }
    }
  }

  // create spaceship
  {
    bool created = false;
    while (!created) {
      auto x = std::rand() % world_state.grid.GetSize().x;
      auto y = std::rand() % world_state.grid.GetSize().y;
      auto& cell = world_state.grid[x][y];
      if (cell.state != CellState::Blocked) {
        auto cell_size = sgl::GetCellSize(world_state);
        auto pos = glm::vec3(cell_size.x * x, cell_size.y * y, 0);
        auto transform = einu::Transform{};
        transform.SetPosition(pos + glm::vec3(3, 3, 0));
        if (glm::vec2(transform.GetPosition()) !=
            world_state.trading_post_pos) {
          transform.SetScale(glm::vec3(0.2f, 0.2f, 0));
          sys::CreateSpaceship(*ett_mgr, transform);
          created = true;
        }
      }
    }
  }

  // create star
  {
    bool created = false;
    while (!created) {
      auto x = std::rand() % world_state.grid.GetSize().x;
      auto y = std::rand() % world_state.grid.GetSize().y;
      auto& cell = world_state.grid[x][y];
      if (cell.state != CellState::Blocked) {
        auto cell_size = sgl::GetCellSize(world_state);
        auto pos = glm::vec3(cell_size.x * x, cell_size.y * y, 0);
        auto transform = einu::Transform{};
        transform.SetPosition(pos + glm::vec3(3, 3, 0));
        if (glm::vec2(transform.GetPosition()) !=
                world_state.trading_post_pos &&
            glm::vec2(transform.GetPosition()) != world_state.space_ship_pos) {
          transform.SetScale(glm::vec3(0.2f, 0.2f, 0));
          sys::CreateStar(*ett_mgr, transform);
          created = true;
        }
      }
    }
  }

  // create starchaser
  auto starchaser = einu::EID{};
  {
    bool created = false;
    while (!created) {
      auto x = std::rand() % world_state.grid.GetSize().x;
      auto y = std::rand() % world_state.grid.GetSize().y;
      auto& cell = world_state.grid[x][y];
      if (cell.state != CellState::Blocked) {
        auto cell_size = sgl::GetCellSize(world_state);
        auto pos = glm::vec3(cell_size.x * x, cell_size.y * y, 0);
        auto transform = einu::Transform{};
        transform.SetPosition(pos + glm::vec3(3, 3, 0));
        if (glm::vec2(transform.GetPosition()) !=
                world_state.trading_post_pos &&
            glm::vec2(transform.GetPosition()) != world_state.space_ship_pos &&
            glm::vec2(transform.GetPosition()) != world_state.star_pos) {
          transform.SetScale(glm::vec3(0.02f, 0.05f, 0));
          starchaser = sys::CreateStarchaser(*ett_mgr, transform);
          created = true;
        }
      }
    }
  }

  // camera
  auto proj =
      einu::graphics::Projection{einu::graphics::Projection::Type::Orthographic,
                                 einu::graphics::Projection::OrthographicAttrib{
                                     -10, 10.f + world_state.world_size.x, -10,
                                     10.f + world_state.world_size.y}};

  auto cam_mat = einu::graphics::ProjectionMatrix(proj) *
                 einu::graphics::ViewMatrix(einu::graphics::View{});

  // views
  auto move_view = einu::EntityView<
      einu::XnentList<einu::cmp::Transform, einu::cmp::Movement>>{};

  auto sprite_render_view = einu::EntityView<
      einu::XnentList<einu::cmp::Transform, einu::graphics::cmp::Sprite>>{};

  auto cell_view = einu::EntityView<
      einu::XnentList<einu::graphics::cmp::Sprite, const cmp::Cell>>{};

  auto cell_frame_view = einu::EntityView<
      einu::XnentList<einu::graphics::cmp::Sprite, const cmp::CellFrameTag>>{};

  // game loop
  while (!win.shouldClose) {
    einu::window::sys::PoolEvents(win);
    einu::graphics::sys::Clear();

    einu::sys::UpdateTime(time);

    cell_view.View(*ett_mgr);
    for (auto&& [sprite, cell] : cell_view.Components()) {
      sys::UpdateCellBlock(world_state, cell, sprite);
    }

    cell_frame_view.View(*ett_mgr);
    for (auto&& [sprite, cell_frame_tag] : cell_frame_view.Components()) {
      sys::UpdateCellFrame(sprite);
    }

    sys::RunStarChaserFSM(*ett_mgr, starchaser);

    // move and rotate
    move_view.View(*ett_mgr);
    for (auto&& [transform, movement] : move_view.Components()) {
      sys::Move(time, world_state, transform, movement);
      sys::Rotate(transform, movement);
    }

    sys::RenderPath(*ett_mgr,
                    ett_mgr->GetComponent<cmp::PathFinding>(starchaser));

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

  // TODO(Xiaoyue Chen): clean up
}

}  // namespace astar
