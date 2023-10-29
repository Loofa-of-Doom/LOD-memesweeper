#pragma once
class Memefield
{
public:
	enum class State
	{
		Hidden,
		Flagged,
		Revealed
	};
private:
	class Tile
	{
	public:
	private:
		State state = State::Hidden;
	};
public:
private:
	static constexpr int width = 20;
	static constexpr int height = 15;
};

