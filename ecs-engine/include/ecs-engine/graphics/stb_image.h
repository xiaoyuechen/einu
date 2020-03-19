#pragma once

#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable : ALL_CODE_ANALYSIS_WARNINGS 26451 4505 4100)
#define STBI_NO_STDIO
#define STBI_NO_LINEAR
#define STBI_NO_HDR
#define STBI_ONLY_PNG
#define STB_IMAGE_IMPLEMENTATION
#include <stb-image/stb_image.h>
#pragma warning(pop)

