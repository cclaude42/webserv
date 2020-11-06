/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigServer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 15:28:08 by user42            #+#    #+#             */
/*   Updated: 2020/11/05 22:24:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigServer.hpp"

ConfigServer::ConfigServer(void):
_root("/"),
_client_body_buffer_size(8000)
{
    t_listen    listenDefault;

    listenDefault.host = "localhost";
    listenDefault.port = 80;
    this->_listen.push_back(listenDefault);

    //  maybe set default error pages
    return ;
}

ConfigServer::ConfigServer(ConfigServer const &src) {
    if (this != &src)
        *this = src;
    return ;
}

ConfigServer::~ConfigServer(void) {
    return ;
}

ConfigServer	&ConfigServer::operator=(ConfigServer const &src) {
    if (this != &src)
        *this = src;
    return *this;
}

int     ConfigServer::parse(unsigned int &index, fileVector &file) {
    std::string                 directive = "";
    fileVector                  args;
    parseMap::iterator          iter;
    parseMap::iterator          tmpIter;

    for (index ; index < file.size() && file[index] != "}"; index++) {
        if ((tmpIter = Config::parsingMap.find(file[index])) == Config::parsingMap.end()) {
            if (directive == "")
                return file[index] == "}" ? 1 : 0;
            args.push_back(file[index]);
        }
        else
        {
            (this->*iter->second)(args);
            args.clear();
            directive = "";
            iter = tmpIter;
        }
    }

    //  if listen is not set, listen to port 80 on localhost by default
    if (file[index] == "}") {
        if (this->_listen.size() == 0) {
            args.push_back("localhost");
            args.push_back("80");
            (this->*Config::parsingMap["listen"])(args);
        }
        ++index;
        return 1;
    }
    return 0;
}
