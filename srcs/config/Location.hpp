/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:41:28 by user42            #+#    #+#             */
/*   Updated: 2020/11/09 00:18:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP

# define LOCATION_HPP

# include "Config.hpp"

# define locationParseMap std::map<std::string, void (Location::*)(fileVector)>

class Location {
    public:
        Location(void);
        Location(Location const &src);
        virtual ~Location(void);

        Location   &operator=(Location const &src);
		int		parse(unsigned int &i, std::vector<std::string> &file);

		friend	std::ostream &operator<<(std::ostream &out, const Location &location);
    private:
        static locationParseMap locationParsingMap;
        static locationParseMap initLocationMap();
        void    addListen(std::vector<std::string> args);
        void    addRoot(std::vector<std::string> args);
        void    addErrorPage(std::vector<std::string> args);
        void    addClientBodyBufferSize(std::vector<std::string> args);
		void	addCgiParam(std::vector<std::string> args);
        void    addCgiPass(std::vector<std::string> args);

		std::string							_root;
		std::vector<t_error_page>			_error_page; // error page redirections
		int									_client_body_buffer_size; // max size for the client body, defaults to 8 000
		std::map<std::string, std::string>	_cgi_param = std::map<std::string, std::string>();
        std::string                         _cgi_pass;
		std::map<std::string, Location>		_location;

        class	ExceptionInvalidArguments: public std::exception {
			virtual const char	*what() const throw();
		};      
};

#endif
