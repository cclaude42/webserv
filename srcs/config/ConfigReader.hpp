/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigReader.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:33:47 by user42            #+#    #+#             */
/*   Updated: 2021/03/25 14:20:52 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_READER_HPP

# define CONFIG_READER_HPP

# include "webserv.hpp"

# define READER_BUFFER_SIZE 1024

typedef std::vector<std::string> fileVector;

class ConfigReader {
	public:
		ConfigReader(void);
		ConfigReader(ConfigReader const &src);
		virtual	~ConfigReader(void);

		ConfigReader			&operator=(ConfigReader const &src);
		static fileVector  		readFile(const char *filename);
		static fileVector		split(std::string str, std::string charset);
		class	FileNotFoundException: public std::exception{
			virtual const char	*what() const throw();
		};
	private:
};

#endif
