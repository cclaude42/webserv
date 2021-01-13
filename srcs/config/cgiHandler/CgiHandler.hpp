/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 15:08:57 by frthierr          #+#    #+#             */
/*   Updated: 2021/01/13 15:09:17 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HANDLER_HPP

# define CGI_HANDLER_HPP

# include <iostream>
# include <iomanip>
# include <string>

class CgiHandler {
	public:
		CgiHandler(void);
		CgiHandler(CgiHandler const &src);
		virtual ~CgiHandler(void);

		CgiHandler   &operator=(CgiHandler const &src);

	private:
		
};

#endif
