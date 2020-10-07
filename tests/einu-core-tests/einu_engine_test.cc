#include <einu-core/einu_core.h>
#include <gtest/gtest.h>

namespace einu {

struct C1 : IComponent {};
struct C2 : IComponent {};

struct EnginePolicy {
  using ComponentList = ComponentList<C1, C2>;
};

TEST(EinuEngine, CreateEngineWillRegisterComponents) {
  auto engine = EinuEngine(EnginePolicy{});
  using namespace internal;
  EXPECT_EQ(GetComponentIndex<C1>(), 0);
  EXPECT_EQ(GetComponentIndex<C2>(), 1);
}

}  // namespace einu