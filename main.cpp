/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:12:11 by hbaudet           #+#    #+#             */
/*   Updated: 2020/11/03 23:35:23 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

int	main(int ac, char *av[])
{
	(void)ac;
	(void)av;

	Request test("salut");

	std::cout << test;

	return 0;
}
