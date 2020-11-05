/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:12:11 by hbaudet           #+#    #+#             */
/*   Updated: 2020/11/05 17:17:20 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include <fstream>
#include <sstream>

int	main(int ac, char *av[])
{
	
	(void)ac;
	(void)av;

	std::ifstream get("test_files/GET");
	std::stringstream in;

	in << get.rdbuf();

	Request test(in.str().c_str());

	std::cout << test;

	return 0;
}
