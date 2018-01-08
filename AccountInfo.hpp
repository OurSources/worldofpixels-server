#pragma once

#include <string>
#include <unordered_set>
#include <cstdint>

class AccountInfo {
public:
	std::uint64_t const uid;
	std::uint32_t const clr;
	std::string name;
	std::unordered_set<std::uint64_t> groups;
	bool isTemporary;

	AccountInfo(std::uint64_t uid, std::string name, std::unordered_set<std::uint64_t> groups)
	: uid(uid),
	  clr(0),
	  name(std::move(name)),
	  groups(std::move(groups)),
	  isTemporary(false) { }

	bool inGroup(std::string const & group) {
		return false; //TODO: groups.find(group) != groups.end();
	}
};