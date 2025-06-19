#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <unistd.h> // For usleep
#include <cmath>
#include <cstdlib>
#include <fstream>

using namespace std;
using namespace sf;

// Constants for window dimensions and player size
const int resolutionX = 960;
const int resolutionY = 640;
const int boxPixelsX = 32;
const int boxPixelsY = 32;

// Function declarations

//Declaration of draw and move player functions
void drawPlayer(RenderWindow& window, float player_x, float player_y, Sprite& playerSprite, float& player_height);
void movePlayer(float& player_x, float& player_y, Sprite& playerSprite, Clock& player_speed, float& left_boundary, float& right_boundary, const int pollination_num, float pollination_x[], bool pollination_exists[],float& player_move,bool& boss_level);

//Declaration of draw and move bullet functions
void moveBullet(float& bullet_y, bool& bullet_exists, Clock& bulletClock);
void drawBullet(RenderWindow& window, float bullet_x, float bullet_y, Sprite& bulletSprite);

//Declaration of draw and move bees functions
void moveBees(float& bees_x, float& bees_y, Clock& beesClock, bool& direction_right, int& pollination_count, bool bee_alive[], int bee_index, bool pollination_exists_arr[], const int pollination_num, float honey_x[], float honey_y[], const int numBees, bool honey_exist[], int& horizontalShift,int extra_combs,float pollination_x[],bool& first_left ,bool& first_right, float beehives_x[],float beehives_y[],bool beehives_exist[],bool& hive_found,int& hive_count,float red_honey_x[], float red_honey_y[], bool red_honey_exist[], int killerBees,int& max_beehives);
void drawBees(RenderWindow& window, Sprite beesSprites[], float bees_x[], float bees_y[], bool direction_right[], bool bee_alive[], int numBees);
void activateBees(bool bee_alive[], int& remaining_bees_count, Clock& activationClock, int activationIntervals[], int numBees);


//Declaration of collision functions
void collision(float& bees_x, float& bees_y, float& bullet_x, float& bullet_y, bool& bullet_exists, bool& bee_alive, Sound& collisionSound, float honey_x[], float honey_y[], bool honey_exist[], int index, int& score, sf::Text& scoreText, float& bird_x, float& bird_y, const int numBees, sf::Sound& collision_honeySound, int extra_combs,int killerBees,float red_honey_x[], float red_honey_y[], bool red_honey_exist[],float speed_inc_x[],float speed_inc_y[],bool speed_inc_exist[],int& speed_inc_count,Sprite speed_inc_sprite[],float speed_dec_x[],float speed_dec_y[],bool speed_dec_exist[],int& speed_dec_count,Sprite speed_dec_sprite[],float height_inc_x[],float height_inc_y[],bool height_inc_exist[],int& height_inc_count,Sprite height_inc_sprite[],float height_dec_x[],float height_dec_y[],bool height_dec_exist[],int& height_dec_count,Sprite height_dec_sprite[],float beehives_x[],float beehives_y[],bool beehives_exist[],bool& hive_found,int& hive_count,int& max_beehives,bool& boss_level,int& bird_hit); 

void killer_collision(float& killerBees_x, float& killerBees_y, sf::Clock KillerBeesClock[], int& killer_bees_count, sf::Sprite killerBeesSprites[], bool& KillerBee_alive, int killerBees, int killer_activationIntervals[], int& killer_speed,float& bullet_x, float& bullet_y, bool& bullet_exists,sf::Sound& collisionSound,int& score, sf::Text& scoreText,sf::Sound& collision_honeySound,int index,float red_honey_x[], float red_honey_y[], bool red_honey_exist[],bool& boss_level,float speed_inc_x[],float speed_inc_y[],bool speed_inc_exist[],int& speed_inc_count,Sprite speed_inc_sprite[],float speed_dec_x[],float speed_dec_y[],bool speed_dec_exist[],int& speed_dec_count,Sprite speed_dec_sprite[],float height_inc_x[],float height_inc_y[],bool height_inc_exist[],int& height_inc_count,Sprite height_inc_sprite[],float height_dec_x[],float height_dec_y[],bool height_dec_exist[],int& height_dec_count,Sprite height_dec_sprite[]);

void powers_collision(RenderWindow& window,float speed_inc_x[],float speed_inc_y[],bool speed_inc_exist[],int& speed_inc_count,Sprite speed_inc_sprite[],float speed_dec_x[],float speed_dec_y[],bool speed_dec_exist[],int& speed_dec_count,Sprite speed_dec_sprite[],float height_inc_x[],float height_inc_y[],bool height_inc_exist[],int& height_inc_count,Sprite height_inc_sprite[],float height_dec_x[],float height_dec_y[],bool height_dec_exist[],int& height_dec_count,Sprite height_dec_sprite[],sf::Sound& collisionSound,bool& s_inc_activated,bool& s_dec_activated,bool& h_inc_activated,bool& h_dec_activated,float& bullet_x, float& bullet_y, bool& bullet_exists,float&player,float& player_height);


//Declaration of drawing functions
void drawHoney(RenderWindow& window, float honey_x[], float honey_y[], bool honey_exist[], int numBees, Sprite honeySprites[], int extra_combs,Clock& activationClock, int activationIntervals[],float red_honey_x[], float red_honey_y[], bool red_honey_exist[], int killerBees, Sprite red_honeySprites[]);
void drawPollination(RenderWindow& window, bool pollination_exists[], const int pollination_num, Sprite pollinationSprites[], int pollination_count, float pollination_x[], float pollination_y);
void drawBeehives(RenderWindow& window, float beehives_x[], float beehives_y[], bool beehives_exist[], int& hive_count, Sprite beehivesSprites[],int& max_beehives);
void draw_speedInc(RenderWindow& window, float speed_inc_x[], float speed_inc_y[], bool speed_inc_exist[], int& speed_inc_count, Sprite speed_inc_sprite[]);
void draw_speedDec(RenderWindow& window, float speed_dec_x[], float speed_dec_y[], bool speed_dec_exist[], int& speed_dec_count, Sprite speed_dec_sprite[]);
void draw_heightDec(RenderWindow& window, float height_dec_x[], float height_dec_y[], bool height_dec_exist[], int& height_dec_count, Sprite height_dec_sprite[]) ;
void draw_heightInc(RenderWindow& window, float height_inc_x[], float height_inc_y[], bool height_inc_exist[], int& height_inc_count, Sprite height_inc_sprite[]);
void drawFixedPlayer(RenderWindow& window, float fixed_player_x[], float fixed_player_y[], bool fixed_player_exist[], Sprite fixed_playerSprites[], int& count_bullet);



//Declaration of killer Bees functions
void activate_Killerbees(bool KillerBee_alive[], int& killer_bees_count, Clock& activationClock, int killer_activationIntervals[], int& killerBees);
void draw_Killerbees(RenderWindow& window, Sprite killerBeesSprites[], float killerBees_x[], float killerBees_y[], bool direction_right_killer[], bool KillerBee_alive[], int& killerBees);
void move_Killerbees(float& killerBees_x, float& killerBees_y, Clock& KillerBeesClock, bool& direction_right_killer, int& pollination_count, bool KillerBee_alive[], bool pollination_exists[], const int pollination_num, const int killerBees, int& killer_speed, int& bee_index,bool& first_left ,bool& first_right);

//Declaration of applying power function for boss level
void applyPowers(RenderWindow& window,float red_honey_x[], float red_honey_y[], bool red_honey_exist[],float speed_inc_x[],float speed_inc_y[],bool speed_inc_exist[],int& speed_inc_count,Sprite speed_inc_sprite[],float speed_dec_x[],float speed_dec_y[],bool speed_dec_exist[],int& speed_dec_count,Sprite speed_dec_sprite[],float height_inc_x[],float height_inc_y[],bool height_inc_exist[],int& height_inc_count,Sprite height_inc_sprite[],float height_dec_x[],float height_dec_y[],bool height_dec_exist[],int& height_dec_count,Sprite height_dec_sprite[],float& player_move,int& max_comparisons, float& orignal_speed,float& orignal_height,float& player_height,bool& s_inc_activated,bool& s_dec_activated,bool& h_inc_activated,bool& h_dec_activated);

//Declaration of File handling functions
void showHighScore(sf::RenderWindow& window, const std::string& fileName, sf::Font& font);
void addPlayer(const string& filename, string& name , int& score);


//Declaration of draw and move bird and points bird function
void drawBird(RenderWindow& window, float& bird_x, float& bird_y, Sprite& birdSprite, bool& bird_exists);
void moveBird(float& bird_x, float& bird_y, bool& bird_exists, float& target_x, float& target_y, bool& target_reached);
void points_bird(float& target_x, float& target_y, Clock& pauseClock, bool& target_reached) ;


// Level 1 function
void level_1(RenderWindow& window, Sprite beesSprites[], Clock beesClocks[], float bees_x[], float bees_y[], bool direction_right[], bool bee_alive[], int numBees, float bullet_x, float bullet_y, bool& bullet_exists, Sound& collisionSound, float honey_x[], float honey_y[], bool honey_exist[], Sprite honeySprites[], int& score, Text& scoreText, bool pollination_exists[], const int pollination_num, Sprite pollinationSprites[], int& pollination_count, float pollination_x[], float& pollination_y, bool& pollination_direction, float& bird_x, float& bird_y, bool& bird_exists, Clock birdClock, Sprite birdSprite, bool& bird_moved, float& bird_speed, float& target_x, float& target_y, float fixed_player_x[], float fixed_player_y[], bool fixed_player_exist[], Sprite fixed_playerSprites[], int& count_bullet, int& remaining_bees_count, Clock remaining_beesClocks, bool& all_bees_spawned, bool& any_bee_alive, Sound& collision_honeySound, int& horizontalShift, int extra_combs,Clock& activationClock, int activationIntervals[],float red_honey_x[],float red_honey_y[],bool red_honey_exist[], float killerBees_x[], float killerBees_y[], Clock KillerBeesClock[], bool direction_right_killer[], int& killer_bees_count, Sprite killerBeesSprites[], bool KillerBee_alive[], int& killerBees, int killer_activationIntervals[], int& killer_speed, Sprite red_honeySprites[],bool& first_left ,bool& first_right,Clock pauseClock, float beehives_x[],float beehives_y[],bool beehives_exist[],bool& hive_found,int& hive_count,Sprite beehivesSprites[],int& max_beehives,float speed_inc_x[],float speed_inc_y[],bool speed_inc_exist[],int& speed_inc_count,Sprite speed_inc_sprite[],float speed_dec_x[],float speed_dec_y[],bool speed_dec_exist[],int& speed_dec_count,Sprite speed_dec_sprite[],float height_inc_x[],float height_inc_y[],bool height_inc_exist[],int& height_inc_count,Sprite height_inc_sprite[],float height_dec_x[],float height_dec_y[],bool height_dec_exist[],int& height_dec_count,Sprite height_dec_sprite[],bool& target_reached,bool& boss_level,int& bird_hit);


//Level 2 function
void level_2(RenderWindow& window, Sprite beesSprites[], Clock beesClocks[], float bees_x[], float bees_y[], bool direction_right[], bool bee_alive[], int numBees, float bullet_x, float bullet_y, bool& bullet_exists, Sound& collisionSound, float honey_x[], float honey_y[], bool honey_exist[], Sprite honeySprites[], int& score, Text& scoreText, bool pollination_exists[], const int pollination_num, Sprite pollinationSprites[], int& pollination_count, float pollination_x[], float& pollination_y, bool& pollination_direction, float& bird_x, float& bird_y, bool& bird_exists, Clock birdClock, Sprite birdSprite, bool& bird_moved, float& bird_speed, float& target_x, float& target_y, float fixed_player_x[], float fixed_player_y[], bool fixed_player_exist[], Sprite fixed_playerSprites[], int& count_bullet, int& remaining_bees_count, Clock remaining_beesClocks, bool& all_bees_spawned, bool& any_bee_alive, Sound& collision_honeySound, int horizontalShift, int extra_combs, Clock spawnBees, Clock& activationClock, int activationIntervals[], float killerBees_x[], float killerBees_y[], Clock KillerBeesClock[], bool direction_right_killer[], int& killer_bees_count, Sprite killerBeesSprites[], bool KillerBee_alive[], int& killerBees, int killer_activationIntervals[], int& killer_speed,float red_honey_x[],float red_honey_y[],bool red_honey_exist[],Sprite red_honeySprites[],int& level,bool& first_left ,bool& first_right, float beehives_x[],float beehives_y[],bool beehives_exist[],bool& hive_found,int& hive_count,Sprite beehivesSprites[],bool& boss_level,int& max_beehives,float speed_inc_x[],float speed_inc_y[],bool speed_inc_exist[],int& speed_inc_count,Sprite speed_inc_sprite[],float speed_dec_x[],float speed_dec_y[],bool speed_dec_exist[],int& speed_dec_count,Sprite speed_dec_sprite[],float height_inc_x[],float height_inc_y[],bool height_inc_exist[],int& height_inc_count,Sprite height_inc_sprite[],float height_dec_x[],float height_dec_y[],bool height_dec_exist[],int& height_dec_count,Sprite height_dec_sprite[],bool& target_reached,int& bird_hit);


//Level 3 function
void level_3(RenderWindow& window, Sprite beesSprites[], Clock beesClocks[], float bees_x[], float bees_y[], bool direction_right[], bool bee_alive[], int numBees, float bullet_x, float bullet_y, bool& bullet_exists, Sound& collisionSound, float honey_x[], float honey_y[], bool honey_exist[], Sprite honeySprites[], int& score, Text& scoreText, bool pollination_exists[], const int pollination_num, Sprite pollinationSprites[], int& pollination_count, float pollination_x[], float& pollination_y, bool& pollination_direction, float& bird_x, float& bird_y, bool& bird_exists, Clock birdClock, Sprite birdSprite, bool& bird_moved, float& bird_speed, float& target_x, float& target_y, float fixed_player_x[], float fixed_player_y[], bool fixed_player_exist[], Sprite fixed_playerSprites[], int& count_bullet, int& remaining_bees_count, Clock remaining_beesClocks, bool& all_bees_spawned, bool& any_bee_alive, Sound& collision_honeySound, int horizontalShift, int extra_combs, Clock spawnBees, Clock& activationClock, int activationIntervals[], float killerBees_x[], float killerBees_y[], Clock KillerBeesClock[], bool direction_right_killer[], int& killer_bees_count, Sprite killerBeesSprites[], bool KillerBee_alive[], int& killerBees, int killer_activationIntervals[], int& killer_speed,float red_honey_x[],float red_honey_y[],bool red_honey_exist[],Sprite red_honeySprites[],int& level,bool& gameStarted,bool& first_left ,bool& first_right, float beehives_x[],float beehives_y[],bool beehives_exist[],bool& hive_found,int& hive_count,Sprite beehivesSprites[],bool& boss_level,int& max_beehives,float speed_inc_x[],float speed_inc_y[],bool speed_inc_exist[],int& speed_inc_count,Sprite speed_inc_sprite[],float speed_dec_x[],float speed_dec_y[],bool speed_dec_exist[],int& speed_dec_count,Sprite speed_dec_sprite[],float height_inc_x[],float height_inc_y[],bool height_inc_exist[],int& height_inc_count,Sprite height_inc_sprite[],float height_dec_x[],float height_dec_y[],bool height_dec_exist[],int& height_dec_count,Sprite height_dec_sprite[],bool& target_reached,int& bird_hit);




// Boss level / Level 4 function
void bossLevel(RenderWindow& window, Sprite beesSprites[], Clock beesClocks[], float bees_x[], float bees_y[], bool direction_right[], bool bee_alive[], int numBees, float bullet_x, float bullet_y, bool& bullet_exists, Sound& collisionSound, float honey_x[], float honey_y[], bool honey_exist[], Sprite honeySprites[], int& score, Text& scoreText, bool pollination_exists_arr[], const int pollination_num, Sprite pollinationSprites[], int& pollination_count, float pollination_x[], float& pollination_y, bool& pollination_direction, float& bird_x, float& bird_y, bool& bird_exists, Clock birdClock, Sprite birdSprite, bool& bird_moved, float& bird_speed, float& target_x, float& target_y, float fixed_player_x[], float fixed_player_y[], bool fixed_player_exist[], Sprite fixed_playerSprites[], int& count_bullet, int& remaining_bees_count, Clock remaining_beesClocks, bool& all_bees_spawned, bool& any_bee_alive, Sound& collision_honeySound, int horizontalShift, int extra_combs, Clock spawnBees, Clock& activationClock, int activationIntervals[], float killerBees_x[], float killerBees_y[], Clock KillerBeesClock[], bool direction_right_killer[], int& killer_bees_count, Sprite killerBeesSprites[], bool KillerBee_alive[], int& killerBees, int killer_activationIntervals[], int& killer_speed, float red_honey_x[], float red_honey_y[], bool red_honey_exist[], Sprite red_honeySprites[], int& level, bool& gameStarted, bool& first_left, bool& first_right, float beehives_x[], float beehives_y[], bool beehives_exist[], bool& hive_found, int& hive_count, Sprite beehivesSprites[], float& player_move, bool& boss_level, float& left_boundary, float& right_boundary, float& extra_hives, Texture killerTexture, Texture honeyTexture, Texture beesTexture, bool& initialise_boss_level, int& max_beehives, float speed_inc_x[], float speed_inc_y[], bool speed_inc_exist[], int& speed_inc_count, Sprite speed_inc_sprite[], float speed_dec_x[], float speed_dec_y[], bool speed_dec_exist[], int& speed_dec_count, Sprite speed_dec_sprite[], float height_inc_x[], float height_inc_y[], bool height_inc_exist[], int& height_inc_count, Sprite height_inc_sprite[], float height_dec_x[], float height_dec_y[], bool height_dec_exist[], int& height_dec_count, Sprite height_dec_sprite[], int& max_comparisons, float& orignal_speed, float& orignal_height, float& player_height, bool& s_inc_activated, bool& s_dec_activated, bool& h_inc_activated, bool& h_dec_activated,bool& target_reached,int& bird_hit) ;


void enterName(sf::RenderWindow& window, sf::Font& font, std::string& playerName);


// Main Function
int main() {
    srand(time(0));

    // Create the main window
    RenderWindow window(VideoMode(resolutionX, resolutionY), "Buzz Bombers", Style::Close | Style::Titlebar);
    window.setPosition(Vector2i(500, 200));

    // Load and play background music
    Music bgMusic;
    if (!bgMusic.openFromFile("Music/magical_journey.ogg")) {
        cout << "Error: Could not load background music!" << endl;
        return -1;
    }
    bgMusic.play();
    bgMusic.setVolume(50);

    // Load collision sound
    SoundBuffer collisionBuffer;
    if (!collisionBuffer.loadFromFile("Sounds/hit.wav")) {
        cout << "Error: Could not load collision sound!" << endl;
        return -1;
    }
    Sound collisionSound;
    collisionSound.setBuffer(collisionBuffer);
    collisionSound.setVolume(50);

    // Load collision sound for honeycomb
    SoundBuffer collision_honeyBuffer;
    if (!collision_honeyBuffer.loadFromFile("Sounds/fire.wav")) {
        cout << "Error: Could not load collision sound!" << endl;
        return -1;
    }
    Sound collision_honeySound;
    collision_honeySound.setBuffer(collision_honeyBuffer);
    collision_honeySound.setVolume(50);

    // Player Initialization
    float player_x = (resolutionX / 2) - boxPixelsX;
    float player_y = resolutionY - (4 * boxPixelsY);
    float left_boundary = 0;
    float right_boundary = 960;
    Clock playerClock;
    float player_move = 8;
    float orignal_speed = 8;
    float player_height = 1;
    float orignal_height = 1;

    Texture playerTexture;
    Sprite playerSprite;
    if (!playerTexture.loadFromFile("Textures/spray.png")) {
        cout << "Error: Could not load player texture!" << endl;
        return -1;
    }
    playerSprite.setTexture(playerTexture);
    
    

    // Fixed Players Initialization
    Texture fixed_playerTexture;
    if (!fixed_playerTexture.loadFromFile("Textures/spray.png")) {
        cout << "Error: Could not load fixed player texture!" << endl;
        return -1;
    }

    const int numFixedPlayers = 2;
    Sprite fixed_playerSprites[numFixedPlayers];
    bool fixed_player_exist[numFixedPlayers] = {true, true}; // All fixed players exist initially
    float fixed_player_x_arr[numFixedPlayers];
    float fixed_player_y_arr[numFixedPlayers];

    // Initialize Fixed Player Positions and Sprite Setup
    for (int i = 0; i < numFixedPlayers; ++i) {
        fixed_player_x_arr[i] = 50.0f * i; // Set x-coordinate (e.g., 0 and 50)
        fixed_player_y_arr[i] = 575.0f;    // Set y-coordinate
        fixed_playerSprites[i].setTexture(fixed_playerTexture);
        fixed_playerSprites[i].setScale(1, 1); // Set sprite scale
    }

    // Bullet Initialization
    float bullet_x = player_x;
    float bullet_y = player_y;
    bool bullet_exists = false;
    int count_bullet = 0;
    Clock bulletClock;

    Texture bulletTexture;
    Sprite bulletSprite;
    if (!bulletTexture.loadFromFile("Textures/bullet.png")) {
        cout << "Error: Could not load bullet texture!" << endl;
        return -1;
    }
    bulletSprite.setTexture(bulletTexture);
    bulletSprite.setScale(2, 2);

    // Ground Initialization
    RectangleShape groundRectangle(Vector2f(960, 64));
    groundRectangle.setPosition(0, resolutionY - 64);
    groundRectangle.setFillColor(Color::Green);

    // Initial Level and Bees Configuration
    int level = 1;
    int numBees = 20; // Level 1 has 20 bees
    int horizontalShift = 2;
    int extra_combs = 3; // Initial extra honeycombs

    // Bees Initialization
    float bees_x[numBees], bees_y[numBees];
    bool direction_right[numBees];
    Clock beesClocks[numBees];
    Sprite beesSprites[numBees];
    bool bee_alive[numBees];
    int remaining_bees_count = 0; // Initial bees alive
    Clock activationClock;
    int activationIntervals[numBees];
    Clock remaining_beesClocks;
    // declearing following 2 for level 2
    Clock spawnBees;
    int index;
    
    Texture beesTexture;
    if (!beesTexture.loadFromFile("Textures/Regular_bee.png")) {
        cout << "Error: Could not load bees texture!" << endl;
        return -1;
    }

    for (int i = 0; i < numBees; ++i) {
        bees_x[i] = (i % 10) * 100; // Spread bees horizontally
        bees_y[i] = 0;              // Start at top of the screen
        direction_right[i] = (i % 2 == 0); // Alternate direction
        beesSprites[i].setTexture(beesTexture);
        beesSprites[i].setScale(1, 1);
        activationIntervals[i] = (1 + rand() % 3); 
        bee_alive[i] = false; 
    }

    // Honeycomb Setup
    int max_honeycombs = 35;
    float honey_x[max_honeycombs];
    float honey_y[max_honeycombs];
    bool honey_exist[max_honeycombs] = {false};
    Sprite honeySprites[max_honeycombs];

    Texture honeyTexture;
    if (!honeyTexture.loadFromFile("Textures/honeycomb.png")) {
        cout << "Error: Could not load honeycomb texture!" << endl;
        return -1;
    }

    // Initialize all honeySprites
    for (int i = 0; i < max_honeycombs; ++i) {
        honeySprites[i].setTexture(honeyTexture);
        honeySprites[i].setScale(0.7, 0.7); // Adjust scale as needed
    }

    // Randomly place initial honeycombs
    for (int i = 0; i < extra_combs; ++i) {
        honey_x[i] = rand() % resolutionX;
        honey_y[i] = rand() % (resolutionY / 2);
        honey_exist[i] = true; // Mark as active
        window.draw(honeySprites[i]); // Draw initial honeycombs
    }

    // Initialize the score text
    Font font;
    if (!font.loadFromFile("font.ttf")) {
        cout << "Error: Could not load font!" << endl;
        return -1;
    }

    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(60);       // Font size
    scoreText.setFillColor(Color::Black); // Font color
    scoreText.setStyle(Text::Bold);       // Bold font
    scoreText.setString("00000");         // Initial score

    // Position the score text at the bottom-right corner
    scoreText.setPosition(710, 570); // Adjust based on your window resolution

    //Displaying the bullet count
    
    Text bulletText;
    bulletText.setFont(font);
    bulletText.setCharacterSize(80);       // Font size
    bulletText.setFillColor(Color::Black); // Font color
    bulletText.setStyle(Text::Bold);       // Bold font
    bulletText.setPosition(400, 557);



    // Score variable
    int score = 0;

    // Pollination Initialization
    Texture pollinationTexture;
    if (!pollinationTexture.loadFromFile("Textures/obstacles.png")) {
        cout << "Error: Could not load pollination texture!" << endl;
        return -1;
    }

    const int pollination_num = 30; // Number of pollination objects
    int pollination_count = 0;
    bool pollination_exists_arr[pollination_num] = {false};
    Sprite pollinationSprites[pollination_num];
    float pollination_x[pollination_num];
    float pollination_y_fixed = 505.0f; // Fixed y-position for all flowers
    bool pollination_direction; // Currently unused
    bool first_left = true ;
    bool first_right = true;
    
    for (int i = 0; i < pollination_num; ++i) {
        pollination_x[i] = i * 32; // Spread flowers horizontally
        pollinationSprites[i].setTexture(pollinationTexture);
        pollinationSprites[i].setScale(2.5, 2.5);
        pollination_exists_arr[i] = false; // Initially false
    }

    // Hummingbird Initialization
    float bird_x = 0, bird_y = 0;        
    float target_x , target_y;
    bool bird_exists = true;
    float bird_speed = 2;     
    Clock birdClock;
    Clock pauseClock;
    int bird_hit;
    bool bird_moved;
    bool target_reached;
    Texture birdTexture;
    Sprite birdSprite;
    birdSprite.setColor(sf::Color(0, 0, 255)); // Full dark blue tint
    if (!birdTexture.loadFromFile("Textures/bird.png")) {
        cout << "Error: Could not load bird texture!" << endl;
        return -1;
    }
    birdSprite.setTexture(birdTexture);
    birdSprite.setScale(2, 2);
    
    
    //killer Bees Initialization
    int killerBees = 5;
    int length = 20; // so it doesnt give error for level 3
    float killerBees_x[length], killerBees_y[length];
    bool direction_right_killer[length];
    Clock KillerBeesClocks[length];
    Sprite killerBeesSprites[length];
    bool killerBee_alive[length];
    int killer_bees_count = 0; // Initial bees alive
    Clock killer_activationClock;
    int killer_activationIntervals[length];
    int killer_speed = 8;

    Texture killerTexture;
    if (!killerTexture.loadFromFile("Textures/Fast_bee.png")) {
        cout << "Error: Could not load bees texture!" << endl;
        return -1;
    }

    for (int i = 0; i < length; ++i) {
        killerBees_x[i] = (i % 10) * 100; // Spread bees horizontally
        killerBees_y[i] = 0;              // Start at top of the screen
        direction_right_killer[i] = (i % 2 == 0); // Alternate direction
        killerBeesSprites[i].setTexture(killerTexture);
        killerBeesSprites[i].setScale(1, 1);
        killer_activationIntervals[i] = 2 + (rand() % 3); 
        killerBee_alive[i] = false; 
    }
    
    //Initializing arrays for red honey combs
    int max_red_honey = 15;
    float red_honey_x[max_red_honey];
    float red_honey_y[max_red_honey];
    bool red_honey_exist[max_red_honey] = {false};
    Sprite red_honeySprites[max_red_honey];

    Texture red_honeyTexture;
    if (!red_honeyTexture.loadFromFile("Textures/honeycomb_red.png")) {
        cout << "Error: Could not load honeycomb texture!" << endl;
        return -1;
    }

    // Initialize all red honeySprites
    for (int i = 0; i < max_red_honey ; i++) {
        red_honeySprites[i].setTexture(red_honeyTexture);
        red_honeySprites[i].setScale(0.7, 0.7); 
        red_honey_exist[i] = false;

    }
    
    // Initialising beeHives
    Texture beehivesTexture;
    if (!beehivesTexture.loadFromFile("Textures/hive.png")) {
        cout << "Error: Could not load beehive texture!" << endl;
        return -1;
    }
    int max_beehives = 35;
    float beehives_x[max_beehives];
    float beehives_y[max_beehives];
    bool beehives_exist[max_beehives] = {false};
    Sprite beehivesSprites[max_beehives];
    bool hive_found = false; 
    int hive_count = 0 ;
    float extra_hives ;
     
    
    // Initialize all beehives Sprites
    for (int i = 0; i < max_beehives; ++i) {
        beehivesSprites[i].setTexture(beehivesTexture);
        beehivesSprites[i].setScale(1, 1);
        beehives_exist[i] = false;
    }
    
    // Randomly place initial beehives
        beehives_x[0] = rand() % resolutionX;
        beehives_y[0] = rand() % (resolutionY / 2);
        beehives_exist[0] = true; 
        window.draw(beehivesSprites[0]); 
    

    // Game State Flags
    bool any_bee_alive = true; 
    bool all_bees_spawned = false;
    bool is_level_2 = false;
    string name;
    
    
    // Setting up menu of size 4
    const int menu_size = 4;
    string menuItems[menu_size] = {"Start Game", "Boss Level", "High Score", "Exit"};
    Text menuText[menu_size];
    
    // initialising menu items
    for (int i = 0; i < menu_size; i++) 
    {
      menuText[i].setFont(font);
      menuText[i].setString(menuItems[i]);
      menuText[i].setCharacterSize(50);
      menuText[i].setFillColor(Color::White);
      menuText[i].setPosition(300, 200 + i * 60);
    }
    
    int selected_option = 0;
    menuText[selected_option].setFillColor(Color::Red); // Highlight the first option

    bool menu_entered = true;
    bool gameStarted = false;
    bool display_score = false;
    bool name_entered = false;
    bool boss_level = false;
    bool initialise_boss_level = false;
    bool initiate_boss_level = false;

    
    // declearing file name
    string fileName = "Leaderboard.txt";
    
    
    // Declearing variables for boss level increase and decrease speed and height
     
   
    // Increase speed power
    int no_inc_speed = 50;
    float speed_inc_x[no_inc_speed];
    float speed_inc_y[no_inc_speed];
    bool speed_inc_exist[no_inc_speed] = {false};
    int speed_inc_count = 0 ;
    Sprite speed_inc_sprite[no_inc_speed];

    Texture speed_incTexture;
    if (!speed_incTexture.loadFromFile("Sprites/Speed_Inc.png")) {
        cout << "Error: Could not load honeycomb texture!" << endl;
        return -1;
    }

    // Initialize all increase speed power variables
    for (int i = 0; i < no_inc_speed ; i++) {
        speed_inc_sprite[i].setTexture(speed_incTexture);
        speed_inc_sprite[i].setScale(1, 1); 
        speed_inc_exist[i] = false;

    }
    
       
    // Decrease speed power
    int no_dec_speed = 50;
    float speed_dec_x[no_dec_speed];
    float speed_dec_y[no_dec_speed];
    bool speed_dec_exist[no_dec_speed] = {false};
    int speed_dec_count = 0 ;
    Sprite speed_dec_sprite[no_dec_speed];

    Texture speed_decTexture;
    if (!speed_decTexture.loadFromFile("Sprites/Speed_Dec.png")) {
        cout << "Error: Could not load honeycomb texture!" << endl;
        return -1;
    }

    // Initialize all increase speed power variables
    for (int i = 0; i < no_dec_speed ; i++) {
        speed_dec_sprite[i].setTexture(speed_decTexture);
        speed_dec_sprite[i].setScale(1, 1); // Adjust scale as needed
        speed_dec_exist[i] = false;

    }

    
    // Increase Height power
    int no_inc_height = 50;
    float height_inc_x[no_inc_height];
    float height_inc_y[no_inc_height];
    bool height_inc_exist[no_inc_height] = {false};
    int height_inc_count = 0 ;
    Sprite height_inc_sprite[no_inc_height];

    Texture height_incTexture;
    if (!height_incTexture.loadFromFile("Sprites/Height_Inc.png")) {
        cout << "Error: Could not load honeycomb texture!" << endl;
        return -1;
    }

    // Initialize all increase speed power variables
    for (int i = 0; i < no_inc_height ; i++) {
        height_inc_sprite[i].setTexture(height_incTexture);
        height_inc_sprite[i].setScale(1, 1);
        height_inc_exist[i] = false;

    }
    
    // Decrease Height power
    int no_dec_height = 50;
    float height_dec_x[no_dec_height];
    float height_dec_y[no_dec_height];
    bool height_dec_exist[no_dec_height] = {false};
    int height_dec_count = 0 ;
    Sprite height_dec_sprite[no_dec_height];

    Texture height_decTexture;
    if (!height_decTexture.loadFromFile("Sprites/Height_Dec.png")) {
        cout << "Error: Could not load honeycomb texture!" << endl;
        return -1;
    }

    // Initialize all increase speed power variables
    for (int i = 0; i < no_dec_height ; i++) {
        height_dec_sprite[i].setTexture(height_decTexture);
        height_dec_sprite[i].setScale(1, 1); // Adjust scale as needed
        height_dec_exist[i] = false;

    }
    
    //For activating and checking power
    int max_comparisons = 30;
    bool s_inc_activated = false , s_dec_activated = false , h_inc_activated = false , h_dec_activated = false;
    
    
    
    // Printing the level 1 2 3 and main menu graphics so declearing all variables
    sf::Texture level1_texture;
    if (!level1_texture.loadFromFile("Pictures/level1.png")) 
    { 
     cout << "Error: Could not load image" << std::endl;
    }
     Sprite level1_sprite;
     level1_sprite.setTexture(level1_texture);  
     
     // Now according to the size of the orignal image displaying the image
     float textureWidth = 1050.0f;  
     float textureHeight = 700.0f; 
     float windowWidth = 960.0f;   
     float windowHeight = 640.0f;  
     // Calculating the height and width
     float scaleX = windowWidth / textureWidth;
     float scaleY = windowHeight / textureHeight;
     // Apply the scaling
     level1_sprite.setScale(scaleX, scaleY);
     // Create a clock to display the sprite for 10 seconds
     sf::Clock level1_Tclock;
    
    // For level 2
    sf::Texture level2_texture;
    if (!level2_texture.loadFromFile("Pictures/level2.png")) 
    { 
     cout << "Error: Could not load image" << std::endl;
    }
     Sprite level2_sprite;
     level2_sprite.setTexture(level2_texture);  
     level2_sprite.setScale(scaleX, scaleY);
     sf::Clock level2_Tclock; 
    
    // for level 3
    sf::Texture level3_texture;
    if (!level3_texture.loadFromFile("Pictures/level3.png")) 
    { 
     cout << "Error: Could not load image" << std::endl;
    }
     Sprite level3_sprite;
     level3_sprite.setTexture(level3_texture);  
     level3_sprite.setScale(scaleX, scaleY);
     sf::Clock level3_Tclock; 
     
     // for level 4
    sf::Texture level4_texture;
    if (!level4_texture.loadFromFile("Pictures/level4.png")) 
    { 
     cout << "Error: Could not load image" << std::endl;
    }
     Sprite level4_sprite;
     level4_sprite.setTexture(level4_texture);  
     level4_sprite.setScale(scaleX, scaleY);
     sf::Clock level4_Tclock; 
    
  // background of menu
     sf::Texture menuTexture;
    if (!menuTexture.loadFromFile("Pictures/menu.png")) {
        cout << "error"<<endl;
        }
        
    sf::Sprite menuSprite(menuTexture);
    bool ss_displayed = false;
    


 // Main game loop
while (window.isOpen()) {
    // Handle events
    sf::Event e;
    while (window.pollEvent(e)) {
        if (e.type == sf::Event::Closed) {
            window.close(); // Close the window
        }

        if (menu_entered) {
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Up) {
                    menuText[selected_option].setFillColor(sf::Color::Red);
                    selected_option = (selected_option - 1 + menu_size) % menu_size;
                    menuText[selected_option].setFillColor(sf::Color::White);
                } else if (e.key.code == sf::Keyboard::Down) {
                    menuText[selected_option].setFillColor(sf::Color::Red);
                    selected_option = (selected_option + 1) % menu_size;
                    menuText[selected_option].setFillColor(sf::Color::White);
                } else if (e.key.code == sf::Keyboard::Enter) {
                    if (selected_option == 0) {
                        cout << "Starting Game ...\n";
                        menu_entered = false;
                        gameStarted = true; // Set gameStarted to true to enter the game loop
                    } else if (selected_option == 1) {
                        cout << "Starting Boss Level...\n";
                        menu_entered = false;
                        boss_level = true;
                    } else if (selected_option == 2) {
                        cout << "Showing High Score...\n";
                        menu_entered = false;
                        display_score = true;
                    } else if (selected_option == 3) {
                        cout << "Exiting program...\n";
                        window.close(); // Close the window if option 3 is selected
                    }
                }
            }
        }
    }

    
    window.clear();

    // If menu_entered, draw menu background and text
    if (menu_entered) {
        window.draw(menuSprite); // Draw background sprite

        // Draw menu options on top of the background
        for (int i = 0; i < menu_size; i++) {
            window.draw(menuText[i]);
        }

        
        window.display();
    }

    // Displaying the high score screen if user selects high score option
    if (display_score) {
        showHighScore(window, fileName, font);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            menu_entered = true;
            display_score = false;
        }
    }

    // Initiallising things to directly access boss level if user selects the boss level
    if (boss_level && !initiate_boss_level) {
        gameStarted = true;
        level = 4;
        initiate_boss_level = false;
    }
    
    // Game started logic
    if (gameStarted) 
    {
        // Displaying the level 1 starting texture
        while (level1_Tclock.getElapsedTime().asSeconds() < 5 && !boss_level) { 
        window.clear();             
        window.draw(level1_sprite);   
        window.display();            
    
        }
        // asking the user to enter the name in terminal as i was unable to do that in game window
        if(name_entered == false)
         {
         cout << "Enter your name : ";
         cin >> name;
         name_entered = true;
         }    
        // Handle Bullet Firing
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !bullet_exists) {
            bullet_exists = true;
            count_bullet++;
            bullet_x = player_x + (boxPixelsX / 2);
            bullet_y = player_y;
            // handling drawing of fixed players
            if(count_bullet >= 56)
            fixed_player_exist[1] = false;
            if(count_bullet >= 102)
            fixed_player_exist[0] = false;    
        }
        
        //Ending the game if bullet count exceeds 156
        if(count_bullet >= 128)
        level = 5;
        
        
        // Move player based on keyboard input
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            movePlayer(player_x, player_y, playerSprite, playerClock, left_boundary, right_boundary, pollination_num, pollination_x, pollination_exists_arr,player_move,boss_level);
        }
        
        //Making bird inactive if it has faced 3 hits
        if(bird_hit == 3)
        {
         bird_hit = 0;
         bird_exists = false;
         pauseClock.restart();
        }
        //Making bird come back after 15 seconds 
        if(pauseClock.getElapsedTime().asSeconds() > 15)
        {
         bird_exists = true;
        }
       
        
        //Drawing and moving bird
        if (bird_exists) 
        {
         points_bird(target_x, target_y, birdClock, bird_moved);
         moveBird(bird_x, bird_y, bird_exists, target_x, target_y, bird_moved);
        // drawBird(window, bird_x, bird_y, birdSprite, bird_exists);
        }

        // Clear the window and draw the ground
        window.clear();
        window.draw(groundRectangle);

        // Draw the player
        drawPlayer(window, player_x, player_y, playerSprite, player_height);

        // Move and draw bullet if it exists
        if (bullet_exists) {
            moveBullet(bullet_y, bullet_exists, bulletClock);
            drawBullet(window, bullet_x, bullet_y, bulletSprite);
        }
       
        // Executing level 1
        if ((any_bee_alive || !all_bees_spawned) && count_bullet < 158 && level == 1) {
            // Call Level 1 function to handle bee movements and collisions
            level_1(window, beesSprites, beesClocks, bees_x, bees_y, direction_right, bee_alive, numBees, bullet_x, bullet_y, bullet_exists, collisionSound, honey_x, honey_y, honey_exist, honeySprites, score, scoreText, pollination_exists_arr, pollination_num, pollinationSprites, pollination_count, pollination_x, pollination_y_fixed, pollination_direction, bird_x, bird_y, bird_exists, birdClock, birdSprite, bird_moved, bird_speed, target_x, target_y, fixed_player_x_arr, fixed_player_y_arr, fixed_player_exist, fixed_playerSprites, count_bullet, remaining_bees_count, remaining_beesClocks, all_bees_spawned, any_bee_alive, collision_honeySound, horizontalShift, extra_combs,activationClock,activationIntervals,red_honey_x,red_honey_y,red_honey_exist,killerBees_x,killerBees_y,
KillerBeesClocks,direction_right_killer,killer_bees_count,killerBeesSprites,killerBee_alive,killerBees,
killer_activationIntervals,killer_speed,red_honeySprites,first_left,first_right,pauseClock,beehives_x,
beehives_y,beehives_exist,hive_found,hive_count,beehivesSprites, max_beehives,        speed_inc_x,speed_inc_y,speed_inc_exist,speed_inc_count,speed_inc_sprite,speed_dec_x,speed_dec_y, speed_dec_exist,speed_dec_count,speed_dec_sprite,height_inc_x,height_inc_y,height_inc_exist,height_inc_count,
height_inc_sprite,height_dec_x,height_dec_y,height_dec_exist,height_dec_count, height_dec_sprite, target_reached,boss_level,bird_hit);
        
       }  
       // Transition to Level 2 if Level 1 conditions are met
        else if (level == 1) {
            level = 2;
            cout << "Level 1 ended, transitioning to Level 2" << endl;
            
            //Adding beehives points after end of level 
            for(int i = 0 ; i < max_beehives ; i++)
            {
             if(beehives_exist[i])
             {
              if(beehives_y[i] < 64)
              {
               score += 2000; // Adding 2000 score for beehive on top two tier
              }
              else if(beehives_y[i] < 160)
              {
               score += 1600; // Adding 1600 score for beehive on 3 , 4 and 5 tier
              }
              else 
              {
               score += 1000; // Adding 1000 score for beehive on remaining tier
              }
             }
            }
            scoreText.setString(to_string(score));//Setting it to score
            


            // Reset honeycomb existence
            for (int i = 0; i < numBees + 3; ++i) {
                honey_exist[i] = false;
            }

            // Reset bees for Level 2
            for (int i = 0; i < numBees; ++i) {
                bees_x[i] = 0.0f;             // Reset bee X position
                bees_y[i] = 0.0f;             // Reset bee Y position
                direction_right[i] = false;   // Reset direction
                beesClocks[i].restart();      // Reset bee clock
                bee_alive[i] = false;         // Mark bees as inactive
            }
            // Reseting the bullet_count based on the lives the user uses
            if(count_bullet < 56)
            {
             count_bullet = 0 ;
            }
            else if(count_bullet < 112)
            { count_bullet = 56;
            }
            else if(count_bullet < 158)
            {
             count_bullet = 112;
            }
            // Reset pollination for Level 2
            pollination_count = 0; 
            first_left = true;
            first_right = true;

            for (int i = 0; i < pollination_num; ++i) {
              pollination_exists_arr[i] = false; 
              pollinationSprites[i].setPosition(-100, -100); 
             }
             
             bird_exists = true;
            }
       
   
      
        // Drawing fixed players means the lives of the can 
        drawFixedPlayer(window, fixed_player_x_arr, fixed_player_y_arr, fixed_player_exist, fixed_playerSprites, count_bullet);
         
        // Level 2 Initialization
        if (level == 2 && !is_level_2) {
            is_level_2 = true;
            cout << "Level 2 started" << endl;

            // Seting parameters for Level 2
            remaining_bees_count = 0; // Reset remaining_bees_count for Level 2
            numBees = 15; 
            extra_combs = 9;
            horizontalShift = 4;
            any_bee_alive = true; 
            all_bees_spawned = false;

            // Initialize honeycomb for Level 2
            for (int i = 0; i < numBees + extra_combs; ++i) {
                honeySprites[i].setTexture(honeyTexture);
             
            }
            // Randomly place 9 honeycombs initially for Level 2
            for (int i = 0; i < 9; ++i) {
                honey_x[i] = rand() % resolutionX;
                honey_y[i] = rand() % (resolutionY / 2);
                honey_exist[i] = true; 
            }

            // Resetting bees for Level 2
              for (int i = 0; i < numBees; ++i) {
               bees_x[i] = (i % 10) * 100; // Spread bees horizontally
               bees_y[i] = 0;              // Start at top of the screen
               direction_right[i] = (i % 2 == 0); // Alternate direction
               beesSprites[i].setTexture(beesTexture);
               beesSprites[i].setScale(1, 1);
               activationIntervals[i] = (2+rand() % 3); 
               bee_alive[i] = false; 
               
               
            //Resetting boundary of player as it is causing the error in the game 
            left_boundary = 0 ;
            right_boundary = 960; 
        
        // r=Resetting beehives            
        for (int i = 0; i < hive_count; ++i) {
        beehivesSprites[i].setTexture(beehivesTexture);
        beehivesSprites[i].setScale(1, 1); // Adjust scale as needed
        beehives_exist[i] = false;
        
        //Resetting timer so that screenshot can be displayed for 5 seconds
        level2_Tclock.restart();
        
        bird_exists = true;
     }
    }
   }

         
        
        // Level 2 Logic
        if (level == 2 && is_level_2) {
          if (level2_Tclock.getElapsedTime().asSeconds() < 5 && !boss_level) {
        // Show Level 2 screenshot for 5 seconds
        window.clear();               // Clear the window
        window.draw(level2_sprite);   // Draw the screenshot for Level 2
        window.display(); 
        } 
        else
         {
            // Call Level 2 function to handle bee movements and collisions
         level_2(window,beesSprites,beesClocks,bees_x,bees_y,direction_right,bee_alive,numBees,bullet_x,bullet_y,
                bullet_exists,collisionSound,honey_x,honey_y,honey_exist,honeySprites,score,scoreText,
                pollination_exists_arr, pollination_num,pollinationSprites,pollination_count,pollination_x,
                pollination_y_fixed,pollination_direction,bird_x,bird_y,bird_exists,birdClock,birdSprite,bird_moved,
                bird_speed,target_x,target_y,fixed_player_x_arr,fixed_player_y_arr, fixed_player_exist,
                fixed_playerSprites,count_bullet,remaining_bees_count,remaining_beesClocks,all_bees_spawned,
                any_bee_alive,collision_honeySound,horizontalShift,extra_combs,spawnBees,activationClock,
                activationIntervals,killerBees_x,killerBees_y,KillerBeesClocks,direction_right_killer,
                killer_bees_count,killerBeesSprites,killerBee_alive,killerBees,killer_activationIntervals,
                killer_speed,red_honey_x,red_honey_y,red_honey_exist,red_honeySprites,level,first_left, first_right,beehives_x,beehives_y,beehives_exist,hive_found,hive_count,beehivesSprites,boss_level, max_beehives,      speed_inc_x,speed_inc_y,speed_inc_exist,speed_inc_count,speed_inc_sprite,speed_dec_x,speed_dec_y, speed_dec_exist,speed_dec_count,speed_dec_sprite,height_inc_x,height_inc_y,height_inc_exist,height_inc_count,
height_inc_sprite,height_dec_x,height_dec_y,height_dec_exist,height_dec_count, height_dec_sprite,target_reached, bird_hit);

           } 
           }
           
           // initialising variables for level 3 
           if((level == 3)  && (is_level_2))
           { 
             is_level_2 = false;
             cout<<"Level 2 ended"<<endl;
             
            //Adding beehives points after end of level 
            for(int i = 0 ; i < max_beehives ; i++)
            {
             if(beehives_exist[i])
             {
              if(beehives_y[i] < 64)
              {
               score += 2000; // Adding 2000 score for beehive on top two tier
              }
              else if(beehives_y[i] < 160)
              {
               score += 1600; // Adding 1600 score for beehive on 3 , 4 and 5 tier
              }
              else 
              {
               score += 1000; // Adding 1000 score for beehive on remaining tier
              }
             }
            }
            scoreText.setString(to_string(score));//Setting it to score 
             for (int i = 0; i < numBees +  extra_combs; ++i) {
                honey_exist[i] = false;
            }
             for (int i = 0; i < killerBees; ++i) {
                red_honey_exist[i] = false;
            }
            // Resetting bees for Level 3
            for (int i = 0; i < numBees; ++i) {
                bees_x[i] = 0.0f;            
                bees_y[i] = 0.0f;            
                direction_right[i] = false;  
                beesClocks[i].restart();     
                bee_alive[i] = false;        
            }
            // Resetting killer bees for Level 3
            for (int i = 0; i < killerBees; ++i) {
                killerBees_x[i] = 0.0f;      
                killerBees_y[i] = 0.0f;      
                direction_right_killer[i] = false;
                KillerBeesClocks[i].restart();    
                killerBee_alive[i] = false;       
             }
             
            // Resetting pollination for Level 3
            pollination_count = 0;
            first_left = true ;
            first_right = true;
            for (int i = 0; i < pollination_num; ++i) {
                pollination_exists_arr[i] = false;
            }
            // resetting beehives            
        for (int i = 0; i < hive_count; ++i) {
        beehivesSprites[i].setTexture(beehivesTexture);
        beehivesSprites[i].setScale(1, 1); 
        beehives_exist[i] = false;
        }
                        
            // Set parameters for Level 3
            remaining_bees_count = 0; 
            numBees = 20; 
            extra_combs = 15;
            horizontalShift = 4;
            killerBees = 10;

            // Initialize honey for Level 3
            for (int i = 0; i < numBees + extra_combs; ++i) {
                honeySprites[i].setTexture(honeyTexture);
               
            }
            // Randomly place 15 honeycombs initially for Level 3
            for (int i = 0; i < extra_combs; ++i) {
                honey_x[i] = rand() % resolutionX;
                honey_y[i] = rand() % (resolutionY / 2);
                honey_exist[i] = true; 
            }

            // Prepare bees for Level 2
              for (int i = 0; i < numBees; ++i) {
               bees_x[i] = (i % 10) * 100; 
               bees_y[i] = 0;              
               direction_right[i] = (i % 2 == 0); 
               beesSprites[i].setTexture(beesTexture);
               beesSprites[i].setScale(1, 1);
               activationIntervals[i] = (rand() % 3); 
               bee_alive[i] = false; 
    }


            
            // Preparing killer bees for level 3
             for (int i = 0; i < killerBees; ++i) {
             killerBees_x[i] = (i % 10) * 100; 
             killerBees_y[i] = 0;              
             direction_right_killer[i] = (i % 2 == 0); 
             killerBeesSprites[i].setTexture(killerTexture);
             killerBeesSprites[i].setScale(1, 1);
             killer_activationIntervals[i] = 1 + (rand() % 3); 
             killerBee_alive[i] = false; 
             }
             
            // Reseting the bullet_count based on the lives the user uses
            if(count_bullet < 56)
            {
             count_bullet = 0 ;
            }
            else if(count_bullet < 112)
            { count_bullet = 56;
            }
            else if(count_bullet < 158)
            {
             count_bullet = 112;
            }
            
            //Resetting boundary of player as it is causing the error in the game 
            left_boundary = 0 ;
            right_boundary = 960;
            
            //Resetting timer to display texture for level 3
            level3_Tclock.restart();
            }
            
        // Executing level 3    
        if (level == 3 )
         {//Displaying the texture
        while(level3_Tclock.getElapsedTime().asSeconds() < 10 && !boss_level) { 
        window.clear();              
        window.draw(level3_sprite);  
        window.display();            
    
        }
        
            // Call Level 3 function to handle bee movements and collisions
         level_3(window,beesSprites,beesClocks,bees_x,bees_y,direction_right,bee_alive,numBees,bullet_x,bullet_y,
                bullet_exists,collisionSound,honey_x,honey_y,honey_exist,honeySprites,score,scoreText,
                pollination_exists_arr, pollination_num,pollinationSprites,pollination_count,pollination_x,
                pollination_y_fixed,pollination_direction,bird_x,bird_y,bird_exists,birdClock,birdSprite,bird_moved,
                bird_speed,target_x,target_y,fixed_player_x_arr,fixed_player_y_arr, fixed_player_exist,
                fixed_playerSprites,count_bullet,remaining_bees_count,remaining_beesClocks,all_bees_spawned,
                any_bee_alive,collision_honeySound,horizontalShift,extra_combs,spawnBees,activationClock,
                activationIntervals,killerBees_x,killerBees_y,KillerBeesClocks,direction_right_killer,
                killer_bees_count,killerBeesSprites,killerBee_alive,killerBees,killer_activationIntervals,
                killer_speed,red_honey_x,red_honey_y,red_honey_exist,red_honeySprites,level,gameStarted, first_left,first_right,beehives_x,beehives_y,beehives_exist,hive_found,hive_count,beehivesSprites,boss_level, max_beehives,        speed_inc_x,speed_inc_y,speed_inc_exist,speed_inc_count,speed_inc_sprite,speed_dec_x,speed_dec_y, speed_dec_exist,speed_dec_count,speed_dec_sprite,height_inc_x,height_inc_y,height_inc_exist,height_inc_count,
height_inc_sprite,height_dec_x,height_dec_y,height_dec_exist,height_dec_count, height_dec_sprite,target_reached, bird_hit);
               // resetting variables if the game is played in flow 
               if(level == 4) 
               {
            //Adding beehives points after end of level 
            for(int i = 0 ; i < max_beehives ; i++)
            {
             if(beehives_exist[i])
             {
              if(beehives_y[i] < 64)
              {
               score += 2000; // Adding 2000 score for beehive on top two tier
              }
              else if(beehives_y[i] < 160)
              {
               score += 1600; // Adding 1600 score for beehive on 3 , 4 and 5 tier
              }
              else 
              {
               score += 1000; // Adding 1000 score for beehive on remaining tier
              }
             }
            }
            scoreText.setString(to_string(score));//Setting it to score
                // Setting parameters for Level 4
           for (int i = 0; i < numBees +  extra_combs; ++i) 
            {
              honey_exist[i] = false;
            }
             for (int i = 0; i < killerBees; ++i) 
             {
              red_honey_exist[i] = false;
             }
            // Resetting bees for Level 4
            for (int i = 0; i < numBees; ++i) 
            {
                bees_x[i] = 0.0f;             
                bees_y[i] = 0.0f;             
                direction_right[i] = false;   
                beesClocks[i].restart();      
                bee_alive[i] = false;         
            }
            // Resetting killer bees for Level 4
            for (int i = 0; i < killerBees; ++i) {
                killerBees_x[i] = 0.0f;             
                killerBees_y[i] = 0.0f;             
                direction_right_killer[i] = false;  
                KillerBeesClocks[i].restart();      
                killerBee_alive[i] = false;         
             }
             
            // Resetting pollination for Level 4
            pollination_count = 0;
            first_left = true ;
            first_right = true;
            for (int i = 0; i < pollination_num; ++i) 
            {
             pollination_exists_arr[i] = false;
            }
            
            // Reseting the bullet_count based on the lives the user uses
            if(count_bullet < 56)
            {
             count_bullet = 0 ;
            }
            else if(count_bullet < 112)
            { count_bullet = 56;
            }
            else if(count_bullet < 158)
            {
             count_bullet = 112;
            }
            
            //Resetting boundary of player as it is causing the error in the game 
            left_boundary = 0 ;
            right_boundary = 960;
            
            // resetting beehives            
            for (int i = 0; i < max_beehives; ++i) 
            {
             beehivesSprites[i].setTexture(beehivesTexture);
             beehivesSprites[i].setScale(1, 1); // Adjust scale as needed
             beehives_exist[i] = false;
            }
            level4_Tclock.restart();
            bird_exists = true;
         }
      }
          
       
 // Executing the boss level
 if (level == 4) {
 //Displaying the texture for level 4
  while(level4_Tclock.getElapsedTime().asSeconds() < 13 ) 
  { 
    window.clear();               
    window.draw(level4_sprite);   
    window.display();             
  }  //Calling boss level function
    bossLevel(window, beesSprites, beesClocks, bees_x, bees_y, direction_right, bee_alive, numBees, bullet_x,  bullet_y, bullet_exists, collisionSound, honey_x, honey_y, honey_exist, honeySprites, score, scoreText, pollination_exists_arr, pollination_num, pollinationSprites, pollination_count, pollination_x, pollination_y_fixed, pollination_direction, bird_x, bird_y, bird_exists, birdClock, birdSprite, bird_moved, bird_speed, target_x, target_y, fixed_player_x_arr, fixed_player_y_arr, fixed_player_exist, fixed_playerSprites, count_bullet, remaining_bees_count, remaining_beesClocks, all_bees_spawned, any_bee_alive, collision_honeySound, horizontalShift, extra_combs, spawnBees, activationClock, activationIntervals, killerBees_x, killerBees_y, KillerBeesClocks, direction_right_killer, killer_bees_count, killerBeesSprites, killerBee_alive, killerBees, killer_activationIntervals, killer_speed, red_honey_x, red_honey_y, red_honey_exist, red_honeySprites, level, gameStarted, first_left, first_right, beehives_x, beehives_y, beehives_exist, hive_found, hive_count, beehivesSprites, player_move, boss_level, left_boundary, right_boundary, extra_hives, killerTexture, honeyTexture, beesTexture, initialise_boss_level, max_beehives, speed_inc_x, speed_inc_y, speed_inc_exist, speed_inc_count, speed_inc_sprite, speed_dec_x, speed_dec_y, speed_dec_exist, speed_dec_count, speed_dec_sprite, height_inc_x, height_inc_y, height_inc_exist, height_inc_count, height_inc_sprite, height_dec_x, height_dec_y, height_dec_exist, height_dec_count, height_dec_sprite, max_comparisons, orignal_speed, orignal_height, player_height, s_inc_activated, s_dec_activated, h_inc_activated, h_dec_activated,target_reached,bird_hit);
    if (level == 5 )
    {
    //Adding beehives points after end of level 
            for(int i = 0 ; i < max_beehives ; i++)
            {
             if(beehives_exist[i])
             {
              if(beehives_y[i] < 64)
              {
               score += 2000; // Adding 2000 score for beehive on top two tier
              }
              else if(beehives_y[i] < 160)
              {
               score += 1600; // Adding 1600 score for beehive on 3 , 4 and 5 tier
              }
              else 
              {
               score += 1000; // Adding 1000 score for beehive on remaining tier
              }
             }
            }
            scoreText.setString(to_string(score));//Setting it to score
    }        
 }
        //Displaying bullet remaining
        if(count_bullet >=56)
        {
        bulletText.setString(to_string(112-count_bullet));
        }
        else if(count_bullet >= 112)
        {
        bulletText.setString(to_string(158-count_bullet));
        }
        else
        {
      bulletText.setString(to_string(56 - count_bullet));

        }
        
        
        
    // Ending the game if level become 5 and displaying the leaderboard      
    if(level == 5)
     {
     gameStarted = false;
     //Adding the score and name of player in file
     addPlayer(fileName,name ,score);  
     display_score = true ;
     boss_level = false;
       
     }

        // Update the window
        window.draw(scoreText);
        window.draw(bulletText);
        window.display();
    }
   }
   
    return 0;
}  


// Function Definitions

// Draw the player on the window
void drawPlayer(RenderWindow& window, float player_x, float player_y, Sprite& playerSprite , float& player_height) {
    playerSprite.setPosition(player_x, player_y);
    playerSprite.setScale(1, player_height);
    window.draw(playerSprite);
}

// Move the player based on input and constraints
void movePlayer(float& player_x, float& player_y, Sprite& playerSprite, Clock& player_speed, float& left_boundary, float& right_boundary, const int pollination_num, float pollination_x[], bool pollination_exists[],float& player_move,bool& boss_level) {
     if (player_speed.getElapsedTime().asMilliseconds() < 20)
        return;
     
   // Finding boundaries means based on left and right flower and limiting the movement of player
   for (int i=0 ; i < pollination_num ; i++)
   { 
     if(pollination_x[i] > player_x && pollination_x[i] < right_boundary && pollination_exists[i] == true )
      right_boundary = pollination_x[i];
     if(pollination_x[i] < player_x && pollination_x[i] > left_boundary && pollination_exists[i] == true )
      left_boundary = pollination_x[i];
   }
     
    if (((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && (player_x <= resolutionX - boxPixelsX ))&&(player_x+5 < right_boundary)) {
        player_x += player_move;
    }
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && (player_x >= 0)&&(player_x-5 > left_boundary)) {
        player_x -= player_move;
    }
    
    player_speed.restart();
    playerSprite.setPosition(player_x, player_y);
    
}

// Move the bullet upwards and make bullet exists false if it goes off-screen
void moveBullet(float& bullet_y, bool& bullet_exists, Clock& bulletClock) {
    if (bulletClock.getElapsedTime().asMilliseconds() > 20) { 
        bullet_y -= 16.0f; // Bullet speed
        bulletClock.restart();

        if (bullet_y < 0) {
            bullet_exists = false; // Making bullet vanish / deactivate if it goes of the screen
        }
    }
}

// Draw the bullet on the window
void drawBullet(RenderWindow& window, float bullet_x, float bullet_y, Sprite& bulletSprite) {
    bulletSprite.setPosition(bullet_x, bullet_y);
    window.draw(bulletSprite);
}

// Move bees based on their direction and handle collisions with honeycombs
void moveBees(float& bees_x, float& bees_y, Clock& beesClock, bool& direction_right, int& pollination_count, bool bee_alive[], int bee_index, bool pollination_exists_arr[], const int pollination_num, float honey_x[], float honey_y[], const int numBees, bool honey_exist[], int& horizontalShift,int extra_combs,float pollination_x[],bool& first_left ,bool& first_right, float beehives_x[],float beehives_y[],bool beehives_exist[],bool& hive_found,int& hive_count ,float red_honey_x[], float red_honey_y[], bool red_honey_exist[], int killerBees,int& max_beehives) 
{
 if (beesClock.getElapsedTime().asMilliseconds() < 20)
        return;
    beesClock.restart();

    // Moving the bees across the screen and changing its directions
    //Moving bee right
    if (direction_right) 
    {
        bees_x += horizontalShift;

        // Checking if bee reaches right side of the boundary
        if (bees_x >= resolutionX - boxPixelsX) 
        {
            hive_found = false;

            // Check for honeycomb below to create a hive as bee will be stuck
            for (int i = 0; i < numBees + extra_combs; i++) {
                if (((honey_y[i] - (bees_y+32)) < 32) && ((honey_y[i] - (bees_y+32) > 0)) && honey_exist[i] && abs(bees_x - honey_x[i]) < 32)  {
                    hive_found = true;
                    beehives_x[hive_count] = bees_x;
                    beehives_y[hive_count] = bees_y;
                    beehives_exist[hive_count] = true;
                    hive_count++;
                    bee_alive[bee_index] = false; // Bee vanishes
                   // return; 
                }
            }
            // Just normally change direction if hive not found
            if (!hive_found) {
                direction_right = false; // Change direction
                bees_y += 32; // Move down
            }
        }

        // Honeycomb collision check
        for (int i = 0; i < numBees + extra_combs; i++) 
        {
            if (abs(bees_x - honey_x[i]) < 32 && abs(bees_y - honey_y[i]) < 32 && honey_exist[i]) {
                direction_right = false;
                bees_y += 32;
                break;
            }
        }
        // Red honeycomb collision check
        for (int i = 0; i < killerBees ; i++) 
        {
         if (abs(bees_x - red_honey_x[i]) < 32 && abs(bees_y - red_honey_y[i]) < 32 && red_honey_exist[i]) 
         {
          direction_right = false;
          bees_y += 32;
          break;
         }
       }
        // Beehive collision check
        for (int i = 0; i < max_beehives ; i++) 
        {
         if (abs(bees_x - beehives_x[i]) < 32 && abs(bees_y - beehives_y[i]) < 32 && beehives_exist[i]) 
         {
          direction_right = false;
          bees_y += 32;
          break;
         }
       }
       
        
     } 
     else 
     { // Moving bee left
        bees_x -= horizontalShift;

        // Checking if left boundary of the screen has been reached
        if (bees_x <= 0) 
        {
          hive_found = false;

          // Check for honeycomb below for hives
         for (int i = 0; i < numBees + extra_combs; i++) 
         {
           if (((honey_y[i] - (bees_y+32) < 32)) && ((honey_y[i] - (bees_y+32) > 0)) && honey_exist[i] && (abs(bees_x - honey_x[i]) < 32)) 
           {
             hive_found = true;
             beehives_x[hive_count] = bees_x;
             beehives_y[hive_count] = bees_y;
             beehives_exist[hive_count] = true;
             hive_count++;
             bee_alive[bee_index] = false; // Bee vanishes
             return; 
           }
         }
          // Just normally change direction if hive not found
         if (!hive_found) 
         {
           direction_right = true; // Change direction
           bees_y += 32; // Move down
         }
       }

        // Honeycomb collision check
        for (int i = 0; i < numBees + extra_combs; i++) 
        {
         if (abs(bees_x - honey_x[i]) < 32 && abs(bees_y - honey_y[i]) < 32 && honey_exist[i]) 
         {
          direction_right = true;
          bees_y += 32;
          break;
         }
       }
        // Red honeycomb collision check
        for (int i = 0; i < killerBees ; i++) 
        {
         if (abs(bees_x - red_honey_x[i]) < 32 && abs(bees_y - red_honey_y[i]) < 32 && red_honey_exist[i]) 
         {
          direction_right = true;
          bees_y += 32;
          break;
        }
       }
         // Beehive collision check
       for (int i = 0; i < max_beehives ; i++) 
       {
        if (abs(bees_x - beehives_x[i]) < 32 && abs(bees_y - beehives_y[i]) < 32 && beehives_exist[i]) 
        {
         direction_right = true;
         bees_y += 32;
         break;
        }
      }
   }

    // Pollination logic
    if ((bees_y > 480) && bee_alive[bee_index] && pollination_count < pollination_num) 
    {
     //Declaring a location variable to handle if polliation will exist from right or left
     float location = 0.0f;
     //Checking for center pollination
     if (bees_x == pollination_x[15]) 
     {
      pollination_exists_arr[15] = true;
      pollination_count++;
     }
     //Checking for Left pollination
     else if (direction_right) 
     {
      location = pollination_x[pollination_count];
      //Making bee inactive once it reaches that x value
      if (bees_x >= location) 
      {
       bee_alive[bee_index] = false;
       //Checking for first right to draw 2 flowers
       if (first_right) 
       {
        pollination_exists_arr[pollination_count] = true; 
        pollination_exists_arr[pollination_count + 1] = true;
        pollination_count += 2;
        first_right = false;
       } else 
       {// Drawing 1 flower for subsequent pollination
         pollination_exists_arr[pollination_count] = true;
         pollination_count++;
       }
      }
     }
      else 
      {//Same as above just direction changed
       location = pollination_x[pollination_num - 1 - pollination_count];
       if (bees_x <= location) 
       {
         bee_alive[bee_index] = false;
         if (first_left) 
         {
          pollination_exists_arr[pollination_num - 1 - pollination_count] = true;
          pollination_exists_arr[pollination_num - 2 - pollination_count] = true;
          pollination_count += 2;
          first_left = false;
         } 
         else 
         {
          pollination_exists_arr[pollination_num - 1 - pollination_count] = true;
          pollination_count++;
         }
      }
    }
  }
}


// Draw all alive bees on the window
void drawBees(RenderWindow& window, Sprite beesSprites[], float bees_x[], float bees_y[], bool direction_right[], bool bee_alive[], int numBees) {
    for (int i = 0; i < numBees; ++i) {
        if (bee_alive[i]) { // Draw only alive bees
            beesSprites[i].setPosition(bees_x[i], bees_y[i]);
            // Flip sprite based on direction
            if (!direction_right[i]) {
                beesSprites[i].setScale(0.5, 0.5); // Flip sprite for left direction
            }
            else {
                beesSprites[i].setScale(-0.5, 0.5);  // Default sprite for right direction
            }
            window.draw(beesSprites[i]);
        }
    }
}

// Handle collisions between bullets and bees/honeycombs and of hummingBird and bullet and huming bird and red and yellow honeycombs
void collision(float& bees_x, float& bees_y, float& bullet_x, float& bullet_y, bool& bullet_exists, bool& bee_alive, sf::Sound& collisionSound, float honey_x[], float honey_y[], bool honey_exist[], int index, int& score, sf::Text& scoreText, float& bird_x, float& bird_y, const int numBees, sf::Sound& collision_honeySound, int extra_combs,int killerBees,float red_honey_x[], float red_honey_y[], bool red_honey_exist[],float speed_inc_x[],float speed_inc_y[],bool speed_inc_exist[],int& speed_inc_count,Sprite speed_inc_sprite[],float speed_dec_x[],float speed_dec_y[],bool speed_dec_exist[],int& speed_dec_count,Sprite speed_dec_sprite[],float height_inc_x[],float height_inc_y[],bool height_inc_exist[],int& height_inc_count,Sprite height_inc_sprite[],float height_dec_x[],float height_dec_y[],bool height_dec_exist[],int& height_dec_count,Sprite height_dec_sprite[],float beehives_x[],float beehives_y[],bool beehives_exist[],bool& hive_found,int& hive_count,int& max_beehives,bool& boss_level,int& bird_hit,bool& bird_exists)  
{ int random_number; // generating random number to decide the power to activated for boss level

    // To prevent segmentation and out of bound error as it was coming again and again
    if (index < 0 || index >= numBees + extra_combs) 
    {
     return; 
    }

    // Collision between bullet and bee
    if (bee_alive && bullet_exists && abs(bees_x - bullet_x) < 16 && abs(bees_y - bullet_y) < 16) 
    {// Making bee and bullet inactive after collision
     bee_alive = false;
     bullet_exists = false;
     collisionSound.play();
     score += 100;  // Adding score on collision
     scoreText.setString(to_string(score));// Setting it to string to display on the screen
     // Making yellow honeycombs activated at the place of collision
     honey_x[index + 3] = bees_x;
     honey_y[index + 3] = bees_y;
     if (index + 3 < numBees + extra_combs) 
     {
      honey_exist[index + 3] = true;
     }
    }


    // Collision between bullet and honeycombs
    for (int i = 0; i < numBees + extra_combs; i++)
     {//Checking for collision and same making honeycomb and bullet inactive if they collide
      if (bullet_exists && honey_exist[i] && abs(honey_x[i] - bullet_x) <= 32 && abs(honey_y[i] - bullet_y) <= 32) 
      {
       bullet_exists = false;
       honey_exist[i] = false;
       collision_honeySound.play();
      }
    }
    
    // Collision between bullet and Beehives
    for (int i = 0; i < max_beehives ; i++) 
    {//Checking for collision and same making beehives and bullet inactive if they collide
     if (bullet_exists && beehives_exist[i] && abs(beehives_x[i] - bullet_x) <= 32 && abs(beehives_y[i] - bullet_y) <= 32) 
     {
      bullet_exists = false;
      beehives_exist[i] = false;
      collision_honeySound.play();
     }
   }
   
     // Collision between bullet and hummingBird
     if (bird_exists && bullet_exists && abs(bird_x - bullet_x) <= 32 && abs(bird_y - bullet_y) <= 32) 
     {
      bullet_exists = false;
      bird_hit++;
      collision_honeySound.play();
     }
   


    // Collision between hummingbird and yellow honeycombs
    if(!boss_level)
    {
    for (int i = 0; i < numBees; i++) {
        if (abs(honey_x[i] - bird_x) <= 32 && abs(honey_y[i] - bird_y) <= 32 && (honey_exist[i])) {
            honey_exist[i] = false;
            if (honey_y[i] <= 64)
                score += 1000; // Adding 1000 to score if top two tier
            else if (honey_y[i] <= 160)
                score += 800; //Adding 800 to score if three four five tier
            else
                score += 500;//Adding 500 to score for rest tiers
            scoreText.setString(to_string(score));//Setting it to score
        }
    }
    }
    else
    {// Activating powers if hummingbird eats honeycombs
     for (int i = 0; i < numBees; i++) {
       random_number = (rand()%4) + 1;
        if (abs(honey_x[i] - bird_x) <= 32 && abs(honey_y[i] - bird_y) <= 32 && (honey_exist[i])) 
        {
         if(random_number == 1) // Activating speed increase power
            {
             speed_inc_exist[speed_inc_count] = true;
             speed_inc_x[speed_inc_count] = red_honey_x[i];
             speed_inc_y[speed_inc_count] = red_honey_y[i];
             speed_inc_count++;
            }
            else if(random_number == 2)// Activating speed decrease power
            {
             speed_dec_exist[speed_dec_count] = true;
             speed_dec_x[speed_dec_count] = red_honey_x[i];
             speed_dec_y[speed_dec_count] = red_honey_y[i];
             speed_dec_count++;
            } 
            else if(random_number == 3)// Activating Height increase power
            {
             height_inc_exist[height_inc_count] = true;
             height_inc_x[height_inc_count] = red_honey_x[i];
             height_inc_y[height_inc_count] = red_honey_y[i];
             height_inc_count++;
            }
            else if(random_number == 4) // Activating Height decrease power
            {
             height_dec_exist[height_dec_count] = true;
             height_dec_x[height_dec_count] = red_honey_x[i];
             height_dec_y[height_dec_count] = red_honey_y[i];
             height_dec_count++;
            }
            honey_exist[i] = false;
            if (honey_y[i] <= 64)
                score += 1000; // Adding 1000 to score if top two tier
            else if (honey_y[i] <= 160)
                score += 800; //Adding 800 to score if three four five tier
            else
                score += 500;//Adding 500 to score for rest tiers
            scoreText.setString(to_string(score));//Setting it to score

        } 
     
    }
   }
   
     // Collision between hummingbird and red honeycombs
    
    if(!boss_level) // If not boss level
    {
    for (int i = 0; i < killerBees; i++) {
        if (abs((red_honey_x[i] - bird_x) < 32)&& abs((red_honey_y[i] - bird_y) < 32) && (red_honey_exist[i])) {
            red_honey_exist[i] = false;
            if (red_honey_y[i] <= 64)
                score += 2000; // Adding 2000 to score if top two tier
            else if (honey_y[i] <= 160)
                score += 1800; //Adding 800 to score if three four five tier
            else
                score += 1500;//Adding 500 to score for rest tiers
            scoreText.setString(to_string(score));//Setting it to score
        }
    }
    }
    else 
    {// If it is boss level it will produce the power ups 
    
      for (int i = 0; i < killerBees; i++) 
      {random_number = (rand()%4) + 1;
        if (abs((red_honey_x[i] - bird_x) < 32)&& abs((red_honey_y[i] - bird_y) < 32) && (red_honey_exist[i])) 
     {
       if(random_number == 1)
            {
             speed_inc_exist[speed_inc_count] = true;
             speed_inc_x[speed_inc_count] = red_honey_x[i];
             speed_inc_y[speed_inc_count] = red_honey_y[i];
             speed_inc_count++;
            }
            else if(random_number == 2)
            {
             speed_dec_exist[speed_dec_count] = true;
             speed_dec_x[speed_dec_count] = red_honey_x[i];
             speed_dec_y[speed_dec_count] = red_honey_y[i];
             speed_dec_count++;
            } 
            else if(random_number == 3)
            {
             height_inc_exist[height_inc_count] = true;
             height_inc_x[height_inc_count] = red_honey_x[i];
             height_inc_y[height_inc_count] = red_honey_y[i];
             height_inc_count++;
            }
            else if(random_number == 4)
            {
             height_dec_exist[height_dec_count] = true;
             height_dec_x[height_dec_count] = red_honey_x[i];
             height_dec_y[height_dec_count] = red_honey_y[i];
             height_dec_count++;
            }
            red_honey_exist[i] = false;
            if (red_honey_y[i] <= 64)
                score += 2000; // Adding 2000 to score if top two tier
            else if (honey_y[i] <= 160)
                score += 1800; //Adding 800 to score if three four five tier
            else
                score += 1500;//Adding 500 to score for rest tiers
            scoreText.setString(to_string(score));//Setting it to score
              
       }
      }
     }  
    
}


// Making a new collision function to handle segmentation error as in this it is accessing out if bound killer array
void killer_collision(float& killerBees_x, float& killerBees_y, sf::Clock KillerBeesClock[], int& killer_bees_count, sf::Sprite killerBeesSprites[], bool& KillerBee_alive, int killerBees, int killer_activationIntervals[], int& killer_speed,float& bullet_x, float& bullet_y, bool& bullet_exists,sf::Sound& collisionSound,int& score, sf::Text& scoreText,sf::Sound& collision_honeySound,int index,float red_honey_x[], float red_honey_y[], bool red_honey_exist[],bool& boss_level,float speed_inc_x[],float speed_inc_y[],bool speed_inc_exist[],int& speed_inc_count,Sprite speed_inc_sprite[],float speed_dec_x[],float speed_dec_y[],bool speed_dec_exist[],int& speed_dec_count,Sprite speed_dec_sprite[],float height_inc_x[],float height_inc_y[],bool height_inc_exist[],int& height_inc_count,Sprite height_inc_sprite[],float height_dec_x[],float height_dec_y[],bool height_dec_exist[],int& height_dec_count,Sprite height_dec_sprite[])
{    
    
    // Collision between killer bee and bullet
    if (KillerBee_alive && bullet_exists &&
        abs(killerBees_x - bullet_x) <= 32 && abs(killerBees_y - bullet_y) <= 32) {
        KillerBee_alive = false;
        bullet_exists = false;
        collisionSound.play();
        score += 1000;
        scoreText.setString(to_string(score));

      
        if (index >= 0 && index < killerBees) { // Safeguard index
        red_honey_x[index] = killerBees_x;
        red_honey_y[index] = killerBees_y;
        red_honey_exist[index] = true;
    }
    }

    // Collision between bullet and red honeycombs
   int random_number;
    if(!boss_level)
    {
    for (int i = 0; i < killerBees; i++) {
        if (bullet_exists && red_honey_exist[i] &&
            abs(red_honey_x[i] - bullet_x) <= 32 && abs(red_honey_y[i] - bullet_y) <= 32) {
            bullet_exists = false;
            red_honey_exist[i] = false;
            collision_honeySound.play();
        }
    }  
   }
   else
   {
    for (int i = 0; i < killerBees; i++) 
    {
      random_number = (rand()%4) + 1; // generating random number to decide the power to activated
        if (bullet_exists && red_honey_exist[i] &&
            abs(red_honey_x[i] - bullet_x) <= 32 && abs(red_honey_y[i] - bullet_y) <= 32) {
            // generating power ups
            if(random_number == 1)
            {
             speed_inc_exist[speed_inc_count] = true;
             speed_inc_x[speed_inc_count] = red_honey_x[i];
             speed_inc_y[speed_inc_count] = red_honey_y[i];
             speed_inc_count++;
            }
            else if(random_number == 2)
            {
             speed_dec_exist[speed_dec_count] = true;
             speed_dec_x[speed_dec_count] = red_honey_x[i];
             speed_dec_y[speed_dec_count] = red_honey_y[i];
             speed_dec_count++;
            } 
            else if(random_number == 3)
            {
             height_inc_exist[height_inc_count] = true;
             height_inc_x[height_inc_count] = red_honey_x[i];
             height_inc_y[height_inc_count] = red_honey_y[i];
             height_inc_count++;
            }
            else if(random_number == 4)
            {
             height_dec_exist[height_dec_count] = true;
             height_dec_x[height_dec_count] = red_honey_x[i];
             height_dec_y[height_dec_count] = red_honey_y[i];
             height_dec_count++;
            }
            bullet_exists = false;
            red_honey_exist[i] = false;
            collision_honeySound.play();
    
   }
  }
 }
}  

 
// Checking collosions bullet and power ups  
void powers_collision(RenderWindow& window,float speed_inc_x[],float speed_inc_y[],bool speed_inc_exist[],int& speed_inc_count,Sprite speed_inc_sprite[],float speed_dec_x[],float speed_dec_y[],bool speed_dec_exist[],int& speed_dec_count,Sprite speed_dec_sprite[],float height_inc_x[],float height_inc_y[],bool height_inc_exist[],int& height_inc_count,Sprite height_inc_sprite[],float height_dec_x[],float height_dec_y[],bool height_dec_exist[],int& height_dec_count,Sprite height_dec_sprite[],sf::Sound& collisionSound,bool& s_inc_activated,bool& s_dec_activated,bool& h_inc_activated,bool& h_dec_activated,float& bullet_x, float& bullet_y, bool& bullet_exists,float&player_move,float& player_height)
{
 for (int i = 0; i < speed_inc_count; i++) {
        if (speed_inc_exist[i] && bullet_exists &&
            abs(speed_inc_x[i] - bullet_x) <= 32 && abs(speed_inc_y[i] - bullet_y) <= 32) {
            s_inc_activated = true;
            speed_inc_exist[i] = false;
            bullet_exists = false;
            player_move += 8;
            collisionSound.play();
            }
        if (speed_dec_exist[i] && bullet_exists &&
            abs(speed_dec_x[i] - bullet_x) <= 32 && abs(speed_dec_y[i] - bullet_y) <= 32) {
            s_dec_activated = true;
            speed_dec_exist[i] = false;
            player_move -= 6;
            bullet_exists = false;
            collisionSound.play();
            }
       if (height_inc_exist[i] && bullet_exists &&
            abs(height_inc_x[i] - bullet_x) <= 32 && abs(height_inc_y[i] - bullet_y) <= 32) {
            h_inc_activated = true;
            height_inc_exist[i] = false;
            bullet_exists = false;
            player_height += 2;
            collisionSound.play();
            }
       if (height_dec_exist[i] && bullet_exists &&
            abs(height_dec_x[i] - bullet_x) <= 32 && abs(height_dec_y[i] - bullet_y) <= 32) {
            h_dec_activated = true;
            height_dec_exist[i] = false;
            bullet_exists = false;
            player_height -= 0.5;
            collisionSound.play();
            }
         }
}         
     

// Draw all existing honeycombs on the window
void drawHoney(RenderWindow& window, float honey_x[], float honey_y[], bool honey_exist[], int numBees, Sprite honeySprites[], int extra_combs,float red_honey_x[], float red_honey_y[], bool red_honey_exist[], int killerBees, Sprite red_honeySprites[]) {
    for (int i = 0; i < numBees + extra_combs; ++i)
     {
        if (honey_exist[i])
         { // Draw only existing honeycombs
           honeySprites[i].setPosition(honey_x[i], honey_y[i]);
           window.draw(honeySprites[i]);
         }
     } 
    for (int i = 0; i < killerBees; ++i) 
    {
    if (red_honey_exist[i]) { // Only draw if it exists
        red_honeySprites[i].setPosition(red_honey_x[i], red_honey_y[i]);
        window.draw(red_honeySprites[i]);
    }
   }
}


//Drawing all existing beehives
void drawBeehives(RenderWindow& window, float beehives_x[], float beehives_y[], bool beehives_exist[], int& hive_count, Sprite beehivesSprites[],int& max_beehives ) {
    for (int i = 0; i < max_beehives ; ++i) {
        if (beehives_exist[i]) { // Draw only existing honeycombs
            beehivesSprites[i].setPosition(beehives_x[i], beehives_y[i]);
            window.draw(beehivesSprites[i]);
            }
           } 

}

// Draw all pollination objects on the window
void drawPollination(RenderWindow& window, bool pollination_exists[], const int pollination_num, Sprite pollinationSprites[], int pollination_count, float pollination_x[], float pollination_y) { 
    for(int i = 0; i < pollination_num; ++i) {
        if(pollination_exists[i]) { // Draw only existing pollination objects
            pollinationSprites[i].setPosition(pollination_x[i], pollination_y);
            window.draw(pollinationSprites[i]);
        }
    }
}

//Drawing the humming bird
void drawBird(RenderWindow& window, float& bird_x, float& bird_y, Sprite& birdSprite, bool& bird_exists) {
    if (bird_exists) {
        birdSprite.setPosition(bird_x, bird_y);
        window.draw(birdSprite);
    }
}

// Function to assign new target points to the bird
void points_bird(float& target_x, float& target_y, Clock& pauseClock, bool& target_reached) 
{
  if (pauseClock.getElapsedTime().asMilliseconds() > 5000) 
  { 
  // Setting new target once the old one has been reached      
  // Decreasing the resolution as they were going out of the screen
   target_x = rand() % 950; 
   target_y = rand() % 480; 
   target_reached = false; 
   pauseClock.restart(); // Restarting the clock for the next duration
  }
}


//Function to move Bird
void moveBird(float& bird_x, float& bird_y, bool& bird_exists, float& target_x, float& target_y, bool& target_reached) 
{
 if (bird_exists) // only move if bird exists 
 {
  if (!target_reached) 
  {
   // Move the bird towards the target
   //Handling x direction
   if (bird_x < target_x) 
   {
     bird_x++; 
   } else if (bird_x > target_x) 
   {
    bird_x--;
   }
   //Handling y direction
   if (bird_y < target_y) 
   {
    bird_y++;
   } 
   else if (bird_y > target_y) 
   {
     bird_y--;
   }
   // Check if the bird has reached the target
   if (std::abs(bird_x - target_x) < 32 && std::abs(bird_y - target_y) < 32) 
   {
    target_reached = true; // Mark target as reached
   }
   }
  }
}

// Draw fixed players(lives) on the window
void drawFixedPlayer(RenderWindow& window, float fixed_player_x[], float fixed_player_y[], bool fixed_player_exist[], Sprite fixed_playerSprites[], int& count_bullet) {
    for(int i = 0; i < 2; ++i) { // Assuming three lives and 1 has been used immediately
        if(fixed_player_exist[i]) {
            fixed_playerSprites[i].setPosition(fixed_player_x[i], fixed_player_y[i]);
            window.draw(fixed_playerSprites[i]);
        }
    }
}

//Function to activate the existance of bees
void activateBees(bool bee_alive[], int& remaining_bees_count, Clock& activationClock, int activationIntervals[], int numBees) {
    // Check if it's time to activate a bee
    if (activationClock.getElapsedTime().asSeconds() >= activationIntervals[remaining_bees_count]) {
        if (remaining_bees_count < numBees) {
            bee_alive[remaining_bees_count] = true;
            remaining_bees_count++; 
            activationClock.restart(); 
        }
    }
}





// Killer bees draw , movement and activations all based on simple bees code
// Move bees based on their direction and handle collisions with honeycombs
void move_Killerbees(float& killerBees_x, float& killerBees_y, Clock& KillerBeesClock, bool& direction_right_killer, int& pollination_count, bool KillerBee_alive[], bool pollination_exists[], const int pollination_num, const int killerBees, int& killer_speed, int& bee_index,float pollination_x[],bool& first_left ,bool& first_right) {
    if (KillerBeesClock.getElapsedTime().asMilliseconds() < 20)
        return;

    KillerBeesClock.restart();

    // Move bees horizontally based on direction
    if (direction_right_killer) {
        killerBees_x += killer_speed;
        // Change direction if bee reaches the right boundary
        if (killerBees_x >= resolutionX - boxPixelsX) {
            direction_right_killer = false;
            killerBees_y += 32; // Move down
        }
    }
    else {
        killerBees_x -= killer_speed;
        // Change direction if bee reaches the left boundary
        if (killerBees_x <= 0) {
            direction_right_killer = true;
            killerBees_y += 32; // Move down
        }

    }

  // Handle pollination when bees reach a certain y-position
if ((killerBees_y > 480) && KillerBee_alive[bee_index] && pollination_count < pollination_num) {
    float location = 0.0f;
    if(killerBees_x == pollination_x[15])
    {
     pollination_x[15] = true;
     pollination_count++;
    }
    // Determine the target pollination position based on direction
    else if (direction_right_killer) {
        location = pollination_x[pollination_count]; // Get the next pollination position
        if (killerBees_x >= location) { 
            KillerBee_alive[bee_index] = false;        
            if(first_right)
            {
             // activating 2 flowers on either side if first bee from left or fiest bee from right
             pollination_exists[pollination_count] = true; // Activate the pollination flower
             pollination_exists[pollination_count+1] = true;
             pollination_count += 2;                  
             first_right = false;
            }
            else
            {
             pollination_exists[pollination_count] = true; // Activate the pollination flower
             pollination_count++;             
            }
             
        }
    } else {
        location = pollination_x[pollination_num - 1 - pollination_count];
        if (killerBees_x <= location) { 
            KillerBee_alive[bee_index] = false; 
            if(first_left)
            {
            pollination_exists[pollination_num - 1 - pollination_count] = true; // Activate the pollination flower
            pollination_exists[pollination_num - 2 - pollination_count] = true;
            pollination_count += 2;    
            first_left = false;        
            }
            else
            {
            pollination_exists[pollination_num - 1 - pollination_count] = true; 
            pollination_count++ ;                 
            }
            
        }
    }
}
}




// Draw all alive bees on the window
void draw_Killerbees(RenderWindow& window, Sprite killerBeesSprites[], float killerBees_x[], float killerBees_y[], bool direction_right_killer[], bool KillerBee_alive[], int& killerBees)
{
    for (int i = 0; i < killerBees; ++i) 
    {
      if (KillerBee_alive[i]) 
      { // Draw only alive bees
        killerBeesSprites[i].setPosition(killerBees_x[i], killerBees_y[i]);
        // Flip sprite based on direction
        if (!direction_right_killer[i]) 
        {
         killerBeesSprites[i].setScale(0.5, 0.5); // Flip sprite for left direction
        }
      else 
      {
       killerBeesSprites[i].setScale(-0.5, 0.5);  // Default sprite for right direction
      }
       window.draw(killerBeesSprites[i]);
    }
  }
}

//Activating killer bees same as simple bees
void activate_Killerbees(bool KillerBee_alive[], int& killer_bees_count, Clock& killer_activationClock, int killer_activationIntervals[], int& killerBees)
 {
    // Check if it's time to activate a bee
    if (killer_activationClock.getElapsedTime().asSeconds() >= killer_activationIntervals[killer_bees_count]) {
        if (killer_bees_count < killerBees) {
            KillerBee_alive[killer_bees_count] = true; 
            killer_bees_count++;
            killer_activationClock.restart(); 
        }
    }
}

// Speed increase power
void draw_speedInc(RenderWindow& window, float speed_inc_x[], float speed_inc_y[], bool speed_inc_exist[], int& speed_inc_count, Sprite speed_inc_sprite[]) {
    for (int i = 0; i < speed_inc_count + 1; ++i) {
        if (speed_inc_exist[i]) { 
            speed_inc_sprite[i].setPosition(speed_inc_x[i], speed_inc_y[i]);
            window.draw(speed_inc_sprite[i]);
            }
     }
} 
     
//Speed decrease power          
void draw_speedDec(RenderWindow& window, float speed_dec_x[], float speed_dec_y[], bool speed_dec_exist[], int& speed_dec_count, Sprite speed_dec_sprite[]) {
    for (int i = 0; i < speed_dec_count + 1; ++i) {
        if (speed_dec_exist[i]) { 
            speed_dec_sprite[i].setPosition(speed_dec_x[i], speed_dec_y[i]);
            window.draw(speed_dec_sprite[i]);
            }
    }
}
//Height increase power
void draw_heightDec(RenderWindow& window, float height_dec_x[], float height_dec_y[], bool height_dec_exist[], int& height_dec_count, Sprite height_dec_sprite[]) {
    for (int i = 0; i < height_dec_count + 1; ++i) {
        if (height_dec_exist[i]) { // Draw only existing honeycombs
            height_dec_sprite[i].setPosition(height_dec_x[i], height_dec_y[i]);
            window.draw(height_dec_sprite[i]);
            }
    }
}

//Height decrease power
void draw_heightInc(RenderWindow& window, float height_inc_x[], float height_inc_y[], bool height_inc_exist[], int& height_inc_count, Sprite height_inc_sprite[]) {
    for (int i = 0; i < height_inc_count + 1; ++i) {
        if (height_inc_exist[i]) { // Draw only existing honeycombs
            height_inc_sprite[i].setPosition(height_inc_x[i], height_inc_y[i]);
            window.draw(height_inc_sprite[i]);
            }
    }
}



// Level 1 Function
void level_1(RenderWindow& window, Sprite beesSprites[], Clock beesClocks[], float bees_x[], float bees_y[], bool direction_right[], bool bee_alive[], int numBees, float bullet_x, float bullet_y, bool& bullet_exists, Sound& collisionSound, float honey_x[], float honey_y[], bool honey_exist[], Sprite honeySprites[], int& score, Text& scoreText, bool pollination_exists[], const int pollination_num, Sprite pollinationSprites[], int& pollination_count, float pollination_x[], float& pollination_y, bool& pollination_direction, float& bird_x, float& bird_y, bool& bird_exists, Clock birdClock, Sprite birdSprite, bool& bird_moved, float& bird_speed, float& target_x, float& target_y, float fixed_player_x[], float fixed_player_y[], bool fixed_player_exist[], Sprite fixed_playerSprites[], int& count_bullet, int& remaining_bees_count, Clock remaining_beesClocks, bool& all_bees_spawned, bool& any_bee_alive, Sound& collision_honeySound, int& horizontalShift, int extra_combs,Clock& activationClock, int activationIntervals[],float red_honey_x[],float red_honey_y[],bool red_honey_exist[], float killerBees_x[], float killerBees_y[], Clock KillerBeesClock[], bool direction_right_killer[], int& killer_bees_count, Sprite killerBeesSprites[], bool KillerBee_alive[], int& killerBees, int killer_activationIntervals[], int& killer_speed, Sprite red_honeySprites[],bool& first_left ,bool& first_right,Clock pauseClock, float beehives_x[],float beehives_y[],bool beehives_exist[],bool& hive_found,int& hive_count,Sprite beehivesSprites[],int& max_beehives,float speed_inc_x[],float speed_inc_y[],bool speed_inc_exist[],int& speed_inc_count,Sprite speed_inc_sprite[],float speed_dec_x[],float speed_dec_y[],bool speed_dec_exist[],int& speed_dec_count,Sprite speed_dec_sprite[],float height_inc_x[],float height_inc_y[],bool height_inc_exist[],int& height_inc_count,Sprite height_inc_sprite[],float height_dec_x[],float height_dec_y[],bool height_dec_exist[],int& height_dec_count,Sprite height_dec_sprite[],bool& target_reached,bool& boss_level,int& bird_hit)
{
  // Activate bees one by one based on random intervals
    activateBees(bee_alive, remaining_bees_count, activationClock, activationIntervals, numBees);

    // Move and handle collisions for all alive bees
    for (int i = 0; i < numBees; ++i) 
    {
     if (bee_alive[i]) 
     { // Handling moving and collision of alive bees
      moveBees(bees_x[i], bees_y[i], beesClocks[i], direction_right[i], pollination_count, bee_alive, i, pollination_exists, pollination_num, honey_x, honey_y, numBees, honey_exist, horizontalShift,extra_combs, pollination_x,first_left,first_right,beehives_x,beehives_y,beehives_exist, hive_found,hive_count,red_honey_x,red_honey_y, red_honey_exist, killerBees,max_beehives);
            collision(bees_x[i], bees_y[i], bullet_x, bullet_y,bullet_exists, bee_alive[i], collisionSound,honey_x, honey_y, honey_exist, i,score, scoreText, bird_x, bird_y, numBees,collision_honeySound, extra_combs, killerBees,red_honey_x, red_honey_y, red_honey_exist,speed_inc_x,speed_inc_y,speed_inc_exist,speed_inc_count,
speed_inc_sprite,speed_dec_x,speed_dec_y,speed_dec_exist,speed_dec_count,speed_dec_sprite,height_inc_x,height_inc_y,
height_inc_exist,height_inc_count,height_inc_sprite,height_dec_x,height_dec_y,height_dec_exist,height_dec_count, height_dec_sprite,beehives_x,beehives_y, beehives_exist,hive_found, hive_count,max_beehives,boss_level, bird_hit, bird_exists);
      }
   }


    // Drawing all alive bees
    drawBees(window, beesSprites, bees_x, bees_y, direction_right, bee_alive, numBees);

    // Drawing all existing honeycombs
    drawHoney(window, honey_x, honey_y, honey_exist, numBees, honeySprites, extra_combs,red_honey_x, red_honey_y,red_honey_exist,killerBees,red_honeySprites);
    drawBeehives(window,beehives_x,beehives_y,beehives_exist, hive_count,beehivesSprites,max_beehives);
    // Drawing all pollination objects
    drawPollination(window, pollination_exists, pollination_num, pollinationSprites, pollination_count, pollination_x, pollination_y);

    // Drawing fixed players
    drawFixedPlayer(window, fixed_player_x, fixed_player_y, fixed_player_exist, fixed_playerSprites, count_bullet);
    
  
    drawBird(window, bird_x, bird_y, birdSprite, bird_exists);
    // Exit Level 1 if bullet count exceeds limit
    if (count_bullet >= 158)
        return;

    // Check if all bees have been spawned
    if (remaining_bees_count >= numBees) {
        all_bees_spawned = true;
    } else {
        all_bees_spawned = false;
    }

    // Check if any bees are alive
    int count = 0;
    for (int i = 0; i < numBees; ++i) {
        if (bee_alive[i]) {
            count++;
        }
    }

    // If all bees have been spawned and none are alive, set any_bee_alive flag
    if (all_bees_spawned && count == 0) {
        any_bee_alive = false;
    } else {
        any_bee_alive = true;
    }

    // Exit Level 1 if no bees are alive and all bees have been spawned
    if (!any_bee_alive && all_bees_spawned)
        return;
}


// Level 2 Function
void level_2(RenderWindow& window, Sprite beesSprites[], Clock beesClocks[], float bees_x[], float bees_y[], bool direction_right[], bool bee_alive[], int numBees, float bullet_x, float bullet_y, bool& bullet_exists, Sound& collisionSound, float honey_x[], float honey_y[], bool honey_exist[], Sprite honeySprites[], int& score, Text& scoreText, bool pollination_exists[], const int pollination_num, Sprite pollinationSprites[], int& pollination_count, float pollination_x[], float& pollination_y, bool& pollination_direction, float& bird_x, float& bird_y, bool& bird_exists, Clock birdClock, Sprite birdSprite, bool& bird_moved, float& bird_speed, float& target_x, float& target_y, float fixed_player_x[], float fixed_player_y[], bool fixed_player_exist[], Sprite fixed_playerSprites[], int& count_bullet, int& remaining_bees_count, Clock remaining_beesClocks, bool& all_bees_spawned, bool& any_bee_alive, Sound& collision_honeySound, int horizontalShift, int extra_combs, Clock spawnBees, Clock& activationClock, int activationIntervals[], float killerBees_x[], float killerBees_y[], Clock KillerBeesClock[], bool direction_right_killer[], int& killer_bees_count, Sprite killerBeesSprites[], bool KillerBee_alive[], int& killerBees, int killer_activationIntervals[], int& killer_speed,float red_honey_x[],float red_honey_y[],bool red_honey_exist[],Sprite red_honeySprites[],int& level,bool& first_left ,bool& first_right, float beehives_x[],float beehives_y[],bool beehives_exist[],bool& hive_found,int& hive_count,Sprite beehivesSprites[],bool& boss_level,int& max_beehives,float speed_inc_x[],float speed_inc_y[],bool speed_inc_exist[],int& speed_inc_count,Sprite speed_inc_sprite[],float speed_dec_x[],float speed_dec_y[],bool speed_dec_exist[],int& speed_dec_count,Sprite speed_dec_sprite[],float height_inc_x[],float height_inc_y[],bool height_inc_exist[],int& height_inc_count,Sprite height_inc_sprite[],float height_dec_x[],float height_dec_y[],bool height_dec_exist[],int& height_dec_count,Sprite height_dec_sprite[],bool& target_reached,int& bird_hit) 
{
   // Activatating the  bees
   activateBees(bee_alive, remaining_bees_count, activationClock, activationIntervals, numBees);    activate_Killerbees(KillerBee_alive, killer_bees_count, activationClock, killer_activationIntervals, killerBees);

    // Moving and collision of simple and killer bees
    for (int i = 0; i < numBees; ++i) 
    {
     if (bee_alive[i]) // Only moving and colliding the alive bees
     {//moveBees and collision function
      moveBees(bees_x[i], bees_y[i], beesClocks[i], direction_right[i], pollination_count, bee_alive, i, pollination_exists, pollination_num, honey_x, honey_y, numBees, honey_exist, horizontalShift,extra_combs,pollination_x,first_left ,first_right,beehives_x,beehives_y,beehives_exist, hive_found,hive_count,red_honey_x,red_honey_y, red_honey_exist, killerBees,max_beehives);
      collision(bees_x[i], bees_y[i], bullet_x, bullet_y,bullet_exists, bee_alive[i], collisionSound,honey_x, honey_y, honey_exist, i,score, scoreText, bird_x, bird_y, numBees,collision_honeySound, extra_combs,killerBees,red_honey_x, red_honey_y, red_honey_exist,        speed_inc_x,speed_inc_y,speed_inc_exist,speed_inc_count,speed_inc_sprite,speed_dec_x,speed_dec_y, speed_dec_exist,speed_dec_count,speed_dec_sprite,height_inc_x,height_inc_y,height_inc_exist,height_inc_count,
height_inc_sprite,height_dec_x,height_dec_y,height_dec_exist,height_dec_count, height_dec_sprite,beehives_x,beehives_y, beehives_exist,hive_found, hive_count,max_beehives,boss_level, bird_hit, bird_exists);
     }
     if (i < killerBees ) //Moving and colliding the killer bees by first checking that i is less than the number of killer bees as it was giving segmentation erros
     {
     //Killer collison and Killer move function
      killer_collision(killerBees_x[i],killerBees_y[i],KillerBeesClock,killer_bees_count,killerBeesSprites,
      KillerBee_alive[i],killerBees,killer_activationIntervals, killer_speed, bullet_x,bullet_y,bullet_exists,
      collisionSound,score,scoreText,collision_honeySound,i,red_honey_x,red_honey_y,red_honey_exist,
      boss_level,speed_inc_x,speed_inc_y,speed_inc_exist,speed_inc_count,speed_inc_sprite,speed_dec_x,speed_dec_y,  speed_dec_exist,speed_dec_count,speed_dec_sprite,height_inc_x,height_inc_y,height_inc_exist,height_inc_count,
height_inc_sprite,height_dec_x,height_dec_y,height_dec_exist,height_dec_count, height_dec_sprite);
     if(KillerBee_alive[i])
      {
       move_Killerbees(killerBees_x[i], killerBees_y[i], KillerBeesClock[i], direction_right_killer[i], pollination_count, KillerBee_alive, pollination_exists, pollination_num, killerBees, killer_speed, i,pollination_x,first_left ,first_right);
      }
     }        
   }

    // Drawing all the sprites
    drawBird(window, bird_x, bird_y, birdSprite, bird_exists);
    drawBees(window, beesSprites, bees_x, bees_y, direction_right, bee_alive, numBees);
    draw_Killerbees(window, killerBeesSprites, killerBees_x, killerBees_y, direction_right_killer, KillerBee_alive, killerBees);
    drawHoney(window, honey_x, honey_y, honey_exist, numBees, honeySprites, extra_combs,red_honey_x, red_honey_y,red_honey_exist,killerBees,red_honeySprites);
    drawBeehives(window,beehives_x,beehives_y,beehives_exist, hive_count, beehivesSprites,max_beehives);
    drawPollination(window, pollination_exists, pollination_num, pollinationSprites, pollination_count, pollination_x, pollination_y);
    drawFixedPlayer(window, fixed_player_x, fixed_player_y, fixed_player_exist, fixed_playerSprites, count_bullet);

    // Checking conditions to exit level 2
    if (count_bullet >= 158) //If bullet gets emptied
    {level++;
    return;
    }
    //If all bees has been spawned and they have died
    if ((remaining_bees_count >= numBees) && killer_bees_count >= killerBees)
    {
     all_bees_spawned = true;
    } 
    any_bee_alive = false;
    for (int i = 0; i < numBees; ++i) {
        if (bee_alive[i] )
           { any_bee_alive = true;
            break;
        }
    }
    for (int i = 0; i < killerBees; ++i) 
    {
     if (KillerBee_alive[i] )
     {
      any_bee_alive = true;
      break;
     }
    }
  if (!any_bee_alive && all_bees_spawned)
    {level++; // incrementing the level so it moves to the next level
     return;
    } 
}


// Level 3 Logic
void level_3(RenderWindow& window, Sprite beesSprites[], Clock beesClocks[], float bees_x[], float bees_y[], bool direction_right[], bool bee_alive[], int numBees, float bullet_x, float bullet_y, bool& bullet_exists, Sound& collisionSound, float honey_x[], float honey_y[], bool honey_exist[], Sprite honeySprites[], int& score, Text& scoreText, bool pollination_exists[], const int pollination_num, Sprite pollinationSprites[], int& pollination_count, float pollination_x[], float& pollination_y, bool& pollination_direction, float& bird_x, float& bird_y, bool& bird_exists, Clock birdClock, Sprite birdSprite, bool& bird_moved, float& bird_speed, float& target_x, float& target_y, float fixed_player_x[], float fixed_player_y[], bool fixed_player_exist[], Sprite fixed_playerSprites[], int& count_bullet, int& remaining_bees_count, Clock remaining_beesClocks, bool& all_bees_spawned, bool& any_bee_alive, Sound& collision_honeySound, int horizontalShift, int extra_combs, Clock spawnBees, Clock& activationClock, int activationIntervals[], float killerBees_x[], float killerBees_y[], Clock KillerBeesClock[], bool direction_right_killer[], int& killer_bees_count, Sprite killerBeesSprites[], bool KillerBee_alive[], int& killerBees, int killer_activationIntervals[], int& killer_speed,float red_honey_x[],float red_honey_y[],bool red_honey_exist[],Sprite red_honeySprites[],int& level,bool& gameStarted,bool& first_left ,bool& first_right, float beehives_x[],float beehives_y[],bool beehives_exist[],bool& hive_found,int& hive_count,Sprite beehivesSprites[],bool& boss_level,int& max_beehives,float speed_inc_x[],float speed_inc_y[],bool speed_inc_exist[],int& speed_inc_count,Sprite speed_inc_sprite[],float speed_dec_x[],float speed_dec_y[],bool speed_dec_exist[],int& speed_dec_count,Sprite speed_dec_sprite[],float height_inc_x[],float height_inc_y[],bool height_inc_exist[],int& height_inc_count,Sprite height_inc_sprite[],float height_dec_x[],float height_dec_y[],bool height_dec_exist[],int& height_dec_count,Sprite height_dec_sprite[],bool& target_reached,int& bird_hit) 
{

    // Activatating bees
    activateBees(bee_alive, remaining_bees_count, activationClock, activationIntervals, numBees);
    activate_Killerbees(KillerBee_alive, killer_bees_count, activationClock, killer_activationIntervals, killerBees);

    // Move and handle collisions for bees and killer bees
    for (int i = 0; i < numBees; ++i) 
    {
     if (bee_alive[i]) 
     {
      moveBees(bees_x[i], bees_y[i], beesClocks[i], direction_right[i], pollination_count, bee_alive, i, pollination_exists, pollination_num, honey_x, honey_y, numBees, honey_exist, horizontalShift,extra_combs,pollination_x,first_left,first_right,beehives_x,beehives_y,beehives_exist, hive_found,hive_count,red_honey_x,red_honey_y, red_honey_exist, killerBees,max_beehives);
      collision(bees_x[i], bees_y[i], bullet_x, bullet_y,bullet_exists, bee_alive[i], collisionSound,honey_x, honey_y, honey_exist, i,score, scoreText, bird_x, bird_y, numBees,collision_honeySound, extra_combs,killerBees,red_honey_x, red_honey_y, red_honey_exist,        speed_inc_x,speed_inc_y,speed_inc_exist,speed_inc_count,speed_inc_sprite,speed_dec_x,speed_dec_y, speed_dec_exist,speed_dec_count,speed_dec_sprite,height_inc_x,height_inc_y,height_inc_exist,height_inc_count,
height_inc_sprite,height_dec_x,height_dec_y,height_dec_exist,height_dec_count, height_dec_sprite,beehives_x,beehives_y, beehives_exist,hive_found, hive_count,max_beehives,boss_level, bird_hit,bird_exists);
        }
        //Checking collision of killer bees
        if (i < killerBees ) 
        {
         killer_collision(killerBees_x[i],killerBees_y[i],KillerBeesClock, killer_bees_count,killerBeesSprites,KillerBee_alive[i],killerBees,killer_activationIntervals, killer_speed, bullet_x,bullet_y,bullet_exists,collisionSound,score,scoreText,collision_honeySound,i,red_honey_x, red_honey_y,red_honey_exist,boss_level,speed_inc_x,speed_inc_y,speed_inc_exist,speed_inc_count,speed_inc_sprite,
speed_dec_x,speed_dec_y,speed_dec_exist,speed_dec_count,speed_dec_sprite,height_inc_x,height_inc_y,height_inc_exist,
height_inc_count,height_inc_sprite,height_dec_x,height_dec_y,height_dec_exist,height_dec_count, height_dec_sprite);
         
         if(KillerBee_alive[i])
         {
          move_Killerbees(killerBees_x[i], killerBees_y[i], KillerBeesClock[i], direction_right_killer[i], pollination_count, KillerBee_alive, pollination_exists, pollination_num, killerBees, killer_speed, i,pollination_x,first_left ,first_right);
        }
      }        
    }

    // Drawing all the sprites
     drawBird(window, bird_x, bird_y, birdSprite, bird_exists);
    drawBees(window, beesSprites, bees_x, bees_y, direction_right, bee_alive, numBees);
    draw_Killerbees(window, killerBeesSprites, killerBees_x, killerBees_y, direction_right_killer, KillerBee_alive, killerBees);
    drawHoney(window, honey_x, honey_y, honey_exist, numBees, honeySprites, extra_combs,red_honey_x, red_honey_y,red_honey_exist,killerBees,red_honeySprites);
    drawBeehives(window,beehives_x,beehives_y,beehives_exist, hive_count,beehivesSprites,max_beehives);
    drawPollination(window, pollination_exists, pollination_num, pollinationSprites, pollination_count, pollination_x, pollination_y);
    drawFixedPlayer(window, fixed_player_x, fixed_player_y, fixed_player_exist, fixed_playerSprites, count_bullet);

    // Check conditions to exit level
    if (count_bullet >= 158) 
    {level++;
    return;
    }
    
    if ((remaining_bees_count >= numBees) && killer_bees_count >= killerBees)
    {
     all_bees_spawned = true;
    } 
    any_bee_alive = false;
    for (int i = 0; i < numBees; ++i) 
    {
     if (bee_alive[i] )
     { any_bee_alive = true;
        break;
     }
    }
    for (int i = 0; i < killerBees; ++i) 
    {
     if (KillerBee_alive[i] )
     {
      any_bee_alive = true;
      break;
     }
    }    
    if (!any_bee_alive && all_bees_spawned)
    {level++;
     return;
    } 
}


//Adding the player in the file
void addPlayer(const string& filename, string& name , int& score) 
{// Opening the file in append mode and adding the name
 ofstream myfile(filename, ios::app); // 
    if (myfile.is_open()) 
    {
     myfile << name << " " << score << endl; 
     myfile.close();
    } 
    else 
    {
     cout << "Error opening the file!" << endl;
    }
}
// Declearing function for displaying highest scores

void showHighScore(sf::RenderWindow& window, const std::string& fileName, sf::Font& font)
 {
  // Declearing variables to store name of players
  const int maxPlayers = 10; // Maximum number of players to keep
  string tempNames[100];     
  int tempScores[100];       
  int tempCount = 0;         
  // Reading data of all players from the file and storing in both arrays respectively
    ifstream myfile(fileName);
    if (!myfile.is_open()) 
    {
     cout << "Error! File is not opening." << endl;
     return;
    }

    while (myfile >> tempNames[tempCount] >> tempScores[tempCount]) 
    {
     tempCount++; // counting number of names so can be handled appropriately 
    }
    myfile.close();

    // Sorting players in ascending order by scores using nested for loops and swapping the data
    for (int i = 0; i < tempCount - 1; i++) 
    {
     for (int j = i + 1; j < tempCount; j++) 
     {
      if (tempScores[i] > tempScores[j]) 
      {
       int tempScore = tempScores[i];
       tempScores[i] = tempScores[j];
       tempScores[j] = tempScore;

       string tempName = tempNames[i];
       tempNames[i] = tempNames[j];
       tempNames[j] = tempName;
      }
    }
   }

   // Than storing the name of top 10 players in array of 10 so rest gets discarded this way
    string playerNames[maxPlayers];
    int playerScores[maxPlayers];
    int count = 0;

    for (int i = tempCount - 1; i >= tempCount - maxPlayers && i >= 0; i--) 
    {
     playerNames[count] = tempNames[i];
     playerScores[count] = tempScores[i];
     count++;
    }

    // Write only the top 10 players back to the file in ascending order
    ofstream outFile(fileName);
    if (!outFile.is_open()) 
    {
     cout << "Error! File is not opening for writing." << endl;
     return;
    }
    for (int i = count - 1; i >= 0; i--) 
    {
     outFile << playerNames[i] << " " << playerScores[i] << endl;
    }
    outFile.close();

    // Display leaderboard in descending order
    int y_position = 150; 

    // Displaying heading of leaderboard on screen of game
    sf::Text l_text;
    l_text.setFont(font);
    l_text.setString("LEADERBOARD");
    l_text.setCharacterSize(70);
    l_text.setFillColor(sf::Color::Red);
    l_text.setStyle(sf::Text::Bold);
    l_text.setPosition(260, 80);
    window.draw(l_text);

    // Display names  and scores of top 10 players on the screen
    for (int i = 0; i < count; i++) 
    {
     sf::Text text;
     text.setFont(font);
     text.setString(playerNames[i] + " \t \t " + to_string(playerScores[i]));
     text.setCharacterSize(30);
     text.setFillColor(sf::Color::Yellow);
     text.setPosition(300, y_position);

     window.draw(text);
     y_position += 40; // Increment vertical position
    }

    window.display();
}


// Declearing boss level function
void bossLevel(RenderWindow& window, Sprite beesSprites[], Clock beesClocks[], float bees_x[], float bees_y[], bool direction_right[], bool bee_alive[], int numBees, float bullet_x, float bullet_y, bool& bullet_exists, Sound& collisionSound, float honey_x[], float honey_y[], bool honey_exist[], Sprite honeySprites[], int& score, Text& scoreText, bool pollination_exists_arr[], const int pollination_num, Sprite pollinationSprites[], int& pollination_count, float pollination_x[], float& pollination_y, bool& pollination_direction, float& bird_x, float& bird_y, bool& bird_exists, Clock birdClock, Sprite birdSprite, bool& bird_moved, float& bird_speed, float& target_x, float& target_y, float fixed_player_x[], float fixed_player_y[], bool fixed_player_exist[], Sprite fixed_playerSprites[], int& count_bullet, int& remaining_bees_count, Clock remaining_beesClocks, bool& all_bees_spawned, bool& any_bee_alive, Sound& collision_honeySound, int horizontalShift, int extra_combs, Clock spawnBees, Clock& activationClock, int activationIntervals[], float killerBees_x[], float killerBees_y[], Clock KillerBeesClock[], bool direction_right_killer[], int& killer_bees_count, Sprite killerBeesSprites[], bool KillerBee_alive[], int& killerBees, int killer_activationIntervals[], int& killer_speed, float red_honey_x[], float red_honey_y[], bool red_honey_exist[], Sprite red_honeySprites[], int& level, bool& gameStarted, bool& first_left, bool& first_right, float beehives_x[], float beehives_y[], bool beehives_exist[], bool& hive_found, int& hive_count, Sprite beehivesSprites[], float& player_move, bool& boss_level, float& left_boundary, float& right_boundary, float& extra_hives, Texture killerTexture, Texture honeyTexture, Texture beesTexture, bool& initialise_boss_level, int& max_beehives, float speed_inc_x[], float speed_inc_y[], bool speed_inc_exist[], int& speed_inc_count, Sprite speed_inc_sprite[], float speed_dec_x[], float speed_dec_y[], bool speed_dec_exist[], int& speed_dec_count, Sprite speed_dec_sprite[], float height_inc_x[], float height_inc_y[], bool height_inc_exist[], int& height_inc_count, Sprite height_inc_sprite[], float height_dec_x[], float height_dec_y[], bool height_dec_exist[], int& height_dec_count, Sprite height_dec_sprite[], int& max_comparisons, float& orignal_speed, float& orignal_height, float& player_height, bool& s_inc_activated, bool& s_dec_activated, bool& h_inc_activated, bool& h_dec_activated,bool& target_reached,int& bird_hit) 

{ 
  // Firstly initialising the elements for boss level
   if(initialise_boss_level == false)
    {initialise_boss_level = true;
     // Setting parameters for Level 4
                        
            // Set parameters for Level 4
            remaining_bees_count = 0; 
            numBees = 20; 
            extra_combs = 15;
            horizontalShift = 4;
            killerBees = 10;
            extra_hives = 5;

            // Initialize honeycombs for Level 4
            for (int i = 0; i < numBees + extra_combs; ++i) 
            {
             honeySprites[i].setTexture(honeyTexture);
            }
            // Randomly place 15 honeycombs initially for Level 4
            for (int i = 0; i < extra_combs; ++i) {
                honey_x[i] = rand() % resolutionX;
                honey_y[i] = rand() % (resolutionY / 2);
                honey_exist[i] = true; 
            }
            
           for (int i = 0; i < 5; ++i) { // Initialize 5 beehives pregenerated for level 5
            beehives_x[i] = rand() % resolutionX;
            beehives_y[i] = rand() % (resolutionY / 2);
            beehives_exist[i] = true;
            beehivesSprites[i].setPosition(beehives_x[i], beehives_y[i]);
          }
            // Preparing the bees for Level 4
              for (int i = 0; i < numBees; ++i) 
              {
               bees_x[i] = (i % 10) * 100; 
               bees_y[i] = 0;              
               direction_right[i] = (i % 2 == 0);
               beesSprites[i].setTexture(beesTexture);
               beesSprites[i].setScale(1, 1);
               activationIntervals[i] = (rand() % 3); 
               bee_alive[i] = false; 
              }
          
            // Preparing killer bees for level 4
             for (int i = 0; i < killerBees; ++i) {
             killerBees_x[i] = (i % 10) * 100; 
             killerBees_y[i] = 0;              
             direction_right_killer[i] = (i % 2 == 0); 
             killerBeesSprites[i].setTexture(killerTexture);
             killerBeesSprites[i].setScale(1, 1);
             killer_activationIntervals[i] = 1 + (rand() % 3); 
             KillerBee_alive[i] = false; 
             }
          }

  // Executing boss level function
    //Activating the bees
    activateBees(bee_alive, remaining_bees_count, activationClock, activationIntervals, numBees);
    activate_Killerbees(KillerBee_alive, killer_bees_count, activationClock, killer_activationIntervals, killerBees);

   // Move and handle collisions for bees and killer bees
   for (int i = 0; i < numBees; ++i) 
   {
    if (bee_alive[i]) 
    {//Move bees
     moveBees(bees_x[i], bees_y[i], beesClocks[i], direction_right[i], pollination_count, bee_alive, i, pollination_exists_arr, pollination_num, honey_x, honey_y, numBees, honey_exist, horizontalShift,extra_combs,pollination_x,first_left,first_right,beehives_x,beehives_y,beehives_exist, hive_found,hive_count,red_honey_x,red_honey_y, red_honey_exist, killerBees,max_beehives);
     //Collision os simple bees
     collision(bees_x[i], bees_y[i], bullet_x, bullet_y,bullet_exists, bee_alive[i], collisionSound,honey_x, honey_y, honey_exist, i,score, scoreText, bird_x, bird_y, numBees,collision_honeySound, extra_combs,killerBees,red_honey_x, red_honey_y,red_honey_exist,speed_inc_x,speed_inc_y,speed_inc_exist,
speed_inc_count,speed_inc_sprite,speed_dec_x,speed_dec_y,speed_dec_exist,speed_dec_count,speed_dec_sprite,
height_inc_x,height_inc_y,height_inc_exist,height_inc_count,height_inc_sprite,height_dec_x,height_dec_y,
height_dec_exist,height_dec_count, height_dec_sprite,beehives_x,beehives_y, beehives_exist,hive_found, hive_count,max_beehives,boss_level,bird_hit,bird_exists );
       //Collision of bullet with power
       powers_collision(window,speed_inc_x,speed_inc_y, speed_inc_exist,speed_inc_count,speed_inc_sprite,speed_dec_x,speed_dec_y, speed_dec_exist,speed_dec_count,speed_dec_sprite,height_inc_x,height_inc_y, height_inc_exist,height_inc_count,height_inc_sprite,height_dec_x,height_dec_y, height_dec_exist,height_dec_count,height_dec_sprite,collisionSound, s_inc_activated,s_dec_activated,h_inc_activated,h_dec_activated,bullet_x,bullet_y,bullet_exists,player_move, player_height);
}
   // Checking for killer bees collisons
   if (i < killerBees ) 
   {
    killer_collision(killerBees_x[i],killerBees_y[i],KillerBeesClock, killer_bees_count,killerBeesSprites,KillerBee_alive[i],killerBees,killer_activationIntervals, killer_speed, bullet_x,bullet_y,bullet_exists,collisionSound,score,scoreText,collision_honeySound,i,red_honey_x, red_honey_y,red_honey_exist,boss_level,speed_inc_x,speed_inc_y,speed_inc_exist,speed_inc_count,speed_inc_sprite,speed_dec_x,speed_dec_y, speed_dec_exist,speed_dec_count,speed_dec_sprite,height_inc_x,height_inc_y,height_inc_exist,height_inc_count,
height_inc_sprite,height_dec_x,height_dec_y,height_dec_exist,height_dec_count, height_dec_sprite);
    if(KillerBee_alive[i]) // moving killer bees if they are active
     {
            move_Killerbees(killerBees_x[i], killerBees_y[i], KillerBeesClock[i], direction_right_killer[i], pollination_count, KillerBee_alive, pollination_exists_arr, pollination_num, killerBees, killer_speed, i,pollination_x,first_left ,first_right);
      } 
     }         
   }

  // Drawing all the sprites
    drawBird(window, bird_x, bird_y, birdSprite, bird_exists);
    drawBees(window, beesSprites, bees_x, bees_y, direction_right, bee_alive, numBees);
    draw_Killerbees(window, killerBeesSprites, killerBees_x, killerBees_y, direction_right_killer, KillerBee_alive, killerBees);
    drawHoney(window, honey_x, honey_y, honey_exist, numBees, honeySprites, extra_combs,red_honey_x, red_honey_y,red_honey_exist,killerBees,red_honeySprites);
    drawBeehives(window,beehives_x,beehives_y,beehives_exist, hive_count,beehivesSprites,max_beehives);
    drawPollination(window, pollination_exists_arr, pollination_num, pollinationSprites, pollination_count, pollination_x, pollination_y);
    drawFixedPlayer(window, fixed_player_x, fixed_player_y, fixed_player_exist, fixed_playerSprites, count_bullet);
    draw_heightInc(window,height_inc_x,height_inc_y, height_inc_exist,height_inc_count,height_inc_sprite);
    draw_heightDec(window,height_dec_x,height_dec_y, height_dec_exist,height_dec_count,height_dec_sprite); 
    draw_speedDec(window,speed_dec_x,speed_dec_y,speed_dec_exist, speed_dec_count,speed_dec_sprite);
    draw_speedInc(window,speed_inc_x,speed_inc_y,speed_inc_exist, speed_inc_count,speed_inc_sprite);      

    // Checking conditions to exit level
    if (count_bullet >= 158) //If bullet gets finished
    {level++;// incrementing the level so game can end
    return;
    }
    
    if ((remaining_bees_count >= numBees) && killer_bees_count >= killerBees)
    {
     all_bees_spawned = true;
    } 
    any_bee_alive = false;
    for (int i = 0; i < numBees; ++i) 
    {
     if (bee_alive[i] )
     {
      any_bee_alive = true;
      break;
     }
    }
    for (int i = 0; i < killerBees; ++i) 
    {
     if (KillerBee_alive[i] )
     {
      any_bee_alive = true;
      break;
     }
    }

    if (!any_bee_alive && all_bees_spawned)
    {level++; // incrementing the level so game can end
     return;
    } 
}





