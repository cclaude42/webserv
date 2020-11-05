/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigReader.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:33:47 by user42            #+#    #+#             */
/*   Updated: 2020/11/05 12:25:41 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_READER_HPP

# define CONFIG_READER_HPP

# include "webserv.hpp"

typedef std::vector<std::vector<std::string>> tokenizedFile;

// Usage:
// - initialize an instance of this class with the name of the file you want to read
// - call the readFile member function
// - access the file inside a string via the readFile member function

// this class reads the whole file at once, so don't use it to read an infinite file such as /dev/random

class ConfigReader {
	public:
		ConfigReader(char * const fileName, int bufferSize = 512, char endLine = '\n');
		ConfigReader(ConfigReader const &src);
		virtual	~ConfigReader(void);

		ConfigReader				&operator=(ConfigReader const &src);
		int          			readFile();
		tokenizedFile			getFile() const;
		void					getFileOneLine(std::vector<std::string>	&line) const;
		void         			close() const;

		class		CannotOpenFileException: public std::exception {
			virtual const char	*what() const throw();
		};

	private:
		ConfigReader(void);
		int							_fd;
		char*              			_fileName;
		int							_bufferSize;
		char						_endLine;
		tokenizedFile				_file;
};

#endif
