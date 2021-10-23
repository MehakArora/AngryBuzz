//
// Created by mehak on 10/23/2021.
//

#include <sstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Make code easier to type with "using namespace"
using namespace sf;
#define UNICORN 8;
#define GEORGIABULLDOG 10;



int main()
{
    // Create a video mode object
    VideoMode vm(1920, 1080);

    // Create and open a window for the game
    RenderWindow window(vm, "Buzzy's Revenge", Style::Fullscreen);

    // Create a texture to hold a graphic on the GPU
    Texture textureBackground;
    Texture textureBuzz, textureLives, textureInsect, textureCreature[10];
    textureBackground.loadFromFile("graphics/background.png");
    textureBuzz.loadFromFile("graphics/smallbuzzy.png");
    textureLives.loadFromFile("graphics/buzzylife.png");
    textureInsect.loadFromFile("graphics/bee.png");
    textureCreature[0].loadFromFile("graphics/bunny.png");
    textureCreature[1].loadFromFile("graphics/chicken.png");
    textureCreature[2].loadFromFile("graphics/dog.png");
    textureCreature[3].loadFromFile("graphics/frog.png");
    textureCreature[4].loadFromFile("graphics/mouse.png");
    textureCreature[5].loadFromFile("graphics/pig.png");
    textureCreature[6].loadFromFile("graphics/sheep.png");
    textureCreature[7].loadFromFile("graphics/tiger.png");
    textureCreature[8].loadFromFile("graphics/angry_unicorn.png");
    textureCreature[10].loadFromFile("graphics/Georgia_Bulldogs_logo_dog_g.png");


    // Create a sprite
    Sprite spriteBackground;
    Sprite spriteBuzz, spriteLives, spriteInsect, spriteCreature[10];

    // Attach the texture to the sprite
    spriteBackground.setTexture(textureBackground);
    spriteBuzz.setTexture(textureBuzz);
    spriteLives.setTexture(textureLives);
    spriteInsect.setTexture(textureInsect);
    for (int i; i < 10; i++ )
    {
        spriteCreature[i].setTexture(textureCreature[i]);
    }

    // Power bar
    RectangleShape powerBar, powerBarOutline;
    float powerBarWidth = 400;
    float powerBarHeight = 40;
    powerBarOutline.setSize(Vector2f(powerBarWidth, powerBarHeight));
    powerBarOutline.setOutlineColor(Color::Black);
    powerBarOutline.setOutlineThickness(6);
    powerBarOutline.setFillColor(Color::Transparent);

    powerBar.setSize(Vector2f(powerBarWidth*0.75f, powerBarHeight));
    powerBar.setFillColor(Color::Red);

    //Create Text Objects
    Text titleText;
    Text scoreText;
    Text livesText;
    Text messageText[4];
    Text powerText;
    Text nameText[2];

    // We need to choose a font
    Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");

    // Set the font to our message
    titleText.setFont(font);
    scoreText.setFont(font);
    livesText.setFont(font);
    powerText.setFont(font);

    for (int i = 0; i < 4 ; i++)
    {
        messageText[i].setFont(font);
    }

    for (int i = 0; i < 2 ; i++)
    {
        nameText[i].setFont(font);
    }


    // Assign the actual message
    titleText.setString("Buzzy's Revenge");
    scoreText.setString("Score = 99");
    livesText.setString("Lives : ");
    messageText[0].setString("Press Enter to Restart Game");
    messageText[1].setString("Press Esc to Exit");
    messageText[2].setString("Press Space to Powerup");
    messageText[3].setString("Press up/down arrow to aim");
    powerText.setString("Power ");
    nameText[0].setString(" Created by ");
    nameText[1].setString(" Mehak Arora ");

    titleText.setCharacterSize(100);
    scoreText.setCharacterSize(25);
    livesText.setCharacterSize(25);
    for (int i = 0; i < 4 ; i++)
    {
        messageText[i].setCharacterSize(50);
    }

    powerText.setCharacterSize(25);

    for (int i = 0; i < 2 ; i++)
    {
        nameText[i].setCharacterSize(25);
    }

    titleText.setFillColor(Color::Red);
    scoreText.setFillColor(Color::White);
    livesText.setFillColor(Color::White);
    for (int i = 0; i < 4 ; i++)
    {
        messageText[i].setFillColor(Color::White);
    }
    powerText.setFillColor(Color::White);
    for (int i = 0; i < 2 ; i++)
    {
        nameText[i].setFillColor(Color::White);
    }


    // Set the spriteBackground to cover the screen
    spriteBackground.setPosition(0, 0);


    // Position the text
    FloatRect textRect = titleText.getLocalBounds();

    titleText.setOrigin(textRect.left +
                          textRect.width / 2.0f,
                          textRect.top +
                          textRect.height / 2.0f);

    titleText.setPosition(1920 / 2.0f, 1080 / 4.0f - 100);
    float lastPos = 1080 / 4.0f + 25;
    int textSpace = 75;

    for (int i = 0; i < 4 ; i++)
    {

        textRect = messageText[i].getLocalBounds();
        messageText[i].setOrigin(textRect.left +
                              textRect.width / 2.0f,
                              textRect.top +
                              textRect.height / 2.0f);
        messageText[i].setPosition(1920 / 2.0f, lastPos + textSpace);
        lastPos += textSpace;
    }

    lastPos += 100;
    textSpace = 25;
    for (int i = 0; i < 2 ; i++)
    {

        textRect = nameText[i].getLocalBounds();
        nameText[i].setOrigin(textRect.left +
                                 textRect.width / 2.0f,
                                 textRect.top +
                                 textRect.height / 2.0f);

        nameText[i].setPosition(1920 / 2.0f, lastPos + textSpace);
        lastPos += textSpace;
    }

    scoreText.setPosition(1750, 20);
    livesText.setPosition(30, 30);
    powerText.setPosition(30, 1000);
    powerBar.setPosition(135 ,  995);
    powerBarOutline.setPosition(135 ,  995);

    float creaturePos[10][2];
    int creatureOrder[10] = {0,1,2,3,4,5,6,7,8,9};
    float startY(1080 / 4.0f + 100);
    float x1(1700), x2(1750);

    for (int i = 0 ; i < 10; i++)
    {
        if(i < 5)
        {
            creaturePos[i][0] = x1;
        }
        else
        {
            creaturePos[i][0] = x2;
        }

        creaturePos[i][1] = startY + i*10;
    }

    int index;
    for (int i = 0; i < 10; i++)
    {
        index = creatureOrder[i];
        spriteCreature[index].setPosition(creaturePos[i][0], creaturePos[i][1]);
    }

    while(window.isOpen()){

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        // Clear everything from the last frame
        window.clear();

        // Draw our game scene here
        window.draw(spriteBackground);
        window.draw(powerBar);
        window.draw(powerBarOutline);
        window.draw(titleText);
        window.draw(scoreText);
        window.draw(livesText);
        window.draw(powerText);
        for (int i = 0; i < 4 ; i++){
            window.draw(messageText[i]);
        }

        for (int i = 0; i < 2 ; i++){
            window.draw(nameText[i]);
        }

        // Show everything we just drew
        window.display();
    }
    return 0;
}