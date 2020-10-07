#include <einu-core/internal/component_mask.h>
#include <gtest/gtest.h>

namespace einu {
namespace internal {

struct MockComponent1 : IComponent {
  int v = -1;
};

struct MockComponent2 : IComponent {
  int v = -1;
};

TEST(ComponentMask, _) {
  SetComponentIndex<MockComponent1>(ComponentIndex(1));
  SetComponentIndex<MockComponent2>(ComponentIndex(2));
  using CL = ComponentList<MockComponent1, MockComponent2>;
  auto sig = ComponentMask(CL());
  EXPECT_EQ(sig.SizeInBytes(), 1);
  EXPECT_EQ(*(std::uint8_t*)sig.Data(), std::stoi("110", 0, 2));
}

TEST(GetComponentMask, _) {
  SetComponentIndex<MockComponent1>(ComponentIndex(10));
  SetComponentIndex<MockComponent2>(ComponentIndex(14));
  using CL = ComponentList<MockComponent1, MockComponent2>;
  auto sig = ComponentMask(CL());
  EXPECT_EQ(sig.SizeInBytes(), 2);
  EXPECT_EQ(*(std::uint16_t*)sig.Data(), std::stoi("0100010000000000", 0, 2));
}

TEST(ComponentMask, OperatorBitWiseAnd) {
  SetComponentIndex<MockComponent1>(ComponentIndex(1));
  SetComponentIndex<MockComponent2>(ComponentIndex(2));
  using CL = ComponentList<MockComponent1, MockComponent2>;
  auto sig = ComponentMask(CL());
  EXPECT_EQ(*(std::uint8_t*)sig.Data(), std::stoi("110", 0, 2));
  auto ssig = StaticComponentMask<16>{"1111111100000110"};
  auto r = sig & ssig;
  EXPECT_EQ(r.to_string(), "0000000000000110");
}

}  // namespace internal
}  // namespace einu