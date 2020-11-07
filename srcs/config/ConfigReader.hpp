/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigReader.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:33:47 by user42            #+#    #+#             */
/*   Updated: 2020/11/07 16:18:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_READER_HPP

# define CONFIG_READER_HPP

# include <iostream>
# include <iomanip>
# include <string>
# include <vector>
# include <sstream>
# include <algorithm>
# include <iterator>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# define BUFFER_SIZE 512

typedef std::vector<std::string> fileVector;

class ConfigReader {
	public:
		ConfigReader(void);
		ConfigReader(ConfigReader const &src);
		virtual	~ConfigReader(void);

		ConfigReader			&operator=(ConfigReader const &src);
		static fileVector  		readFile(const char *filename);
		static fileVector		split(std::string str, std::string charset);
	private:
};

#endif
