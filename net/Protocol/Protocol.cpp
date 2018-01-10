#include "Protocol.hpp"

Protocol::Protocol(uWS::Hub & h, sol::state & luaState)
verifState(h, loginState, luaState),
loginState(),
{ }

NetworkState & Protocol::getInitialNetworkState() {
	return verifState;
}