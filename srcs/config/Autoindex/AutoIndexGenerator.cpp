/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AutoIndexGenerator.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:29:01 by user42            #+#    #+#             */
/*   Updated: 2021/01/19 15:33:02 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AutoIndexGenerator.hpp"

AutoIndexGenerator::AutoIndexGenerator(void) {
    return ;
}

AutoIndexGenerator::AutoIndexGenerator(AutoIndexGenerator const &src) {
    (void)src;
    return ;
}

AutoIndexGenerator::~AutoIndexGenerator(void) {
    return ;
}

AutoIndexGenerator	&AutoIndexGenerator::operator=(AutoIndexGenerator const &src) {
    (void)src;
    return *this;
}

std::string         AutoIndexGenerator::getPage(const char *path, std::string const &host, int port) {
    std::string dirName(path);
    DIR *dir = opendir(path);
    std::string page =\
    "<!DOCTYPE html>\n\
    <html>\n\
    <head>\n\
            <title>" + dirName + "</title>\n\
    </head>\n\
    <body>\n\
    <h1>INDEX</h1>\n\
    <p>\n";

    if (dir == NULL) {
        std::cerr << "Error: could not open " << path << std::endl;
        return "";
    }
    if (dirName[0] != '/')
        dirName = "/" + dirName;
    for (struct dirent *dirEntry = readdir(dir); dirEntry; dirEntry = readdir(dir)) {
        page += AutoIndexGenerator::getLink(std::string(dirEntry->d_name), dirName, host, port);
    }
    page +="\
    </p>\n\
    </body>\n\
    </html>\n";
    closedir(dir);
    return page;
}

std::string         AutoIndexGenerator::getLink(std::string const &dirEntry, std::string const &dirName, std::string const &host, int port) {
    return "\t\t<p><a href=\"http://" + host + ":" + to_string(port) + dirName + "/" + dirEntry + "\">" + dirEntry + "</a></p>\n";  
}