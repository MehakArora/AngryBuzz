//
// Created by mehak on 10/23/2021.
//

#include <sstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Make code easier to type with "using namespace"
using namespace sf;

int main()
{
    // Create a video mode object
    VideoMode vm(1920, 1080);

    // Create and open a window for the game
    RenderWindow window(vm, "Buzzy's Revenge", Style::Fullscreen);

    // Create a texture to hold a graphic on the GPU
    Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");

    // Create a sprite
    Sprite spriteBackground;

    // Attach the texture to the sprite
    spriteBackground.setTexture(textureBackground);

    // Set the spriteBackground to cover the screen
    spriteBackground.setPosition(0, 0);


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

    for (int i = 0; i < 4 ; i++){
        messageText[i].setFont(font);
    }

    for (int i = 0; i < 2 ; i++){
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
    for (int i = 0; i < 4 ; i++){
        messageText[i].setCharacterSize(50);
    }
    powerText.setCharacterSize(25);
    for (int i = 0; i < 2 ; i++){
        nameText[i].setCharacterSize(25);
    }

    titleText.setFillColor(Color::Red);
    scoreText.setFillColor(Color::White);
    livesText.setFillColor(Color::White);
    for (int i = 0; i < 4 ; i++){
        messageText[i].setFillColor(Color::White);
    }
    powerText.setFillColor(Color::White);
    for (int i = 0; i < 2 ; i++){
        nameText[i].setFillColor(Color::White);
    }

    // Position the text
    FloatRect textRect = titleText.getLocalBounds();

    titleText.setOrigin(textRect.left +
                          textRect.width / 2.0f,
                          textRect.top +
                          textRect.height / 2.0f);

    titleText.setPosition(1920 / 2.0f, 1080 / 4.0f - 100);
    float lastPos = 1080 / 4.0f + 25;
    int textSpace = 75;

    for (int i = 0; i < 4 ; i++){

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
    for (int i = 0; i < 2 ; i++){

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
    powerText.setPosition(30, 1010);

    while(window.isOpen()){

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        // Clear everything from the last frame
        window.clear();

        // Draw our game scene here
        window.draw(spriteBackground);
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