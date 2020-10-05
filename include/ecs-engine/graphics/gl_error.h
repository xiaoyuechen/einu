#pragma once

#include <exception>
#include <string>

namespace einu {

class GLError : public std::exception {
public:
	GLError() = default;
	explicit GLError(const char* message);
	virtual ~GLError() = default;

	virtual const char* what() const noexcept override;

private:
	std::string message_{};
};


void GLErrorCallback(int error, const char* description);

}
