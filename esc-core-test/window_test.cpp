#include "pch.h"
// pre-compiled header

#include "ecs-engine/graphics/graphics.h"
#include "ecs-engine/window/window.h"

namespace ecs {
//////////////////////////////////////////////////////////////////////////
// WindowTest:
//////////////////////////////////////////////////////////////////////////
struct WindowTest : testing::Test {
  WindowTest()
      : window(Window::Mode::WINDOWED, 1280, 720, "application") {}
  Window window;
};

TEST_F(WindowTest, ShouldClose) {
  while (!window.ShouldClose()) {
    window.SwapBuffer();
    window.PollEvents();
  }
  EXPECT_EQ(window.ShouldClose(), true);
}

TEST_F(WindowTest, SetInputCallback) {
  auto key_callback = []([[maybe_unused]] Window& win,
                         input::KeyboardKey key,
                         input::Action,
                         input::ModifierKey) {
    printf("%s\n", GetKeyName(key));
  };

  window.SetInputCallback(input::KeyFn{key_callback});

  auto cursor_pos_callback = []([[maybe_unused]] Window& win,
                                double x,
                                double y) { printf("%.2f, %.2f\n", x, y); };

  window.SetInputCallback(input::CursorPosFn{cursor_pos_callback});

  while (!window.ShouldClose()) {
    window.SwapBuffer();
    window.PollEvents();
  }
}

TEST_F(WindowTest, Render) {
  VertexArray vao;
  vao.Bind();

  VertexBuffer vbo;
  VertexFormat format;

  // clang-format off
  constexpr float verts[] = {
      -0.5f, -0.5f, 0.0f, 
      0.5f, -0.5f, 0.0f,  
      0.0f, 0.5f, 0.0f,   
  };
  // clang-format on

  vbo.Set(sizeof(verts), verts);
  format.AddAttribute(0, 3, GL_FLOAT, GL_FALSE);

  while (!window.ShouldClose()) {
    window.PollEvents();

    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    format.Bind();
    vbo.Bind();
    vbo.Render(GL_TRIANGLES, 0, 3);

    window.SwapBuffer();
  }
}
}  // namespace ecs