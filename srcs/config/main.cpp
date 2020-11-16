/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franciszer <franciszer@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 15:46:21 by user42            #+#    #+#             */
/*   Updated: 2020/11/16 22:04:22 by franciszer       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

int main(int ac, char * const argv[])
{
    (void)ac;
    try {
        Config  config;
        RequestConfig requestConfig;

        t_listen    listen= {0, 80};
        
        config.parse(argv[1]); 
        ConfigServer    server;
        requestConfig = config.getConfigForRequest(listen, "/blabla/love", "example");
        std::cout << requestConfig << std::endl;
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}