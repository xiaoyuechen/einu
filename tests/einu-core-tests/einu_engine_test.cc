#include <einu-core/einu_core.h>
#include <gtest/gtest.h>

namespace einu {

struct C1 : IComponent {};
struct C2 : IComponent {};

using TestEnginePolicy = EnginePolicy<ComponentList<C1, C2>, SinglenentList<>>;

TEST(EinuEngine, CreateEngineWillRegisterComponents) {
  auto engine = EinuEngine(TestEnginePolicy{});
  using namespace internal;
  EXPECT_EQ(GetComponentIndex<C1>(), 0);
  EXPECT_EQ(GetComponentIndex<C2>(), 1);
}

}  // namespace einu