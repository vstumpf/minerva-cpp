#include "modes/LoginMode.hpp"

#include <SDL.h>
#include "common/debug.hpp"
#include "common/globals.hpp"

void LoginMode::init() {}

// // Shader sources
// const GLchar* vertexSource = R"glsl(
//     #version 150 core
//     in vec2 position;
//     void main()
//     {
//         gl_Position = vec4(position, 0.0, 1.0);
//     }
// )glsl";
// const GLchar* fragmentSource = R"glsl(
//     #version 150 core
//     out vec4 outColor;
//     void main()
//     {
//         outColor = vec4(1.0, 1.0, 1.0, 1.0);
//     }
// )glsl";

int LoginMode::run() {
  // // Create Vertex Array Object
  // GLuint vao;
  // glGenVertexArrays(1, &vao);
  // glBindVertexArray(vao);

  // // Create a Vertex Buffer Object and copy the vertex data to it
  // GLuint vbo;
  // glGenBuffers(1, &vbo);

  // GLfloat vertices[] = {
  // 	0.0f,  0.5f,
  // 	0.5f, -0.5f,
  // 	-0.5f, -0.5f
  // };

  // glBindBuffer(GL_ARRAY_BUFFER, vbo);
  // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // // Create and compile the vertex shader
  // GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  // glShaderSource(vertexShader, 1, &vertexSource, NULL);
  // glCompileShader(vertexShader);

  // // Create and compile the fragment shader
  // GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  // glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
  // glCompileShader(fragmentShader);

  // // Link the vertex and fragment shader into a shader program
  // GLuint shaderProgram = glCreateProgram();
  // glAttachShader(shaderProgram, vertexShader);
  // glAttachShader(shaderProgram, fragmentShader);
  // glBindFragDataLocation(shaderProgram, 0, "outColor");
  // glLinkProgram(shaderProgram);
  // glUseProgram(shaderProgram);

  // // Specify the layout of the vertex data
  // GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
  // glEnableVertexAttribArray(posAttrib);
  // glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

  // SDL_Event windowEvent;
  // while (getShouldLoop()) {
  // 	if (SDL_PollEvent(&windowEvent)) {
  // 		switch (windowEvent.type) {
  // 		case SDL_QUIT:
  // 			setShouldLoop(false);
  // 			break;
  // 		case SDL_KEYUP:
  // 			if (windowEvent.key.keysym.sym == SDLK_ESCAPE)
  // 				setShouldLoop(false);
  // 			break;
  // 		}
  // 	}
  // 	update();
  // }

  // glDeleteProgram(shaderProgram);
  // glDeleteShader(fragmentShader);
  // glDeleteShader(vertexShader);

  getCamera().reset();

  SDL_Event windowEvent;
  while (getShouldLoop()) {
    if (SDL_PollEvent(&windowEvent)) {
      switch (windowEvent.type) {
        case SDL_QUIT:
          setShouldLoop(false);
          break;
        case SDL_MOUSEWHEEL:
          if (windowEvent.wheel.y > 0) {
            getCamera().addDistance(-5.f);
          } else if (windowEvent.wheel.y < 0) {
            getCamera().addDistance(5.f);
          }
          break;
        case SDL_KEYUP:
          switch (windowEvent.key.keysym.sym) {
            case SDLK_ESCAPE:
              setShouldLoop(false);
              break;
            case SDLK_w:
              getCamera().addLatitude(5.f);
              break;
            case SDLK_s:
              getCamera().addLatitude(-5.f);
              break;
            case SDLK_a:
              getCamera().addLongitude(5.f);
              break;
            case SDLK_d:
              getCamera().addLongitude(-5.f);
              break;
            case SDLK_UP:
              playerPos.y += 1;
              break;
            case SDLK_DOWN:
              playerPos.y -= 1;
              break;
            case SDLK_LEFT:
              playerPos.x -= 1;
              break;
            case SDLK_RIGHT:
              playerPos.x += 1;
              break;
          }
          break;
      }
    }
    update();
  }

  return 0;
}

void LoginMode::exit() {}

// char const* gl_error_string(GLenum const err) noexcept
// {
//   switch (err)
//   {
//     // opengl 2 errors (8)
//     case GL_NO_ERROR:
//       return "GL_NO_ERROR";

//     case GL_INVALID_ENUM:
//       return "GL_INVALID_ENUM";

//     case GL_INVALID_VALUE:
//       return "GL_INVALID_VALUE";

//     case GL_INVALID_OPERATION:
//       return "GL_INVALID_OPERATION";

//     case GL_STACK_OVERFLOW:
//       return "GL_STACK_OVERFLOW";

//     case GL_STACK_UNDERFLOW:
//       return "GL_STACK_UNDERFLOW";

//     case GL_OUT_OF_MEMORY:
//       return "GL_OUT_OF_MEMORY";

//     // opengl 3 errors (1)
//     case GL_INVALID_FRAMEBUFFER_OPERATION:
//       return "GL_INVALID_FRAMEBUFFER_OPERATION";

//     // gles 2, 3 and gl 4 error are handled by the switch above
//     default:
//       assert(!"unknown error");
//       return nullptr;
//   }
// }

void LoginMode::update() {
  // // Clear the screen to black
  // glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  // glClear(GL_COLOR_BUFFER_BIT);

  // // Draw a triangle from the 3 vertices
  // glDrawArrays(GL_TRIANGLES, 0, 3);
  // auto error = glGetError();

  // LOG(debug, gl_error_string(error));

  // // Swap buffers
  // renderer_->flip();

  minerva::globals::gRenderer->clear();
  getCamera().onCalcViewInfo(playerPos);

  auto pos = glm::vec3(0.f, 0.f, 0.f);
  int currentTick = SDL_GetTicks();
  pos.x = static_cast<float>(currentTick % 4000) / 1000.f - 2;
  pos.y = static_cast<float>(currentTick % 4000) / 1000.f - 2;
  pos.z = 1;
  growlithe_.setPos(pos);
  growlithe_.render(getCamera());

  pos.x = (static_cast<float>(currentTick % 4000) / 1000.f - 2);
  pos.y = -(static_cast<float>(currentTick % 4000) / 1000.f - 2);
  growlithe2_.setPos(pos);
  growlithe2_.render(getCamera());

  minerva::globals::gRenderer->drawScene(getCamera());
  minerva::globals::gRenderer->flip();
}
