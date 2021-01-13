/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:45:55 by frthierr          #+#    #+#             */
/*   Updated: 2021/01/13 15:03:33 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	int	pipefd[2];
	int	in;
	char	buffer[512] = {'\0'};
	pid_t	id;

	pipe(pipefd);
	id = fork();
	if (id) {
		close(pipefd[0]);
		dup2(STDOUT_FILENO, pipefd[1]);
		close(pipefd[1]);
		return 0;
	}
	else {
		close(pipefd[1]);
		dup2(STDIN_FILENO, pipefd[0]);
		read(pipefd[0], buffer, 12);
		printf("buffer:\n\t%s", buffer);
		close(pipefd[0]);
		return 0;
	}
	return 0;
}
