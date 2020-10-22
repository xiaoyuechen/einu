#include <einu-core/einu_engine.h>
#include <gtest/gtest.h>

namespace einu {

struct C1 : Xnent {};
struct C2 : Xnent {};

using TestEnginePolicy = EnginePolicy<NeedList<XnentList<C1, C2>, XnentList<>>>;

TEST(EinuEngine, CreateEngineWillRegisterComponents) {
  auto engine = EinuEngine<TestEnginePolicy>();
  using namespace internal;
  EXPECT_EQ(GetXnentTypeID<C1>(), 0);
  EXPECT_EQ(GetXnentTypeID<C2>(), 1);
}

}  // namespace einu