#include "ecs-engine/graphics/sampler.h"

namespace ecs {

Sampler::Sampler() { glGenSamplers(1, &sampler_); }

Sampler::~Sampler() { glDeleteSamplers(0, &sampler_); }

void Sampler::Set(const GLenum filter,
                  const GLenum address_mode_u,
                  const GLenum address_mode_v) {
  Bind();
  glSamplerParameteri(sampler_, GL_TEXTURE_MIN_FILTER, filter);
  glSamplerParameteri(sampler_, GL_TEXTURE_MAG_FILTER, filter);
  glSamplerParameteri(sampler_, GL_TEXTURE_WRAP_S, address_mode_u);
  glSamplerParameteri(sampler_, GL_TEXTURE_WRAP_T, address_mode_v);
}

void Sampler::Bind() const { glBindSampler(0, sampler_); }

}  // namespace ecs