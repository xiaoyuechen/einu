#pragma once

#include <einu-core/i_entity.h>
#include <gmock/gmock.h>

namespace einu {

class MockEntity : public IEntity {
 public:
  MOCK_METHOD(EID, GetIDImpl, (), (const, noexcept, override));
  MOCK_METHOD(void, ResetImpl, (), (noexcept, override));
  MOCK_METHOD(bool, HasComponentsImpl, (const internal::DynamicXnentMask& mask),
              (const, noexcept, override));
  MOCK_METHOD(const Xnent&, GetComponentImpl, (XnentTypeID id),
              (const, noexcept, override));
  MOCK_METHOD(Xnent&, GetComponentImpl, (XnentTypeID id),
              (noexcept, override));
  MOCK_METHOD(void, AddComponentImpl, (XnentTypeID id, Xnent& comp),
              (override));
  MOCK_METHOD(Xnent&, RemoveComponentImpl, (XnentTypeID id),
              (noexcept, override));
};

}  // namespace einu