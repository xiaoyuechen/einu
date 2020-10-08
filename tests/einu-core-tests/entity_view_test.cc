#include <einu-core/entity_view.h>
#include <gtest/gtest.h>

namespace einu {

struct MockComponent1 : Xnent {
  int v = -1;
};

struct MockComponent2 : Xnent {
  int v = -1;
};

using namespace internal;

class MockEntity : public IEntity {
 private:
  virtual EID GetID() const noexcept override { return 0; }

  virtual bool HasComponentsImpl(const XnentMask&) const noexcept override {
    return false;
  }

  virtual const Xnent& GetComponentImpl(
      XnentIndex idx) const noexcept override {
    if (idx == 1) return comp1_;
    return comp2_;
  }

  virtual Xnent& GetComponentImpl(XnentIndex idx) noexcept override {
    if (idx == rtti::ClassIndex(1)) return comp1_;
    return comp2_;
  }

  virtual void AddComponentImpl(XnentIndex, Xnent&) override {}

  virtual Xnent& RemoveComponentImpl(XnentIndex idx) noexcept override {
    return comp1_;
  }

  MockComponent1 comp1_;
  MockComponent2 comp2_;
};

TEST(EntityView, c) {
  rtti::SetClassIndex<MockComponent1>(rtti::ClassIndex(1));
  rtti::SetClassIndex<MockComponent2>(rtti::ClassIndex(2));

  MockEntity ett;
  auto view = EntityView<XnentList<MockComponent1, MockComponent2>>(ett);

  auto&& [comp1, comp2] = view();
  comp1.v = 666;
  comp2.v = 999;

  auto&& [c1, c2] = view();
  EXPECT_EQ(c1.v, 666);
  EXPECT_EQ(c2.v, 999);

  auto const_view =
      EntityView<XnentList<const MockComponent1, const MockComponent2>>(ett);
  auto&& [cc1, cc2] = const_view();
  EXPECT_EQ(cc1.v, 666);
  EXPECT_EQ(cc2.v, 999);
}

}  // namespace einu
