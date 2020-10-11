#pragma once

#include <memory>
#include <unordered_map>

#include "einu-core/i_entity_pool.h"
#include "einu-core/i_world.h"

namespace einu {
namespace internal {

class World final : public IWorld {
 public:
  World(IEntity& singlentity);

 private:
  using EntityTable = std::unordered_map<EID, IEntity*>;

  void AddEntityImpl(IEntity& ett) override;
  void RemoveEntityImpl(EID eid) override;
  IEntity& GetEntityImpl(EID eid) noexcept override;
  const IEntity& GetEntityImpl(EID eid) const noexcept override;
  std::size_t GetEntityCountImpl() const noexcept override;
  void GetAllEntitiesImpl(EntityBuffer& buffer) const override;
  IEntity& GetSinglenityImpl() noexcept override;
  const IEntity& GetSinglenityImpl() const noexcept override;

  EntityTable entity_table_;
  IEntity& singlentity_;
};

class WorldFactory final : public IWorldFactory {
 public:
  WorldFactory(IEntityPool& ett_pool)
      : ett_pool_{ett_pool} {}

 private:
  std::unique_ptr<IWorld> CreateWorldImpl() const override;

  IEntityPool& ett_pool_;
};

}  // namespace internal
}  // namespace einu