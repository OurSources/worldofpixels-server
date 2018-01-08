#pragma once

#include <net/NetworkState.hpp>
#include <Logger.hpp>

#include <uWS.h>
#include <sol.hpp>

#include <cstdint>
#include <cstddef>
#include <vector>
#include <functional>

class Protocol {
public:
	static constexpr std::uint8_t VERSION = 0x00;
	
	class VerificationState : public NetworkState {
		Logger log;
		std::vector<std::function<void(Ws *, std::function<void(bool)>)>> verifySteps;

	public:
		struct Storage {
			std::size_t verifyIndex;
			std::function<void(std::string)> onMsg;
			bool valid;

		};
		
		VerificationState(uWS::Hub & h, NetworkState * upgrade, sol::state &);

		void addVerificationStep(std::function<void(Ws *, std::function<void(bool)>)>);

	private:
		void onStepCompleted(Ws *, bool success);
	};
	
	class LoginState : public NetworkState {
		Logger log;
		
	};
	
	class LobbyState : public NetworkState {
		
	};
	
	class PlayState : public NetworkState {
		
	};
	
	VerificationState verifState;
	LoginState loginState;
	LobbyState lobbyState;
	PlayState playState;
	
	Protocol(sol::state & luaState);

	NetworkState & getInitialNetworkState();
};
