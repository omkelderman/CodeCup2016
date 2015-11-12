#include "GameException.h"

GameException::GameException(const std::string& reason) : std::runtime_error(reason) {
}
