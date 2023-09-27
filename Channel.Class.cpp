#include "Channel.Class.hpp"

Channel::Channel() : _channelName("Unknown"), _topicMessage("None"), \
					 _topic_restricted(true), _invite_only(false), \
					_passPhrase(""), _userlimit(-1) {}

Channel::Channel(std::string name) : _channelName(name), _topicMessage("None"), \
					 _topic_restricted(false), _invite_only(false), \
					_passPhrase(""), _userlimit(-1) {}

Channel::Channel(std::string name, bool topic, bool invite, std::string pass, int userlimit) : \
					_channelName(name),  _topicMessage("None"), \
					_topic_restricted(topic), _invite_only(invite), \
					_passPhrase(pass), _userlimit(userlimit) {}


//changes operator/kick-flag or adds a user if not in the container, returns 1 if succesfull
int Channel::give_priveleges(std::string cli) {

	if (VERBOSE)
		std::cout << "give_privileges" << std::endl;

	std::map<std::string, bool>::iterator it = _users.find(cli);
	if (it != _users.end()) {
		it->second = true;
		return (1);
	}
	else {
		if (DEBUG)
			std::cout << "No User found, returned 0" << std::endl;
		return (0);
	}
}

//changes operator/kick-flag or adds a user if not in the container, returns 1 if succesfull
int Channel::rm_priveleges(std::string cli) {

	if (VERBOSE)
		std::cout << "remove_privileges" << std::endl;

	std::map<std::string, bool>::iterator it = _users.find(cli);
	if (it != _users.end()) {
		it->second = false;
		return (1);
	}
	else {
		if (DEBUG)
			std::cout << "No User found, returned 0" << std::endl;
		return (0);
	}
}

/*
	//a client gets added with its appropriate privilieges
   The JOIN command is used by a user to request to start listening to
   the specific channel.  Servers MUST be able to parse arguments in the
   form of a list of target, but SHOULD NOT use lists when sending JOIN
   messages to clients.

   Once a user has joined a channel, he receives information about
   all commands his server receives affecting the channel.  This
   includes JOIN, MODE, KICK, PART, QUIT and of course PRIVMSG/NOTICE.
   This allows channel members to keep track of the other channel
   members, as well as channel modes.

   If a JOIN is successful, the user receives a JOIN message as
   confirmation and is then sent the channel's topic (using RPL_TOPIC) and
   the list of users who are on the channel (using RPL_NAMREPLY), which
   MUST include the user joining.

   Note that this message accepts a special argument ("0"), which is
   a special request to leave all channels the user is currently a member
   of.  The server will process this message as if the user had sent
   a PART command (See Section 3.2.2) for each channel he is a member
   of.
*/
int Channel::add_user(std::string client, bool operatorflag) {

	if (VERBOSE)
		std::cout << "add_user" << std::endl;

	std::map<std::string, bool>::iterator it = _users.find(client);
	if (it == _users.end()) {
		// if (DEBUG) {
			std::cout << "ADD_USER()" << std::endl;
			std::cout << "clientname = " << client << std::endl;
		// }

		this->_users[client] = operatorflag;
			list_clients_in_channel();
			list_channel_attributes();
		return (1);
	}
	else {
		if (DEBUG)
			std::cout << "User already exists, returned 0" << std::endl;
		return (0);
	}
}

//checks if a user is existent in this channel
bool Channel::is_in_channel(std::string name) {
	
	if (VERBOSE)
		std::cout << "is_in_channel()" << std::endl;

	std::map<std::string, bool>::iterator it = _users.find(name);
	if (it != _users.end()) {
		if (DEBUG)
			std::cout << "User found in channel, returned 1" << std::endl;
		return (true);
	}
	else {
		if (DEBUG)
			std::cout << "User not found in channel, returned 0" << std::endl;
		return (false);
	}
}

//cheks if a user is operator in this channel
bool Channel::is_operator(std::string name) {

	if (VERBOSE)
		std::cout << "is_in_channel()" << std::endl;

	std::map<std::string, bool>::iterator it = _users.find(name);
	if (it->second) {
		if (DEBUG)
			std::cout << "User is operator" << std::endl;
		return (true);
	}
	else {
		if (DEBUG)
			std::cout << "User is not operator" << std::endl;
		return (false);
	}
}

//==============================================================================
//Debugging
//lists all clients in the channel and their privileges
void Channel::list_clients_in_channel(void) {

	if (VERBOSE)
		std::cout << "list_clients_in_channel" << std::endl;

	std::map<std::string, bool>::iterator it = _users.begin();
	for ( ; it != _users.end(); it++) {
		std::cout << "Client: " << it->first << " Privilieges: " << it->second << std::endl;
	}
	std::cout << "-------------------------------------" << std::endl;
}

void Channel::list_channel_attributes(void) {

	if (VERBOSE)
		std::cout << "list_channel_attributes" << std::endl;

		std::cout << "ChannelName: " << _channelName << std::endl;
		std::cout << "TopicMessage: " << _topicMessage << std::endl;
		std::cout << "Topic restricted?: " << _topic_restricted << std::endl;
		std::cout << "Invite Only? " << _invite_only << std::endl;
		std::cout << "Password: " << _passPhrase << std::endl;
		std::cout << "Userlimit: " << _userlimit << std::endl;
	std::cout << "--------------------" << std::endl;

}

//==============================================================================
//setter
void Channel::set_users(std::map<std::string, bool> users) {_users = users;}
void Channel::set_name(std::string name) {_channelName = name;}
void Channel::set_topic(std::string message) {_topicMessage = message;}
void Channel::set_topic_restriction(bool restriction) {_topic_restricted = restriction;}
void Channel::set_invite_only(bool restriction) {_invite_only = restriction;}
void Channel::set_passphrase(std::string passphrase) {_passPhrase = passphrase;}
void Channel::set_userlimit(int limit) {_userlimit = limit;}

//getter
std::map<std::string, bool> Channel::get_users(void) {return (_users);}
std::string Channel::get_name(void) {return (_channelName);}
std::string Channel::get_topic(void) {return (_topicMessage);}
bool Channel::get_topic_restriction(void) {return (_topic_restricted);}
bool Channel::get_invite_only(void) {return (_invite_only);}
std::string Channel::get_passphrase(void) {return (_passPhrase);}
int Channel::get_userlimit(void) {return (_userlimit);}