#include "main.h"
#include "timer.h"
#include "player.h"
#include "platform.h"
#include "wall.h"
#include "wall_design.h"
#include "coins.h"
#include "enemy1.h"
#include "enemy2.h"
#include "projectiles.h"
#include "propulsion.h"
#include "balloons.h"
#include "enemy3.h"
#include "magnets.h"
#include "semic.h"
#include "dragon.h"
#include "ball.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Player protagonist;
Platform platform;
Wall wall;
WallDesign wall_design1,wall_design2,wall_design3;
vector<Coin> coins;
vector<Enemy1> enemies1;
vector<Enemy2> enemies2;
vector<Balloon> balloons;
vector<Propulsion> propulsions;
vector<Ball> balls;
Coin new_coin;
Enemy1 new_enemy1;
Enemy2 new_enemy2;
Enemy3 enemy3;
Projectile projectile;
Balloon new_balloon;
Propulsion new_propulsion;
Magnet magnet;
Semic semic;
Dragon viserion;
Ball new_ball;
bounding_box_t platform_obj, player_obj;

long long int score =0;
int direction,projectile_appeared = 0, jump_flag = 0, dragon_gone = 0, enemy3_gone = 0, time_var = 0,time_ball= 0, propulsion_time = 0, projectile_activated,level = 1 ;
float camera_x = 0, velocity_x = 7, velocity_y = 0, slow_down =0, dash =0.0;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0, velocity = 0.0, projectile_velocity = 0.0;
float camera_rotation_angle = 0;
time_t current_time1 = time(NULL), current_time2 = time(NULL), current_time3 = time(NULL), current_time4 = time(NULL), current_time5 = time(NULL);
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
    glm::vec3 eye ( camera_x, 0, 1 );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (camera_x, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    wall.draw(VP);
    wall_design1.draw(VP);
    wall_design2.draw(VP);
    wall_design3.draw(VP);
    platform.draw(VP);
    enemy3.draw(VP);
    magnet.draw(VP);
    semic.draw(VP);

    if (projectile_appeared == 1)
        projectile.draw(VP);

    for (int i=0; i< coins.size(); i++)
        coins[i].draw(VP);
    
    for ( int i=0; i< enemies1.size(); i++)
        enemies1[i].draw(VP);

    for ( int i=0; i< enemies2.size(); i++)
         enemies2[i].draw(VP);
    
    for ( int i=0; i< balloons.size(); i++)
        balloons[i].draw(VP);

    for ( int i=0; i< propulsions.size(); i++)
        propulsions[i].draw(VP);
    
    for ( int i=0; i< balls.size(); i++)
        balls[i].draw(VP);
    if(dragon_gone == 0)
        viserion.draw(VP);
    protagonist.draw(VP);
}

bool line_collision(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    float uA = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
    float uB = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));

    // if uA and uB are between 0-1, lines are colliding
    if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) 
        return true;
    else 
        return false;
}

bool enemy1_collision(Enemy1 enemy, Player protagonist)
{
    bool left =   line_collision(protagonist.position.x -0.35,protagonist.position.y-0.15,protagonist.position.x -0.35,protagonist.position.y-0.65,enemy.position.x,enemy.position.y,enemy.position.x+cos((enemy.rotation * M_PI)/ 180.0f),enemy.position.y+sin((enemy.rotation * M_PI)/ 180.0f));
    bool right =  line_collision(protagonist.position.x +0.25,protagonist.position.y-0.15,protagonist.position.x +0.25,protagonist.position.y-0.65,enemy.position.x,enemy.position.y,enemy.position.x+cos((enemy.rotation * M_PI)/ 180.0f),enemy.position.y+sin((enemy.rotation * M_PI)/ 180.0f));
    bool top =    line_collision(protagonist.position.x -0.35,protagonist.position.y-0.15,protagonist.position.x +0.25,protagonist.position.y-0.15,enemy.position.x,enemy.position.y,enemy.position.x+cos((enemy.rotation * M_PI)/ 180.0f),enemy.position.y+sin((enemy.rotation * M_PI)/ 180.0f));
    bool bottom = line_collision(protagonist.position.x -0.35,protagonist.position.y-0.65,protagonist.position.x +0.25,protagonist.position.y-0.65,enemy.position.x,enemy.position.y,enemy.position.x+cos((enemy.rotation * M_PI)/ 180.0f),enemy.position.y+sin((enemy.rotation * M_PI)/ 180.0f));

    if ((left || right || top || bottom)) 
        return true;
    else
        return false;
}

bool enemy2_collision(Enemy2 enemy, Player protagonist)
{
    bool left =   line_collision(protagonist.position.x -0.35,protagonist.position.y-0.15,protagonist.position.x -0.35,protagonist.position.y-0.65,enemy.position.x,enemy.position.y,enemy.position.x+1,enemy.position.y);
    bool right =  line_collision(protagonist.position.x +0.25,protagonist.position.y-0.15,protagonist.position.x +0.25,protagonist.position.y-0.65,enemy.position.x,enemy.position.y,enemy.position.x+1,enemy.position.y);
    bool top =    line_collision(protagonist.position.x -0.35,protagonist.position.y-0.15,protagonist.position.x +0.25,protagonist.position.y-0.15,enemy.position.x,enemy.position.y,enemy.position.x+1,enemy.position.y);
    bool bottom = line_collision(protagonist.position.x -0.35,protagonist.position.y-0.65,protagonist.position.x +0.25,protagonist.position.y-0.65,enemy.position.x,enemy.position.y,enemy.position.x+1,enemy.position.y);

    if ((left || right || top || bottom)) 
        return true;
    else
        return false;
}

// bool balloon_enemy1(Balloon balloon, Enemy1 enemy)
// {
//     bool left =   line_collision(balloon.position.x,balloon.position.y,balloon.position.x+enemy.position.x,enemy.position.y,enemy.position.x+cos((enemy.rotation * M_PI)/ 180.0f),enemy.position.y+sin((enemy.rotation * M_PI)/ 180.0f));
//     bool right =  line_collision(,,enemy.position.x,enemy.position.y,enemy.position.x+cos((enemy.rotation * M_PI)/ 180.0f),enemy.position.y+sin((enemy.rotation * M_PI)/ 180.0f));
//     bool top =    line_collision(,,enemy.position.x,enemy.position.y,enemy.position.x+cos((enemy.rotation * M_PI)/ 180.0f),enemy.position.y+sin((enemy.rotation * M_PI)/ 180.0f));
//     bool bottom = line_collision(,,enemy.position.x,enemy.position.y,enemy.position.x+cos((enemy.rotation * M_PI)/ 180.0f),enemy.position.y+sin((enemy.rotation * M_PI)/ 180.0f));

//     if ((left || right || top || bottom)) 
//         return true;
//     else
//         return false;
// }

void tick_input(GLFWwindow *window) {
    jump_flag = 0;
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up    = glfwGetKey(window, GLFW_KEY_SPACE);
    int shoot = glfwGetKey(window, GLFW_KEY_X);
    if ( left == GLFW_PRESS ) 
        protagonist.tick(-1, false, 0);
    if ( right == GLFW_PRESS ){
        if ( protagonist.position.x >= camera_x + 2)
            camera_x += 1.0/40;
        protagonist.tick(1, false, 0);
    }
    if ( up == GLFW_PRESS ){
        jump_flag = 1;
        if (protagonist.position.y <= 3.75)
            protagonist.tick(1, true, 0);
        if ( propulsion_time % 9 == 0){
            new_propulsion = Propulsion(protagonist.position.x,protagonist.position.y-1, COLOR_FUEL);
            propulsions.push_back(new_propulsion);
            propulsion_time = 0;
        }
    }
    if ( shoot == GLFW_PRESS) {
        if (time_var%9==0){
            new_balloon = Balloon(protagonist.position.x + 0.25, protagonist.position.y - 0.25, COLOR_BALLOON);
            balloons.push_back(new_balloon);
            time_var = 0;
        }
    }
}

void tick_elements() {
    
    char title[100];
    // camera_x += 1.0/60;
    // protagonist.position.x += 1.0/60;
    time_var += 1;
    time_ball += 1;
    propulsion_time += 1;

    //if (protagonist.position.x-semic.position.x)
    if(!(detect_collision(protagonist.bounding_box(),magnet.bounding_box()))){
        if( magnet.position.x >= camera_x && magnet.position.x <= camera_x + 4){
            slow_down += 0.0002;
            if(magnet.position.x >= protagonist.position.x)
                protagonist.position.x += 1.0/100;
            else
                protagonist.position.x -= 1.0/100;
        }          
        else
            slow_down = 0;
    }
    else
    {
        slow_down = 0;
    }
    
    if(viserion.position.x - camera_x <= 5){
        viserion.tick(protagonist.position.y);
        if (time_ball%30==0){
            new_ball = Ball(viserion.position.x - 0.3, protagonist.position.y , COLOR_GREEN);
            balls.push_back(new_ball);
            time_ball = 0;
        }
        for( int i=0; i< balls.size();i++)
        {
            if(detect_collision(protagonist.bounding_box(),balls[i].bounding_box()))
            {
                balls.erase(balls.begin()+i);
                score -= 5;
            }
            else             
                balls[i].tick();
        }
    }

    if ( time(NULL) - current_time7 >= (30+(rand()%10)))
    {
        dragon_gone = 1;
    }



    if (!(protagonist.position.y <= -2.4) && jump_flag == 0)
        velocity += 0.03;
    else 
        velocity = 0.0;

    velocity -= slow_down;
    protagonist.tick(0, false, velocity);

    for( int i=0; i< coins.size(); i++)
    {
        if(coins[i].position.x <= camera_x - 10 || detect_collision(protagonist.bounding_box(),coins[i].bounding_box())){
            coins.erase(coins.begin() + i );
            score += 10;
        } 
    }
    for( int i=0; i< enemies1.size(); i++)
    {
        if(enemies1[i].position.x <= camera_x - 10 || enemy1_collision(enemies1[i],protagonist)){
            enemies1.erase(enemies1.begin() + i);
            score -= 3;
        }
    }
    for( int i=0; i< enemies2.size(); i++)
    {
        if(enemies2[i].position.x <= camera_x - 10 || enemy2_collision(enemies2[i],protagonist))
        {
            protagonist.position.y = -2.4;
            protagonist.position.x = camera_x + 2.3;
            enemies2.erase(enemies2.begin() + i);
            score -= 7;
        }
    }
    for( int i=0 ; i< balloons.size(); i++)
    {
        for( int j=0; j< enemies2.size(); j++)
        {
            if(detect_collision(balloons[i].bounding_box(),enemies2[j].bounding_box())){
                enemies2.erase(enemies2.begin() + j);
                score += 2;
            }
        }

    }

    if (detect_collision(protagonist.bounding_box(),enemy3.bounding_box()))
    {
        enemy3.position.x =  camera_x + 20; 
        enemy3.position.y =  3.3;
        velocity_x = 7;
        velocity_y = 0; 
        score -= 5;
    }

    if( time(NULL) - current_time1 >= (2+(rand()%7)))
    {
        if(coins.size() <= 8)
        {
            new_coin =  Coin(camera_x+(float)(4.6+(rand() / (RAND_MAX/3))), (float)(-0.5+(rand()/ (RAND_MAX/4.2))), COLOR_COINS);
            coins.push_back(new_coin);
            current_time1 = time(NULL);
        }
    }

    if( time(NULL) - current_time2 >= (6+(rand()%3)))
    {
        if(enemies1.size() <= 2)
        {
            new_enemy1 =  Enemy1(camera_x+(float)(4.8+(rand() / (RAND_MAX/5))), (float)(-0.0+(rand()/ (RAND_MAX/4))), COLOR_RED);
            enemies1.push_back(new_enemy1);
            current_time2 = time(NULL);
        }
    }

    if( time(NULL) - current_time3 >= (10+(rand()%8)))
    {
        if(enemies2.size() <= 2)
        {
            new_enemy2 = Enemy2(camera_x+(float)(6 + (rand()%20)),-3,COLOR_RED);
            enemies2.push_back(new_enemy2);
            current_time3 = time(NULL);
        }
    }

    if ( time(NULL) - current_time4 >= (20+(rand()%10)))
    {
        projectile = Projectile(camera_x + 4, 3 ,COLOR_RED);
        projectile_appeared = 1;
        current_time4 = time(NULL); 
    }


    if (!(projectile.position.y <= -2.7)){
        projectile.tick(projectile_velocity);
        projectile_velocity += 0.03;
    }
    else
    {
        projectile_velocity = 0.0;
        projectile.position.x = camera_x -10;
    }

    if(detect_collision(projectile.bounding_box(),protagonist.bounding_box()))
    {
        projectile_activated = 1;
        dash = 10;
        projectile_appeared = 0;
    }
    if(projectile_activated == 1 && dash >= 0)
    {
        protagonist.tick(dash, false, 0);
        camera_x += (dash*1.0)/40;
        dash -= 0.03;
        score += 1;
    }
    else
        dash = 0.0;
    

    for ( int i=0 ; i< enemies2.size(); i++)
    {
        if( enemies2[i].position.y <= -2.8)
            enemies2[i].direction = 1;
        if (enemies2[i].position.y >= 4)
            enemies2[i].direction = -1;
        enemies2[i].tick();
    }
    for ( int i=0 ; i< balloons.size(); i++)
    {
        if(!(balloons[i].position.y <= -2.7)){
            balloons[i].tick();
            balloons[i].velocity += 0.03; 
        }
        else{
            balloons[i].position.x = camera_x - 10;
            balloons[i].velocity = 0.0;
        }
    }
    for ( int i=0 ; i< propulsions.size(); i++)
    {
        if(!(projectile.position.y <= -3))
            propulsions[i].tick();
        else
            propulsions[i].position.x = camera_x - 10;
    }
    if (!(enemy3.position.y <= -2.7))
    {
        enemy3.tick(velocity_x, velocity_y);
        velocity_x -= 0.03;
        velocity_y -= 0.008;
    }
    else
    {    
        enemy3.position.x =  camera_x + 20; 
        enemy3.position.y =  3.3;
        velocity_x = 7;
        velocity_y = 0;
    }

    if(magnet.position.x <= camera_x - 10){
        magnet.position.x = camera_x + 30;
        magnet.position.y = (float)(-0.0+(rand()/ (RAND_MAX/2)));
    }
    if (score > 300)
        level = 2;
    sprintf(title,"LEVEL: %d    SCORE: %lld", level, score);
    glfwSetWindowTitle(window, title);
}   

                                                                                                                                                                                                                                                                                                                                                            
/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    protagonist       = Player(2.3, -2.4, COLOR_PLAYER);
    platform          = Platform(-4, -6, COLOR_PLATFORM);
    wall              = Wall(-4, -3, COLOR_WALL);
    wall_design1      = WallDesign(-4, -1, COLOR_WALLDESIGN);
    wall_design2      = WallDesign(-4, 1, COLOR_WALLDESIGN);
    wall_design3      = WallDesign(-4, 3, COLOR_WALLDESIGN);
    enemy3            = Enemy3(camera_x + 20, 3.3, COLOR_ENEMY3);
    magnet            = Magnet(camera_x + 8,2, COLOR_MAGNET);
    semic             = Semic(2,2, 1, COLOR_RING);
    viserion          = Dragon(30,-1.4,COLOR_DRAGON);
    
    platform_obj.x = platform.position.x;
    platform_obj.y = platform.position.y;
    platform_obj.height = 3.0f; 
    platform_obj.width = 20.0f;

    player_obj.x   = protagonist.position.x;
    player_obj.y   = protagonist.position.y;
    player_obj.height = 0.75f;
    player_obj.width = 0.50f;

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
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
