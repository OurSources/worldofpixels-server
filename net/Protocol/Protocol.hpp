#pragma once

#include <net/NetworkState.hpp>

#include <uWS.h>

#include <cstdint>
#include <cstddef>
#include <vector>
#include <functional>

class Protocol {
public:
	static constexpr std::uint8_t VERSION = 0x00;
	
	class VerificationState : public NetworkState {
		std::vector<std::function<void(Ws &, decltype(onStepCompleted))>> verifySteps;
		
	public:
		struct Storage {
			std::size_t verifyIndex;
			
		};
		
		VerificationState(uWS::Hub & h, NetworkState * upgrade, sol::state &);
		
		void addVerificationStep(std::function<void(Ws &, decltype(onStepCompleted))>);
		
	private:
		void onStepCompleted(Ws &, bool success);
	};
	
	class LoginState : public NetworkState {
		
	};
	
	class LobbyState : public NetworkState {
		
	};
	
	class PlayState : public NetworkState {
		
	};
	
	
	Protocol(sol::state & luaState);
};
