/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigReader.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:34:43 by user42            #+#    #+#             */
/*   Updated: 2020/11/05 12:15:18 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigReader.hpp"

ConfigReader::ConfigReader(char * const fileName, int bufferSize, char endLine):
_fileName(fileName),
_bufferSize(bufferSize),
_endLine(endLine)
{
	if ((this->_fd = open(this->_fileName, O_RDONLY)) == -1)
		throw CannotOpenFileException();
	return ;
}

ConfigReader::ConfigReader(void) {
	return ;
}

ConfigReader::ConfigReader(ConfigReader const &src) {
	if (this != &src)
		*this = src;
	return ;
}

ConfigReader::~ConfigReader(void) {
	return ;
}

ConfigReader	&ConfigReader::operator=(ConfigReader const &src) {
	if (this != &src)
		*this = src;
	return *this;
}

int          ConfigReader::readFile() {
	int							ret = this->_bufferSize;
	char						buffer[this->_bufferSize];
	std::vector<std::string>	file;
	std::string					line = "";

	for (int i = 0; i < this->_bufferSize; i++)
		buffer[i] = '\0';

	//	Reading the file and adding each line as a string to a vector
	for (ret = this->_bufferSize; ret > 0;\
	ret = read(this->_fd, buffer, this->_bufferSize)) {
		for (int i = 0; i < ret ; i++) {
			if (buffer[i] != '\n')
				line += buffer[i];
			else
			{
				file.push_back(line);
				line = "";
			}
		}
	}

	//	Get the last line, which is ignored otherwise
	if (line != "")
		file.push_back(line);
	if (ret == -1) {
		std::cerr << "error reading file" << std::endl;
		return 0;
	}

	//	Separate tokens by whitespace and putting them in a vector,
	//	then put these in another vector which contains the whole file
	for (std::vector<std::string>::iterator i = file.begin(); i != file.end(); i++) {
		std::vector<std::string>    tokens;

		if (*i != "") {
			std::istringstream iss(*i);
			std::copy(std::istream_iterator<std::string>(iss),
			std::istream_iterator<std::string>(),
			back_inserter(tokens));
			this->_file.push_back(tokens);
			tokens.clear();
		}
	}
	return 1;
}

const char		*ConfigReader::CannotOpenFileException::what() const throw() {
	return "Exception: could not open file";
}

tokenizedFile	ConfigReader::getFile() const {
	return this->_file;
}

void			ConfigReader::getFileOneLine(std::vector<std::string>	&line) const {

	for (unsigned int i = 0 ; i < this->_file.size() ; i++) {
		for (unsigned int j = 0; j < this->_file[i].size(); j++) {
			if (this->_file[i][j] != "\n")
				line.push_back(this->_file[i][j]);
		}
	}
}
