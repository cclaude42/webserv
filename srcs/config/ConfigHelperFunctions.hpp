/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigHelperFunctions.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 14:26:35 by user42            #+#    #+#             */
/*   Updated: 2020/11/18 14:27:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HELPER_FUNCTIONS_HPP

# define CONFIG_HELPER_FUNCTIONS_HPP

# include <string>

bool 			isDigits(const std::string &str);
unsigned int	strToIp(std::string strIp);
std::string		removeAdjacentSlashes(std::string &str);


#endif
