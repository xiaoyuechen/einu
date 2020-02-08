#ifndef INSTANCED_SPRITE_RENDERING_SYSTEM_H_
#define INSTANCED_SPRITE_RENDERING_SYSTEM_H_

#include <array>

#include "ecs-engine/core/system.h"
#include "ecs-engine/extension/component/instanced_sprite_component.h"
#include "ecs-engine/extension/component/singleton_camera_component.h"
#include "ecs-engine/extension/component/transform_component.h"
#include "ecs-engine/extension/policy/default_unit_policy.h"
#include "ecs-engine/math/primitive.h"

namespace ecs {

using InstancedSpriteRenderingSystemComponentList =
    RequiredComponentList<InstancedSpriteComponent, TransformComponent>;

template <typename EntityManager, typename UnitPolicy = DefaultUnitPolicy>
class InstancedSpriteRenderingSystem
    : public System<EntityManager,
                    InstancedSpriteRenderingSystemComponentList> {
 public:
  InstancedSpriteRenderingSystem(EntityManager& ett_mgr);

  void Render();

 private:
  struct InstanceState {
    std::array<uint8_t, 4> color;
    glm::mat4 transform;
  };

  struct Vertex {
    glm::vec2 pos;
    glm::vec2 uv;
  };

  using TupArr = std::vector<typename System<
      EntityManager,
      InstancedSpriteRenderingSystemComponentList>::ComponentTuple>;

  using System =
      System<EntityManager, InstancedSpriteRenderingSystemComponentList>;

  void SetCameraUniform();
  void UpdateTupleMap();
  void SetQuadVBOData(const ecs::IntRect& rect, const glm::ivec2& tex_extent);
  void SetInstanceVBOData(const TupArr& tup_arr);
  std::array<Vertex, 6> GetVerts(const ecs::IntRect& rect,
                                 const glm::ivec2& tex_extent) const;

  ShaderProgram program_;
  VertexBuffer quad_vbo_;
  VertexArray vao_;
  VertexBuffer instance_vbo_;

  std::vector<InstanceState> instance_state_cache_;
  std::map<Sprite*, TupArr> tuple_map_;
};

//////////////////////////////////////////////////////////////////////////

template <typename EntityManager, typename UnitPolicy>
inline InstancedSpriteRenderingSystem<EntityManager, UnitPolicy>::
    InstancedSpriteRenderingSystem(EntityManager& ett_mgr)
    : System(ett_mgr) {
  VertexShader vertex_shader(
      "../ecs-engine/resource/instanced_sprite_vertex_shader.glsl");
  FragmentShader fragment_shader(
      "../ecs-engine/resource/instanced_sprite_fragment_shader.glsl");
  program_.Set(vertex_shader, fragment_shader);

  vao_.Bind();

  auto pos_loc = program_.GetAttributeLocation("a_pos");
  auto tex_coord_loc = program_.GetAttributeLocation("a_texcoord");
  VertexFormat format{};
  format.AddAttribute(pos_loc, 2, GL_FLOAT, false);
  format.AddAttribute(tex_coord_loc, 2, GL_FLOAT, false);
  quad_vbo_.Bind();
  format.Enable();

  VertexFormat instance_format{};
  auto color_loc = program_.GetAttributeLocation("a_color");
  instance_format.AddAttribute(color_loc, 4, GL_UNSIGNED_BYTE, false, 1);
  auto transform_loc = program_.GetAttributeLocation("a_transform");
  for (auto i = 0; i != 4; ++i) {
    auto loc = transform_loc + i;
    instance_format.AddAttribute(loc, 4, GL_FLOAT, false, 1);
  }
  instance_vbo_.Bind();
  instance_format.Enable();
}

template <typename EntityManager, typename UnitPolicy>
inline void
InstancedSpriteRenderingSystem<EntityManager, UnitPolicy>::Render() {
  program_.Bind();
  SetCameraUniform();
  vao_.Bind();
  UpdateTupleMap();
  for (const auto& [sprite_ptr, tuple_arr] : tuple_map_) {
    program_.SetUniform("local_transform", sprite_ptr->transform);
    auto& texture = sprite_ptr->texture;
    texture.Bind();
    const auto& rect = sprite_ptr->texture_rect;
    const auto tex_extent = glm::ivec2(texture.Width(), texture.Height());
    SetQuadVBOData(rect, tex_extent);
    SetInstanceVBOData(tuple_arr);

    quad_vbo_.Bind();
    quad_vbo_.RenderInstance(GL_TRIANGLES, 0, 6,
                             static_cast<uint32_t>(tuple_arr.size()));
  }
}

template <typename EntityManager, typename UnitPolicy>
inline void
InstancedSpriteRenderingSystem<EntityManager, UnitPolicy>::SetCameraUniform() {
  const auto& ett_mgr = System::GetEntityManager();
  const auto& camera =
      ett_mgr.GetSingletonComponent<SingletonCameraComponent>();
  auto view = camera.view;
  view.position *= UnitPolicy::PixelPerUnit();
  view.target *= UnitPolicy::PixelPerUnit();
  auto view_matrix = view.GetViewMatrix();
  const auto projection = camera.projection * UnitPolicy::PixelPerUnit();
  auto projection_matrix = projection.GetProjectionMatrix();
  auto cam_matrix = projection_matrix * view_matrix;
  program_.SetUniform("camera", cam_matrix);
}

template <typename EntityManager, typename UnitPolicy>
inline void
InstancedSpriteRenderingSystem<EntityManager, UnitPolicy>::SetQuadVBOData(
    const ecs::IntRect& rect, const glm::ivec2& tex_extent) {
  auto verts = GetVerts(rect, tex_extent);
  quad_vbo_.Set(verts.size() * sizeof(Vertex), verts.data());
}

template <typename EntityManager, typename UnitPolicy>
inline void
InstancedSpriteRenderingSystem<EntityManager, UnitPolicy>::SetInstanceVBOData(
    const TupArr& tup_arr) {
  instance_state_cache_.clear();
  for (const auto& [sprite, transform] : tup_arr) {
    auto copy_transform = transform;
    copy_transform.SetPosition(copy_transform.GetPosition() *
                               UnitPolicy::PixelPerUnit());
    auto state = InstanceState{sprite.color, copy_transform.GetCachedTransform()};
    instance_state_cache_.push_back(state);
  }
  instance_vbo_.Set(sizeof(InstanceState) * instance_state_cache_.size(),
                    instance_state_cache_.data());
}

template <typename EntityManager, typename UnitPolicy>
inline std::array<
    typename InstancedSpriteRenderingSystem<EntityManager, UnitPolicy>::Vertex,
    6>
InstancedSpriteRenderingSystem<EntityManager, UnitPolicy>::GetVerts(
    const ecs::IntRect& rect, const glm::ivec2& tex_extent) const {
  /**
   * 3  ------ 2
   *   |      |
   * 0  ------ 1
   */

  std::array<Vertex, 4> rect_verts{};
  rect_verts[0].pos = glm::vec2{rect.left, rect.buttom};
  rect_verts[1].pos = rect_verts[0].pos + glm::vec2{rect.width, 0};
  rect_verts[2].pos = rect_verts[1].pos + glm::vec2{0, rect.height};
  rect_verts[3].pos = rect_verts[0].pos + glm::vec2{0, rect.height};

  for (auto&& rect_vert : rect_verts) {
    rect_vert.uv = rect_vert.pos;
    rect_vert.uv.x /= tex_extent.x;
    rect_vert.uv.y /= tex_extent.y;
  }

  std::array<Vertex, 6> verts = {
      rect_verts[0], rect_verts[1], rect_verts[2],  // triangle 1
      rect_verts[2], rect_verts[3], rect_verts[0],  // triangle 2
  };

  return verts;
}

template <typename EntityManager, typename UnitPolicy>
inline void
InstancedSpriteRenderingSystem<EntityManager, UnitPolicy>::UpdateTupleMap() {
  tuple_map_.clear();
  for (const auto& tuple : System::GetMatchingComponentTuples()) {
    const auto& [instanced_sprite, transform] = tuple;
    auto sprite = instanced_sprite.sprite;
    if (sprite) {
      tuple_map_[instanced_sprite.sprite].push_back(tuple);
    }
  }
}

}  // namespace ecs

#endif  // INSTANCED_SPRITE_RENDERING_SYSTEM_H_
