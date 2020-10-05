#include "einu-engine/graphics/vertex_array.h"

namespace einu {

VertexArray::VertexArray() { glGenVertexArrays(1, &vertex_array_); }

VertexArray::~VertexArray() { glDeleteVertexArrays(1, &vertex_array_); }

void VertexArray::Bind() const { glBindVertexArray(vertex_array_); }

}  // namespace einu