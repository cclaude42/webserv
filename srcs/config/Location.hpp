/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:41:28 by user42            #+#    #+#             */
/*   Updated: 2020/11/13 11:40:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP

# define LOCATION_HPP

# include "Config.hpp"

class Location: public ConfigServer {
	public:
		Location(void);
		Location(Location const &src);
		virtual ~Location(void);

		Location   &operator=(Location const &src);

		friend	std::ostream &operator<<(std::ostream &out, const Location &location);

		int		parse(unsigned int &i, std::vector<std::string> &file);

	private:
		static locationParseMap parsingMap;
		static locationParseMap initLocationMap();
};

#endif
