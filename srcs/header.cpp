/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 22:05:04 by cclaude           #+#    #+#             */
/*   Updated: 2020/10/31 22:32:37 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniserv.hpp"

void	fill_head(char *header)
{
	char	str[60] = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: ";

	for (int i = 0 ; i < 58 ; i++)
		header[i] = str[i];
}

int		get_length(const char *file)
{
	int			fd;
	struct stat	buf;

	fd = open(file, O_RDONLY, S_IRWXU);
	fstat(fd, &buf);

	return (buf.st_size);
}

void	fill_length(char *header, const char *file)
{
	int		div = 1000000000;
	int		size = get_length(file);
	int		i = 0;

	while (header[i])
		i++;
	while (size / div == 0 && div != 0)
		div = div / 10;
	while (div != 0)
	{
		header[i++] = size / div % 10 + 48;
		div = div / 10;
	}
	header[i++] = '\n';
	header[i++] = '\n';
}

void	fill_content(char *header, const char *file)
{
	char	buffer[50000];
	int		i = 0;
	int		j = 0;
	int		fd;

	fd = open(file, O_RDONLY, S_IRWXU);
	ft_memset(buffer, 0, 50000);
	read(fd, buffer, 50000);
	close(fd);

	while (header[i])
		i++;
	while (buffer[j])
		header[i++] = buffer[j++];
}

void	make_header(char *header, const char *file)
{
	ft_memset(header, 0, 50000);
	fill_head(header);
	fill_length(header, file);
	fill_content(header, file);
}
