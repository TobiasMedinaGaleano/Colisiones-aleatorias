//VectorDeRectangulos.h
#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <random>

using vecDeRect = std::vector<sf::RectangleShape>;

inline float generarNumeroAleatorio(const int& min, const int& max) {
	std::random_device rd;
	std::mt19937 mt(rd());

	std::uniform_real_distribution<float> dist(min, max);
	return dist(mt);
}

class VectorDeRectangulos {
private:
	vecDeRect rectangles;

public:
	VectorDeRectangulos() = default;
	virtual ~VectorDeRectangulos() = default;

	/////////////////////////////////////////////

	VectorDeRectangulos operator=(const VectorDeRectangulos&) = delete;
	VectorDeRectangulos(const VectorDeRectangulos&) = delete;

	/////////////////////////////////////////////

	void generarRectanglesShapesAleatorios(const sf::FloatRect& jugador);
	vecDeRect getVectorDeRectangulos() const noexcept;

private:



	sf::RectangleShape generarRectangleShapeAleatorio(const sf::FloatRect& lugarAIgnorar) const noexcept;
	sf::Color generarColorAleatorio() const noexcept;
	sf::Vector2f generarPosicionAleatoria() const noexcept;
	sf::Vector2f generarTamañoAleatorio() const noexcept;


};

