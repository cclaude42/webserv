/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:46:12 by user42            #+#    #+#             */
/*   Updated: 2021/01/19 11:16:08 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AutoIndexGenerator.hpp" 

int main(int argc, char const *argv[])
{
    (void)argc;
	if (!argv[1])
		return 1;
    std::string const page = AutoIndexGenerator::getPage(argv[1], "localhost", 80);
    if (page == "") {
        std::cout << "Could not read directory " << argv[1] << std::endl;
    }
    std::cout << page << std::endl;
    return 0;
}
