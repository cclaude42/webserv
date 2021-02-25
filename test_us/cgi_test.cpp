/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi_test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 10:15:30 by hbaudet           #+#    #+#             */
/*   Updated: 2021/02/25 10:22:50 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define RESET "\033[0m"

using namespace std;

int main(int ac, char **av, char **envp)
{
	cout << RED << "CGI Tester" <<"\n\n";
	cout << RESET << "Received " << ac << " args" <<'\n';
	cout << GREEN;

	while (--ac >= 0)
		cout << av[ac] << '\n';
	
	cout << "\n" << RESET << "Env is :" << '\n';
	cout << YELLOW;

	for (int i = 0; envp[i]; i++)
		cout << envp[i] << '\n';
	
	cout << RESET << "\n\n";

	return 1;
}