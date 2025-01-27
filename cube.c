#include <SDL2/SDL.h>
#include <stdbool.h>

// Resolution of an Anbernic RG35XXH
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define CUBE_SIZE 100

 typedef struct {
    float x, y, z;
} Point3D;

typedef struct {
    int x, y;
} Point2D;

// Rotation angles
float angleX = 0.0f, angleY = 0.0f;

void handleInput(bool *running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
    case SDL_QUIT:
        *running = false;
        break;
    case SDL_KEYDOWN: // Keyboard
      switch (event.key.keysym.sym) {
          case SDLK_UP: angleX -= 5.0f; break;
          case SDLK_DOWN: angleX += 5.0f; break;
          case SDLK_LEFT: angleY -= 5.0f; break;
          case SDLK_RIGHT: angleY += 5.0f; break;
          case SDLK_RETURN: *running = false; break;
      }
      break;
    case SDL_CONTROLLERBUTTONDOWN: // Gamepad
      switch (e->cbutton.button) {
          case SDL_CONTROLLER_BUTTON_DPAD_UP: angleX -= 5.0f; break;
          case SDL_CONTROLLER_BUTTON_DPAD_DOWN: angleX += 5.0f; break;
          case SDL_CONTROLLER_BUTTON_DPAD_LEFT: angleY -= 5.0f; break;
          case SDL_CONTROLLER_BUTTON_DPAD_RIGHT: angleY += 5.0f; break;
          case SDL_CONTROLLER_BUTTON_START: *running = false; break;
      }
    }
}

void rotateX(Point3D *point, float angle) {
    float rad = angle * M_PI / 180.0;
    float y = point->y * cos(rad) - point->z * sin(rad);
    float z = point->y * sin(rad) + point->z * cos(rad);
    point->y = y;
    point->z = z;
}

void rotateY(Point3D *point, float angle) {
    float rad = angle * M_PI / 180.0;
    float x = point->x * cos(rad) + point->z * sin(rad);
    float z = -point->x * sin(rad) + point->z * cos(rad);
    point->x = x;
    point->z = z;
}

Point2D project(Point3D point) {
    float distance = 500;
    float factor = distance / (distance + point.z);
    Point2D projected = {
        .x = (int)(point.x * factor + SCREEN_WIDTH / 2),
        .y = (int)(point.y * factor + SCREEN_HEIGHT / 2)
    };
    return projected;
}

int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0) {
      printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
      return 1;
    }

    // Create window
    SDL_Window *window = SDL_CreateWindow(
        "Cube", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      SDL_Quit();
      return 1;
    }

    // Create renderer
    SDL_Renderer *renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
      printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
      SDL_DestroyWindow(window);
      SDL_Quit();
      return 1;
    }

    // Cube
    Point3D cube[8] = {
        {-CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE},
        { CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE},
        { CUBE_SIZE,  CUBE_SIZE, -CUBE_SIZE},
        {-CUBE_SIZE,  CUBE_SIZE, -CUBE_SIZE},
        {-CUBE_SIZE, -CUBE_SIZE,  CUBE_SIZE},
        { CUBE_SIZE, -CUBE_SIZE,  CUBE_SIZE},
        { CUBE_SIZE,  CUBE_SIZE,  CUBE_SIZE},
        {-CUBE_SIZE,  CUBE_SIZE,  CUBE_SIZE}
    };

    Point3D transformed[8];

    int edges[12][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, // Back face
        {4, 5}, {5, 6}, {6, 7}, {7, 4}, // Front face
        {0, 4}, {1, 5}, {2, 6}, {3, 7}  // Connecting edges
    };

    bool running = true;
    while (running) {
        handleInput(&running);

        // Fill background
        SDL_SetRenderDrawColor(renderer, 40, 40, 50, 255);
        SDL_RenderClear(renderer);

        // Update cube point coordinates
        for (int i = 0; i < 8; i++) {
            transformed[i] = cube[i];
            rotateX(&transformed[i], angleX);
            rotateY(&transformed[i], angleY);
        }

        // Draw the cube edges
        SDL_SetRenderDrawColor(renderer, 255, 255, 220, 255);
        for (int i = 0; i < 12; i++) {
            Point2D p1 = project(transformed[edges[i][0]]);
            Point2D p2 = project(transformed[edges[i][1]]);
            drawLine(renderer, p1, p2);
        }
    }

    // Exit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

