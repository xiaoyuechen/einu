#pragma once

#include <einu-core/i_entity.h>
#include <gmock/gmock.h>

namespace einu {

class MockEntity : public IEntity {
 private:
  MOCK_METHOD(EID, GetIDImpl, (), (const, noexcept, override));
  MOCK_METHOD(bool, HasComponentsImpl, (const internal::DynamicXnentMask& mask),
              (const, noexcept, override));
  MOCK_METHOD(const Xnent&, GetComponentImpl, (internal::XnentTypeID id),
              (const, noexcept, override));
  MOCK_METHOD(Xnent&, GetComponentImpl, (internal::XnentTypeID id),
              (noexcept, override));
  MOCK_METHOD(void, AddComponentImpl, (internal::XnentTypeID id, Xnent& comp),
              (override));
  MOCK_METHOD(Xnent&, RemoveComponentImpl, (internal::XnentTypeID id),
              (noexcept, override));
};

}  // namespace einu