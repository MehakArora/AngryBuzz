//
// Created by mehak on 10/23/2021.
//

#include <sstream>
#include <iostream>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Make code easier to type with "using namespace"
using namespace sf;
#define UNICORN 8;
#define GEORGIABULLDOG 9;
#define TIGER 0;
#define PI 3.14159265


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

    textureCreature[0].loadFromFile("graphics/tiger.png");
    textureCreature[1].loadFromFile("graphics/chicken.png");
    textureCreature[2].loadFromFile("graphics/dog.png");
    textureCreature[3].loadFromFile("graphics/frog.png");
    textureCreature[4].loadFromFile("graphics/mouse.png");
    textureCreature[5].loadFromFile("graphics/pig.png");
    textureCreature[6].loadFromFile("graphics/sheep.png");
    textureCreature[7].loadFromFile("graphics/bunny.png");
    textureCreature[8].loadFromFile("graphics/angry_unicorn.png");
    textureCreature[9].loadFromFile("graphics/Georgia_Bulldogs_logo_dog_g.png");


    // Create a sprite
    const int totalLives = 5;

    Sprite spriteBackground;
    Sprite spriteBuzz, spriteLives[totalLives], spriteInsect, spriteCreature[10];

    // Attach the texture to the sprite
    spriteBackground.setTexture(textureBackground);
    spriteBuzz.setTexture(textureBuzz);
    spriteInsect.setTexture(textureInsect);
    
    for (int i = 0; i < totalLives; i++)
    {
        spriteLives[i].setTexture(textureLives);
    }

    FloatRect textRect;

    for (int i = 0; i < 10; i++ )
    {
        spriteCreature[i].setTexture(textureCreature[i]);
        textRect = spriteCreature[i].getLocalBounds();
        spriteCreature[i].setOrigin(textRect.left +
                                        textRect.width / 2.0f,
                                        textRect.top +
                                        textRect.height / 2.0f);
    }

    //Set Scale for bunny and tiger
    spriteCreature[0].setScale(1/8.0f, 1/8.0f);

    // Power bar
    RectangleShape powerBar, powerBarOutline;
    float powerBarWidth = 400;
    float powerBarHeight = 40;
    float power = 0.75f;
    powerBarOutline.setSize(Vector2f(powerBarWidth, powerBarHeight));
    powerBarOutline.setOutlineColor(Color::Black);
    powerBarOutline.setOutlineThickness(6);
    powerBarOutline.setFillColor(Color::Transparent);

    powerBar.setSize(Vector2f(powerBarWidth*power, powerBarHeight));
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
    scoreText.setCharacterSize(30);
    livesText.setCharacterSize(30);
    for (int i = 0; i < 4 ; i++)
    {
        messageText[i].setCharacterSize(50);
    }

    powerText.setCharacterSize(30);

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
    textRect = titleText.getLocalBounds();

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

    scoreText.setPosition(1710, 20);
    livesText.setPosition(30, 33);
    powerText.setPosition(30, 1000);
    powerBar.setPosition(150 ,  1000);
    powerBarOutline.setPosition(150 ,  1000);

    Vector2f scaleCurrent;
    spriteInsect.setPosition( 1600,(1080 / 4.0f) - 100);
    scaleCurrent = spriteInsect.getScale();
    spriteInsect.setScale(scaleCurrent.x * 1.5f, scaleCurrent.y * 1.5f);

    textRect = spriteBuzz.getLocalBounds();
    spriteBuzz.setOrigin(textRect.left +
                          textRect.width / 2.0f,
                          textRect.top +
                          textRect.height / 2.0f);
    spriteBuzz.setPosition(50, (1080 / 2.0f) + 200);
    spriteBuzz.setRotation(-30);
    scaleCurrent = spriteBuzz.getScale();
    spriteBuzz.setScale(scaleCurrent.x * 1.2f, scaleCurrent.y * 1.2f);

    for (int i =0; i < totalLives; i++)
    {
        scaleCurrent = spriteLives[i].getScale();
        spriteLives[i].scale(scaleCurrent.x /2.0f, scaleCurrent.y/2.0f);
        spriteLives[i].setPosition(120 + i*55 ,20);

    }


    Vector2f creaturePos[10];

    float startY(1080 / 3.0f );
    float x1(1650), x2(1780);

    for (int i = 0 ; i < 10; i++)
    {
        if(i < 5)
        {
            creaturePos[i].x = x1;
        }
        else
        {
            creaturePos[i].x = x2;
        }

        creaturePos[i].y = startY + (i % 5)*120;
    }

    int index;
    srand(time(0));

    int column1[5], column2[5], creatureRest[8] = {1,2,3,4,5,6,7,8};

    if(rand()%2 == 0)
    {
        column1[4] = TIGER;
        column2[4] = GEORGIABULLDOG;
    }
    else
    {
        column1[4] = GEORGIABULLDOG;
        column2[4] = TIGER;
    }

    shuffle(creatureRest, creatureRest + 8, std::default_random_engine(time(0) + 2 ));
    for (int i =0; i < 4; i++)
    {
        column1[i] = creatureRest[i];
        column2[i] = creatureRest[i+4];
    }
    shuffle(column1, column1 + 5, std::default_random_engine(time(0) ));
    shuffle(column2, column2 + 5, std::default_random_engine(time(0) + 1));

    for (int i = 0; i < 10 ; i++)
    {
        index = (i < 5) ? column1[i]:column2[i-5];
        spriteCreature[index].setPosition(creaturePos[i].x, creaturePos[i].y);
    }

    bool paused = true;
    int score = 0;
    bool acceptInput = false;
    bool buzzFlying = false;
    bool beeCollide = false;
    bool dis1(true), disp2(true);
    bool creatureCollide = false;
    int creatureIndex;
    float angle;
    bool beeActive = false;
    Vector2f buzzVelocity, beeVelocity;
    Clock clock, beeClock;
    int beeTime;

    float a(-9.8 * 50), tmax(4), tmin(1), vInitialMin, vInitialMax;
    vInitialMin = (1920 - (50))/tmax;
    vInitialMax = (1920 - (50))/tmin;

    while(window.isOpen()){

        /*
        Event event;
        while (window.pollEvent(event))
        {


            if (event.type == Event::KeyReleased && !paused)
            {
                // Listen for key presses again
                acceptInput = true;
            }

        }
        */

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        // Start the game
        if (paused && Keyboard::isKeyPressed(Keyboard::Return))
        {
            paused = false;
            acceptInput = true;
            power = 0;
            powerBar.setSize(Vector2f(powerBarWidth*power, powerBarHeight));
            score = 0;
            std::stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());
        }

        if(!paused)
        {
            Time dt = clock.restart();
            float dtBee;


            //BEE
            if (!beeActive)
            {

                // How fast is the bee
                srand((int)time(0) * 10);
                beeVelocity.x = (rand() % 200) + 200;
                beeVelocity.y = (rand() % 200) - 100;

                // How high is the bee
                srand((int)time(0) * 10);
                float height = (rand() % 500) + 100;
                spriteInsect.setPosition(2000, height);
                beeActive = true;
                dtBee = beeClock.getElapsedTime().asSeconds();

            }
            else
                // Move the bee
            {
                if(spriteInsect.getPosition().y - (beeVelocity.y * dt.asSeconds()) < 30)
                {
                    beeVelocity.y = -100;
                }
                else if( spriteInsect.getPosition().y - (beeVelocity.y * dt.asSeconds()) > 1000 )
                {
                    beeVelocity.y = 100;
                }

                if( (beeClock.getElapsedTime().asSeconds() - dtBee)   > 1)
                {
                    srand((int)time(0) * 10);
                    beeVelocity.y = (rand() % 200) - 100;
                    dtBee = beeClock.getElapsedTime().asSeconds();
                }
                spriteInsect.setPosition(
                        spriteInsect.getPosition().x -
                        (beeVelocity.x * dt.asSeconds()),
                        spriteInsect.getPosition().y - beeVelocity.y*dt.asSeconds());

                // Has the bee reached the right hand edge of the screen?
                if (spriteInsect.getPosition().x < -10)
                {
                    beeActive = false;
                }
            }



            //BUZZ
            if (acceptInput && !buzzFlying)
            {
                if (Keyboard::isKeyPressed(Keyboard::Down))
                {
                    angle = spriteBuzz.getRotation();
                    spriteBuzz.setRotation(angle + 1e-2);
                }

                if (Keyboard::isKeyPressed(Keyboard::Up))
                {

                    angle = spriteBuzz.getRotation();
                    spriteBuzz.setRotation(angle - 1e-2);
                }

                if (Keyboard::isKeyPressed(Keyboard::Space))
                {
                    if (power < 1) {
                        power += 1e-4;
                    }
                    powerBar.setSize(Vector2f(powerBarWidth * power, powerBarHeight));

                }

                Event event;
                while (window.pollEvent(event)) {
                    if (event.type == Event::KeyReleased && event.key.code == Keyboard::Space) {
                        float velocity = ((vInitialMax - vInitialMin)*power)/cos(spriteBuzz.getRotation() * PI / 180);
                        buzzVelocity.x = velocity * cos(spriteBuzz.getRotation() * PI / 180);
                        buzzVelocity.y = velocity * sin(spriteBuzz.getRotation() * PI / 180);
                        acceptInput = false;
                        buzzFlying = true;
                    }
                }

            }


            //Buzz Flying
            if(buzzFlying)
            {
                spriteBuzz.setPosition(
                        spriteBuzz.getPosition().x +
                        (buzzVelocity.x * dt.asSeconds()),
                        spriteBuzz.getPosition().y + buzzVelocity.y*dt.asSeconds());

                buzzVelocity.y = buzzVelocity.y - a*dt.asSeconds();
                float theta = atan2(buzzVelocity.y, buzzVelocity.x) * 180 / PI;
                spriteBuzz.setRotation(theta);

                //Detect Collision
                float epsilon = 50;
                Vector2f distance = spriteBuzz.getPosition() - spriteInsect.getPosition();
                if(abs(distance.x) < epsilon && abs(distance.y) < epsilon){
                    beeCollide = true;
                    acceptInput = true;
                    buzzFlying = false;
                }

                for (int i = 0; i < 10; i++)
                {
                    distance = spriteBuzz.getPosition() - creaturePos[i];
                    if(abs(distance.x) < epsilon && abs(distance.y) < epsilon){
                        creatureCollide = true;
                        buzzFlying = false;
                        acceptInput = true;
                        creatureIndex = (i < 5) ? column1[i]: column2[i-5];
                        break;
                    }
                }
            }

            if(creatureCollide)
            {
                spriteBuzz.setPosition(-100,0);
                if(creatureIndex == 0 || creatureIndex == 9)
                {
                    spriteBuzz.setPosition(50, (1080 / 2.0f) + 200);
                    spriteBuzz.setRotation(-35);
                }
                else if (creatureIndex == 8){
                    spriteBuzz.setPosition(50, (1080 / 2.0f) + 200);
                    spriteBuzz.setRotation(-35);
                }
                else {
                    spriteBuzz.setPosition(50, (1080 / 2.0f) + 200);
                    spriteBuzz.setRotation(-35);
                }

            }

            if(beeCollide)
            {
                spriteBuzz.setPosition(50, (1080 / 2.0f) + 200);
                spriteBuzz.setRotation(-35);
            }
        }


        // Clear everything from the last frame
        window.clear();

        // Draw our game scene here
        window.draw(spriteBackground);
        window.draw(powerBar);
        window.draw(powerBarOutline);
        window.draw(scoreText);
        window.draw(livesText);
        window.draw(powerText);

        window.draw(spriteBuzz);
        window.draw(spriteInsect);
        for (int i=0; i < totalLives; i++)
        {
            window.draw(spriteLives[i]);
        }

        for (int i=0; i<10; i++)
        {
            window.draw(spriteCreature[i]);
        }

        if(paused)
        {
            for (int i = 0; i < 4 ; i++){
                window.draw(messageText[i]);
            }

            for (int i = 0; i < 2 ; i++){
                window.draw(nameText[i]);
            }
            window.draw(titleText);
        }


        // Show everything we just drew
        window.display();
    }
    return 0;
}