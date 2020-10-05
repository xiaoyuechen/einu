#include "einu-engine/graphics/gl_error.h"

namespace einu {

GLError::GLError(const char* message)
{
	message_ = message;
}

const char* GLError::what() const noexcept
{
	return message_.c_str();
}

void GLErrorCallback([[maybe_unused]] int error, const char* description)
{
	throw GLError(description);
}

}