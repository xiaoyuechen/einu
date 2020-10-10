#include <einu-core/internal/xnent_mask.h>
#include <gtest/gtest.h>

namespace einu {
namespace internal {

TEST(XnentMaskTest, a_new_mask_has_the_correct_size_and_bits_set_1) {
  auto sig = DynamicXnentMask{XnentTypeID(1), XnentTypeID(2)};
  EXPECT_EQ(sig.SizeInBytes(), 1);
  EXPECT_EQ(*(std::uint8_t*)sig.Data(), 0b110);
}

TEST(XnentMaskTest, a_new_mask_has_the_correct_size_and_bits_set_2) {
  auto sig = DynamicXnentMask{XnentTypeID(12), XnentTypeID(6)};
  EXPECT_EQ(sig.SizeInBytes(), 2);
  EXPECT_EQ(*(std::uint16_t*)sig.Data(), 0b0001000001000000);
}

TEST(XnentMaskTest, OperatorBitWiseAnd) {
  auto sig = DynamicXnentMask{XnentTypeID(1), XnentTypeID(2)};
  EXPECT_EQ(*(std::uint8_t*)sig.Data(), 0b110);
  auto ssig = StaticXnentMask<16>{"1111111100000110"};
  auto r = sig & ssig;
  EXPECT_EQ(r.to_ulong(), 0b0000000000000110);
}

TEST(XnentMaskTest, EqualsEqualsOperator) {
  auto mask = DynamicXnentMask{XnentTypeID(1), XnentTypeID(2)};
  auto smask = StaticXnentMask<16>{"1111111100000000"};
  EXPECT_EQ(mask & smask, StaticXnentMask<16>{});
  EXPECT_EQ(mask | smask, StaticXnentMask<16>{"1111111100000110"});
}

}  // namespace internal
}  // namespace einu