#pragma once

#include <map>

namespace ecs {

template <typename Key, typename Resource>
class SingletonResourceComponent : public IComponent {
  using Map = std::map<Key, Resource>;

 public:
  template <typename... Args>
  Resource& Emplace(const Key& key, Args&&... args);
  Resource& Get(const Key& key);
  const Resource& Get(const Key& key) const;
  void Unload(const Key& key);
  void UnloadAll();

 private:
  Map map_;
};

//////////////////////////////////////////////////////////////////////////

template <typename Key, typename Resource>
template <typename... Args>
inline Resource& SingletonResourceComponent<Key, Resource>::Emplace(const Key& key,
                                                   Args&&... args) {
  auto result = map_.try_emplace(key, std::forward<Args>(args)...);
  return result.first->second;
}

template <typename Key, typename Resource>
inline const Resource& SingletonResourceComponent<Key, Resource>::Get(
    const Key& key) const {
  return map_.at(key);
}

template <typename Key, typename Resource>
inline void SingletonResourceComponent<Key, Resource>::Unload(const Key& key) {
  map_.erase(key);
}

template <typename Key, typename Resource>
inline void SingletonResourceComponent<Key, Resource>::UnloadAll() {
  map_.clear();
}

template <typename Key, typename Resource>
inline Resource& SingletonResourceComponent<Key, Resource>::Get(
    const Key& key) {
  return const_cast<Resource&>(
      static_cast<const SingletonResourceComponent&>(*this).Get(key));
}

}  // namespace ecs
