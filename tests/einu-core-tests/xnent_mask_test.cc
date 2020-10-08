#include <einu-core/internal/xnent_mask.h>
#include <gtest/gtest.h>

namespace einu {
namespace internal {

struct MockComponent1 : Xnent {
  int v = -1;
};

struct MockComponent2 : Xnent {
  int v = -1;
};

TEST(XnentMask, _) {
  SetXnentIndex<MockComponent1>(XnentIndex(1));
  SetXnentIndex<MockComponent2>(XnentIndex(2));
  using CL = XnentList<MockComponent1, MockComponent2>;
  auto sig = XnentMask(CL());
  EXPECT_EQ(sig.SizeInBytes(), 1);
  EXPECT_EQ(*(std::uint8_t*)sig.Data(), std::stoi("110", 0, 2));
}

TEST(GetXnentMask, _) {
  SetXnentIndex<MockComponent1>(XnentIndex(10));
  SetXnentIndex<MockComponent2>(XnentIndex(14));
  using CL = XnentList<MockComponent1, MockComponent2>;
  auto sig = XnentMask(CL());
  EXPECT_EQ(sig.SizeInBytes(), 2);
  EXPECT_EQ(*(std::uint16_t*)sig.Data(), std::stoi("0100010000000000", 0, 2));
}

TEST(XnentMask, OperatorBitWiseAnd) {
  SetXnentIndex<MockComponent1>(XnentIndex(1));
  SetXnentIndex<MockComponent2>(XnentIndex(2));
  using CL = XnentList<MockComponent1, MockComponent2>;
  auto sig = XnentMask(CL());
  EXPECT_EQ(*(std::uint8_t*)sig.Data(), std::stoi("110", 0, 2));
  auto ssig = StaticXnentMask<16>{"1111111100000110"};
  auto r = sig & ssig;
  EXPECT_EQ(r.to_string(), "0000000000000110");
}

TEST(XnentMask, EqualsEqualsOperator) {
  SetXnentIndex<MockComponent1>(XnentIndex(1));
  SetXnentIndex<MockComponent2>(XnentIndex(2));
  using CL = XnentList<MockComponent1, MockComponent2>;
  auto mask = XnentMask(CL());
  auto smask = StaticXnentMask<16>{"1111111100000000"};
  EXPECT_EQ(mask & smask, StaticXnentMask<16>{});
  EXPECT_EQ(mask | smask, StaticXnentMask<16>{"1111111100000110"});
}

}  // namespace internal
}  // namespace einu