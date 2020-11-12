/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 22:04:01 by user42            #+#    #+#             */
/*   Updated: 2020/11/12 15:17:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <iomanip>
# include <string>

void	printIp(unsigned int ip) {
	unsigned char	m[4];
	reinterpret_cast<unsigned char*>(&ip);
	for (size_t i = 0; i < 4; i++) {
		std::cout << (unsigned int)m[i];
		if (i != 3)
			std::cout << ".";
	}
	std::cout << std::endl;
}

int main(int argc, char const *argv[])
{
	std::string strIp = "255.1.128.1";

	unsigned int final = strToIp(strIp);
	std::cout << "final: " << final << std::endl;
	printIp(final);
	return 0;
}
