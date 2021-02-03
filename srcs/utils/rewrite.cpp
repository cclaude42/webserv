/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rewrite.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 16:57:03 by hbaudet           #+#    #+#             */
/*   Updated: 2021/02/02 17:13:16 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "webserv.hpp"
#include <string>
#include <iostream>
#include <sstream>

std::string rewrite(std::string location, std::string uri, std::string path)
{
    size_t  beg = uri.find(location);
    size_t  end = beg + location.size();

    std::stringstream ret;

    std::string tmp;

    tmp = uri.substr(end);
    ret << path << tmp;
   

    return ret.str();
}

int main()
{
    std::string my_str = rewrite("/directory", "/directory/ma_page.html", "/YoupiBanane");
    
    std::cout <<my_str << std::endl;
}