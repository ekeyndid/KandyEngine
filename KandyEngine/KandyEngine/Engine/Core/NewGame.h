#ifndef NEWGAME_H
#define NEWGAME_H

class NewGame
{
public:
	NewGame() {}
	virtual ~NewGame() {}

	virtual bool OnCreate() = 0;
	virtual void Update(const float deltaTime_) = 0;
	virtual void Render() = 0;

};
#endif // !NEWGAME_H

