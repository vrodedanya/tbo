#include "logger.hpp"
#include "signal_manager.hpp"

bool tbo::logger::TurnedOn = true;

tbo::logger::Priority tbo::logger::current_priority = tbo::logger::LOW_PRIORITY;
