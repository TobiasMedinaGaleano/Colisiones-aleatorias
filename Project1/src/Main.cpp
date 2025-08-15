//Main.cpp
#include <SFML/Graphics.hpp>
#include "VectorDeRectangulos.h"

static void mostrarVectorDeColisiones(const VectorDeRectangulos& rectangulos, sf::RenderWindow& window) {
	vecDeRect rects = rectangulos.getVectorDeRectangulos();
	for (sf::RectangleShape rect : rects)
		window.draw(rect);
}

static inline sf::Vector2f procesarEntrada(const float& move) {
	sf::Vector2f vec = { 0, 0 };

	using k = sf::Keyboard;
	if (k::isKeyPressed(k::A) || k::isKeyPressed(k::Left)) vec.x = -move;
	if (k::isKeyPressed(k::D) || k::isKeyPressed(k::Right)) vec.x = move;
	if (k::isKeyPressed(k::W) || k::isKeyPressed(k::Up)) vec.y = -move;
	if (k::isKeyPressed(k::S) || k::isKeyPressed(k::Down)) vec.y = move;
	return vec;
}

static inline bool elJugadorColisionaConUnObjeto(const VectorDeRectangulos& rectangulos, const sf::FloatRect& jugador) {
	for (sf::RectangleShape rects : rectangulos.getVectorDeRectangulos()) {
		if (jugador.intersects(rects.getGlobalBounds())) {
			return true;
		}
	}
	return false;
}

static inline bool elJugadorColisiona(sf::RectangleShape jugador, const sf::Vector2f& posicionAMover, const VectorDeRectangulos& rects) {
	jugador.move(posicionAMover);
	sf::FloatRect posRect = jugador.getGlobalBounds();

	return (posRect.top < 0 || (posRect.top + posRect.height) > 800 || posRect.left < 0 || (posRect.left + posRect.width) > 1200) || elJugadorColisionaConUnObjeto(rects, jugador.getGlobalBounds());
}

int main() {
	sf::RenderWindow window(sf::VideoMode(1200, 800), "Colision aleatoria", sf::Style::Close);

	sf::Image ico;
	ico.loadFromFile("icono.png");
	window.setIcon(ico.getSize().x, ico.getSize().y, ico.getPixelsPtr());



	sf::RectangleShape jugador({ 20.f, 20.f });
	jugador.setFillColor(sf::Color::Black);
	jugador.setOrigin(10.f, 10.f);

	jugador.setPosition(600, 400);

	constexpr float velocidad = 700.f;

	VectorDeRectangulos rects;
	rects.generarRectanglesShapesAleatorios(jugador.getGlobalBounds());


	sf::Clock clock;

	while (window.isOpen()) {

		sf::Event _e;
		while (window.pollEvent(_e)) {
			if (_e.type == sf::Event::Closed) {
				window.close();
			}

			if (_e.type == sf::Event::KeyPressed) {
				if (_e.key.code == sf::Keyboard::R) {
					rects.generarRectanglesShapesAleatorios(jugador.getGlobalBounds());
				}

				if (_e.key.code == sf::Keyboard::Escape) {
					window.close();
				}
			}

		}



		float deltaTime = clock.restart().asSeconds();

		sf::Vector2f mover = procesarEntrada(velocidad * deltaTime);
		if (!elJugadorColisiona(jugador, mover, rects)) {
			jugador.move(mover);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			rects.generarRectanglesShapesAleatorios(jugador.getGlobalBounds());




		window.clear(sf::Color::White);

		mostrarVectorDeColisiones(rects, window);
		window.draw(jugador);

		window.display();
	}


	return 0;
}