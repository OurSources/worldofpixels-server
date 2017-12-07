#include "Protocol.hpp"

Protocol::VerificationState::VerificationState(uWS::Hub & h, NetworkState * upgrade, sol::state & luaState)
: NetworkState(h, 2048, upgrade) {
	group->onTransfer([this](Ws * ws) {
		ws->setUserData(reinterpret_cast<void *>());
	});
	
	group->onMessage([this](Ws * ws, const char * msg, size_t len, uWS::OpCode oc) {
		
	});
	
	group->onDisconnection([this](Ws * ws, int c, const char * msg, size_t len){
		
	});
}
