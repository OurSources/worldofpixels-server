#pragma once

#include <uWS.h>

#include <cstddef>
#include <functional>
#include <memory>

class NetworkState {
public:
	using Ws = uWS::WebSocket<uWS::SERVER>;
	
	std::unique_ptr<uWS::Group<uWS::SERVER>> const group;
	NetworkState * const upgradeState;
	NetworkState * const downgradeState;
	
	explicit NetworkState(uWS::Hub &, std::uint32_t maxPayload = 16384,
			NetworkState * upgrade = nullptr, NetworkState * downgrade = nullptr);
	virtual ~NetworkState();
	
	void transfer(Ws *);
	
	virtual bool upgrade(Ws *);
	virtual bool downgrade(Ws *);
};
