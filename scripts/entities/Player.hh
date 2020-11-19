#pragma once
#include "../graphics/sprites/ItemSprite.hh"
#include <SFML/Graphics.hpp>
#include "../mapa/Level.hh"
#include "../mapa/StatusBar.hh"
#include "../weapons/Arma.hh"

class Player {
    public:
        Player(Level* level);
        void evaluateEvent(sf::Event event, Level& level);
        void draw(sf::RenderWindow& window) const;
        void hurt(float damage);
        Arma* getWeapon() const;
    private:
        void moveLeft(Level& level);
        void moveRight(Level& level);
        void moveUp(Level& level);
        void moveDown(Level& level);
        void evaluateLeft(Level& level);
        void evaluateRight(Level& level);
        void evaluateUp(Level& level);
        void evaluateDown(Level& level);
        void attackRight(Level& level);
        void attackLeft(Level& level);
        void attackUp(Level& level);
        void attackDown(Level& level);

        void updateSpritePosition();
        void checkItem(Level& level, Item* objItem, int desiredFila, int desiredColumna);
        void changeWeapon();
        float getVida() const;
        
        void checkCeldaObjetivo(Level& level) const;
        void die();
        int currentArma;
        std::vector<Arma*> armas; // 0 -> No arma, 1,2 -> Espada, Escudo
        int fila;
        int columna;
        ItemSprite* sprite;  //player sprite
        StatusBar* statusBar;
        int score;
};
