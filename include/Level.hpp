
#ifndef LEVEL_HPP
# define LEVEL_HPP

struct LevelData {
private:
	int	height;
public:
	LevelData();
};

class Level {
private:
	int			width;
	int			height;
	LevelData	*data;
public:
	Level(int width, int height);
};

#endif
