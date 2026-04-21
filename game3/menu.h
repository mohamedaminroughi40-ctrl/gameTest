#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "game.h"  // Add this

using namespace std;
using namespace sf;

enum MenuState
{
    MAIN_MENU,
    OPTIONS_MENU,
    LEVEL_SELECT,
    GAME_PLAY
};

class Menu
{
private:
    // Window properties
    float windowWidth;
    float windowHeight;

    // Menu state
    MenuState currentState;
    int selectedIndex;
    int selectedLevel;

    // Fonts and sounds
    Font font;
    Music music;
    SoundBuffer buffer;
    Sound sound;

    // Backgrounds
    Texture bgTexture1, bgTexture2;
    Sprite backgroundMain, backgroundOptions;

    // Main menu
    RectangleShape buttons[3];
    Text menu[3];

    // Options menu
    Text optionsTitle;
    Text volumeText;
    Text volumeValue;
    RectangleShape volumeSlider;
    RectangleShape volumeKnob;
    RectangleShape backButtonRect;
    Text backButton;
    float volumeLevel;
    bool isDraggingKnob;

    // Level select
    Text levelTitle;
    Texture levelTextures[3];
    Sprite levelSprites[3];
    RectangleShape levelBoxes[3];
    Text levelTexts[3];
    bool levelHover[3];
    RectangleShape levelBackButton;
    Text levelBackText;

    // Game
    game* currentGame;
    RenderWindow* mainWindow;  // Add this
    View gameView;
    float cameraX;

    // Test game (for menu preview)
    RectangleShape testPlayer;
    Vector2f testPlayerVelocity;
    float testPlayerSpeed;
    bool gameRunning;

public:
    Menu(float width, float height, RenderWindow* window);  // Update signature
    ~Menu();  // Add destructor
    
    void updateVolume();
    void updateGame(float deltaTime);
    void updateCurrentGame(float deltaTime);  // Add this for real game
    void update(float deltaTime);

    void moveUp();
    void moveDown();

    int getSelectedIndex();
    MenuState getCurrentState();  // Add this
    void setCurrentState(MenuState state);  // Add this

    void handleMouseMainMenu(RenderWindow& window);
    void handleMouseOptions(RenderWindow& window, Event& event);
    void handleInput(RenderWindow& window, Event& event);

    void draw(RenderWindow& window);
};

#endif