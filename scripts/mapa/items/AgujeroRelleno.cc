#include "AgujeroRelleno.hh"

AgujeroRelleno::AgujeroRelleno(int fila, int columna): Item(fila, columna, "agujeroRelleno", 4) {

}

void AgujeroRelleno::draw(sf::RenderWindow& window) const {
    window.draw(sprite->getSprite());
}