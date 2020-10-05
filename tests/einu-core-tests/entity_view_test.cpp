#include <einu-core/einu_core.h>
#include <gtest/gtest.h>

namespace einu {

struct MockComponent1 : IComponent {
  int v = -1;
};

struct MockComponent2 : IComponent {
  int v = -1;
};

class MockEntity : public IEntity {
 public:
  virtual bool IsActive() const override { return false; }

  virtual void Destroy() override {}

 private:
  virtual bool HasComponent(rtti::ClassIndex idx) const override {
    return false;
  }

  virtual const IComponent& GetComponent(rtti::ClassIndex idx) const override {
    if (idx == 1) return comp1_;
    return comp2_;
  }

  virtual IComponent& GetComponent(rtti::ClassIndex idx) override {
    if (idx == rtti::ClassIndex(1)) return comp1_;
    return comp2_;
  }

  virtual IComponent& AddComponent(rtti::ClassIndex idx) override {
    return comp1_;
  }

  virtual void RemoveComponent(rtti::ClassIndex idx) override {}

  MockComponent1 comp1_;
  MockComponent2 comp2_;
};

TEST(EntityView, c) {
  rtti::SetClassIndex<MockComponent1>(rtti::ClassIndex(1));
  rtti::SetClassIndex<MockComponent2>(rtti::ClassIndex(2));

  MockEntity ett;
  auto view = EntityView<ComponentList<MockComponent1, MockComponent2>>(ett);

  auto&& [comp1, comp2] = view();
  comp1.v = 666;
  comp2.v = 999;

  auto&& [c1, c2] = view();
  EXPECT_EQ(c1.v, 666);
  EXPECT_EQ(c2.v, 999);

  auto const_view =
      EntityView<ComponentList<const MockComponent1, const MockComponent2>>(
          ett);
  auto&& [cc1, cc2] = const_view();
  EXPECT_EQ(cc1.v, 666);
  EXPECT_EQ(cc2.v, 999);
}

}  // namespace einu
