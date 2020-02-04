#include "ecs-engine/graphics/vertex_format.h"

#include <cassert>

namespace ecs {

namespace {

constexpr uint32_t SizeOfGLType(GLenum type)
{
	switch (type) {
	case GL_FLOAT:
		return sizeof(GLfloat);
	case GL_UNSIGNED_BYTE:
		return sizeof(uint8_t);
	}
	assert(false && "incorrect type");
	return 0;
}
}

void VertexFormat::AddAttribute(uint32_t index, uint32_t size, GLenum type, bool normalized)
{
	const Attribute attribute{ index, size, type, normalized };
	AddAttribute(attribute);
}

void VertexFormat::AddAttribute(const Attribute& attribute) {
	assert(attribute_count_ < kAttributeCount);
	uint32_t at = attribute_count_++;
	attributes_[at] = attribute;
	attributes_[at].offset = stride_;

	stride_ += attribute.size * SizeOfGLType(attribute.type);
}

bool VertexFormat::IsValid() const
{
	return attribute_count_ > 0;
}

void VertexFormat::Bind() const
{
	for (uint32_t index = 0; index != kAttributeCount; ++index) {
		glDisableVertexAttribArray(index);
	}

	for (uint32_t index = 0; index != attribute_count_; ++index) {
		const Attribute& attrib = attributes_[index];
		glEnableVertexAttribArray(attrib.index);
		glVertexAttribPointer(attrib.index, attrib.size, attrib.type, attrib.normalized, stride_, (const void*)attrib.offset);
	}
}

}