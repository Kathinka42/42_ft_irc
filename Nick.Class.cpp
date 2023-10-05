#include "Nick.Class.hpp"

/* PASS
first step, even before connecting with a nickname
entry from client: PASS <YourServerPassword>
variables:
	command = PASS
	paramVec[0] = YourServerPassword

	462	ERR_ALREADYREGISTRED
	461	ERR_NEEDMOREPARAMS
*/

Nick::Nick(Server &server, Client &client, std::string message) : Command(server, client , message){}

Nick::~Nick() {};

/* ---------------------- METHODS --------------------------------------------*/


int Nick::executeCommand(){

	Command::tokenizeMsg();
	if (Command::checkRegistrationStatus())
		return 1;
	if (checkEmptyParamter())
		return 1;

	std::string allowed_chars = "abcdefghijklmnopqrstuvwxyz0123456789{}[]\\|";
	for (size_t i = 0; i < this->_paramVec[0].length(); ++i){
        char ch = this->_paramVec[0][i];
		if (allowed_chars.find(ch) != std::string::npos){}
        else {
			// numReply(client, ERR_ERRONEUSNICKNAME(this->_hostname, client.getNickName()));
			Command::returnMsgToServer(ERR_ERRONEUSNICKNAME(this->_server->getHostname(), this->_client->getNickName()));
			return 1;
        }
	}
    // check if nickname already exists on same server
	std::vector<Client>::iterator it = this->_server->getClients().begin();
	for (;it != this->_server->getClients().end(); it++){
		if (it->getNickName() == this->_paramVec[0]){
			// numReply(client, ERR_NICKNAMEINUSE(this->_hostname, client.getNickName()));
			return 1;
        }
	}
	//if superuser, he will be welcomed.
	if (this->_client->getNickName() == "superuser") {
		// numReply(client, RPL_WELCOME(this->_hostname, client.getNickName(), client.getUserName()));
		// numReply(client, RPL_YOURHOST(this->_hostname, client.getNickName()));
		this->_client->getSu(true);
		this->_client->registerClient(SUPERUSER);
		return (0);
	}
	
	// if client typed om username, he will be welcomed after nickname
	if (this-_client->getStatus() == USERNAME) {
		this->_client->setNickName(this->_paramVec[0]);
		// numReply(client, RPL_WELCOME(this->_hostname, client.getNickName(), client.getUserName()));
		// numReply(client, RPL_YOURHOST(this->_hostname, client.getNickName()));
		this->_client->registerClient(WELCOMED);
		return (0);
	}
	else {
		this->_client->setNickName(this->_paramVec[0]);
		this->_client->registerClient(NICKNAME);
	}
	return 0;
}

int Nick::checkEmptyParamter(){
	std::cout << MAGENTA << "EMPTYPARAM\n" << RESET;
	if (this->_paramVec.empty() || this->_paramVec[0].empty()){
		Command::returnMsgToServer(ERR_NONICKNAMEGIVEN(this->_server->getHostname()));
		return (1);
	}
	return (0);
}