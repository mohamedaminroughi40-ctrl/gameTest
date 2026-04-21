#include "Menu.h"

using namespace sf;

Menu::Menu(float width, float height, RenderWindow* window)
{
    windowWidth = width;
    windowHeight = height;
    mainWindow = window;
    currentGame = nullptr;
    
    currentState = MAIN_MENU;
    isDraggingKnob = false;
    volumeLevel = 50.0f;
    selectedLevel = -1;

    // Load font
    if (!font.loadFromFile("assets/ARCADE.ttf"))
    {
        cout << "Error loading font!" << endl;
    }

    // Load and play music
    if (music.openFromFile("assets/sound/mixkit-love-787.mp3"))
    {
        music.setLoop(true);
        music.setVolume(volumeLevel);
        music.play();
    }

    // Load background textures
    if (!bgTexture1.loadFromFile("assets/bg1.png"))
    {
        cout << "Error loading bg1.png!" << endl;
    }
    if (!bgTexture2.loadFromFile("assets/bg2.png"))
    {
        cout << "Error loading bg2.png!" << endl;
    }

    // Setup main menu background (just the first background)
    backgroundMain.setTexture(bgTexture1);
    Vector2u textureSize1 = bgTexture1.getSize();
    float scaleX1 = width / textureSize1.x;
    float scaleY1 = height / textureSize1.y;
    backgroundMain.setScale(scaleX1, scaleY1);
    backgroundMain.setPosition(0, 0);

    // Setup options menu background (second background)
    backgroundOptions.setTexture(bgTexture2);
    Vector2u textureSize2 = bgTexture2.getSize();
    float scaleX2 = width / textureSize2.x;
    float scaleY2 = height / textureSize2.y;
    backgroundOptions.setScale(scaleX2, scaleY2);
    backgroundOptions.setPosition(0, 0);
        
    // Load sound
    if (!buffer.loadFromFile("assets/sound/mixkit.wav"))
    {
        cout << "Error loading sound!" << endl;
    }
    sound.setBuffer(buffer);

    // ===== MAIN MENU SETUP =====
    string options[3] = { "Play", "Options", "Exit" };
    float buttonWidth = width / 4;
    float buttonHeight = height / 10;

    for (int i = 0; i < 3; i++)
    {
        // Setup buttons
        buttons[i].setSize(Vector2f(buttonWidth, buttonHeight));
        buttons[i].setFillColor(Color(100, 100, 100, 200));
        buttons[i].setOutlineColor(Color::White);
        buttons[i].setOutlineThickness(2);
        buttons[i].setPosition(
            width / 2 - buttonWidth / 2,
            height / 2 + i * (height / 6) - buttonHeight / 2
        );

        // Setup text
        menu[i].setFont(font);
        menu[i].setString(options[i]);
        menu[i].setCharacterSize(height / 15);
        menu[i].setFillColor(Color::White);

        // Center text
        FloatRect textRect = menu[i].getLocalBounds();
        menu[i].setOrigin(textRect.left + textRect.width / 2.0f,
            textRect.top + textRect.height / 2.0f);
        menu[i].setPosition(
            width / 2,
            height / 2 + i * (height / 6)
        );
    }

    selectedIndex = 0;
    menu[selectedIndex].setFillColor(Color::Yellow);
    buttons[selectedIndex].setFillColor(Color(150, 150, 50, 200));

    // ===== OPTIONS MENU SETUP =====

    // Title with background panel for visibility
    optionsTitle.setFont(font);
    optionsTitle.setString("OPTIONS");
    optionsTitle.setCharacterSize(height / 10);
    optionsTitle.setFillColor(Color::Yellow);
    optionsTitle.setOutlineColor(Color::Black);
    optionsTitle.setOutlineThickness(3);
    FloatRect titleRect = optionsTitle.getLocalBounds();
    optionsTitle.setOrigin(titleRect.left + titleRect.width / 2.0f,
        titleRect.top + titleRect.height / 2.0f);
    optionsTitle.setPosition(width / 2, height / 6);

    // Volume text
    volumeText.setFont(font);
    volumeText.setString("VOLUME");
    volumeText.setCharacterSize(height / 20);
    volumeText.setFillColor(Color::White);
    volumeText.setOutlineColor(Color::Black);
    volumeText.setOutlineThickness(2);
    volumeText.setPosition(width / 3, height / 3);

    // Volume value display
    volumeValue.setFont(font);
    volumeValue.setCharacterSize(height / 20);
    volumeValue.setFillColor(Color::Yellow);
    volumeValue.setOutlineColor(Color::Black);
    volumeValue.setOutlineThickness(2);
    updateVolume();

    // Volume slider background
    float sliderWidth = width / 3;
    float sliderHeight = height / 30;
    volumeSlider.setSize(Vector2f(sliderWidth, sliderHeight));
    volumeSlider.setFillColor(Color(80, 80, 80, 200));
    volumeSlider.setOutlineColor(Color::White);
    volumeSlider.setOutlineThickness(2);
    volumeSlider.setPosition(width / 3, height / 3 + height / 15);

    // Volume knob
    float knobWidth = height / 20;
    float knobHeight = height / 15;
    volumeKnob.setSize(Vector2f(knobWidth, knobHeight));
    volumeKnob.setFillColor(Color::Yellow);
    volumeKnob.setOrigin(knobWidth / 2, knobHeight / 2);

    // Update knob position based on volume
    float knobX = volumeSlider.getPosition().x + (volumeLevel / 100.0f) * sliderWidth;
    volumeKnob.setPosition(knobX, volumeSlider.getPosition().y + sliderHeight / 2);

    // Back button for options
    float backWidth = width / 5;
    float backHeight = height / 12;
    backButtonRect.setSize(Vector2f(backWidth, backHeight));
    backButtonRect.setFillColor(Color(100, 100, 100, 200));
    backButtonRect.setOutlineColor(Color::White);
    backButtonRect.setOutlineThickness(2);
    backButtonRect.setPosition(width / 2 - backWidth / 2, height * 3 / 4);

    backButton.setFont(font);
    backButton.setString("BACK TO MENU");
    backButton.setCharacterSize(height / 25);
    backButton.setFillColor(Color::White);
    backButton.setOutlineColor(Color::Black);
    backButton.setOutlineThickness(2);

    // Center back button text
    FloatRect backTextRect = backButton.getLocalBounds();
    backButton.setOrigin(backTextRect.left + backTextRect.width / 2.0f,
        backTextRect.top + backTextRect.height / 2.0f);
    backButton.setPosition(width / 2, height * 3 / 4 + backHeight / 2);

    // ===== LEVEL SELECT MENU SETUP =====
    // 
    // Title
    levelTitle.setFont(font);
    levelTitle.setString("SELECT LEVEL");
    levelTitle.setCharacterSize(height / 10);
    levelTitle.setFillColor(Color::Yellow);
    levelTitle.setOutlineColor(Color::Black);
    levelTitle.setOutlineThickness(3);
    FloatRect levelTitleRect = levelTitle.getLocalBounds();
    levelTitle.setOrigin(levelTitleRect.left + levelTitleRect.width / 2.0f,
        levelTitleRect.top + levelTitleRect.height / 2.0f);
    levelTitle.setPosition(width / 2, height / 6);

    // Level boxes (3 squares next to each other)
    float boxSize = height / 3; // Square size
    float spacing = (width - (boxSize * 3)) / 4; // Space between boxes

    // Load level images
    if (!levelTextures[0].loadFromFile("assets/Backgrounds/PNG/summer6/Summer6.png"))
        cout << "Error loading level1.png!" << endl;
    if (!levelTextures[1].loadFromFile("assets/Backgrounds/PNG/summer5/Summer5.png"))
        cout << "Error loading level2.png!" << endl;
    if (!levelTextures[2].loadFromFile("assets/Backgrounds/PNG/summer 1/Summer1.png"))
        cout << "Error loading level3.png!" << endl;


    for (int i = 0; i < 3; i++)
    {
        // Create square box
        levelBoxes[i].setSize(Vector2f(boxSize, boxSize));
        levelBoxes[i].setFillColor(Color(100, 100, 100, 200));
        levelBoxes[i].setOutlineColor(Color::White);
        levelBoxes[i].setOutlineThickness(3);
        levelBoxes[i].setPosition(
            spacing + (boxSize + spacing) * i,
            height / 2 - boxSize / 2
        );

        // Setup level images inside boxes

        levelSprites[i].setTexture(levelTextures[i]);

        // Scale image to fit inside box with margin

        float imageSize = boxSize - 60; // 30px margin on each side
        Vector2u textureSize = levelTextures[i].getSize();
        float scaleX = imageSize / textureSize.x;
        float scaleY = imageSize / textureSize.y;
        levelSprites[i].setScale(scaleX, scaleY);

        // Center image in the box
        float imageX = levelBoxes[i].getPosition().x + (boxSize / 2) - (imageSize / 2);
        float imageY = levelBoxes[i].getPosition().y + (boxSize / 2) - (imageSize / 2);
        levelSprites[i].setPosition(imageX, imageY);

        // Level text (LEVEL 1, LEVEL 2, LEVEL 3)
        levelTexts[i].setFont(font);
        string levelNum = "LEVEL " + to_string(i + 1);
        levelTexts[i].setString(levelNum);
        levelTexts[i].setCharacterSize(height / 25);
        levelTexts[i].setFillColor(Color::White);
        levelTexts[i].setOutlineColor(Color::Black);
        levelTexts[i].setOutlineThickness(2);

        // Center text under the box
        FloatRect textRect = levelTexts[i].getLocalBounds();
        levelTexts[i].setOrigin(textRect.left + textRect.width / 2.0f,
            textRect.top + textRect.height / 2.0f);
        levelTexts[i].setPosition(
            spacing + (boxSize + spacing) * i + boxSize / 2,
            height / 2 + boxSize / 2 + 40
        );

        levelHover[i] = false;
    }

    // Level select back button
    levelBackButton.setSize(Vector2f(backWidth, backHeight));
    levelBackButton.setFillColor(Color(100, 100, 100, 200));
    levelBackButton.setOutlineColor(Color::White);
    levelBackButton.setOutlineThickness(2);
    levelBackButton.setPosition(width / 2 - backWidth / 2, height * 3 / 4);

    levelBackText.setFont(font);
    levelBackText.setString("BACK TO MENU");
    levelBackText.setCharacterSize(height / 25);
    levelBackText.setFillColor(Color::White);
    levelBackText.setOutlineColor(Color::Black);
    levelBackText.setOutlineThickness(2);
    backTextRect = levelBackText.getLocalBounds();
    levelBackText.setOrigin(backTextRect.left + backTextRect.width / 2.0f,
        backTextRect.top + backTextRect.height / 2.0f);
    levelBackText.setPosition(width / 2, height * 3 / 4 + backHeight / 2);

    // Game play setuup ( just a test )
    testPlayer.setSize(Vector2f(50, 50));
    testPlayer.setFillColor(Color::Green);
    testPlayer.setPosition(width / 2, height - 100);
    testPlayerSpeed = 300.f;
    testPlayerVelocity = Vector2f(0, 0);
    gameRunning = true;

    gameView.reset(FloatRect(0, 0, width, height));
    cameraX = 0;

}


void Menu::updateVolume()
{
    stringstream ss;
    ss << fixed << setprecision(0) << volumeLevel << "%";
    volumeValue.setString(ss.str());

    // Position volume value text next to slider
    FloatRect valueRect = volumeValue.getLocalBounds();
    volumeValue.setPosition(
        volumeSlider.getPosition().x + volumeSlider.getSize().x + 20,
        volumeSlider.getPosition().y + volumeSlider.getSize().y / 2 - valueRect.height / 2
    );

    // Update music volume
    music.setVolume(volumeLevel);
}

void Menu::updateGame(float deltaTime)
{
    if (!gameRunning) return;

    testPlayer.move(testPlayerVelocity * deltaTime);

    // Keep player inside window vertically
    if (testPlayer.getPosition().y < 0)
        testPlayer.setPosition(testPlayer.getPosition().x, 0);
    if (testPlayer.getPosition().y > backgroundMain.getGlobalBounds().height - testPlayer.getSize().y)
        testPlayer.setPosition(testPlayer.getPosition().x,
            backgroundMain.getGlobalBounds().height - testPlayer.getSize().y);

    cameraX = testPlayer.getPosition().x + testPlayer.getPosition().x / 2 - gameView.getSize().x / 2;
    if (cameraX < 0) cameraX = 0; // i do this case to not go left side

    gameView.setCenter(cameraX + gameView.getSize().x / 2, gameView.getSize().y / 2);

}



void Menu::updateCurrentGame(float deltaTime)
{
    if (currentGame == nullptr) return;
    
    currentGame->update();
}

void Menu::update(float deltaTime)
{
    if (currentState == GAME_PLAY)
    {
        if (currentGame != nullptr)
            updateCurrentGame(deltaTime);
        else
            updateGame(deltaTime);  // Fallback to test game
    }
}

void Menu::moveUp()
{
    if (currentState == MAIN_MENU)
    {
        menu[selectedIndex].setFillColor(Color::White);
        buttons[selectedIndex].setFillColor(Color(100, 100, 100, 200));

        selectedIndex = (selectedIndex - 1 + 3) % 3;

        menu[selectedIndex].setFillColor(Color::Yellow);
        buttons[selectedIndex].setFillColor(Color(150, 150, 50, 200));

        sound.play();
    }
}


void Menu::moveDown()
{
    if (currentState == MAIN_MENU)
    {
        menu[selectedIndex].setFillColor(Color::White);
        buttons[selectedIndex].setFillColor(Color(100, 100, 100, 200));

        selectedIndex = (selectedIndex + 1) % 3;

        menu[selectedIndex].setFillColor(Color::Yellow);
        buttons[selectedIndex].setFillColor(Color(150, 150, 50, 200));

        sound.play();
    }
}



int Menu::getSelectedIndex()
{
    return selectedIndex;
}



void Menu::handleMouseMainMenu(RenderWindow& window)
{
    Vector2i mousePos = Mouse::getPosition(window);
    Vector2f worldPos = window.mapPixelToCoords(mousePos);

    for (int i = 0; i < 3; i++)
    {
        if (buttons[i].getGlobalBounds().contains(worldPos))
        {
            if (selectedIndex != i)
            {
                menu[selectedIndex].setFillColor(Color::White);
                buttons[selectedIndex].setFillColor(Color(100, 100, 100, 200));

                selectedIndex = i;
                menu[selectedIndex].setFillColor(Color::Yellow);
                buttons[selectedIndex].setFillColor(Color(150, 150, 50, 200));

                sound.play();
            }
            break;
        }
    }
}



void Menu::handleMouseOptions(RenderWindow& window, Event& event)
{
    Vector2i mousePos = Mouse::getPosition(window);
    Vector2f worldPos = window.mapPixelToCoords(mousePos);

    // Handle volume knob dragging
    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
    {
        if (volumeKnob.getGlobalBounds().contains(worldPos))
        {
            isDraggingKnob = true;
        }
        else if (backButtonRect.getGlobalBounds().contains(worldPos))
        {
            sound.play();
            currentState = MAIN_MENU;
        }
    }

    if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
    {
        isDraggingKnob = false;
    }

    // Update volume based on knob dragging
    if (isDraggingKnob || (event.type == Event::MouseMoved && Mouse::isButtonPressed(Mouse::Left) && isDraggingKnob))
    {
        float sliderLeft = volumeSlider.getPosition().x;
        float sliderRight = sliderLeft + volumeSlider.getSize().x;
        float knobX = worldPos.x;

        // Clamp knob position
        if (knobX < sliderLeft) knobX = sliderLeft;
        if (knobX > sliderRight) knobX = sliderRight;

        // Calculate volume percentage
        float percentage = (knobX - sliderLeft) / volumeSlider.getSize().x;
        volumeLevel = percentage * 100.0f;

        // Update knob position
        volumeKnob.setPosition(knobX, volumeKnob.getPosition().y);

        // Update volume text and music
        updateVolume();
    }
}


void Menu::handleInput(RenderWindow& window, Event& event)
{
    if (currentState == MAIN_MENU)
    {
        // Keyboard navigation for main menu
        if (event.type == Event::KeyPressed)
        {
            if (event.key.code == Keyboard::Up)
                moveUp();
            if (event.key.code == Keyboard::Down)
                moveDown();
            if (event.key.code == Keyboard::Enter)
            {
                int selected = getSelectedIndex();
                if (selected == 0)
                {
                    sound.play();
                    currentState = LEVEL_SELECT;
                }
                else if (selected == 1)
                {
                    sound.play();
                    currentState = OPTIONS_MENU;
                }
                else if (selected == 2)
                    window.close();
            }
        }

        // Mouse input for main menu
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
        {
            Vector2i mousePos = Mouse::getPosition(window);
            Vector2f worldPos = window.mapPixelToCoords(mousePos);

            for (int i = 0; i < 3; i++)
            {
                if (buttons[i].getGlobalBounds().contains(worldPos))
                {
                    if (i == 0)
                    {
                        sound.play();
                        currentState = LEVEL_SELECT;
                    }
                    else if (i == 1)
                    {
                        sound.play();
                        currentState = OPTIONS_MENU;
                    }
                    else if (i == 2)
                        window.close();
                    break;
                }
            }
        }

        handleMouseMainMenu(window);
    }
    else if (currentState == OPTIONS_MENU)
    {
        // Keyboard controls for options menu
        if (event.type == Event::KeyPressed)
        {
            if (event.key.code == Keyboard::Left)
            {
                volumeLevel -= 5;
                if (volumeLevel < 0) volumeLevel = 0;

                // Update knob position
                float knobX = volumeSlider.getPosition().x + (volumeLevel / 100.0f) * volumeSlider.getSize().x;
                volumeKnob.setPosition(knobX, volumeKnob.getPosition().y);
                updateVolume();
                sound.play();
            }
            else if (event.key.code == Keyboard::Right)
            {
                volumeLevel += 5;
                if (volumeLevel > 100) volumeLevel = 100;

                // Update knob position
                float knobX = volumeSlider.getPosition().x + (volumeLevel / 100.0f) * volumeSlider.getSize().x;
                volumeKnob.setPosition(knobX, volumeKnob.getPosition().y);
                updateVolume();
                sound.play();
            }
            else if (event.key.code == Keyboard::Escape)
            {
                sound.play();
                currentState = MAIN_MENU;
            }
        }

        handleMouseOptions(window, event);
    }
    else if (currentState == LEVEL_SELECT)
    {
        // Mouse hover effect for level boxes
        Vector2i mousePos = Mouse::getPosition(window);
        Vector2f worldPos = window.mapPixelToCoords(mousePos);

        for (int i = 0; i < 3; i++)
        {
            if (levelBoxes[i].getGlobalBounds().contains(worldPos))
            {
                if (!levelHover[i])
                {
                    levelBoxes[i].setFillColor(Color(150, 150, 50, 200));
                    levelBoxes[i].setOutlineColor(Color::Yellow);
                    levelHover[i] = true;
                }
            }
            else
            {
                if (levelHover[i])
                {
                    levelBoxes[i].setFillColor(Color(100, 100, 100, 200));
                    levelBoxes[i].setOutlineColor(Color::White);
                    levelHover[i] = false;
                }
            }
        }

        // Mouse click on level boxes
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
        {
            for (int i = 0; i < 3; i++)
            {
                if (levelBoxes[i].getGlobalBounds().contains(worldPos))
                {
                    sound.play();
                    selectedLevel = i + 1;
                    cout << "Starting LEVEL " << selectedLevel << "!" << endl;

                    // Start the real game instead of test game
                    if (currentGame != nullptr)
                        delete currentGame;
                    
                    currentGame = new game(mainWindow);  // Create new game instance
                    currentState = GAME_PLAY;
                    gameRunning = true;
                    break;
                }
            }

            // Check back button click
            if (levelBackButton.getGlobalBounds().contains(worldPos))
            {
                sound.play();
                currentState = MAIN_MENU;
            }
        }

        // Keyboard navigation for level select
        if (event.type == Event::KeyPressed)
        {
            if (event.key.code == Keyboard::Escape)
            {
                sound.play();
                currentState = MAIN_MENU;
            }
        }
    }
    else if (currentState == GAME_PLAY)
    {
        if (currentGame != nullptr)
        {
            // Only handle ESC key to return to menu
            // Do NOT render here - rendering happens in draw()
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Escape)
                {
                    delete currentGame;
                    currentGame = nullptr;
                    currentState = LEVEL_SELECT;
                    gameRunning = true;
                }
            }
        }
        else
        {
            // Fallback test game controls
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Left)
                    testPlayerVelocity.x = -testPlayerSpeed;
                if (event.key.code == Keyboard::Right)
                    testPlayerVelocity.x = testPlayerSpeed;
                if (event.key.code == Keyboard::Up)
                    testPlayerVelocity.y = -testPlayerSpeed;
                if (event.key.code == Keyboard::Down)
                    testPlayerVelocity.y = testPlayerSpeed;
                if (event.key.code == Keyboard::Escape)
                {
                    currentState = LEVEL_SELECT;
                    gameRunning = true;
                }
            }
            if (event.type == Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Left || event.key.code == Keyboard::Right)
                    testPlayerVelocity.x = 0;
                if (event.key.code == Keyboard::Up || event.key.code == Keyboard::Down)
                    testPlayerVelocity.y = 0;
            }
        }
    }
}

void Menu::draw(RenderWindow& window)
{
    if (currentState == MAIN_MENU)
    {
        window.draw(backgroundMain);
        for (int i = 0; i < 3; i++)
        {
            window.draw(buttons[i]);
            window.draw(menu[i]);
        }
    }
    else if (currentState == OPTIONS_MENU)
    {
        window.draw(backgroundMain);
        window.draw(backgroundOptions);
        window.draw(optionsTitle);
        window.draw(volumeText);
        window.draw(volumeValue);
        window.draw(volumeSlider);
        window.draw(volumeKnob);
        window.draw(backButtonRect);
        window.draw(backButton);
    }
    else if (currentState == LEVEL_SELECT)
    {
        window.draw(backgroundMain);
        window.draw(backgroundOptions);
        window.draw(levelTitle);
        for (int i = 0; i < 3; i++)
        {
            window.draw(levelBoxes[i]);
            window.draw(levelSprites[i]);
            window.draw(levelTexts[i]);
        }
        window.draw(levelBackButton);
        window.draw(levelBackText);
    }
    else if (currentState == GAME_PLAY)
    {
        if (currentGame != nullptr)
        {
            // Render the actual game here (not in handleInput!)
            currentGame->render();
        }
        else
        {
            window.draw(backgroundMain);
            Sprite movingBg = backgroundOptions;
            movingBg.setPosition(-cameraX, 0);
            window.draw(movingBg);
            movingBg.setPosition(movingBg.getPosition().x + movingBg.getGlobalBounds().width, 0);
            window.draw(movingBg);
            window.setView(gameView);
            window.draw(testPlayer);
            window.setView(window.getDefaultView());
        }
    }
}

Menu::~Menu()
{
    if (currentGame != nullptr)
    {
        delete currentGame;
        currentGame = nullptr;
    }
}

MenuState Menu::getCurrentState()
{
    return currentState;
}

void Menu::setCurrentState(MenuState state)
{
    currentState = state;
}

