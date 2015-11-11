//

#ifndef CODECUP_GAMEEXCEPTION_H
#define CODECUP_GAMEEXCEPTION_H

#include <stdexcept>

class GameException : public std::runtime_error {

public:
    GameException(const std::string& reason);
};


#endif //CODECUP_GAMEEXCEPTION_H
