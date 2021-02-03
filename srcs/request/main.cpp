/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:12:11 by hbaudet           #+#    #+#             */
/*   Updated: 2021/02/03 12:14:30 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include <fstream>
#include <sstream>

int	main(int ac, char *av[])
{

	(void)ac;
	(void)av;

	std::ifstream get("test_us//GET");
	std::stringstream in;

	in << get.rdbuf();

	Request test(in.str().c_str());

	std::cout << test;

	return 0;
}
