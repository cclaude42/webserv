/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi_test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 10:15:30 by hbaudet           #+#    #+#             */
/*   Updated: 2021/03/01 16:14:17 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define RESET "\033[0m"

using namespace std;

int main(int ac, char **av, char **envp)
{
	cout << RED << "CGI Tester" <<"\n\n";
	cout << RESET << "Received " << ac << " args" <<'\n';
	cout << "Reading body from stdin :\n";
	cout << GREEN;

	 for (string line; getline(cin, line);) {
        cout << line << '\n';
		cerr << GREEN << "std_error>" << line << RESET << '\n';
    }
	cout << "End of Body\n";

	while (--ac >= 0)
		cout << av[ac] << '\n';
	
	cout << "\n\n" << RESET << "Env is :" << '\n';
	cout << YELLOW;


	if (!envp || !envp[0])
	{
		cout << "NO env\n" << RESET;
		return 1;
	}
	cout << "START" << '\n';
	cout << (long)envp << '\n';
	cout << envp[0];
	for (int i = 0; envp[i]; i++)
		cout << envp[i] << '\n';
	
	cout << "End of CGI-Tester";
	cout << RESET << "\n\n";

	return 1;
}