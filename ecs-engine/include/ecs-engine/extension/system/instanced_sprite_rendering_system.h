#ifndef INSTANCED_SPRITE_RENDERING_SYSTEM_H_
#define INSTANCED_SPRITE_RENDERING_SYSTEM_H_

#include <array>

#include "ecs-engine/core/system.h"
#include "ecs-engine/extension/component/instanced_sprite_component.h"
#include "ecs-engine/extension/component/singleton_camera_component.h"
#include "ecs-engine/extension/component/transform_component.h"

namespace ecs {

using InstancedSpriteRenderingSystemComponentList =
    RequiredComponentList<InstancedSpriteComponent, TransformComponent>;

template <typename EntityManager>
class InstancedSpriteRenderingSystem
    : public System<EntityManager,
                    InstancedSpriteRenderingSystemComponentList> {
 public:
  InstancedSpriteRenderingSystem(EntityManager& ett_mgr);

  void Render();

 private:
  struct InstanceState {
    std::array<uint8_t, 4> color;
    TransformComponent transform;
  };

  struct Vertex {
    glm::vec2 pos;
    glm::vec2 uv;
  };

  using TupArr = std::vector<typename System::ComponentTuple>;
  void UpdateTupleMap();
  void SetQuadVBOData(const ecs::IntRect& rect);
  void SetInstanceVBOData(const TupArr& tup_arr);
  std::array<Vertex, 6> GetVerts(const ecs::IntRect& rect) const;

  ShaderProgram program_;
  VertexBuffer quad_vbo_;
  VertexArray vao_;
  VertexBuffer instance_vbo_;

  std::vector<InstanceState> instance_state_cache_;
  std::map<Sprite*, TupArr> tuple_map_;
};

//////////////////////////////////////////////////////////////////////////

template <typename EntityManager>
inline InstancedSpriteRenderingSystem<
    EntityManager>::InstancedSpriteRenderingSystem(EntityManager& ett_mgr)
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

template <typename EntityManager>
inline void InstancedSpriteRenderingSystem<EntityManager>::Render() {
  program_.Bind();
  auto& camera =
      System::GetEntityManager().GetSingletonComponent<SingletonCameraComponent>();
  auto camera_matrix = camera.GetCameraMatrix();
  program_.SetUniform("camera", camera_matrix);

  vao_.Bind();

  UpdateTupleMap();

  for (const auto& [sprite_ptr, tuple_arr] : tuple_map_) {
    program_.SetUniform("local_transform", sprite_ptr->transform);
    sprite_ptr->texture.Bind();
    const IntRect& rect = sprite_ptr->tex_rect;

    SetQuadVBOData(rect);
    SetInstanceVBOData(tuple_arr);

    quad_vbo_.Bind();
    quad_vbo_.RenderInstance(GL_TRIANGLES, 0, 6,
                             static_cast<uint32_t>(tuple_arr.size()));
  }
}

template <typename EntityManager>
inline void InstancedSpriteRenderingSystem<EntityManager>::SetQuadVBOData(
    const ecs::IntRect& rect) {
  auto verts = GetVerts(rect);
  quad_vbo_.Set(verts.size() * sizeof(Vertex), verts.data());
}

template <typename EntityManager>
inline void InstancedSpriteRenderingSystem<EntityManager>::SetInstanceVBOData(
    const TupArr& tup_arr) {
  instance_state_cache_.clear();
  for (const auto& [sprite, transform] : tup_arr) {
    auto state = InstanceState{sprite.color, transform};
    instance_state_cache_.push_back(state);
  }
  instance_vbo_.Set(sizeof(InstanceState) * instance_state_cache_.size(),
                    instance_state_cache_.data());
}

template <typename EntityManager>
inline std::array<
    typename InstancedSpriteRenderingSystem<EntityManager>::Vertex, 6>
InstancedSpriteRenderingSystem<EntityManager>::GetVerts(
    const ecs::IntRect& rect) const {
  /**
   * a  ------ d
   *   |      |
   * b  ------ c
   */
  auto vert_a_pos = glm::vec2{rect.left, rect.top};
  auto vert_b_pos = vert_a_pos + glm::vec2{0, rect.height};
  auto vert_c_pos = vert_b_pos + glm::vec2{rect.width, 0};
  auto vert_d_pos = vert_a_pos + glm::vec2{rect.width, 0};

  auto vert_a = Vertex{vert_a_pos, glm::vec2{0, 1}};
  auto vert_b = Vertex{vert_b_pos, glm::vec2{0, 0}};
  auto vert_c = Vertex{vert_c_pos, glm::vec2{1, 0}};
  auto vert_d = Vertex{vert_d_pos, glm::vec2{1, 1}};

  std::array<Vertex, 6> verts = {
      vert_a, vert_b, vert_d,  // triangle 1
      vert_d, vert_b, vert_c,  // triangle 2
  };

  return verts;
}

template <typename EntityManager>
inline void InstancedSpriteRenderingSystem<EntityManager>::UpdateTupleMap() {
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
