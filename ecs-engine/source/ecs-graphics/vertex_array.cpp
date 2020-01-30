#include "ecs-engine/graphics/vertex_array.h"

namespace ecs {

VertexArray::VertexArray() { glGenVertexArrays(1, &vertex_array_); }

VertexArray::~VertexArray() { glDeleteVertexArrays(1, &vertex_array_); }

void VertexArray::Bind() const { glBindVertexArray(vertex_array_); }

}  // namespace ecs