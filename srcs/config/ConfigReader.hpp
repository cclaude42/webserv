/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigReader.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:33:47 by user42            #+#    #+#             */
/*   Updated: 2020/11/14 14:50:28 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_READER_HPP

# define CONFIG_READER_HPP

# include <iostream>
# include <iomanip>
# include <string>
# include <vector>
# include <map>
# include <set>
# include <sstream>
# include <algorithm>
# include <iterator>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# define READER_BUFFER_SIZE 512


typedef struct	s_listen {
	unsigned int	host;
	int			port;
}				t_listen;

typedef struct  s_error_page {
	std::vector<int>    errorCodes; // all of the codes that will be redirected
	std::string         uri;		// uri to which they are redirected
}               t_error_page;

typedef struct	s_cgi_pass {
	bool		set;
	t_listen	address;
}				t_cgi_pass;

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
