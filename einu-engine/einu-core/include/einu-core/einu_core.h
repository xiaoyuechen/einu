#pragma once

#include <einu-rtti/class_index_storage.h>
#include <einu-tmp/type_list.h>

#include <tuple>
#include <type_traits>
#include <vector>

namespace einu {

using EID = std::size_t;

class IComponent {};

template <typename... Components>
using ComponentList = tmp::SubtypeList<IComponent, Components...>;

using ComponentIndex = rtti::ClassIndex;

template <typename T>
void SetComponentIndex(ComponentIndex idx) {
  static_assert(std::is_base_of<IComponent, T>::value &&
                "<IComponent> must be base of <T>");
  rtti::SetClassIndex<T>(idx);
}

template <typename T>
ComponentIndex GetComponentIndex() {
  static_assert(std::is_base_of<IComponent, T>::value &&
                "<IComponent> must be base of <T>");
  return rtti::GetClassIndex<T>();
}

class ComponentIndexList {
 public:
  template <typename... Ts>
  explicit ComponentIndexList(ComponentList<Ts...>) {
    (list_.push_back(GetComponentIndex<Ts>()), ...);
  }

  auto begin() const { return list_.begin(); }
  auto end() const { return list_.end(); }

 private:
  using List = std::vector<ComponentIndex>;
  List list_;
};

template <typename... Ts>
const ComponentIndexList& GetComponentIndexList(
    ComponentList<Ts...> comp_list) {
  static ComponentIndexList idx_list(comp_list);
  return idx_list;
}

class IEntity {
 public:
  template <typename T>
  bool HasComponent() const {
    return HasComponent(GetComponentIndex<T>());
  }

  template <typename T>
  const T& GetComponent() const {
    return static_cast<const T&>(GetComponent(GetComponentIndex<T>()));
  }

  template <typename T>
  T& GetComponent() {
    return static_cast<T&>(GetComponent(GetComponentIndex<T>()));
  }

  template <typename T>
  T& AddComponent() {
    return static_cast<T&>(AddComponent(GetComponentIndex<T>()));
  }

  template <typename T>
  void RemoveComponent() {
    RemoveComponent(GetComponentIndex<T>());
  }

  template <typename... Ts>
  void PartialCopy(IEntity& dest, ComponentList<Ts...> comp_list) const {
    auto& idx_list = GetComponentIndexList(comp_list);
  }

  virtual bool IsActive() const = 0;
  virtual void Destroy() = 0;

 protected:
  virtual bool HasComponent(ComponentIndex idx) const = 0;
  virtual const IComponent& GetComponent(ComponentIndex idx) const = 0;
  virtual IComponent& GetComponent(ComponentIndex idx) = 0;

  virtual IComponent& AddComponent(ComponentIndex idx) = 0;
  virtual void RemoveComponent(ComponentIndex idx) = 0;
};

template <typename ComponentList>
struct EntityQuery;

template <typename... Ts>
struct EntityQuery<ComponentList<Ts...>> {};

template <typename ComponentList>
class EntityView;

template <typename... Ts>
class EntityView<ComponentList<Ts...>> {
 public:
  EntityView(IEntity& ett) noexcept
      : ett_(ett) {}

  auto operator()() {
    return std::forward_as_tuple(ett_.GetComponent<Ts>()...);
  }

 private:
  IEntity& ett_;
};

// enum class DiffStatus { kModified, kAdded, kDeleted };
//
// struct EntityDiff {
//  IEntity* before;
//  IEntity* after;
//};
//
// struct ComponentDiff {
//  IComponent* before;
//  IComponent* after;
//  std::size_t size;
//};
//
// class ComponentDiffBuffer {
// public:
//  void Commit() {
//    for (auto diff : buffer_) {
//      memcpy(diff.before, diff.after, diff.size);
//    }
//    buffer_.clear();
//  }
//
//  void Add(ComponentDiff diff) { buffer_.push_back(diff); }
//  void Clear() noexcept { buffer_.clear(); }
//
// private:
//  using Buffer = std::vector<ComponentDiff>;
//  Buffer buffer_;
//};

class IEntityManager {
 public:
  virtual IEntity& CreateEntity() = 0;
  virtual void AddEntity(IEntity& ett) = 0;
  virtual void RemoveEntity(IEntity& ett) = 0;
};

class EntityBuffer {
 public:
  void push(IEntity& ett) { buffer_.push_back(ett); }
  void clear() { buffer_.clear(); }
  auto begin() { return buffer_.begin(); }
  auto begin() const { return buffer_.begin(); }
  auto end() { return buffer_.end(); }
  auto end() const { return buffer_.end(); }

 private:
  using Buffer = std::vector<std::reference_wrapper<IEntity>>;
  Buffer buffer_;
};

class IWorld {
 public:
  virtual IEntity& CreateEntity() = 0;
  virtual void AddEntity(IEntity& ett) = 0;
  virtual void RemoveEntity(const IEntity& ett) = 0;
  virtual IEntity& GetEntity(EID eid) noexcept = 0;
  virtual const IEntity& GetEntity(EID eid) const noexcept = 0;
  virtual std::size_t GetEntityCount() const noexcept = 0;
  virtual void GetEntities(EntityBuffer& buffer) const = 0;

 private:
};

class IWorldForker {
 public:
  template <typename ComponentList>
  void Fork(ComponentList comp_list, const IWorld& src, IWorld& dest) {
    Fork(GetComponentIndexList(comp_list), src, dest);
  }

 protected:
  virtual void Fork(const ComponentIndexList& idx_list, const IWorld& src,
                    IWorld& dest) = 0;
};

class IWorldMerger {
 public:
  virtual void Merge(const IWorld& src, IWorld& dest) = 0;
};




}  // namespace einu