#include "PlayState.hpp"

#include "BitmapText.hpp"
#include "ResourceManager.hpp"

#include <iostream>

const int BPM = 144;

void PlayState::init() {
	trans.cover(true);
	trans.reveal();

	beat.openFromFile("Resource/Music/Beat.ogg");
	beat.setLoop(true);
	beat.play();
}

void PlayState::gotEvent(sf::Event event) {

}

void PlayState::update(sf::Time elapsed) {
	// Update level timer
	levelTimer -= elapsed.asSeconds();
	if (levelTimer <= 0) {
		if (breakTime) {
			// Start level
			breakTime = false;
			levelTimer += 10;
			beatTimer = 0;
			beatCounter = -1;
		}
		else {
			// Go to break
			breakTime = true;
			levelTimer = 13.33 - beat.getPlayingOffset().asSeconds();
			trans.cover();

			breakMessage = "Level " + std::to_string(level) + " Complete!";
		}
	}

	// Update beat timer
	beatTimer -= elapsed.asSeconds();
	if (beatTimer <= 0) {
		beatTimer += 60.0f / BPM;
		beatCounter += 1;
		onBeat();
	}

	// Update level info
	if (breakTime && beatCounter >= 29 && trans.isCovered()) {
		level += 1;
		trans.reveal();
	}

	trans.update(elapsed);
}

void PlayState::render(sf::RenderWindow &window) {
	// Render backdrop
	sf::RectangleShape backdrop(sf::Vector2f(240, 135));
	backdrop.setFillColor(sf::Color(130, 190, 80));
	window.draw(backdrop);

	// Render level name
	BitmapText text(rm::loadTexture("Resource/Image/Font.png"), "Level " + std::to_string(level));
	text.setColor(sf::Color::White);
	text.setPosition(2, 2);
	window.draw(text);

	// Render transition
	window.draw(trans);

	// Render break text
	if (beatCounter >= 26) {
		text.setText(breakMessage);
		text.setPosition(120 - text.getWidth() / 2, 38);
		window.draw(text);
	}
	if (beatCounter >= 27) {
		text.setText("Perfect: ???");
		text.setPosition(120 - text.getWidth() / 2, 58);
		window.draw(text);
	}
	if (beatCounter >= 28) {
		text.setText("Attempts: ???");
		text.setPosition(120 - text.getWidth() / 2, 68);
		window.draw(text);
	}
	if (beatCounter >= 29) {
		text.setText("Moving on!");
		text.setPosition(120 - text.getWidth() / 2, 88);
		window.draw(text);
	}

	// DEBUG
	text.setText(std::to_string(levelTimer));
	text.setPosition(2, 125);
	window.draw(text);
	text.setText(std::to_string((int)beatCounter));
	text.setPosition(2, 115);
	window.draw(text);
}

void PlayState::onBeat() {
	std::cout << (breakTime ? "Break - " : "Play - ") << beatCounter << " - " << levelTimer << "\n";
}
