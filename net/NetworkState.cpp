#include "NetworkState.hpp"

NetworkState::NetworkState(uWS::Hub & h, std::uint32_t maxPayload,
		NetworkState * upgrade, NetworkState * downgrade)
: group(h.createGroup<uWS::SERVER>(uWS::PERMESSAGE_DEFLATE | uWS::NO_DELAY, maxPayload)),
  upgradeState(upgrade),
  downgradeState(downgrade) {
	group->listen(uWS::TRANSFERS);
};

NetworkState::~NetworkState() {
	group->terminate();
}

void NetworkState::transfer(Ws * ws) {
	ws->transfer(group.get());
}

bool NetworkState::upgrade(Ws * ws) {
	if (upgradeState) {
		upgradeState->transfer(ws);
		return true;
	}
	return false;
}

bool NetworkState::downgrade(Ws * ws) {
	if (downgradeState) {
		downgradeState->transfer(ws);
		return true;
	}
	return false;
}
