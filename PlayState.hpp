#pragma once

#include "State.hpp"

#include "Transition.hpp"

class PlayState : public State {
public:
	virtual void init() override;
	virtual void gotEvent(sf::Event event) override;
	virtual void update(sf::Time elapsed) override;
	virtual void render(sf::RenderWindow &window) override;

private:
	Transition trans;
};

