#include "Protocol.hpp"

Protocol::VerificationState::VerificationState(uWS::Hub & h, NetworkState * upgrade, sol::state & luaState)
: NetworkState(h, 2048, upgrade),
  log(__func__) {
	group->onTransfer([this](Ws * ws) {
		log.debug << "Socket transferred" << std::endl;
		Storage * s = new Storage{0, [](std::string) {}};
		ws->setUserData(s);
		onStepCompleted(ws, true);
	});
	
	group->onMessage([this](Ws * ws, char * msg, std::size_t len, uWS::OpCode oc) {
		Storage * s = static_cast<Storage *>(ws->getUserData());
		s->onMsg(std::string(msg, len));
	});
	
	group->onDisconnection([](Ws * ws, int c, char * msg, std::size_t len) {
		// has bug (possible use after free)
		delete static_cast<Storage *>(ws->getUserData());
	});
}

// function (SocketProperties, onCompletion);

void Protocol::VerificationState::onStepCompleted(Ws * ws, bool success = true) {
	Storage * s = static_cast<Storage *>(ws->getUserData());

	if (!success) {
		ws->close();
	}

	if (s->verifyIndex >= verifySteps.size()) {
		delete s;
		ws->setUserData(nullptr);
		upgrade(ws);
	} else {
		log.debug << "Running verify step " << s->verifyIndex << " of " << verifySteps.size() << std::endl;
		verifySteps[s->verifyIndex++](ws, [this, ws](bool success) {
			onStepCompleted(ws, success);
		});
	}
}