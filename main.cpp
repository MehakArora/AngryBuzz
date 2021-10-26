/*
Author: Mehak Arora
Class: ECE 6122
Last Date Modified: 10/26/2021

Description:
Code for the game 'Buzzy's Revenge'

*/

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
const int totalLives = 5;
int column1[5], column2[5];
Sprite spriteCreature[10];
Text plusScore;
Vector2f velocity;


void Shuffle(int seed, Vector2f creaturePos[10]){
    /*
     * Randomly Shuffle the creatures on screen
     */
    int index;
    int creatureRest[8] = {1,2,3,4,5,6,7,8};
    srand(time(0) + seed);
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

    shuffle(creatureRest, creatureRest + 8, std::default_random_engine(time(0) + 2 + seed));
    for (int i =0; i < 4; i++)
    {
        column1[i] = creatureRest[i];
        column2[i] = creatureRest[i+4];
    }
    shuffle(column1, column1 + 5, std::default_random_engine(time(0) + seed));
    shuffle(column2, column2 + 5, std::default_random_engine(time(0) + 1 + seed));

    for (int i = 0; i < 10 ; i++)
    {
        index = (i < 5) ? column1[i]:column2[i-5];
        spriteCreature[index].setPosition(creaturePos[i].x, creaturePos[i].y);
        spriteCreature[index].setRotation(0);
    }
}

int main()
{

    // Create a video mode object
    VideoMode vm(1920, 1080);
    //const VideoMode gameDisplay = VideoMode::getDesktopMode();

    //std::cout<<gameDisplay.width << " " << gameDisplay.height << std::endl;
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


    /* ************************* SPRITES ********************/
    // Create sprites
    Sprite spriteBackground;
    Sprite spriteBuzz, spriteLives[totalLives], spriteInsect;

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

    //Set Scale for tiger
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

    /* ************************* Text Object ********************/
    Text titleText;
    Text scoreText;
    Text livesText;
    Text messageText[4];
    Text powerText;
    Text nameText[2];

    Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");

    titleText.setFont(font);
    scoreText.setFont(font);
    livesText.setFont(font);
    powerText.setFont(font);
    plusScore.setFont(font);

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
    plusScore.setString("0");

    titleText.setCharacterSize(100);
    scoreText.setCharacterSize(30);
    livesText.setCharacterSize(30);
    plusScore.setCharacterSize(30);
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
    plusScore.setFillColor(Color::Cyan);

    for (int i = 0; i < 4 ; i++)
    {
        messageText[i].setFillColor(Color::White);
    }
    powerText.setFillColor(Color::White);
    for (int i = 0; i < 2 ; i++)
    {
        nameText[i].setFillColor(Color::White);
    }


    /* ************************* Set Positions ********************/
    spriteBackground.setPosition(0, 0);
    plusScore.setPosition(3000,3000);

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

    scoreText.setPosition(1700, 20);
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
    spriteBuzz.setRotation(-35);
    scaleCurrent = spriteBuzz.getScale();
    spriteBuzz.setScale(scaleCurrent.x * 1.2f, scaleCurrent.y * 1.2f);

    for (int i =0; i < totalLives; i++)
    {
        scaleCurrent = spriteLives[i].getScale();
        spriteLives[i].scale(scaleCurrent.x /2.0f, scaleCurrent.y/2.0f);
        spriteLives[i].setPosition(120 + i*55 ,20);

    }

    //Positions of creatures in columns
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

    /* *************************** Sounds ***************************** */
    SoundBuffer chopBuffer;
    chopBuffer.loadFromFile("sound/chop.wav");
    Sound chop;
    chop.setBuffer(chopBuffer);

    SoundBuffer deathBuffer;
    deathBuffer.loadFromFile("sound/death.wav");
    Sound death;
    death.setBuffer(deathBuffer);

    // Out of time
    SoundBuffer ootBuffer;
    ootBuffer.loadFromFile("sound/out_of_time.wav");
    Sound outOfTime;
    outOfTime.setBuffer(ootBuffer);

    // Sad
    SoundBuffer sadBuffer;
    sadBuffer.loadFromFile("sound/sad.wav");
    Sound sad;
    sad.setBuffer(sadBuffer);

    // Unicorn
    SoundBuffer unicornBuffer;
    unicornBuffer.loadFromFile("sound/reachgoal.wav");
    Sound unicorn;
    unicorn.setBuffer(unicornBuffer);

    // Bee
    SoundBuffer beeBuffer;
    beeBuffer.loadFromFile("sound/bee.wav");
    Sound bee;
    bee.setBuffer(beeBuffer);


    /* *************************** Check Variables ***************************** */

    bool paused = true;
    bool acceptInput = false;
    bool buzzFlying = false;
    bool buzzFalling = false;
    bool beeCollide = false;
    bool foundUnicorn = false;
    bool gameOver = false;
    bool reset = false;
    bool disp1(true), disp2(true);
    bool creaturesFalling = false;
    bool creatureCollide = false;
    bool beeActive = false;
    bool makeScoreFly = false;

    /* *************************** Other Variables ***************************** */
    int creatureIndex;
    float angle, creatureVelocity(0);
    int lives = totalLives;
    int score = 0;
    int creature;

    Vector2f buzzVelocity, beeVelocity;
    Clock clock, beeClock;

    //Setting the initial velocity of Buzz
    float a(-9.8 * 50), tmax(4), tmin(1), vInitialMin, vInitialMax;
    vInitialMin = (1920 - (50))/tmax;
    vInitialMax = (1920 - (50))/tmin;

    /* *************************** RANDOM SHUFFLE ***************************** */

    Shuffle(0, creaturePos);


    /* *************************** START GAME LOOP ***************************** */

    int counter = 0; //Makes randomising more random
    while(window.isOpen()){

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        // Start the game
        if (paused && Keyboard::isKeyPressed(Keyboard::Return))
        {
            reset = true;
            lives = 5;
            score = 0;
            std::stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());

        }

        //Reset score, power, creatures
        if(reset)
        {
            paused = false;
            acceptInput = true;
            disp1 = true;
            disp2 = true;
            foundUnicorn = false;

            power = 0;
            powerBar.setSize(Vector2f(powerBarWidth*power, powerBarHeight));

            Shuffle(counter, creaturePos);
            spriteBuzz.setPosition(50, (1080 / 2.0f) + 200);
            spriteBuzz.setRotation(-35);
            reset = false;
            counter++;

        }

        if(!paused)
        {
            Time dt = clock.restart();
            float dtBee;


            /* ****************** MOVE THE BEE RANDOMLY *********************** */
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



            /* ****************** SET BUZZ ANGLE AND POWER *********************** */

            if (acceptInput && !buzzFlying)
            {
                if (Keyboard::isKeyPressed(Keyboard::Down))
                {
                    angle = spriteBuzz.getRotation();
                    spriteBuzz.setRotation(angle + 1e-1);
                }

                if (Keyboard::isKeyPressed(Keyboard::Up))
                {

                    angle = spriteBuzz.getRotation();
                    spriteBuzz.setRotation(angle - 1e-1);
                }

                if (Keyboard::isKeyPressed(Keyboard::Space))
                {
                    if (power < 1) {
                        power += 5e-4;
                    }
                    powerBar.setSize(Vector2f(powerBarWidth * power, powerBarHeight));

                }

                Event event; //Listen for space key release
                while (window.pollEvent(event)) {
                    if (event.type == Event::KeyReleased && event.key.code == Keyboard::Space) {
                        chop.play();
                        float velocity = ((vInitialMax - vInitialMin)*power)/cos(spriteBuzz.getRotation() * PI / 180);
                        buzzVelocity.x = velocity * cos(spriteBuzz.getRotation() * PI / 180);
                        buzzVelocity.y = velocity * sin(spriteBuzz.getRotation() * PI / 180);
                        acceptInput = false;
                        buzzFlying = true;
                    }
                }
            }

            /* ****************** PROJECTILE MOTION AND COLLISION *********************** */
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

                if(abs(distance.x) < epsilon && abs(distance.y) < epsilon)
                {
                    beeCollide = true;
                    acceptInput = true;
                    buzzFlying = false;
                }
                else
                {
                    for (int i = 0; i < 10; i++)
                    {
                        if(!disp1 && i < 5){
                            continue;
                        }
                        else if(!disp2 && i > 5){
                            continue;
                        }
                        creature = (i < 5) ? column1[i]:column2[i-5];
                        if(!foundUnicorn || (foundUnicorn &&  creature!=8)) {
                            distance = spriteBuzz.getPosition() - creaturePos[i];
                            if (abs(distance.x) < epsilon && abs(distance.y) < epsilon) {
                                creatureCollide = true;
                                buzzFlying = false;
                                acceptInput = true;
                                creatureIndex = i;
                                break;
                            }
                        }
                    }
                }

                //Reset if hits nothing
                if(spriteBuzz.getPosition().x > 2000 || spriteBuzz.getPosition().y > 1300){
                    lives -= 1;
                    spriteBuzz.setPosition(50, (1080 / 2.0f) + 200);
                    spriteBuzz.setRotation(-35);
                    power = 0;
                    powerBar.setSize(Vector2f(powerBarWidth*power, powerBarHeight));
                    acceptInput = true;
                    buzzFlying = false;
                    if(lives == 0){
                        gameOver = true;
                        paused = true;
                        outOfTime.play();
                    }
                }

            }


            if(creatureCollide)
            {
                creature = (creatureIndex < 5) ? column1[creatureIndex]:column2[creatureIndex-5];
                if(creature == 0 || creature == 9)   //Tiger and Bulldog
                {
                    score += 25;
                    if(creatureIndex < 5){
                        disp1 = false;
                    }
                    else{
                        disp2 = false;
                    }
                    creaturesFalling = true;
                    death.play();
                    acceptInput = false;
                    std::stringstream ss;
                    ss << "+" << 25;
                    plusScore.setString(ss.str());
                    plusScore.setCharacterSize(30);
                    plusScore.setPosition(spriteBuzz.getPosition());

                    velocity.x = (1700 - spriteBuzz.getPosition().x)/2;
                    velocity.y = (30 - spriteBuzz.getPosition().y)/2;
                    makeScoreFly = true;
                }
                else if (creature == 8 && !foundUnicorn){  //Unicorn
                    foundUnicorn = true;
                    unicorn.play();
                    lives = (lives < 5) ? lives + 1: lives;
                    spriteCreature[creature].setPosition(3000, 3000);
                    int j((creatureIndex % 5) - 1), index;
                    for (j; j >= 0; j--){
                        index = (creatureIndex < 5) ? column1[j]:column2[j];
                        spriteCreature[index].setPosition(creaturePos[int(creatureIndex/5)*5 + j+1]);
                        if(creatureIndex < 5){
                            column1[j+1] = column1[j];
                        }
                        else{
                            column2[j+1] = column2[j];
                        }
                    }

                    if(creatureIndex < 5){
                        column1[0] = UNICORN;
                    }
                    else{
                        column2[0] = UNICORN;
                    }

                }
                else{   //Woodland Creature
                    lives -= 1;
                    buzzFalling = true;
                    sad.play();
                    acceptInput = false;
                    if(lives == 0){
                        gameOver = true;
                        paused = true;
                        outOfTime.play();
                    }
                }

                if(!buzzFalling ){
                    spriteBuzz.setPosition(50, (1080 / 2.0f) + 200);
                    spriteBuzz.setRotation(-35);
                }

                power = 0;
                powerBar.setSize(Vector2f(powerBarWidth*power, powerBarHeight));
                creatureCollide = false;
                if(!makeScoreFly){
                    std::stringstream ss;
                    ss << "Score = " << score;
                    scoreText.setString(ss.str());
                }

            }

            if(beeCollide)
            {
                bee.play();
                std::stringstream ss;
                ss << "+" << 25;
                plusScore.setString(ss.str());
                plusScore.setCharacterSize(30);
                plusScore.setPosition(spriteBuzz.getPosition());

                velocity.x = (1700 - spriteBuzz.getPosition().x)/2;
                velocity.y = (30 - spriteBuzz.getPosition().y)/2;
                makeScoreFly = true;
                power = 0;
                powerBar.setSize(Vector2f(powerBarWidth*power, powerBarHeight));

                score += 75;
                spriteBuzz.setPosition(50, (1080 / 2.0f) + 200);
                spriteBuzz.setRotation(-35);
                beeCollide = false;

            }

            if(makeScoreFly){

                //std::cout << plusScore.getPosition().x << " " << plusScore.getPosition().y << std::endl;
                if(plusScore.getPosition().y  > 0 && plusScore.getPosition().x < 1920){
                    plusScore.setPosition( plusScore.getPosition().x + velocity.x * dt.asSeconds(), plusScore.getPosition().y + velocity.y * dt.asSeconds());
                    //plusScore.setCharacterSize(plusScore.getCharacterSize() + 5);
                    acceptInput = false;
                }
                else{
                    plusScore.setPosition(-3000,-3000);
                    makeScoreFly = false;
                }

                if(!makeScoreFly){
                    //spriteBuzz.setPosition(50, (1080 / 2.0f) + 200);
                    //spriteBuzz.setRotation(-35);
                    std::stringstream ss;
                    ss << "Score = " << score;
                    scoreText.setString(ss.str());
                    acceptInput = true;
                }
            }

            if(buzzFalling){
                buzzVelocity.y = buzzVelocity.y - a*dt.asSeconds();
                buzzVelocity.x = 0;
                spriteBuzz.setPosition(
                        spriteBuzz.getPosition().x,
                        spriteBuzz.getPosition().y + buzzVelocity.y*dt.asSeconds());
                float rotAngle = 5e-1;
                acceptInput = false;

                spriteBuzz.rotate(rotAngle);

                if(spriteBuzz.getPosition().y > 1300){
                    spriteBuzz.setPosition(50, (1080 / 2.0f) + 200);
                    spriteBuzz.setRotation(-35);
                    buzzFalling = false;
                    acceptInput = true;
                }

            }

            if(creaturesFalling) {

                float rotAngle = 5e-1;
                creatureVelocity += a*dt.asSeconds();
                bool check1(true), check2(true);

                for (int j=0; j < 5; j++)
                {
                    if (!disp1)
                    {
                        check1 = false;
                        if(!foundUnicorn || (foundUnicorn && column1[j]!=8))
                        {
                            spriteCreature[column1[j]].setPosition(
                                    spriteCreature[column1[j]].getPosition().x,
                                    spriteCreature[column1[j]].getPosition().y - creatureVelocity * dt.asSeconds());
                            spriteCreature[column1[j]].rotate(rotAngle);
                        }
                    }
                    if (!disp2)
                    {
                        check2 = false;
                        if(!foundUnicorn || (foundUnicorn && column2[j]!=8))
                        {
                            spriteCreature[column2[j]].setPosition(
                                    spriteCreature[column2[j ]].getPosition().x,
                                    spriteCreature[column2[j]].getPosition().y - creatureVelocity * dt.asSeconds());
                            spriteCreature[column2[j]].rotate(rotAngle);
                        }
                    }
                }

                if (!disp1) {
                    int first = (foundUnicorn && column1[0] == 8) ? 1 : 0;
                    if (spriteCreature[column1[first]].getPosition().y > 2000) {
                        check1 = true;
                    }
                }
                if (!disp2) {
                    int first = (foundUnicorn && column2[0] == 8) ? 1 : 0;
                    if (spriteCreature[column2[first]].getPosition().y > 2000) {
                        check2 = true;
                    }
                }

                acceptInput = false;

                if (check1 && check2) {
                    creaturesFalling = false;
                    creatureVelocity = 0;
                    acceptInput = true;
                }


                if (!disp1 && !disp2 && !creaturesFalling) {
                    reset = true;
                }
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
        window.draw(plusScore);

        for (int i=0; i < lives; i++)
        {
            window.draw(spriteLives[i]);
        }

        if(disp1 || creaturesFalling){
            for (int i=0; i<5; i++)
            {
                window.draw(spriteCreature[column1[i]]);
            }
        }

        if(disp2 || creaturesFalling){
            for (int i=0; i<5; i++)
            {
                window.draw(spriteCreature[column2[i]]);
            }
        }

        if(paused)
        {
            if(gameOver){
                titleText.setString("Game Is Now Over");
                window.draw(titleText);
                for (int i = 0; i < 4 ; i++){
                    window.draw(messageText[i]);
                }
            }
            else{
                for (int i = 0; i < 4 ; i++){
                    window.draw(messageText[i]);
                }

                for (int i = 0; i < 2 ; i++){
                    window.draw(nameText[i]);
                }
                window.draw(titleText);
            }

        }


        // Show everything we just drew
        window.display();
    }
    return 0;
}