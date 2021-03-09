/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi_test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 10:15:30 by hbaudet           #+#    #+#             */
/*   Updated: 2021/03/04 16:41:12 by hbaudet          ###   ########.fr       */
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
	while (--ac >= 0)
		cout << av[ac] << '\n';

	cout << "Reading body from stdin :\n";
	cout << GREEN;

	string	first;

	// getline(cin, first);
	// if (first != "\r")
	// 	cerr << GREEN << "std_error>" << first << RESET << endl;
	size_t	body_size = 0;

	for (string line = "test"; 1;) {
		getline(cin, line);
		body_size += line.size();
        cout << line << endl;
		cerr << GREEN << "std_error> " << line << RESET << endl;
		cerr << "Body size : " << body_size << endl;
    }
	cout << RESET << "End of Body\n";
	
	cout << "\n\n" << RESET << "Env is :" << '\n';
	cout << YELLOW;


	if (!envp || !envp[0])
	{
		cout << "NO env\n" << RESET;
		return 1;
	}
	for (int i = 0; envp[i]; i++)
		cout << envp[i] << '\n';
	
	cout << RESET << "End of CGI-Tester\n\n";

	return 1;
}