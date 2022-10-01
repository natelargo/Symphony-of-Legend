#pragma once

#include <SFML/Graphics.hpp>

class PlayState;

class Legend : public sf::Drawable, public sf::Transformable {
public:
	Legend();

	void setState(PlayState *state);
	void update(sf::Time elapsed);

	// 0 = up
	// 1 = right
	// 2 = down
	// 3 = left
	void turn(int direction);

private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	PlayState *state = nullptr;

	int facing = 1;

	sf::Sprite sprite;
};

