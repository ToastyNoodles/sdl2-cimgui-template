#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#define CIMGUI_USE_OPENGL3
#define CIMGUI_USE_SDL2
#include <cimgui/cimgui.h>
#include <cimgui/cimgui_impl.h>
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

bool windowShouldClose = false;
bool showDemoWindow = true;
ImVec4 clearColor = {0.1f, 0.1f, 0.1f, 1.0f};

void ImGUITestWindow()
{
    static float f = 0.0f;
    static int counter = 0;

    igBegin("Hello, world!", NULL, 0);
    igText("This is some useful text");
    igCheckbox("Demo window", &showDemoWindow);

    igSliderFloat("Float", &f, 0.0f, 1.0f, "%.3f", 0);
    igColorEdit3("clear color", (float*)&clearColor, 0);

    ImVec2 buttonSize;
    buttonSize.x = 0;
    buttonSize.y = 0;
    if (igButton("Button", buttonSize))
    {
        counter++;
    }
    igSameLine(0.0f, -1.0f);
    igText("counter = %d", counter);

    igText("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / igGetIO()->Framerate, igGetIO()->Framerate);
    igEnd();
}

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    
    SDL_Window* window = SDL_CreateWindow("Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);

    SDL_GLContext* glContext = SDL_GL_CreateContext(window);
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        printf("Failed to load GL context.\n");
    }

    printf("Vendor: %s\n", glGetString(GL_VENDOR));
    printf("Device: %s\n", glGetString(GL_RENDERER));
    printf("Version: %s\n", glGetString(GL_VERSION));

    igCreateContext(NULL);
    ImGuiIO* io = igGetIO();
    ImGui_ImplSDL2_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init("#version 330");
    igStyleColorsDark(NULL);

    while (!windowShouldClose)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
            {
                windowShouldClose = true;
            }
        }

        //Begin Frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        igNewFrame();

        if (showDemoWindow)
        {
            igShowDemoWindow(&showDemoWindow);
        }

        ImGUITestWindow();

        //Render Frame
        igRender();
        SDL_GL_MakeCurrent(window, glContext);
        glViewport(0, 0, (int)io->DisplaySize.x, (int)io->DisplaySize.y);
        glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());

        //End Frame
        SDL_GL_SwapWindow(window);
    }
}