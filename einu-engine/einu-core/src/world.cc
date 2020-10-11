#include "einu-core/internal/world.h"

namespace einu {
namespace internal {

void World::AddEntityImpl(IEntity& ett) {
  entity_table.emplace(ett.GetID(), &ett);
}

void World::RemoveEntityImpl(EID eid) { entity_table.erase(eid); }

einu::IEntity& World::GetEntityImpl(EID eid) noexcept {
  return *entity_table.at(eid);
}

const einu::IEntity& World::GetEntityImpl(EID eid) const noexcept {
  return *entity_table.at(eid);
}

std::size_t World::GetEntityCountImpl() const noexcept {
  return entity_table.size();
}

void World::GetAllEntitiesImpl(EntityBuffer& buffer) const {
  buffer.clear();
  for (auto [id, ett] : entity_table) {
    buffer.push_back(*ett);
  }
}

einu::IEntity& World::GetSinglenityImpl() noexcept { return *singlentity; }

const einu::IEntity& World::GetSinglenityImpl() const noexcept {
  return *singlentity;
}

}  // namespace internal
}  // namespace einu