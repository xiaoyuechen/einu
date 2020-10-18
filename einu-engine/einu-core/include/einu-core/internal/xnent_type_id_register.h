#pragma once

#include <einu-tmp/static_algo.h>

#include "einu-core/xnent_list.h"
#include "einu-core/xnent_type_id.h"

namespace einu {
namespace internal {

template <typename XnentList>
class XnentTypeIDRegister {
  using TypeList = typename ToTypeList<XnentList>::Type;
  static constexpr std::size_t kCount = tmp::Size<TypeList>::value;

 public:
  XnentTypeIDRegister() noexcept {
    tmp::StaticFor<kCount>([](auto i) {
      using Xnent = tmp::TypeAt<TypeList, i>::Type;
      SetXnentTypeID<Xnent>(XnentTypeID{i});
    });
  }

  ~XnentTypeIDRegister() noexcept {
    tmp::StaticFor<kCount>([](auto i) {
      using Xnent = tmp::TypeAt<TypeList, i>::Type;
      ResetXnentTypeID<Xnent>();
    });
  }
};

}  // namespace internal
}  // namespace einu