#pragma once

#include <map>
#include <memory>
#include <type_traits>

#include "einu-engine/core/component_context.h"
#include "einu-engine/core/i_singleton_component.h"
#include "einu-engine/utility/algorithm.h"
#include "einu-engine/utility/rtti/class_index.h"

namespace einu {

class SingletonComponentManager {
 public:
  template <typename T, typename... Args>
  T& Make(Args&&... args) {
    auto idx = rtti::GetClassIndex<T>();
    assert(comps_.find(idx) == comps_.end() &&
           "singleton component already made");
    auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
    auto& ref = *ptr;
    comps_[idx] = std::move(ptr);
    return ref;
  }

  template <typename T>
  const T& Get() const {
    auto idx = rtti::GetClassIndex<T>();
    return static_cast<const T&>(*comps_.at(idx));
  }

  template <typename T>
  T& Get() noexcept {
    return const_cast<T&>(
        static_cast<const SingletonComponentManager&>(*this).Get<T>());
  }

  template <typename... Ts>
  void MakeRestDefault(SingletonComponentList<Ts...>) {
    auto f = [&](auto i) {
      if (comps_.find(rtti::ClassIndex(i)) == comps_.end()) {
        comps[i] =
            MakeDefault<std::tuple_element<i, std::tuple<Ts...>>::type>();
      }
    };
    algo::StaticFor<sizeof...(Ts)>(f);
  }

 private:
  template <typename T>
  typename std::enable_if<!std::is_default_constructible<T>::value,
                          std::unique_ptr<T>>::type
  MakeDefault() {
    static_assert(false && "<T> is not default constructible");
    return nullptr;
  }

  template <typename T>
  typename std::enable_if<std::is_default_constructible<T>::value,
                          std::unique_ptr<T>>::type
  MakeDefault() {
    return std::make_unique<T>();
  }

  using Ptr = std::unique_ptr<ISingletonComponent>;
  using Map = std::map<rtti::ClassIndex, Ptr>;
  Map comps_;
};

}  // namespace einu