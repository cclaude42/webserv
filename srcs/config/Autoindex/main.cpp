/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:46:12 by user42            #+#    #+#             */
/*   Updated: 2020/11/18 17:20:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AutoIndexGenerator.hpp" 

int main(int argc, char const *argv[])
{
    (void)argc;
    std::string const page = AutoIndexGenerator::getPage(argv[1], "localhost", 80);
    if (page == "") {
        std::cout << "Could not read directory " << argv[1] << std::endl;
    }
    std::cout << page << std::endl;
    return 0;
}
