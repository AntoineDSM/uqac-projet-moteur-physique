//Date de création :
//Créer par :
//Date de dernière modification :
//Modifié par : 



#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>



int main(int, char**)
{
    GLFWwindow* window;

    glGetString(GL_VERSION);
    //Initialize the library //
    if (!glfwInit())
        return -1;

    // Create a windowed mode window and its OpenGL context 
    window = glfwCreateWindow(640, 480, "Hello World Victor", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    
    //Make the window's context current //
    glfwMakeContextCurrent(window);
    // Initialize ImGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
   // ImGui_ImplOpenGL3_Init("#version 450");

    // Variables to be changed in the ImGUI window
    bool drawTriangle = true;
    float size = 1.0f;
    float color[4] = { 0.8f, 0.3f, 0.02f, 1.0f };



    // Loop until the user closes the window //
    while (!glfwWindowShouldClose(window))
    {
        // Render here //
        glClear(GL_COLOR_BUFFER_BIT);

        // Tell OpenGL a new frame is about to begin
        //ImGui_ImplOpenGL3_NewFrame();
        //ImGui_ImplGlfw_NewFrame();
        //ImGui::NewFrame();


        // ImGUI window creation
        ImGui::Begin("My name is window, ImGUI window");
        // Text that appears in the window
        ImGui::Text("Hello there adventurer!");
        // Checkbox that appears in the window
        ImGui::Checkbox("Draw Triangle", &drawTriangle);
        // Slider that appears in the window
        ImGui::SliderFloat("Size", &size, 0.5f, 2.0f);
        // Fancy color editor that appears in the window
        ImGui::ColorEdit4("Color", color);
        // Ends the window
        ImGui::End();


        // Renders the ImGUI elements
        ImGui::Render();
        //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap front and back buffers //
        glfwSwapBuffers(window);

        // Poll for and process events //
        glfwPollEvents();
    }

    // Deletes all ImGUI instances
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();


    glfwTerminate();
    
}


