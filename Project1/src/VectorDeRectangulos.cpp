//VectorDeRectangulos.cpp
#include "VectorDeRectangulos.h"
#include <random>

void VectorDeRectangulos::generarRectanglesShapesAleatorios(const sf::FloatRect& jugador) {
	rectangles.clear();

	for (int i = 0; i < 20; i++) {
		rectangles.push_back(generarRectangleShapeAleatorio(jugador));
	}
}

vecDeRect VectorDeRectangulos::getVectorDeRectangulos() const noexcept {
	return rectangles;
}


sf::RectangleShape VectorDeRectangulos::generarRectangleShapeAleatorio(const sf::FloatRect& lugarAIgnorar) const noexcept {

	sf::Vector2f tamaño = generarTamañoAleatorio();
	sf::RectangleShape rect(tamaño);
	rect.setOrigin(tamaño.x / 2.f, tamaño.y / 2.f);

	rect.setFillColor(generarColorAleatorio());

	rect.setOutlineColor(sf::Color::Black);

	rect.setPosition(generarPosicionAleatoria());

	sf::FloatRect rectbounds = rect.getGlobalBounds();
	for (sf::RectangleShape rectangle : rectangles) {
		if (rectbounds.intersects(rectangle.getGlobalBounds())) {
			return generarRectangleShapeAleatorio(lugarAIgnorar);
		}
	}
	if (rectbounds.intersects(lugarAIgnorar)) return generarRectangleShapeAleatorio(lugarAIgnorar);

	return rect;
}

sf::Color VectorDeRectangulos::generarColorAleatorio() const noexcept {
	return sf::Color(generarNumeroAleatorio(0, 255), generarNumeroAleatorio(0, 255), generarNumeroAleatorio(0, 255));
}

sf::Vector2f VectorDeRectangulos::generarPosicionAleatoria() const noexcept {
	return { generarNumeroAleatorio(0, 1200), generarNumeroAleatorio(0, 800) };
}

sf::Vector2f VectorDeRectangulos::generarTamañoAleatorio() const noexcept {
	return { generarNumeroAleatorio(50, 200), generarNumeroAleatorio(50, 200) };
}
