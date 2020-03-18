#pragma once

#include <map>

namespace ecs {

template <typename Key, typename Resource>
class ResourceManager {
  using Map = std::map<Key, Resource>;

 public:
  template <typename... Args>
  void Load(const Key& key, const char* filename, Args&&... constructor_args);
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
inline void ResourceManager<Key, Resource>::Load(const Key& key,
                                                 const char* filename,
                                                 Args&&... constructor_args) {
  auto result = map_.try_emplace(key, std::forward<Args>(constructor_args)...);
  if (result.second) {
    (result.first)->second.LoadFromFile(filename);
  }
}

template <typename Key, typename Resource>
inline const Resource& ResourceManager<Key, Resource>::Get(
    const Key& key) const {
  return map_.at(key);
}

template <typename Key, typename Resource>
inline void ResourceManager<Key, Resource>::Unload(const Key& key) {
  map_.erase(key);
}

template <typename Key, typename Resource>
inline void ResourceManager<Key, Resource>::UnloadAll() {
  map_.clear();
}

template <typename Key, typename Resource>
inline Resource& ResourceManager<Key, Resource>::Get(const Key& key) {
  return const_cast<Resource&>(
      static_cast<const ResourceManager&>(*this).Get(key));
}

}  // namespace ecs