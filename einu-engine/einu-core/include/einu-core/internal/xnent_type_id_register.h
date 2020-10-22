#pragma once

#include <einu-tmp/static_algo.h>
#include <einu-tmp/type_list.h>

#include "einu-core/xnent_list.h"
#include "einu-core/xnent_type_id.h"

namespace einu {
namespace internal {

template <typename XnentList>
class XnentTypeIDRegister {
 public:
  XnentTypeIDRegister() noexcept {
    RequireUnique();

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

 private:
  using TypeList = typename ToTypeList<XnentList>::Type;
  static constexpr std::size_t kCount = tmp::Size<TypeList>::value;

  static constexpr void RequireUnique() noexcept {
    tmp::StaticFor<kCount>([](auto i) {
      using Xnent = tmp::TypeAt<TypeList, i>::Type;
      static_assert(tmp::CountType<TypeList, Xnent>::value == 1 &&
                    "Xnents must be unique");
    });
  }
};

}  // namespace internal
}  // namespace einu