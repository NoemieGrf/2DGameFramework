#include "../GameManagerTypeGetter.h"

class UserInputManager: public GameManagerTypeGetter<GameManagerType::UserInput>
{
public:

public:
    void Tick() override;
    void LateTick() override;

private:

};