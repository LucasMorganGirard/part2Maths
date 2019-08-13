
#include "line.hpp"

line::line(sf::RenderWindow& win, sf::Vector2f const xy) : mWin(win), mA(0), mB(0), mC(0), mRotate(false){
    mDiagonale = std::sqrt(win.getSize().x * win.getSize().x + win.getSize().y * win.getSize().y);
    mRecBefore = sf::RectangleShape(sf::Vector2f(1, mDiagonale));
    mRecAfter = sf::RectangleShape(sf::Vector2f(1, mDiagonale));
    mRecBefore.setOrigin(0, mDiagonale);
    mRecBefore.setPosition(xy);
    mRecAfter.setPosition(xy);
    if(!mFont.loadFromFile(resourcePath() + "sansation.ttf")){
        return EXIT_FAILURE;
    }
    mText.setFont(mFont);
    mText.setFillColor(sf::Color::Blue);
    mText.setCharacterSize(20);
    mText.setPosition(30, 30);
    mText.setString("mMMMMML");
}

line::~line(){
    std::cout << "destruction" << std::endl;
}

void line::rotate(){
    if(mRotate){
        mRecBefore.rotate(0.1);
        mRecAfter.rotate(0.1);
        calculEquationDroite();
    }
}

void line::setStartingPt(int const x, int const y){
    mRecBefore.setPosition(x, y);
    mRecAfter.setPosition(x, y);
    calculEquationDroite();
}

void line::setStartingPt(sf::Vector2f const xy){
    mRecBefore.setPosition(xy);
    mRecAfter.setPosition(xy);
    calculEquationDroite();
}

sf::Vector2f line::getStartingPt() const{
    return mRecAfter.getPosition();
}

void line::calculEquationDroite(){
    sf::Vector2f pt2 = findSecondPt();
    mA = pt2.y - mRecAfter.getPosition().y;
    mB = mRecAfter.getPosition().x - pt2.x;
    mC = - ((mB * mRecAfter.getPosition().y) + (mA * mRecAfter.getPosition().x));
    mText.setString("EQ : " + std::to_string(mA) + "x + " + std::to_string(mB) + "y + " + std::to_string(mC));
}

sf::Vector2f line::findSecondPt() const{
    bool testMode = false;
    float angle = mRecAfter.getRotation()/(180/M_PI); //en radiant
    sf::Vector2f result;
    if (angle == 0) {
        
        result = sf::Vector2f(0, mDiagonale);
        
    }else if (angle == 90){
        
        result = sf::Vector2f(mDiagonale, 0);

    }else if (angle == 180){
        
        result = sf::Vector2f(0, -mDiagonale);
        
    }else if (angle == 270){
        
        result = sf::Vector2f(-mDiagonale, 0);
        
    }else{
        
        if (angle < 90){
            angle = angle - (M_PI_2);
            result = sf::Vector2f(50*cos(angle), 50*sin(angle));
        }else if (angle > 90 && angle < 180){
            angle = angle - (M_PI);
            result = sf::Vector2f(50*sin(angle), 50*cos(angle));
        }else if (angle > 180 && angle < 270){
            angle = angle - ((3*M_PI)/2);
            result = sf::Vector2f(50*cos(angle), 50*sin(angle));
        }else{
            angle = angle - (2*M_PI);
            result = sf::Vector2f(50*sin(angle), 50*cos(angle));
        }
    }
    
    result = sf::Vector2f(result.x + mRecAfter.getPosition().x, result.y + mRecAfter.getPosition().y);
    
    if(testMode){
        sf::CircleShape c = sf::CircleShape(10);
        c.setOrigin(10,10);
        c.move(result);
        c.setFillColor(sf::Color::Yellow);
        mWin.draw(c);
    }
    return result;
}

void line::drawLine() const{
    mWin.draw(mRecBefore);
    mWin.draw(mRecAfter);
    mWin.draw(mText);
}

void line::onOffRotate(){
    mRotate = !mRotate;
}

float line::getA() const{return mA;}
float line::getB() const{return mB;}
float line::getC() const{return mC;}
