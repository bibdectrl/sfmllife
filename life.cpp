#include <cstdlib>					
#include <iostream>
#include <time.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

constexpr int WIDTH{80}, HEIGHT{60}, ALIVE{1}, DEAD{0};
constexpr float GRIDSIZE{10.0};

class LifeWorld {
	public:
		LifeWorld();
		LifeWorld(const LifeWorld& lw);
		int mooreNeighboursSum(int x, int y);
		void update();
		void draw();
		void draw(sf::RenderWindow& window);
	private:
        	int grid[WIDTH][HEIGHT];
		int oldGrid[WIDTH][HEIGHT];
};

LifeWorld::LifeWorld(){
 for (int i = 0; i < WIDTH; i++){
   for (int j = 0; j < HEIGHT; j++){
     grid[i][j] = (rand() % 10 < 3) ? 1 : 0;
     oldGrid[i][j] = grid[i][j];
   }
 }
}


int LifeWorld::mooreNeighboursSum(int x, int y){
  int xp = (x == WIDTH - 1) ? 0 : x + 1;
  int xm = (x == 0) ? WIDTH - 1 : x - 1;
  int yp = (y == HEIGHT - 1) ? 0 : y + 1;
  int ym = (y == 0) ? HEIGHT - 1 : y - 1;
  return grid[xp][y] + 
         grid[xm][y] +  
	 grid[x][yp] +  
	 grid[x][ym] +  
	 grid[xp][yp] + 
	 grid[xp][ym] + 
	 grid[xm][yp] + 
	 grid[xm][ym]; 
}

void LifeWorld::update(){
  for (int i = 0; i < WIDTH; i++){
    for (int j = 0; j < HEIGHT; j++){
      int n = mooreNeighboursSum(i, j);
      if (oldGrid[i][j] == DEAD){
        if (n == 3){
          grid[i][j] == 1;
        } else {
          grid[i][j] == 0;
	}
      }
      else {
        if (n == 2 || n == 3){
          grid[i][j] == 1;
	} else {
          grid[i][j] == 0;   
	}
      }	      
     }
  }
  
  for (int i = 0; i < WIDTH; i++){
    for (int j = 0; j < HEIGHT; j++){
      oldGrid[i][j] = grid[i][j];
    }
  }
}

void LifeWorld::draw(sf::RenderWindow &window){
  for (int i = 0; i < WIDTH; i++){
    for (int j = 0; j < HEIGHT; j++){
      if (grid[i][j] == ALIVE){	    
        sf::RectangleShape l_rect;
        l_rect.setFillColor(sf::Color::Red);
	l_rect.setSize(sf::Vector2f{GRIDSIZE, GRIDSIZE});
	l_rect.setPosition(i*GRIDSIZE, j*GRIDSIZE);
	window.draw(l_rect);
    }
  }
 }
}
class Game {
  public:
    Game(sf::RenderWindow &window);
    LifeWorld m_lifeWorld;
    sf::RenderWindow &m_renderWindow;
    void run();
  private:
    void update();
    void draw();
};

Game::Game(sf::RenderWindow& window) : m_renderWindow(window), m_lifeWorld(LifeWorld()) {}

void Game::update(){
  m_lifeWorld.update();
}

void Game::draw(){
  m_lifeWorld.draw(m_renderWindow);
}

void Game::run(){
  while (m_renderWindow.isOpen()){
       sf::Event event;
       while (m_renderWindow.pollEvent(event)){
          if (event.type == sf::Event::Closed){
            m_renderWindow.close();
            break;
          }
      }
      m_lifeWorld.update();
      m_lifeWorld.draw(m_renderWindow);
 }
}


int main(void){
  sf::RenderWindow window(sf::VideoMode(800, 600), "Life");
  Game game(window);
  game.run();
}
