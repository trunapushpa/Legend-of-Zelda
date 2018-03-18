#include "main.h"
#include "timer.h"
#include "water.h"
#include "boat.h"
#include "rock.h"
#include "sail.h"
#include "arrow.h"
#include "barrel.h"
#include "fireball.h"
#include "monster.h"
#include "health.h"
#include "boss.h"
#include "boosterbox.h"
#include "island.h"
#include "man.h"
#include "treasure.h"

using namespace std;

GLMatrices Matrices;
GLuint programID;
GLFWwindow *window;
CVectors CamVectors;

enum cam_view {
    FOLLOW, TOP, TOWER, BOAT, HELICOPTER
} camView;

/**************************
* Customizable functions *
**************************/

bool drag = false, cannonR = false;
double cxpos, pxpos, cypos, pypos;

float randomfInRange(float LO, float HI) {
    return LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
}

Water water;
Boat boat;
Rock rock[1000];
Barrel barrel[200];
Sail sail;
Arrow wind_arrow;
Fireball fireball, booster;
Monster monster[50];
Health health[50];
Boss boss[50];
Boosterbox boosterbox;
Island island;
Man man;
Treasure treasure;

void dispScore() {
    string e = "Legend of Zelda \t|\t Score : ";
    string f = "\t|\t Health: ";
    std::string s = std::to_string(boat.points);
    std::string g = std::to_string(boat.health);
    s = e + s + f + g;
    glfwSetWindowTitle(window, const_cast<char *>(s.c_str()));
}

Mix_Music *pops;
Mix_Music *hurts;
Mix_Music *jumps;
Mix_Music *coins;

float wind_angle = 0.0f;
float wind_mag = 0.01f;

int window_width = 1366;
int window_height = 768;
long long int camTime = 0;
int monsterKillCount = 0, bsct = 0;
bool linked = false;
long long int windct = 60 * 5, lastHitTime = 0, boosterct = -1, linkct = -5;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
glm::vec3 helcamEye = glm::vec3(0, 50.0f, -15.0f);
glm::vec3 helcamTarget = glm::vec3(0, 1.0f, 0.0f);

Timer t60(1.0 / 45);

void hurt() {
    if (hurts) {
        // Start Playback
        if (Mix_PlayMusic(hurts, 1) != 0) {
            std::cerr << "Mix_PlayMusic ERROR: " << Mix_GetError() << std::endl;
        }
    } else {
        std::cerr << "Mix_LoadMuS ERROR: " << Mix_GetError() << std::endl;
    }
}

void coin() {
    if (coins) {
        // Start Playback
        if (Mix_PlayMusic(coins, 1) != 0) {
            std::cerr << "Mix_PlayMusic ERROR: " << Mix_GetError() << std::endl;
        }
    } else {
        std::cerr << "Mix_LoadMuS ERROR: " << Mix_GetError() << std::endl;
    }
}


void jump() {
    return;
    if (jumps) {
        // Start Playback
        if (Mix_PlayMusic(jumps, 1) != 0) {
            std::cerr << "Mix_PlayMusic ERROR: " << Mix_GetError() << std::endl;
        }
    } else {
        std::cerr << "Mix_LoadMuS ERROR: " << Mix_GetError() << std::endl;
    }
}

void pop() {
    if (pops) {
        // Start Playback
        if (Mix_PlayMusic(pops, 1) != 0) {
            std::cerr << "Mix_PlayMusic ERROR: " << Mix_GetError() << std::endl;
        }
    } else {
        std::cerr << "Mix_LoadMuS ERROR: " << Mix_GetError() << std::endl;
    }
}

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram(programID);

    if (camView == FOLLOW) {
        if (!linked) {
            CamVectors.eye = boat.tcam;
            CamVectors.target = boat.position;
            CamVectors.target.x += 15.0f * sin(boat.rotation * M_PI / 180.0f);
            CamVectors.target.z += 15.0f * cos(boat.rotation * M_PI / 180.0f);
            CamVectors.target.y = 0.0f;
            CamVectors.up = glm::vec3(0, 1, 0);
        }
        else{
            CamVectors.eye = man.tcam;
            CamVectors.target = man.position;
            CamVectors.target.x += 15.0f * sin(man.rotation * M_PI / 180.0f);
            CamVectors.target.z += 15.0f * cos(man.rotation * M_PI / 180.0f);
            CamVectors.target.y = 0.0f;
            CamVectors.up = glm::vec3(0, 1, 0);
        }
    } else if (camView == TOP) {
        if (!linked) {
            CamVectors.eye = boat.position;
            CamVectors.eye.y = 50;
            CamVectors.target = boat.position;
            CamVectors.target.z -= 2.0f;
            CamVectors.target.y = 0.0f;
            CamVectors.up = glm::vec3(0, -1, 0);
        }
        else{
            CamVectors.eye = man.position;
            CamVectors.eye.y = 50;
            CamVectors.target = man.position;
            CamVectors.target.z -= 2.0f;
            CamVectors.target.y = 0.0f;
            CamVectors.up = glm::vec3(0, -1, 0);
        }
    } else if (camView == TOWER) {
        CamVectors.eye.z = -5;
        CamVectors.eye.x = 10;
        CamVectors.eye.y = 7;
        CamVectors.target = boat.position;
        CamVectors.target.y = 0.0f;
        CamVectors.up = glm::vec3(0, 1, 0);
    } else if (camView == BOAT) {
        CamVectors.eye = boat.hcam;
        CamVectors.target = boat.position;
        CamVectors.target.x += 150.0f * sin(boat.rotation * M_PI / 180.0f);
        CamVectors.target.z += 150.0f * cos(boat.rotation * M_PI / 180.0f);
        CamVectors.target.y = 0.0f;
        CamVectors.up = glm::vec3(0, 1, 0);
    } else if (camView == HELICOPTER) {
        CamVectors.eye = helcamEye;
        CamVectors.target = helcamTarget;
        CamVectors.up = glm::vec3(0, 1, 0);
    }

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt(CamVectors.eye, CamVectors.target, CamVectors.up); // Rotating Camera for 3D
//    glm::mat4 rotate    = glm::rotate((float) (-boat.rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.view = Matrices.view;
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
    water.draw(VP, boat);
    for (int i = 0; i < 1000; ++i) {
        rock[i].draw(VP);
    }
    for (int i = 0; i < 200; ++i) {
        barrel[i].draw(VP);
    }
    for (int i = 0; i < 50; ++i) {
        monster[i].draw(VP);
        if (health[i].position.y >= 0.0f)
            health[i].draw(VP);
        if (boss[i].position.y >= 0.0f)
            boss[i].draw(VP);
    }
    boat.draw(VP);
    sail.draw(VP, wind_angle, boat.rotation);
    glm::vec3 arrow_pos = boat.position;
    arrow_pos.x -= 1.7f * sin(boat.rotation * M_PI / 180.0f);
    arrow_pos.y = 0.2f;
    arrow_pos.z -= 1.7f * cos(boat.rotation * M_PI / 180.0f);
    wind_arrow.draw(VP, wind_angle, arrow_pos);
    fireball.draw(VP);
    if (boosterct >= 0)
        booster.draw(VP);
    boosterbox.draw(VP);
    island.draw(VP);
    // TODO: uncomment this line
    if (linked)
        man.draw(VP);
    treasure.draw(VP);
//    ball2.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int front = glfwGetKey(window, GLFW_KEY_UP);
    int back = glfwGetKey(window, GLFW_KEY_DOWN);
    int left = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int jmp = glfwGetKey(window, GLFW_KEY_SPACE);
    int cam_change = glfwGetKey(window, GLFW_KEY_C);
    int left_cannon = glfwGetKey(window, GLFW_KEY_A);
    int right_cannon = glfwGetKey(window, GLFW_KEY_D);
    int up_cannon = glfwGetKey(window, GLFW_KEY_W);
    int down_cannon = glfwGetKey(window, GLFW_KEY_S);
    int shoot = glfwGetKey(window, GLFW_KEY_F);

    double deltax, deltay;

    glfwGetCursorPos(window, &cxpos, &cypos);
//    cout << cxpos << " " << cypos << endl;
    if (camView == HELICOPTER && drag) {
        float dragx = ((float) cxpos - (float) pxpos) / 10;
        float dragy = ((float) cypos - (float) pypos) / 10;

        glm::vec3 delta = helcamTarget - helcamEye;
        glm::vec3 l;
        l.x += delta.x / sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
        l.y += delta.y / sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
        l.z += delta.z / sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);

        float coss = l.z / sqrt(l.x * l.x + l.z * l.z);
        float sinn = l.x / sqrt(l.x * l.x + l.z * l.z);

        helcamTarget.x += dragy * sinn;
        helcamTarget.z += dragy * coss;

        helcamTarget.x += dragx * coss;
        helcamTarget.z -= dragx * sinn;
    }


    // TODO: Comment this line if use right clicksss
    cannonR = true;

    if (cannonR) {
        int w_width, w_height;
        glfwGetWindowSize(window, &w_width, &w_height);
        boat.cannon_roty = ((float) (w_height - cypos)) * 90.0f / (w_height);
        boat.cannon_rotz = ((float) (w_width / 2 - cxpos)) * 180.0f / (w_width);
    }

    pxpos = cxpos;
    pypos = cypos;

    if (front || up_cannon) {
        if (!linked) {
            if (boosterct >= 0 && boat.speed < 0.6f)
                boat.speed = 0.6f;
            else if (boat.speed < 0.3f)
                boat.speed = 0.3f;
        } else {
            man.set_position(man.position.x + ((float) (0.2) * (float) sin(man.rotation * M_PI / 180.0f)), man.position.y,
                             man.position.z + ((float) (0.2) * (float) cos(man.rotation * M_PI / 180.0f)));
        }
    }
    if (back || down_cannon) {
        if (!linked) {
            boat.speed = 0;
        }
    }
    if (left || left_cannon) {
        if (!linked) {
            boat.rotate(1.5f);
            man.rotate(1.5f);
        }
        else{
            man.rotate(1.5f);
        }
//        boat.set_position(boat.position.x+0.1f,boat.position.y,boat.position.z);
    }
    if (right || right_cannon) {
        if (!linked) {
            boat.rotate(-1.5f);
            man.rotate(-1.5f);
        }
        else{
            man.rotate(-1.5f);
        }
//        boat.set_position(boat.position.x-0.1f,boat.position.y,boat.position.z);
    }
    // TODO: SET CANNON ROTATION WITH KEYBOARD IF NEEDED
//    if (left_cannon) {
//        boat.cannon_rotz++;
//    }
//    if (right_cannon) {
//        boat.cannon_rotz--;
//    }
//    if (up_cannon) {
//        boat.cannon_roty++;
//    }
//    if (down_cannon) {
//        boat.cannon_roty--;
//    }
    if (jmp) {
        if (!linked) {
            if ((boat.position.y) <= 0.57f) {
                jump();
                boat.speedy = 0.23f;
            }
        }
    }
    if (shoot || (drag && cannonR)) {
        if (fireball.position.y <= 0 && !linked) {
            pop();
            fireball.position = boat.position;
            fireball.position.y += 1.65f * sin(boat.cannon_roty * M_PI / 180.0f);
            fireball.position.x += 1.65f * cos(boat.cannon_roty * M_PI / 180.0f) *
                                   sin((boat.rotation + boat.cannon_rotz) * M_PI / 180.0f);
            fireball.position.z += 1.65f * cos(boat.cannon_roty * M_PI / 180.0f) *
                                   cos((boat.rotation + boat.cannon_rotz) * M_PI / 180.0f);

            fireball.speedy = 0.7f * sin(boat.cannon_roty * M_PI / 180.0f);
            fireball.speedx = 0.7f * cos(boat.cannon_roty * M_PI / 180.0f) *
                              sin((boat.rotation + boat.cannon_rotz) * M_PI / 180.0f) +
                              boat.speed * sin(boat.rotation * M_PI / 180.0f);
            fireball.speedz = 0.7f * cos(boat.cannon_roty * M_PI / 180.0f) *
                              cos((boat.rotation + boat.cannon_rotz) * M_PI / 180.0f) +
                              boat.speed * cos(boat.rotation * M_PI / 180.0f);
        }
    }
    if (cam_change && camTime <= 0) {
        camView = (cam_view) ((1 + camView) % (5));
        camTime = 20;
        printf("%d\n", camView);
    }
}

void tick_elements() {
    if (boat.position.x > 350.0f && boat.position.z > 350.0f) {
        windct = 750;
//        cout << "Hell\n";
        wind_angle = -90.0f - 45.0f;
    } else if (boat.position.x < -350.0f && boat.position.z < -350.0f) {
        windct = 750;
//        cout << "Hell2\n";
        wind_angle = 45.0f;
    } else if (boat.position.x > 350.0f && boat.position.z < -350.0f) {
        windct = 750;
//        cout << "Hell3\n";
        wind_angle = -45.0f;
    } else if (boat.position.x < -350.0f && boat.position.z > 350.0f) {
        windct = 750;
//        cout << "Hell4\n";
        wind_angle = 90.0f + 45.0f;
    } else if (boat.position.x > 350.0f) {
        windct = 750;
//        cout << "Hell5\n";
        wind_angle = -90.0f;
    } else if (boat.position.x < -350.0f) {
        windct = 750;
//        cout << "Hell6\n";
        wind_angle = 90.0f;
    } else if (boat.position.z > 350.0f) {
        windct = 750;
//        cout << "Hell7\n";
        wind_angle = 180.0f;
    } else if (boat.position.z < -350.0f) {
        windct = 750;
//        cout << "Hell8\n";
        wind_angle = 0.0f;
    } else {
        windct--;
        if (windct <= 0) {
            windct = 750;
            wind_angle = -179.5f + (rand()) / ((float) (RAND_MAX / (179.5f + 179.5f)));
        }
    }
    for (int i = 0; i < 1000; ++i) {
        if (abs(boat.position.x - rock[i].position.x) < boat.length &&
            abs(boat.position.z - rock[i].position.z) < boat.length && boat.position.y < 0.9f) {
            boat.health--;
            hurt();
            if (boat.health <= 0)
                exit(0);
            rock[i].set_position(randomfInRange(-350.0f, 350.0f), 0.0f, randomfInRange(-350.0f, 350.0f));
            dispScore();
        }
    }
    for (int i = 0; i < 200; ++i) {
        barrel[i].tick();
        if (abs(boat.position.x - barrel[i].position.x) < boat.length &&
            abs(boat.position.z - barrel[i].position.z) < boat.length && boat.position.y > 0.8f) {
            if (barrel[i].color == 2)
                boat.points += 50;
            else if (barrel[i].color == 1)
                boat.points += 40;
            else
                boat.points += 30;
            coin();
            dispScore();
            barrel[i].set_position(randomfInRange(-350.0f, 350.0f), 0.0f, randomfInRange(-350.0f, 350.0f));
        }
    }

    if (abs(boat.position.x - boosterbox.position.x) < (boat.length / 2 + 1.5f) &&
        abs(boat.position.z - boosterbox.position.z) < (boat.length / 2 + 1.5f) &&
        abs(boat.position.y - boosterbox.position.y) < (boat.height / 2 + 1.5f)) {
        boosterbox.position.x = 10000.0f;
        boosterbox.position.z = 10000.0f;
        boosterbox.position.y = -10.0f;
        boosterct = 60 * 10;
    }

    for (int i = 0; i < 50; ++i) {

        if (abs(boss[i].position.x - fireball.position.x) < 5.0f &&
            abs(boss[i].position.z - fireball.position.z) < 5.0f &&
            abs(boss[i].position.y - fireball.position.y) < 13.5 && fireball.position.y > 0.0f && lastHitTime <= 0) {
            lastHitTime = 30;
            fireball.position.x = -10.0f;
            fireball.position.y = -10.0f;
            fireball.position.z = -10.0f;
            boss[i].health--;
//            pop();
            boat.points += 50;
            if (boss[i].health <= 0) {
                boat.points += 500;
                boosterbox = Boosterbox(boss[i].position.x, 1.5f, boss[i].position.z);
                boss[i] = Boss(10000.0f, -40.0f, 10000.0f);
            }
            coin();
            dispScore();
        }

        if (abs(monster[i].position.x - fireball.position.x) < 2.0f &&
            abs(monster[i].position.z - fireball.position.z) < 2.0f &&
            abs(monster[i].position.y - fireball.position.y) < 4.5) {
            fireball.position.x = -10.0f;
            fireball.position.y = -10.0f;
            fireball.position.z = -10.0f;
//            lastHitTime = 60;
            monsterKillCount++;
//            pop();
            boat.points += 200;
            if (monsterKillCount == 5) {
                monsterKillCount = 0;
                boss[(bsct) % 50].set_position(monster[i].position.x, monster[i].position.y, monster[i].position.z);
                bsct++;
            } else {
                health[i].position = monster[i].position;
            }
            float x = randomfInRange(-350.0f, 350.0f);
            float z = randomfInRange(-350.0f, 350.0f);
            monster[i] = Monster(x, 0.0f, z);
            dispScore();
            coin();
        }
        if (abs(boat.position.x - monster[i].position.x) < (boat.length / 2 + 1.0f) &&
            abs(boat.position.z - monster[i].position.z) < (boat.length / 2 + 1.0f)) {
            hurt();
            float x = randomfInRange(-350.0f, 350.0f);
            float z = randomfInRange(-350.0f, 350.0f);
            monster[i] = Monster(x, 0.0f, z);
            boat.health--;
            if (boat.health <= 0)
                exit(0);
            dispScore();
        }
        if (abs(boat.position.x - health[i].position.x) < (boat.length / 2 + 1.0f) &&
            abs(boat.position.z - health[i].position.z) < (boat.length / 2 + 1.0f)) {
            health[i].position.x = 10000.0f;
            health[i].position.z = 10000.0f;
            health[i].position.y = -10.0f;
            boat.health++;
            dispScore();
        }
    }
    if (!linked) {
        boat.tick(wind_mag, wind_angle);
    }
    sail.tick(boat.position);
    fireball.tick();
    booster.tick();
    if (booster.position.y <= 0.0f) {
        booster.position = boat.position;
        booster.position.y += 1.65f * sin((-4) * M_PI / 180.0f);
        booster.position.x += 1.65f * cos((-4) * M_PI / 180.0f) * sin((boat.rotation + (180.0f)) * M_PI / 180.0f);
        booster.position.z += 1.65f * cos((-4) * M_PI / 180.0f) * cos((boat.rotation + (180.0f)) * M_PI / 180.0f);

        booster.speedy = 0.7f * sin((-4) * M_PI / 180.0f);
        booster.speedx = 0.7f * cos((-4) * M_PI / 180.0f) * sin((boat.rotation + (180.0f)) * M_PI / 180.0f) +
                         boat.speed * sin(boat.rotation * M_PI / 180.0f);
        booster.speedz = 0.7f * cos((-4) * M_PI / 180.0f) * cos((boat.rotation + (180.0f)) * M_PI / 180.0f) +
                         boat.speed * cos(boat.rotation * M_PI / 180.0f);
    }
    if (!linked){
        man.set_position(boat.position.x - 0.5f * (float) sin(boat.rotation * M_PI / 180.0f), boat.position.y,
                         boat.position.z - 0.5f * (float) cos(boat.rotation * M_PI / 180.0f));
    }
    if (abs(boat.position.x - island.position.x) <= (400+boat.length/2) && abs(boat.position.z - island.position.z) <= (400+boat.length/2) && !linked && linkct <=0) {
        linked = true;
        man.position.y = 0.81;
        man.set_rot(boat.rotation);
        linkct = 120;
    }
    if (abs(boat.position.x - man.position.x) <= boat.length/2 && abs(boat.position.z - man.position.z) <= boat.length/2 && linkct<=0 && linked){
        linked = false;
        boat.set_rot(man.rotation);
        linkct = 120;
    }
    if (abs(man.position.x - treasure.position.x) <= 1.1f && abs(man.position.y - treasure.position.y) <= 1.1f && abs(man.position.z - treasure.position.z) <= 1.1f){
        treasure.position.x = 1000.0f;
        treasure.position.y = -1000.0f;
        treasure.position.z = 1000.0f;
        boat.points += 2500;
        dispScore();
        coin();
    }
//    camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    water = Water(0.0f, 0.0f, COLOR_DBLUE);
    boat = Boat(0.0f, 0.0f, 1.5f, 1.4f, 2.0f, 0.6f);
    fireball = Fireball(-3, -3, -10, true);
    booster = Fireball(-10, -10, -10, false);
    boosterbox = Boosterbox(-10, -10.0f, -10);
    island = Island(0, 0, 800);
    treasure = Treasure(0,0,800);
    man = Man(boat.position.x, boat.position.y, boat.position.z);
    for (int i = 0; i < 1000; ++i) {
        float x = randomfInRange(-350.0f, 350.0f);
        float z = randomfInRange(-350.0f, 350.0f);
        while (abs(x) < 5)
            x = randomfInRange(-350.0f, 350.0f);
        while (abs(z) < 5)
            z = randomfInRange(-350.0f, 350.0f);
        rock[i] = Rock(x, 0.0f, z);
    }
    for (int i = 0; i < 200; i++) {
        float x = randomfInRange(-350.0f, 350.0f);
        float z = randomfInRange(-350.0f, 350.0f);
        while (abs(x) < 5)
            x = randomfInRange(-350.0f, 350.0f);
        while (abs(z) < 5)
            z = randomfInRange(-350.0f, 350.0f);
        barrel[i] = Barrel(x, 0.0f, z);
    }
    for (int i = 0; i < 50; i++) {
        float x = randomfInRange(-350.0f, 350.0f);
        float z = randomfInRange(-350.0f, 350.0f);
        while (abs(x) < 10)
            x = randomfInRange(-350.0f, 350.0f);
        while (abs(z) < 10)
            z = randomfInRange(-350.0f, 350.0f);
        monster[i] = Monster(x, 0.0f, z);
        health[i] = Health(10000.0f, -10.0f, 10000.0f);
        boss[i] = Boss(10000.0f, -40.0f, 10000.0f);
    }
    sail = Sail(boat.position.x, boat.position.y, boat.position.z);
    wind_arrow = Arrow(boat.position.x, boat.position.y, boat.position.z);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow(window, width, height);

    // Background color of the scene
    glClearColor(COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0,
                 0.0f); // R, G, B, A
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {

    pid_t ppid_before_fork = getpid();
    pid_t pid = fork();

    if (pid == 0)
    {
        int r = prctl(PR_SET_PDEATHSIG, SIGTERM);
        if (r == -1) { perror(0); exit(1); }
        // test in case the original parent exited just
        // before the prctl() call
        if (getppid() != ppid_before_fork)
            exit(1);

        // Init
        if (SDL_Init(SDL_INIT_AUDIO) != 0) {
            std::cerr << "SDL_Init ERROR: " << SDL_GetError() << std::endl;
            return -1;
        }

        // Open Audio device
        if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048) != 0) {
            std::cerr << "Mix_OpenAudio ERROR: " << Mix_GetError() << std::endl;
            return -1;
        }

        // Set Volume
        Mix_VolumeMusic(20);

        // Open Audio Files
        pops = Mix_LoadMUS("boatrow.mp3");
        if (pops) {
            while(1){
            // Start Playback
            if (Mix_PlayMusic(pops, 1) != 0) {
                std::cerr << "Mix_PlayMusic ERROR: " << Mix_GetError() << std::endl;
            }
                sleep(186);
            }
        } else {
            std::cerr << "Mix_LoadMuS ERROR: " << Mix_GetError() << std::endl;
        }
    }
    else{
        srand((unsigned int) time(0));

        window = initGLFW(window_width, window_height);

        initGL(window, window_width, window_height);

        glfwGetCursorPos(window, &pxpos, &pypos);
        glfwSetScrollCallback(window, scroll_callback);

        // Init
        if (SDL_Init(SDL_INIT_AUDIO) != 0) {
            std::cerr << "SDL_Init ERROR: " << SDL_GetError() << std::endl;
            return -1;
        }

        // Open Audio device
        if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048) != 0) {
            std::cerr << "Mix_OpenAudio ERROR: " << Mix_GetError() << std::endl;
            return -1;
        }

        // Set Volume
        Mix_VolumeMusic(100);

        // Open Audio Files
        pops = Mix_LoadMUS("pop.mp3");
        hurts = Mix_LoadMUS("hurt.mp3");
        jumps = Mix_LoadMUS("jump.mp3");
        coins = Mix_LoadMUS("coin.mp3");

        /* Draw in loop */
        while (!glfwWindowShouldClose(window)) {
            // Process timers

            if (t60.processTick()) {
                // 60 fps
                // OpenGL Draw commands
                camTime--;
                if (lastHitTime > -5)
                    lastHitTime--;
                if (boosterct > -5)
                    boosterct--;
                if (linkct > -5)
                    linkct--;
//            cout << boat.position.y << endl;
                draw();
                // Swap Frame Buffer in double buffering
                glfwSwapBuffers(window);

                tick_elements();
                tick_input(window);
//            cout << boat.rotation << endl;
            }

            // Poll for Keyboard and mouse events
            glfwPollEvents();
        }

        Mix_FreeMusic(pops);
        Mix_FreeMusic(hurts);
        Mix_FreeMusic(jumps);
        Mix_FreeMusic(coins);
        pops = 0;
        hurts = 0;
        jumps = 0;
        coins = 0;
        // End
        Mix_CloseAudio();

        quit(window);
    }
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
//    float top    = screen_center_y + 4 / screen_zoom;
//    float bottom = screen_center_y - 4 / screen_zoom;
//    float left   = screen_center_x - 4 / screen_zoom;
//    float right  = screen_center_x + 4 / screen_zoom;
//    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);

    float near = 1.0f;
    float far = 800.0;
    GLfloat fov = M_PI / 2;
    Matrices.projection = glm::perspective(fov, (GLfloat) window_width / (GLfloat) window_height, near, far);

    // set the projection matrix as perspective
    /* glMatrixMode (GL_PROJECTION);
           glLoadIdentity ();
           gluPerspective (fov, (GLfloat) fbwidth / (GLfloat) fbheight, 0.1, 500.0); */
    // Store the projection matrix in a variable for future use
    // Perspective projection for 3D views
}

void dragS() {
    drag = true;
}

void dragE() {
    drag = false;
}

void cannonS() {
    cannonR = true;
}

void cannonE() {
    cannonR = false;
}

void scroll_call(double x_scroll, double y_scroll) {
    glm::vec3 delta = helcamTarget - helcamEye;
    helcamEye.x += (y_scroll) * delta.x / sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
    helcamEye.y += (y_scroll) * delta.y / sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
    helcamEye.z += (y_scroll) * delta.z / sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
}