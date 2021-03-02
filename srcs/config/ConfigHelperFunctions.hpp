/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigHelperFunctions.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 14:26:35 by user42            #+#    #+#             */
/*   Updated: 2021/03/01 12:15:42 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HELPER_FUNCTIONS_HPP

# include "webserv.hpp"

# define CONFIG_HELPER_FUNCTIONS_HPP

# include <string>

bool 			isDigits(const std::string &str);
unsigned int	strToIp(std::string strIp);
std::string		removeAdjacentSlashes(const std::string &str);


#endif
