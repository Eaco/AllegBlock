#include <allegro5/allegro5.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream> 
#include <math.h> 
#include <vector>

 
bool done;
ALLEGRO_EVENT_QUEUE* event_queue;
ALLEGRO_TIMER* timer;
ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_DISPLAY_MODE disp_data;
ALLEGRO_BITMAP* bouncer = NULL;
ALLEGRO_BITMAP* oppo = NULL;
ALLEGRO_BITMAP* tunity = NULL;                    //initialization of allegro data (Display, sprites etc)
float bouncer_x, bouncer_y,bouncer_dy,bouncer_dx;
float oppo_x, oppo_y,oppo_dy,oppo_dx;
   bool key[4] = { false, false, false, false };  //input bools
int displayHeight = 1080;                     
int displayWidth = 1920;                          //right now it's hard coded to 1920*1080, I'll fix soon

struct block                                  //block is simple enough to be a struct for now, so I wont make it a class
{
   int height;
   int width;
   int posx, posy;
   bool collisionio;
   
};



void abort_game(const char* message)
{
    printf("%s \n", message);
    exit(1);                            //closes window, ends task
}
 
void init(void)
{                         //Initialization phase, usually checks for pre-existance but sometimes I'm lazy

    if (!al_init())
        abort_game("Failed to initialize allegro");
      
    if (!al_install_keyboard())
        abort_game("Failed to install keyboard");

      al_init_image_addon();
      al_init_primitives_addon();

      al_install_mouse();


    timer = al_create_timer(1.0 / 60);

  al_get_display_mode(0, &disp_data);
    if (!timer)
        abort_game("Failed to create timer");
 
    al_set_new_display_flags(ALLEGRO_FULLSCREEN);
    display = al_create_display(disp_data.width, disp_data.height);     //this is supposed to make the app fullscreen, but fails on ubuntu. (I think this is due to allegro, not me)

    if (!display)
        abort_game("Failed to create display");
 
    event_queue = al_create_event_queue();
    if (!event_queue)
        abort_game("Failed to create event queue");


     // bouncer = al_load_bitmap("/home/ben/Sweden.png");
    if(!bouncer)
       bouncer = al_create_bitmap(100,100);
      if (!bouncer)
        abort_game("bitmap dead yo");

     if(!oppo)
       oppo = al_create_bitmap(100,100);

     if(!tunity)
       tunity = al_create_bitmap(100,100);


     
    al_set_target_bitmap(bouncer);                //create's my three current "sprites"
        al_clear_to_color(al_map_rgb(255,0,255));
    al_set_target_bitmap(oppo);
        al_clear_to_color(al_map_rgb(255,255,0));
      al_set_target_bitmap(tunity);
        al_clear_to_color(al_map_rgb(0,255,255));


    al_set_target_bitmap(al_get_backbuffer(display));






    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));
 
    done = false;
}
 
void shutdown(void)     //shutdown destroys all essentials
{
    if (timer)
        al_destroy_timer(timer);
 

    if (bouncer)
    {
       al_destroy_bitmap(bouncer);
    }

    if (display)
        al_destroy_display(display);
 
    if (event_queue)
        al_destroy_event_queue(event_queue);

}

 
void game_loop(void)          //here is all of the game logic
{
   bool collision;
   int mex = 0,mey =0;
   float angle;
    bool redraw = true;
    al_start_timer(timer);




      std::vector<block> v;      //vectors of blocks
      std::vector<block> b;


      struct block blick;
      blick.height = 40;
      blick.width = 40;

      blick.posy = 400;
      blick.posx = 600;
      v.push_back(blick);
      blick.posy = 200;
      blick.posx = 700;
      v.push_back(blick);
      blick.posy = 800;
      blick.posx = 700;
      v.push_back(blick);
      blick.posy = 450;
      blick.posx = 200;
      v.push_back(blick);
      blick.posy = 1000;
      blick.posx = 1900;
      v.push_back(blick);

      blick.posy = 1500;
      blick.posx = 2000;
      v.push_back(blick);
      blick.posy = 1900;
      blick.posx = 4500;
      v.push_back(blick);
      blick.posy = 700;
      blick.posx = 700;
      v.push_back(blick);
      blick.posy = 2000;
      blick.posx = 200;
      v.push_back(blick);
      blick.posy = 2000;
      blick.posx = 400;
      v.push_back(blick);


      blick.posy = 600;
      blick.posx = 400;
      b.push_back(blick);
      blick.posy = 900;
      blick.posx = 600;
      b.push_back(blick);
      blick.posy = 800;
      blick.posx = 700;
      b.push_back(blick);
      blick.posy = 200;
      blick.posx = 1599;
      b.push_back(blick);
      blick.posy = 900;
      blick.posx = 1700;
      b.push_back(blick);       //all of this will be replaced by a level loader soon
  
 
    while (!done) {         //Actual loop
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        for (int i = 0; i < v.size(); ++i)        //bounding box collision detection
        {
           if ((v[i].posy - 100 < bouncer_y && v[i].posy + 100  > bouncer_y )&& (v[i].posx+100 > bouncer_x && v[i].posx-100 < bouncer_x))
           {
              collision = true;
              v[i].collisionio = true; //IMPLEMENT COLLISION rectification
           }
        }
         for (int i = 0; i < v.size(); ++i)
        {
          for (int j = 0; j < b.size(); ++j)
          {
            /* code */
          
           if ((v[i].posy - 100 < b[j].posy && v[i].posy + 100  > b[j].posy )&& (v[i].posx+100 > b[j].posx && v[i].posx-100 < b[j].posx))
           {
              b[j].collisionio = true;
              v[i].collisionio = true; //IMPLEMENT COLLISION rectification
           }
         }
        }





        if (event.type == ALLEGRO_EVENT_TIMER) {



        if(!collision)  //this is what governs the speed of the player
        {

            if (bouncer_y < 0)
               bouncer_y = 0;

            if (bouncer_x < 0)
               bouncer_x = 0;

            if (bouncer_x> displayWidth-40)
               bouncer_x = displayWidth-40;

            if (bouncer_y > displayHeight-40)
               bouncer_y = displayHeight-40;

            if (key[1] == true){
               bouncer_dy -= 0.5;
               oppo_dy += 0.5;

            }

            if (key[2]) {
               bouncer_dy += 0.5;
               oppo_dy -=0.5;
            }

            if (key[3]){
               bouncer_dx -= 0.5;
               oppo_dx += 0.5;

            }

            if (key[0] ){
               bouncer_dx += 0.5;
               oppo_dx -= 0.5;
            }

            if (bouncer_dy > 5.0){
               bouncer_dy = 5.0;
               oppo_dy = -5.0;
            }

            if (bouncer_dx > 5.0) {
               bouncer_dx = 5.0;
               oppo_dx = -5.0;
            }
            
            if (bouncer_dy< -5.0) {
               bouncer_dy = -5.0;
               oppo_dy = 5.0;
            }

            if (bouncer_dx < -5.0){
               bouncer_dx = -5.0;
               oppo_dx = 5.0;
            }
         

            bouncer_x += bouncer_dx;
            bouncer_y += bouncer_dy;
            for (int i = 0; i < v.size(); ++i)      //box movement
            {
              if (!v[i].collisionio)    //the v boxes move opposite to player
              {
               v[i].posy -= bouncer_dy;
               v[i].posx -= bouncer_dx;
             }
            }
            for (int i = 0; i < b.size(); ++i)
            {
              if(!b[i].collisionio)     //the b boxes move in the same y direction, opposite x direction
              {
               b[i].posy += bouncer_dy;
               b[i].posx -= bouncer_dx;
              }
            }
            //oppo_y += oppo_dy;
            //oppo_x += oppo_dx;


            if (bouncer_dx > 0)     //slows down the objects
            {
               bouncer_dx -= 0.25;
               oppo_dx += 0.25;
            }
            if (bouncer_dx < 0)
            {
               bouncer_dx += 0.25;
               oppo_dx -= 0.25;
            }

            if (bouncer_dy > 0)
            {
               bouncer_dy -= 0.25;
               oppo_dy += 0.25;
            }
            if (bouncer_dy < 0)
            {
               bouncer_dy += 0.25;
               oppo_dy -= 0.25;
            }
            }

            if (collision == true)
            {
               bouncer_dx = 0;
               bouncer_dy = 0;
            }

            
            redraw = true;
            //update_logic();
        }
       if (event.type == ALLEGRO_EVENT_KEY_DOWN) { //key listening 
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                done = true;
            }
           
            
            if (event.keyboard.keycode == ALLEGRO_KEY_UP)
               {
                  key[1] = true;
               }   
            if (event.keyboard.keycode == ALLEGRO_KEY_DOWN)
            {
               key[2] = true;
            }

            if (event.keyboard.keycode == ALLEGRO_KEY_LEFT)
            {
               key[3] = true;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
            {
               key[0] = true;
            }
        }
         if (event.type == ALLEGRO_EVENT_KEY_UP) {
            
            if (event.keyboard.keycode == ALLEGRO_KEY_UP)
               {
                  key[1] = false;
               }   
            if (event.keyboard.keycode == ALLEGRO_KEY_DOWN)
            {
               key[2] = false;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_LEFT)
            {
               key[3] = false;
            }

            if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
            {
               key[0] = false;
            }
        }

 
        if (redraw && al_is_event_queue_empty(event_queue)) { //drawing
            redraw = false;
            al_clear_to_color(al_map_rgb(0, 0, 0));
            //update_graphics();
           // rotate_sprite(display,bouncer, bouncer_x, bouncer_y, angle);
            for (int i = 0; i < v.size(); ++i)
            {
               al_draw_bitmap(oppo, v[i].posx, v[i].posy, 0);
            }
            for (int i = 0; i < b.size(); ++i)
            {
               al_draw_bitmap(tunity, b[i].posx, b[i].posy, 0);
            }
            al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);
          //  al_draw_bitmap(oppo, oppo_x, oppo_y, 0);
            al_flip_display();
        }
    }
}


int main(int argc, char* argv[])  //main!
{
    init();
    game_loop();
    shutdown();
}



/* g++ hello.cpp -o hello $(pkg-config --cflags --libs allegro-5.0 allegro_main-5.0 allegro_primitives-5.0 allegro_image-5.0)*/