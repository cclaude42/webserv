/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franciszer <franciszer@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 15:46:21 by user42            #+#    #+#             */
/*   Updated: 2020/11/14 21:11:52 by franciszer       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

int main(int ac, char * const argv[])
{
    (void)ac;
    try {
        Config  config;

        t_listen    listen= {0, 80};
        
        config.parse(argv[1]); 
        // std::cout << config;
        ConfigServer    server;
        config.getConfigForRequest(server, listen, "www.example.com", "example");
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}