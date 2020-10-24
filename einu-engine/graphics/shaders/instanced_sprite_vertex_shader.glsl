//VERTEX SHADER
#version 330 core

// This is an optimized shader for instanced sprites.
// Notice that we compute the per-instance transformation here.
// Although the transformation is computed 4 times on the GPU
// (recomputes on every vertex), it is still much faster than on CPU.
// Further more, the direct use of quaternion also reduses computation.


in vec2 a_pos;
in vec2 a_texcoord;
in mat4 a_transform;

in vec4 a_instance_color;
in vec2 a_instance_pos;
in vec4 a_instance_quat;
in vec2 a_instance_scale;

uniform mat4 camera;
uniform mat4 local_transform;

out vec4 f_color;
out vec2 f_texcoord;

vec4 QuatConj(vec4 q) {
  return vec4(-q.x, -q.y, -q.z, q.w);
}

vec4 QuatMultiply(vec4 q1, vec4 q2) {
  vec4 qr;
  qr.x = (q1.w * q2.x) + (q1.x * q2.w) + (q1.y * q2.z) - (q1.z * q2.y);
  qr.y = (q1.w * q2.y) - (q1.x * q2.z) + (q1.y * q2.w) + (q1.z * q2.x);
  qr.z = (q1.w * q2.z) + (q1.x * q2.y) - (q1.y * q2.x) + (q1.z * q2.w);
  qr.w = (q1.w * q2.w) - (q1.x * q2.x) - (q1.y * q2.y) - (q1.z * q2.z);
  return qr;
}

vec3 QuatRotate(vec3 pos, vec4 quat) {
  vec4 conj = QuatConj(quat);
  vec4 quat_pos = vec4(pos, 0);
  vec4 temp = QuatMultiply(quat, quat_pos);
  vec4 result = QuatMultiply(temp, conj);
  return vec3(result.x, result.y, result.z);
}

vec3 Transform(vec3 original_pos, vec3 pos, vec4 quat, vec3 scale) {
  vec3 scaled = original_pos * scale;
  vec3 rotated = QuatRotate(scaled, quat);
  vec3 translated = rotated + pos;
  return translated;
}

void main() {
  vec3 local_transformed = vec3(local_transform * vec4(a_pos, 0, 1));
  vec3 world_transformed = Transform(local_transformed,
                                     vec3(a_instance_pos, 0),
                                     a_instance_quat,
                                     vec3(a_instance_scale, 0));
  gl_Position = camera * vec4(world_transformed, 1);
  f_texcoord = a_texcoord;
  f_color = a_instance_color / 255;
}
