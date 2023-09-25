/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.Class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:40:27 by kczichow          #+#    #+#             */
/*   Updated: 2023/09/25 11:17:32 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <unistd.h>
#include <poll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <map>

#define VERBOSE 0
#define DEBUG 1
#define REGISTERED 2
#define NICKNAME 3
#define USERNAME 4
#define USERLEN 9

class Client{

		protected:
			struct sockaddr_in	_clientAddr;
			struct pollfd		_clientPollfd;
			int					_clientSocket;
			std::string			_userName;
			std::string			_nickName;
			int					_status;

		public:
			Client();
			Client(std::string username, std::string nickname);
			Client (Client const &src);
			Client &operator= (Client const &src);
			~Client();

			struct sockaddr_in &getClientAddr();
			int &getClientSocket();
			int &getClientPollfdFD();
			pollfd &getClientPollfd();
			int &getRegistrationStatus();
			std::string &getNickName();
			std::string &getUserName();
			
			void setClientAddr(struct sockaddr_in &clientAddr);
			void setClientSocket(int clientSocket);
			void setClientPollfdFD (int const &fd);
			void setClientPollfdEvents (int const &event);
			void registerClient(int status);
			void setNickName(std::string nickName);
			void setFullName(std::string fullName);
		
			std::string prvMessage(std::string message, class Client &cli); //sends a private message to an user
			std::string messAge(std::string message, class Channel &chnl); //sends a message to every user inside the channel
};
