#pragma once
class Game {
public:
	Game() = default;
	virtual ~Game() = default;
	bool initialize();
	void runLoop();
	void shutdown();
};
