#pragma once

#include <memory>
#include <unordered_map>

#include "einu-core/i_world.h"

namespace einu {
namespace internal {

class World final : public IWorld {
 public:
  using SinglentityPtr = std::unique_ptr<IEntity>;

  World(SinglentityPtr singlentity);

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
  SinglentityPtr singlentity_;
};

}  // namespace internal
}  // namespace einu