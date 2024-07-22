#include <iostream>
#include <SFML/Graphics.hpp>

int main() {

    int currentLeftScore = 0;
    int currentRightScore = 0;

    sf::RenderWindow ventana(sf::VideoMode(1920, 1080),"Ventana de SMFL");

#pragma region //Dibujo Paletas y Borde del juego
    sf::RectangleShape leftPalette(sf::Vector2f(30, 150));
    leftPalette.setFillColor(sf::Color::White);
    leftPalette.setPosition(50, 465);

    sf::RectangleShape rightPalette(sf::Vector2f(30, 150));
    rightPalette.setFillColor(sf::Color::White);
    rightPalette.setPosition(1840, 465);

    sf::RectangleShape borderGame(sf::Vector2f(1900, 1060));  //El margen lo tengo que restar al doble al contorno para compensar la posicion, y sumarselo a la posicion
    borderGame.setFillColor(sf::Color::Black);
    borderGame.setPosition(10,10);
    borderGame.setOutlineColor(sf::Color::White);
    borderGame.setOutlineThickness(10.0f);
#pragma endregion

#pragma region //Linea divisora



    const int numMiddleBars = 40;
    sf::RectangleShape middleBarArray[numMiddleBars];
    for (int n = 0; n < numMiddleBars; n++) {
        middleBarArray[n].setSize(sf::Vector2f(10, 20));
        middleBarArray[n].setFillColor(sf::Color::White);
        middleBarArray[n].setPosition(956, 30 * n + 10);
    }
#pragma endregion


    sf::RectangleShape ball(sf::Vector2f(25, 25));
    ball.setFillColor(sf::Color::White);
    ball.setPosition(948,300);
    sf::Vector2f respawnPosition(948, 300);
    sf::Vector2f ballMovement(.1f, .1f);
    bool goingRight = true;


    sf::Font font;
    if (!font.loadFromFile("../PressStart2P-Regular.ttf")) {
        std::cerr << "No se encontro la fuente" << std::endl;
        return 2;
    }


    sf::Text leftScore;
    leftScore.setFont(font);
    leftScore.setString(std::to_string(currentLeftScore));
    leftScore.setCharacterSize(150);
    //leftScore.setStyle(sf::Text::Bold);
    leftScore.setPosition(400, 100);

    sf::Text rightScore;
    rightScore.setFont(font);
    rightScore.setString(std::to_string(currentRightScore));
    rightScore.setCharacterSize(150);
    rightScore.setPosition(1370, 100);

    sf::Text rightVictory;
    rightVictory.setFont(font);
    rightVictory.setString("Right side won!");
    rightVictory.setCharacterSize(50);
    rightVictory.setPosition(600, 300);
    bool showRightVictory = false;

    sf::Text leftVictory;
    leftVictory.setFont(font);
    leftVictory.setString("Left side won!");
    leftVictory.setCharacterSize(50);
    leftVictory.setPosition(600, 300);
    bool showLeftVictory = false;

    sf::Event evento;
    while (ventana.isOpen())
    {
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                ventana.close();
            }
#pragma region //Controladores Paletas
            if(evento.type == sf::Event::KeyPressed){
                if(evento.key.code == sf::Keyboard::W){
                    if (leftPalette.getPosition().y > 10) {
                        leftPalette.move(0, -20);
                    }
                }
            }
            if(evento.type == sf::Event::KeyPressed){
                if(evento.key.code == sf::Keyboard::S){
                    if (leftPalette.getPosition().y + 150 < 1070) {
                        leftPalette.move(0, 20);
                    }
                }
            }
            if(evento.type == sf::Event::KeyPressed){
                if(evento.key.code == sf::Keyboard::Up){
                    if (rightPalette.getPosition().y > 10) {
                        rightPalette.move(0, -20);
                    }
                }
            }
            if(evento.type == sf::Event::KeyPressed){
                if(evento.key.code == sf::Keyboard::Down){
                    if (rightPalette.getPosition().y + 150 < 1070) {
                        rightPalette.move(0, 20);
                    }
                }
            }
            if(evento.type == sf::Event::KeyPressed){
                if(evento.key.code == sf::Keyboard::R){
                    currentLeftScore = 0;
                    currentRightScore = 0;
                    ball.setPosition(948,300);
                    ballMovement = sf::Vector2f (.1f, .1f);
                    rightPalette.setPosition(1840, 465);
                    leftPalette.setPosition(50, 465);
                    showRightVictory = false;
                    showLeftVictory = false;
                    ball.setFillColor(sf::Color::White);

                }
            }
#pragma endregion
        }


#pragma region //Rebote pelota con bordes y puntaje
        sf::Vector2f ballPosition = ball.getPosition();
        if (ballPosition.y <= 10 || ballPosition.y >= 1045) {
            ballMovement.y = -ballMovement.y;
        }

        if(ballPosition.x <= 10)
        {
            currentRightScore++;
            ball.setPosition(sf::Vector2f(respawnPosition));
            ballMovement = sf::Vector2f (-.1f, .1f);
        }

        if(ballPosition.x >= 1910)
        {
            currentLeftScore++;
            ball.setPosition(sf::Vector2f(respawnPosition));
            ballMovement = sf::Vector2f (.1f, .1f);
        }

#pragma endregion

        sf::FloatRect rightPaletteBounds = rightPalette.getGlobalBounds();
        sf::FloatRect leftPaletteBounds = leftPalette.getGlobalBounds();
        sf::FloatRect ballBounds = ball.getGlobalBounds();

        if (ballBounds.intersects(leftPaletteBounds) || ballBounds.intersects(rightPaletteBounds) )
        {

            ballMovement = -sf::Vector2f (ballMovement.x, ballMovement.y + .04f);
        }



        ball.move(ballMovement);
        leftScore.setString(std::to_string(currentLeftScore));
        rightScore.setString(std::to_string(currentRightScore));




        ventana.clear(sf::Color::Black);
        ventana.draw(borderGame);

        ventana.draw(leftPalette);
        ventana.draw(rightPalette);
        ventana.draw(leftScore);
        ventana.draw(rightScore);

        for (int i = 0; i < numMiddleBars; i++) {
            ventana.draw(middleBarArray[i]);
        }

        ventana.draw(ball);

        if(currentLeftScore == 5)
        {
            //ventana.draw(leftVictory);
            ballMovement = -sf::Vector2f (0, 0);
            ball.setFillColor(sf::Color::Black);
            showLeftVictory = true;
        }
        if(currentRightScore == 5)
        {
            //ventana.draw(rightVictory);
            ballMovement = -sf::Vector2f (0, 0);
            ball.setFillColor(sf::Color::Black);
            showRightVictory = true;
        }

        if (showLeftVictory) {
            ventana.draw(leftVictory);
        }

        if (showRightVictory) {
            ventana.draw(rightVictory);
        }
        ventana.display();
    }

    return 0;
}