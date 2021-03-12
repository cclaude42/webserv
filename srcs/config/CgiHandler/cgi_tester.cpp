/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi_tester.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 11:16:55 by frthierr          #+#    #+#             */
/*   Updated: 2021/02/25 11:52:06 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iostream"

int main(int argc, char **argv, char **env) {
	std::cout << "IN CGI_TESTER" << std::endl;
	if (!env) {
		std::cout << "ENV IS NULL" << std::endl;
		return 0;
	}
	for (size_t i = 0; env[i]; i++)
		std::cout << i << ": " << env[i] << '\n';
	std::cout << "END CGI_TESTER" << std::endl;
	return 0;
}