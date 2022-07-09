#include "Role.h"
#include <boost/regex.hpp>
#include <boost/xpressive/xpressive.hpp>
#include <stdexcept>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include "handler/Handler.h"
#include "client/MyClient.h"

namespace xp = boost::xpressive;

namespace Module {
	const std::string Role::Marker::GRANT = "grant";
	const std::string Role::Marker::REMOVE = "remove";

	const std::string Role::Info::COMMAND{"role"};
	const std::string Role::Info::MODULE_NAME{"Role"};

	Role::Role() :
		ModuleBase(
			Info::MODULE_NAME,
			Info::COMMAND)
		{}

	bool Role::ExecuteMarker(
		const SleepyDiscord::Message& message,
		const SleepyDiscord::Snowflake<SleepyDiscord::Server>& serverID,
		const SleepyDiscord::Snowflake<SleepyDiscord::User>& userID,
		const Role::Operation::RoleOperationType operation)
	{
		std::vector<std::string> roleIDs = this->MentionedRoleID(message.content);
		bool ret = true;
		for (auto i : roleIDs) {
			if (!operation(Role::Operation::Arguments{ this, serverID, userID, i })) ret = false;
		}
		return ret;
	}

	void Role::Handler(
		const SleepyDiscord::Channel& channel,
		const SleepyDiscord::Message& message,
		const SleepyDiscord::User& user,
		const SleepyDiscord::Emoji& emoji)
	{
		auto IsCommand = [&message]() {
			for (auto prefix : { ">", "!", "?", "\\" }) {
				if (boost::starts_with(message.content, prefix + std::string{ "role" })) {
					return true;
				}
			}
			return false;
		};
		if (!IsCommand()) return;
		std::vector<std::string> splitedRow;
		std::vector<std::string> splitedArgs;
		bool fGrant = false;
		bool fRemove = false;
		boost::split(splitedRow, message.content, boost::is_any_of("\n"));
		boost::split(splitedArgs, splitedRow[0], boost::is_space());
		for (auto arg : splitedArgs) {
			if (arg == Role::Marker::GRANT) fGrant = true;
			if (arg == Role::Marker::REMOVE) fRemove = true;
		}

		if (fGrant) {
			this->ExecuteMarker(message, channel.serverID, user.ID, [](Role::Operation::Arguments arg) {
				return arg.objPtr->Add(arg.serverID, arg.userID, arg.roleID);
				});
		}
		if (fRemove) {
			this->ExecuteMarker(message, channel.serverID, user.ID, [](Role::Operation::Arguments arg) {
				return arg.objPtr->Remove(arg.serverID, arg.userID, arg.roleID);
				});
		}
		return;
	}

	SleepyDiscord::BoolResponse Role::Add(
		const SleepyDiscord::Snowflake<SleepyDiscord::Server>& serverID,
		const SleepyDiscord::Snowflake<SleepyDiscord::User>& userID,
		const SleepyDiscord::Snowflake<SleepyDiscord::Role>& roleID)
	{
		auto clientPtr = MyClientClass::GetInstance();
		return clientPtr->addRole(serverID, userID, roleID);
	}

	SleepyDiscord::BoolResponse Role::Remove(
		const SleepyDiscord::Snowflake<SleepyDiscord::Server>& serverID,
		const SleepyDiscord::Snowflake<SleepyDiscord::User>& userID,
		const SleepyDiscord::Snowflake<SleepyDiscord::Role>& roleID)
	{
		auto clientPtr = MyClientClass::GetInstance();
		return clientPtr->removeRole(serverID, userID, roleID);
	}

	std::vector<std::string> Role::MentionedRoleID(const std::string& context) {
		std::vector<std::string> ret;
		xp::sregex rex = "<@&" >> (+xp::_d) >> ">";
		xp::sregex r = +xp::_d;
		xp::smatch match;
		xp::smatch idMatch;
		if (!xp::regex_search(context, match, rex)) {
			return {};
		}
		xp::sregex_token_iterator mentionItr(context.begin(), context.end(), rex, 0);
		xp::sregex_token_iterator end;
		for (; mentionItr != end; ++mentionItr) {
			std::string mention = (*mentionItr).str();
			xp::sregex_token_iterator idItr(mention.begin(), mention.end(), r, 0);
			for (; idItr != end; ++idItr) {
				ret.push_back((*idItr).str());
			}
		}
		return ret;
	}
}
