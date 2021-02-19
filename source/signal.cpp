#include "signal.hpp"


bool tbo::operator == (const tbo::signal& sig1, const tbo::signal& sig2)
{
	if (sig1.command == sig2.command && sig1.recipient == sig2.recipient) return true;
	else return false;
}

bool tbo::operator != (const tbo::signal& sig1, const tbo::signal& sig2)
{
	if (!(sig1 == sig2)) return true;
	else return false;
}

std::ostream& tbo::operator << (std::ostream& os, const tbo::signal& sig)
{
	os << "Recipient: " << sig.recipient << " | " << "Command: " << sig.command;
	return os;
}
