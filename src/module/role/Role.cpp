#include "Role.h"
#include <boost/regex.hpp>
#include <boost/xpressive/xpressive.hpp>
#include <stdexcept>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include "handler/Handler.h"

namespace xp = boost::xpressive;

namespace Module {
	Role::Role() : ModuleBase("Role", "role", boost::program_options::options_description("Role Module Usage")), discordIO("Role") {
		return;
	}
	
	void Role::Handler(const SleepyDiscord::Channel& channel, const SleepyDiscord::Message& message, const SleepyDiscord::User& user, const SleepyDiscord::Emoji& emoji) {
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
		for (auto args : splitedArgs) {
			if (args == this->MARKER.GRANT) {
				fGrant = true;
			}
			if (args == this->MARKER.REMOVE) {
				fRemove = true;
			}
		}
		
		if (fGrant) {
			if (!this->AddUsingMarker(message, channel.serverID, user.ID)) {
				this->discordIO.SendWithName(channel.ID, "ロール付与に失敗しました 権限等を確認してください");
			}
		}
		if (fRemove) {
		}
		return;
	}

	bool Role::AddUsingMarker(const SleepyDiscord::Message& message,
		const SleepyDiscord::Snowflake<SleepyDiscord::Server>& serverID,
		const SleepyDiscord::Snowflake<SleepyDiscord::User>& targetUserID) {
		std::vector<std::string> roleIDs = this->MentionedRoleID(message.content);
		bool ret = true;
		for (auto i : roleIDs) {
			if (!this->Add(serverID, targetUserID, i)) ret = false;
		}
		return ret;
	}

	bool Role::Add(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& serverID,
		const SleepyDiscord::Snowflake<SleepyDiscord::User>& userID,
		const SleepyDiscord::Snowflake<SleepyDiscord::Role>& roleID) {
		auto clientPtr = this->discordIO.GetClientPtr().lock();
		
		try {
			return clientPtr->addRole(serverID, userID, roleID).cast();
		}
		catch (SleepyDiscord::ErrorCode) {
			return false;
		}
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
				std::cout << (*idItr).str() << std::endl;
				ret.push_back((*idItr).str());
			}
		}
		return ret;
	}
}
