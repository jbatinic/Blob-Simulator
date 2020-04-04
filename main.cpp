#include <stdint.h>
#include <iostream>  
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "imgui_files/imgui.h"
#include "imgui_files/imgui_impl_allegro5.h"

void print_gui(bool* main_menu, int* cantblobs, int* food_count, int* simulation_mode, double* max_velocity, double* rel_velocity, int* smell_radius, int* random_jiggle_limit, double* mortality_rate);

int main(int, char**)
{
    // Setup Allegro
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();
    al_init_primitives_addon();
    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    ALLEGRO_DISPLAY* display = al_create_display(1280, 720);
    ALLEGRO_BITMAP* background = al_load_bitmap("./blob-sprites/background.jpg");
    if (background == NULL) {
        std::cout << "Couldn't load background image!" << std::endl;
        return -1;
    }
    al_set_window_title(display, "Dear ImGui Allegro 5 example");
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplAllegro5_Init(display);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'docs/FONTS.txt' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    bool running = true;

    //Parámetros de la simulación

    bool main_menu = true;
    int cantblobs = 1;
    int food_count = 1;
    int simulation_mode = 1;
    double max_velocity = 15.0;
    double relative_velocity = 1.0;
    int smell_radius = 100;
    int random_j_l = 1;
    double mort_rate = 0.5;


    
    while (running)
    {

        ALLEGRO_EVENT ev;
        while (al_get_next_event(queue, &ev))
        {
            ImGui_ImplAllegro5_ProcessEvent(&ev);
            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                running = false;
            if (ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE)
            {
                ImGui_ImplAllegro5_InvalidateDeviceObjects();
                al_acknowledge_resize(display);
                ImGui_ImplAllegro5_CreateDeviceObjects();
            }
        }

        // Start the Dear ImGui frame

        ImGui_ImplAllegro5_NewFrame();
        ImGui::NewFrame();

        {   
           
            print_gui(&main_menu, &cantblobs, &food_count, &simulation_mode, &max_velocity, &relative_velocity, &smell_radius, &random_j_l, &mort_rate);
            ImGui::ShowDemoWindow(&show_demo_window);

        }

        // Rendering
        ImGui::Render();

        al_clear_to_color(al_map_rgba_f(clear_color.x, clear_color.y, clear_color.z, clear_color.w));
        
        al_draw_scaled_bitmap(background,
            0, 0, 900, 470,
            0, 0, 1280, 720, 0);

        //ACÁ HAY QUE LLAMAR A LAS FUNCIONES DE ALLEGRO PARA DIBUJAR A LOS BLOBS Y LA COMIDA


        ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());
        al_flip_display();
    }

    // Cleanup
    ImGui_ImplAllegro5_Shutdown();
    ImGui::DestroyContext();
    al_destroy_event_queue(queue);
    al_destroy_display(display);
    al_destroy_bitmap(al_load_bitmap("babyblob.png"));

    return 0;
}


void print_gui(bool* main_menu, int* cantblobs, int*food_count, int*simulation_mode, double* max_velocity, double* relative_velocity, int* smell_radius, int* random_jiggle_limit, double * mortality_rate) {
 
    ImGuiWindowFlags window_flags = 0;
    if (*main_menu) {
        ImGui::SetNextWindowPos(ImVec2(500, 50));
        if (*simulation_mode == 1) {
            ImGui::SetNextWindowSize(ImVec2(250, 550));
        }
        else {
            ImGui::SetNextWindowSize(ImVec2(250, 500));
        }

        ImGui::SetNextWindowBgAlpha(0.35f);
        window_flags |= ImGuiWindowFlags_NoTitleBar;
        window_flags |= ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoResize;
    }
    else {
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        if (*simulation_mode == 1) {
            ImGui::SetNextWindowSize(ImVec2(250, 400));
        }
        else {
            ImGui::SetNextWindowSize(ImVec2(250, 350));
        }

        ImGui::SetNextWindowBgAlpha(0.35f);
        //window_flags |= ImGuiWindowFlags_NoTitleBar;
        window_flags |= ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoResize;
    }
    


    ImGui::Begin("Blob-Simulator", 0, window_flags);

    if (*main_menu) {
        ImGui::TextWrapped("Main Menu");
        
        //: a.Modo de simulación: 1 o 2 (no debe ser modificado durante la simulación).

        ImGui::Dummy(ImVec2(0.0f, 10.0f));
        ImGui::AlignTextToFramePadding();
        ImGui::Text("Modo de Simulacion:");
        ImGui::SameLine();
        float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
        ImGui::PushButtonRepeat(true);
        if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { 
            if (*simulation_mode == 1)
                *simulation_mode = 2;
            else
                *simulation_mode = 1;
        }
        ImGui::SameLine(0.0f, spacing);
        if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { 
            if (*simulation_mode == 1)
                *simulation_mode = 2;
            else
                *simulation_mode = 1;
        }
        ImGui::PopButtonRepeat();
        ImGui::SameLine();
        ImGui::Text("%d", *simulation_mode);

        //b.Cantidad inicial de blobs (no debe ser modificado durante la simulación). 

        ImGui::Dummy(ImVec2(0.0f, 10.0f));
        ImGui::TextWrapped("Cantidad de blobs:");
        ImGui::PushItemWidth(ImGui::GetWindowWidth()*0.93f);
        ImGui::SliderInt(" ", cantblobs, 1, 50);
        ImGui::AlignTextToFramePadding();
        if (ImGui::Button("Menos blobs") && *cantblobs > 1)
            (*cantblobs)--;

        ImGui::SameLine(0.0, ImGui::GetStyle().ItemInnerSpacing.x);

        if (ImGui::Button("Mas blobs") && *cantblobs < 50)
            (*cantblobs)++;
        ImGui::Dummy(ImVec2(0.0f, 10.0f));
    }
    else {
        ImGui::TextWrapped("Parameters");

    }

    //h.foodCount: Cantidad de alimento.

    ImGui::Dummy(ImVec2(0.0f, 10.0f));
    ImGui::TextWrapped("Cantidad de comida:");
    ImGui::SliderInt("", food_count, 1, 50);
    if (ImGui::Button("Menos comida") && *food_count > 1)
        (*food_count)--;

    ImGui::SameLine(0.0, ImGui::GetStyle().ItemInnerSpacing.x);

    if (ImGui::Button("Mas comida") && *food_count < 50)
        (*food_count)++;


    //d.Velocidad porcentual de los blobs. (se sugiere utilizar un slider)  
    ImGui::Dummy(ImVec2(0.0f, 10.0f));
    int rel_vel = (*relative_velocity) * 100;
    ImGui::TextWrapped("Velocidad porcentual:");
    ImGui::DragInt("  ", &rel_vel, 1, 0, 100, "%d%%");
    *relative_velocity = rel_vel / 100.0;
    

    //e.smellRadius: Radio de detección de la comida desde el centro del Blob. 

    ImGui::Dummy(ImVec2(0.0f, 10.0f));
    ImGui::TextWrapped("Smell Radius:");
    ImGui::InputInt("   ", smell_radius, 1, 100, 0);

    //f.randomJiggleLimit: Valor aleatorio a sumar para el cálculo de la dirección. 

    ImGui::Dummy(ImVec2(0.0f, 10.0f));
    ImGui::TextWrapped("Random Jiggle Limit:");
    ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.93f);
    ImGui::SliderInt("     ", random_jiggle_limit, 1, 360);

    //g.Probabilidad de muerte de cada grupo etario e(0,1)
 
    ImGui::Dummy(ImVec2(0.0f, 10.0f));
    int death_chance = (*mortality_rate) * 100;
    ImGui::TextWrapped("Tasa de Mortalidad:");
    ImGui::DragInt("    ", &death_chance, 1, 0, 100, "%d%%");
    *mortality_rate = death_chance / 100.0;

    //c.Velocidad máxima de los blobs (solamente en modo 1).
    if (*simulation_mode == 1) {
        ImGui::Dummy(ImVec2(0.0f, 10.0f));
        ImGui::TextWrapped("Velocidad maxima:");
        ImGui::InputFloat("input float", (float*)max_velocity, 0.01f, 1.0f, "%.3f");
    }

    if (*main_menu) {
        ImGui::Dummy(ImVec2(0.0f, 10.0f));
        static int clicked = 0;
        if (ImGui::Button("RUN"))
            clicked++;
        if (clicked & 1)
        {
            *main_menu = false;
        }
    }

    ImGui::End();
}
