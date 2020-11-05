/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:29:38 by user42            #+#    #+#             */
/*   Updated: 2020/11/05 12:28:37 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP

# define CONFIG_HPP

# include "webserv.hpp"
# include "ConfigServer.hpp"
# include "ConfigReader.hpp"

class Config {
    public:
        Config(void);
        Config(Config const &src);
        virtual ~Config(void);

        Config      &operator=(Config const &src);
        int         parse(char * const filename);
    private:
        std::vector<ConfigServer>  _servers;

};

#endif
