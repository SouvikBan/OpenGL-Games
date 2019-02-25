#include <vector>
#include "main.h"
#include "timer.h"
#include "fighter.h"
#include "sea.h"
#include "ring.h"
#include "missile.h"
#include "land.h"
#include "cannon.h"
#include "volcano.h"
#include "fuel.h"
#include "fire.h"
#include "bomb.h"
#include "parachute.h"
#include "sev_seg.h"
#include "compass.h"

using namespace std;

GLMatrices Matrices,Dash;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/


float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0, camera_x = 0, camera_y = 5, camera_z = -35, pitch = 0;
float target_x, target_y, target_z,heli_rotation_x=0,heli_rotation_y = 0,up_x=0,up_y=1,up_z=0;;
float camera_rotation_angle = 0;
int view_type = 2, collide = 0, forward_press = 0,plane_gone=0,counter=0;
int point=0;
bool movement = true;
Fighter fighter; 
Sea sea;
Missile new_missile;
Bomb new_bomb;
Fire new_fire;
vector <Missile> missiles;
vector <Bomb> bombs;
vector <Fire> fires;
Ring rings[100];
int ring_spawn[100];
int cannon_spawn[100];
int parachute_spawn[30];
int fuel_spawn[10];
Land lands[100];
Cannon cannons[100];
Volcano volcanoes[30];
Fuel fuelup[10];
Parachute parachutes[30];
Seven life[3];
Seven points[3];
Seven fuel[3];
Compass compass;

Timer t60(1.0 / 60);


/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( camera_x, camera_y, camera_z );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (target_x, target_y, target_z);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (up_x, up_y, up_z);


    glm::vec3 dash_eye (0, 0, -10);
    glm::vec3 dash_target (0, 0, 0);
    glm::vec3 dash_up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up );
    Dash.view    =  glm::lookAt( dash_eye, dash_target, dash_up);
     // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 dash_VP = Dash.projection * Dash.view;
    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    for( int i=0; i < missiles.size(); i++)
        missiles[i].draw(VP);
    for(int i=0; i< bombs.size(); i++)
        bombs[i].draw(VP);
    for(int i=0; i< fires.size(); i++)
        fires[i].draw(VP);
   
    compass.draw(dash_VP);   
    fighter.draw(VP);
    sea.draw(VP);
    for(int i=0; i<60 ;i++){
        if(ring_spawn[i]== 1)
            rings[i].draw(VP);
        lands[i].draw(VP);
        if(cannon_spawn[i]==1)
            cannons[i].draw(VP);
    }
    for(int i=0 ;i<30 ;i++)
    {
        if(parachute_spawn[i]==1)
            parachutes[i].draw(VP);
        volcanoes[i].draw(VP);
    }
    
    for(int i=0 ;i<10 ;i++)
    {
        if(fuel_spawn[i]==1)
            fuelup[i].draw(VP);
    }
    

    //dashboard render
    int lifepercentage = (int)(fighter.life);
    life[2].draw_num(dash_VP, lifepercentage%10);
    life[1].draw_num(dash_VP, (lifepercentage/10)%10);
    life[0].draw_num(dash_VP, (lifepercentage)/100);
    
    points[0].draw_num(dash_VP, point%10);
    points[1].draw_num(dash_VP, (point/10)%10);
    points[2].draw_num(dash_VP, (point/100));

    int fuelamount = (int)(fighter.fuel/100);
    fuel[0].draw_num(dash_VP, fuelamount%10);
    fuel[1].draw_num(dash_VP, (fuelamount/10)%10);
    fuel[2].draw_num(dash_VP, (fuelamount/100));
}

void bomb_generate(int mouse){
    if(mouse == -1){
        new_missile = Missile(fighter.position.x, fighter.position.y, fighter.position.z);
        new_missile.yaw_angle = fighter.yaw_angle;
        new_missile.pitch_angle = fighter.pitch_angle;
        new_missile.roll_angle = fighter.roll_angle;
        missiles.push_back(new_missile);
    }
    else{
        new_bomb = Bomb(fighter.position.x, fighter.position.y, fighter.position.z);
        bombs.push_back(new_bomb);
    }
}

void tick_input(GLFWwindow *window) {
    forward_press = 0;
    int top_view = glfwGetKey(window, GLFW_KEY_5);
    int front_view = glfwGetKey(window, GLFW_KEY_2);
    int follow_view = glfwGetKey(window, GLFW_KEY_8);
    int tower_view = glfwGetKey(window, GLFW_KEY_9);
    int heli_view  = glfwGetKey(window, GLFW_KEY_1);
    int forward = glfwGetKey(window, GLFW_KEY_W);
    int elevate = glfwGetKey(window, GLFW_KEY_SPACE);
    int descend = glfwGetKey(window, GLFW_KEY_S);
    int left  = glfwGetKey(window,GLFW_KEY_A);
    int right = glfwGetKey(window,GLFW_KEY_D);
    int roll_clock = glfwGetKey(window,GLFW_KEY_Q);
    int roll_counterclock = glfwGetKey(window, GLFW_KEY_E);

    if (top_view) 
        view_type = 1;
    else if(follow_view)
        view_type = 2;
    else if(tower_view)
        view_type = 3;
    else if(front_view)
        view_type = 4;
    else if(heli_view)
        view_type = 5;
    if(forward) {
        fighter.speed += 0.03;
        forward_press = 1;
    }
    if(elevate)
        fighter.pitch_angle += 0.8;
    if(descend)
        fighter.pitch_angle -= 0.8;
    if(left)
        fighter.yaw_angle += 0.8;
    if(right)
        fighter.yaw_angle -= 0.8;    
    if(roll_clock)
        fighter.roll_angle += 0.8;
    if(roll_counterclock)
        fighter.roll_angle -= 0.8;
}

void tick_elements() {
    for( int i=0; i < missiles.size(); i++)
        missiles[i].tick();
    if(fighter.fuel <= 0)
        fighter.position.y -= 1.0f/10.0f;
    if( movement == true){
        fighter.tick();
        if(forward_press == 0 && fighter.speed > 0)
            fighter.speed -= 0.01;
        if ( view_type == 3 ){
            camera_x = fighter.position.x - 30;
            camera_y = fighter.position.y + 70;
            camera_z = fighter.position.z;
            target_x = fighter.position.x;
            target_y = fighter.position.y;
            target_z = fighter.position.z;
            up_z = 0;
        }
        else if( view_type == 2){
            camera_x = fighter.position.x - 35*sin(fighter.yaw_angle*M_PI / 180.0f);
            camera_y = fighter.position.y + 5;
            camera_z = fighter.position.z - 35*cos(fighter.yaw_angle * M_PI / 180.0f);
            target_x = fighter.position.x;
            target_y = fighter.position.y;
            target_z = fighter.position.z;
            up_z = 0;
        }else if( view_type == 1){
            camera_x = fighter.position.x;
            camera_y = fighter.position.y + 40;
            camera_z = fighter.position.z;
            target_x = fighter.position.x;
            target_y = fighter.position.y;
            target_z = fighter.position.z;
            up_z =1;
        }
        else if( view_type == 4 ){
            camera_x = fighter.position.x;
            camera_y = fighter.position.y;
            camera_z = fighter.position.z + 2;
            target_x = camera_x;
            target_y = camera_y;
            target_z = camera_z + 1;
            up_z = 0;
        }
        else if( view_type == 5 ) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        camera_x = fighter.position.x-35*sin(heli_rotation_x*M_PI/180.0f)*cos(heli_rotation_y*M_PI/180.0f);
        camera_y = fighter.position.y + 55*sin(heli_rotation_y*M_PI/180.0f);
        camera_z = fighter.position.z-35*cos(heli_rotation_x*M_PI/180.0f)*cos(heli_rotation_y*M_PI/180.0f);

        up_x = 0;
        up_y = 1;
        up_z = 0;

        target_x = fighter.position.x;
        target_y = fighter.position.y;
        target_z = fighter.position.z;

        double x, y;
        glfwGetCursorPos(window, &x, &y);
        glfwSetCursorPos(window, 350, 350);

        heli_rotation_x += (x - 350);
        heli_rotation_y += (y - 350);
            up_z =0;
        }
    }

    for(int i=0;i<60;i++)
    {
        if(detect_collision(fighter.bounding_box(),rings[i].bounding_box()) && ring_spawn[i]==1)
        {   
            ring_spawn[i] = 0;
            point += 10;
        }
    }    
    counter+=1;
    if(counter%60==0)
    {
        new_fire = Fire(cannons[6].position.x,cannons[6].position.y,cannons[6].position.z);
        new_fire.x_vec = fighter.position.x - cannons[6].position.x;
        new_fire.y_vec = fighter.position.y - cannons[6].position.y;
        new_fire.z_vec = fighter.position.z - cannons[6].position.z;
        fires.push_back(new_fire);
        // printf("spawn %d\n", fires.size());
        counter =0;
    }

    for(int i=0; i<fires.size();i++) {
        printf("xmoveinitial:%f\n", fires[i].x_vec);
        fires[i].tick();
    }
        
    for(int i=0; i< 30; i++)
    {
        if(detect_collision(fighter.bounding_box(),volcanoes[i].bounding_box()))
            quit(window);
    }
     for(int i=0; i< 10; i++)
    {
        if(detect_collision(fuelup[i].bounding_box(),fighter.bounding_box()) && fuel_spawn[i]==1)
           {
               fuel_spawn[i] = 0;
               fighter.fuel += 100;
           } 
            
    }   

    if(fighter.position.y <= sea.position.y)
        movement = false;
    
    for( int i=0; i<bombs.size(); i++){
        for(int j=0 ; j<100;j++){
            if(detect_collision(cannons[j].bounding_box(),bombs[i].bounding_box()) && cannon_spawn[j]==1)
            {
                cannon_spawn[j]=0;
                point += 5;
            }
        }   
    }

    for( int i=0; i<missiles.size(); i++){
        for(int j=0 ; j<30;j++){
            if(detect_collision(parachutes[j].bounding_box(),missiles[i].bounding_box()) && parachute_spawn[j]==1)
            {
                parachute_spawn[j]=0;
                point += 5;
            }
        }   
    }

    for( int i=0; i<bombs.size(); i++){
        if(bombs[i].position.y >= sea.position.y)
            bombs[i].tick();
        else 
            bombs.erase(bombs.begin() + i );
    }

    compass.tick(-fighter.yaw_angle);

}


void mapping()
{
    for(int i=0 ;i< 100; i++){
        float x = (rand() % (2*500)) - 500;
        float z = (rand() % (700)) - 500;
        rings[i] = Ring(x,0,z);
         ring_spawn[i] = 1;
        if(i%2==0)
        {
            lands[i] = Land(x+5,-39.8,z+50);
            cannons[i] = Cannon(x+5, -39.7,z+50);
            cannon_spawn[i] =1;
        }
    }

    for( int i=0; i< 30; i++)
    {
        float x1 = (rand() % (2*500)) - 500;
        float z1 = (rand() % (700)) - 500;
        volcanoes[i] = Volcano(x1, -39.8, z1);
        parachutes[i] = Parachute( x1 -3, 0, z1+2);
        parachute_spawn[i]= 1;
    }
    for(int i=0;i<10;i++)
    {
        float x2 = (rand() % (2*500)) - 600;
        float z2 = (rand() % (700)) - 400;
        fuelup[i] = Fuel(x2,0,z2);
        fuel_spawn[i]=1;
    }
}
/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    mapping();
    fighter = Fighter(0, 10 , 0);
    sea     = Sea(-500, -40, -500);
    //parachute    = Parachute(0, 10 , 20);
    //olcano = Volcano(-3,-39.8,250);

    life[2] = Seven(2, -3.5, 0);
    life[1] = Seven(2.5, -3.5, 0);
    life[0] = Seven(3, -3.5, 0);
    
    points[2] = Seven(2, -3, 0);
    points[1] = Seven(2.5, -3, 0);
    points[0] = Seven(3, -3, 0);

    fuel[2] = Seven(2, -2.5, 0);
    fuel[1] = Seven(2.5, -2.5, 0);
    fuel[0] = Seven(3, -2.5, 0);

    compass = Compass(0, 3, 0, camera_rotation_angle);
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 700;
    int height = 700;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x)*abs(a.x - b.x) + abs(a.y - b.y)*abs(a.y - b.y) + abs(a.z - b.z)*abs(a.z - b.z) 
    < (a.radius + b.radius)*(a.radius+b.radius));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::perspective(glm::radians(15.0f), 1.0f/1.0f, 0.1f, 500.0f);
    Dash.projection = glm::ortho(left, right, bottom, top, 1.0f, 500.0f);
}
