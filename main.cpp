#include <stdint.h>
#include <stdio.h>
#include <iostream>  
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include "imgui_files/imgui.h"
#include "imgui_files/imgui_impl_allegro5.h"

#include "blopping.h"

#define MAXBLOBS 700
#define MAXFRUTA 400
#define VMIN 1.0
#define VMAX 5.0
#define MODO1 1
#define MODO2 2

//function nose donde ponerla
int randomVelocity(int vmax, int vmin);

using namespace std;


void print_gui(bool* main_menu, int* cantblobs, int* food_count, int* simulation_mode, double* max_velocity, int* rel_velocity, int* smell_radius, int* random_jiggle_limit, double* mortality_rate);
void print_al(blob* blobArray, food* foodArray, uint maxblob, uint blobCount, uint foodCount, ALLEGRO_BITMAP* baby, ALLEGRO_BITMAP* grown, ALLEGRO_BITMAP* old, ALLEGRO_BITMAP* food);
void create_world(blob* blobArray, food* foodArray, int food_count, int cantblobs, int mort_rate, int relative_velocity, int smell_radius, int random_j_l, int simulation_mode);

int main(int, char**)
{
    srand(time(NULL));

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

    ALLEGRO_BITMAP* babyBlobSprite = al_load_bitmap("./blob-sprites/babyblob.png");
    if (babyBlobSprite == NULL) {
        std::cout << "Couldn't load babyBlob image!" << std::endl;
        //return -1;
    }
    ALLEGRO_BITMAP* grownBlobSprite = al_load_bitmap("./blob-sprites/grownblob.png");
    if (grownBlobSprite == NULL) {
        std::cout << "Couldn't load grownBlob image!" << std::endl;
        //return -1;
    }
    ALLEGRO_BITMAP* goodOldBlobSprite = al_load_bitmap("./blob-sprites/goodoldblob.png");
    if (goodOldBlobSprite == NULL) {
        std::cout << "Couldn't load goodOldBlob image!" << std::endl;
        //return -1;
    }
    ALLEGRO_BITMAP* foodSprite = al_load_bitmap("./blob-sprites/food.png");
    if (foodSprite == NULL) {
        std::cout << "Couldn't load food image!" << std::endl;
        //return -1;
    }


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
 //   double relative_velocity = 1.0;
    int relative_velocity = 1;
    int smell_radius = 100;
    int random_j_l = 1;
    double mort_rate = 0.5;
    int start = 0;

    //Arreglos de comidas y blobs
    food* foodArray = new food[MAXFRUTA];
    blob* blobArray = new babyBlob[MAXBLOBS];

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
            //ImGui::ShowDemoWindow(&show_demo_window);
        }


        if (main_menu == false && start == 0)
        {
            create_world(blobArray, foodArray, food_count, cantblobs, mort_rate, relative_velocity, smell_radius, random_j_l, simulation_mode);
            start++;
        }


        // Rendering
        ImGui::Render();

        al_clear_to_color(al_map_rgba_f(clear_color.x, clear_color.y, clear_color.z, clear_color.w));

        al_draw_scaled_bitmap(background,
            0, 0, 900, 470,
            0, 0, 1280, 720, 0);

        //ACÁ HAY QUE LLAMAR A LAS FUNCIONES DE ALLEGRO PARA DIBUJAR A LOS BLOBS Y LA COMIDA

        print_al(blobArray, foodArray, MAXBLOBS, cantblobs, food_count, babyBlobSprite, grownBlobSprite, goodOldBlobSprite, foodSprite);
        start_blopping(blobArray, foodArray,mort_rate);         //NOTA ESTE MORT RATE TIENE Q IR CAMBIANDO CON INPUT DE USERRR

        ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());
        al_flip_display();
    }

    // Cleanup
    ImGui_ImplAllegro5_Shutdown();
    ImGui::DestroyContext();
    al_destroy_event_queue(queue);
    al_destroy_display(display);
    al_destroy_bitmap(babyBlobSprite);
    al_destroy_bitmap(grownBlobSprite);
    al_destroy_bitmap(goodOldBlobSprite);
    al_destroy_bitmap(foodSprite);


    return 0;
}



void create_world(blob* blobArray, food* foodArray, int food_count, int cantblobs, int mort_rate, int relative_velocity, int smell_radius, int random_j_l, int simulation_mode)
{

    food::foodTotalCount = food_count;
    blob::blobTotalCount = cantblobs;

    int i;

    for (i = 0; i < cantblobs; i++)          
    {
        //Empiezan todos BABY BLOBS
        /*
         blobArray[i]= blob(random_position_x,
                            random_position_y,
                            random_deathProb,
                            speed,
                            radio,
                            max_food_count,
                            randomjiggle);
         */
         //https://stackoverflow.com/questions/686353/random-float-number-generation
        blobArray[i] = blob((static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (WIDTH)))),
            (static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (HEIGHT)))),
            mort_rate,
            relative_velocity,
            smell_radius,
            BABYMAXFOOD,
            random_j_l);
    }

    for (i = 0; i < food_count; i++)
    {
        foodArray[i] = food((static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / WIDTH))), (static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / HEIGHT))));
    }

    if (simulation_mode == MODO1)
    {
        for (i = 0; i < MAXBLOBS; i++)             //Seteamos velocidades para todos los existentes y futuros blobs para tenerlos listo en blobBirth
        {
            blobArray[i].setVelocity(VMAX);
        }
    }
    else if (simulation_mode == MODO2)
    {
        for (i = 0; i < MAXBLOBS; i++)
        {
            blobArray[i].setVelocity(randomVelocity(VMAX, VMIN));
        }
    }
    al_flip_display();
}

void print_al(blob* blobArray, food* foodArray, uint maxblob, uint blobCount, uint foodCount, ALLEGRO_BITMAP* baby, ALLEGRO_BITMAP* grown, ALLEGRO_BITMAP* old, ALLEGRO_BITMAP* food)
{

    uint i;

    for (i = 0; i < maxblob; i++)
    {
        //ME FALTA CORREGIR LA SUMA DE LOS RADIOS(DEJARLO MAS PROLIJO Y CAMBIAR EL BACKEND)
        if (blobArray[i].getblobStatus())
        {
            al_draw_bitmap(baby, blobArray[i].getPosx(), blobArray[i].getPosy(), 0);
            al_draw_circle(blobArray[i].getPosx() + 20, blobArray[i].getPosy() + 20, blobArray[i].getblobRadius() + 20, al_color_name("red"), 2.0);
        }
        /*
        else if (blobArray[i].getblobStatus() && blobArray[i].getfoodCount() == GROWNMAXFOOD)
        {
            al_draw_bitmap(grown, blobArray[i].getPosx(), blobArray[i].getPosy(), 0);
            al_draw_circle(blobArray[i].getPosx() + 30, blobArray[i].getPosy() + 30, blobArray[i].getblobRadius() + 30, al_color_name("red"), 2.0);
        }
        else if (blobArray[i].getblobStatus() && blobArray[i].getfoodCount() == OLDMAXFOOD)
        {
            al_draw_bitmap(old, blobArray[i].getPosx(), blobArray[i].getPosy(), 0);
            al_draw_circle(blobArray[i].getPosx() + 40, blobArray[i].getPosy() + 40, blobArray[i].getblobRadius() + 40, al_color_name("red"), 2.0);
        }
        */
    }

    for (i = 0; i < foodCount; i++)
    {
        al_draw_bitmap(food, foodArray[i].getPosx_f(), foodArray[i].getPosy_f(), 0);
    }
    al_flip_display();
}


void print_gui(bool* main_menu, int* cantblobs, int* food_count, int* simulation_mode, double* max_velocity, int* relative_velocity, int* smell_radius, int* random_jiggle_limit, double* mortality_rate) {

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
        ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.93f);
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


int randomVelocity(int vmax, int vmin)
{
    return rand() % (vmax - vmin + 1) + vmin;
}