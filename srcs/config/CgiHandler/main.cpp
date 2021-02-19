/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:45:55 by frthierr          #+#    #+#             */
/*   Updated: 2021/01/21 11:49:23 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char const *argv[], char **env)
{
	pid_t	id;
	int		fds[2];
	int		saveStdin;
	int		saveStdout;
	int		status;
	ssize_t	ret;
	char	readbuffer[512] = {0};
	char	buffer[512] = {0};
	std::string	io;

	// SAVING STDIN AND STDOUT IN ORDER TO TURN THEM BACK TO NORMAL LATER
	saveStdin = dup(STDIN_FILENO);
	saveStdout = dup(STDOUT_FILENO);
	
	pipe(fds);
	id = fork();

	// REPLACING STDIN AND STDOUT WITH PIPE
	dup2(fds[0], STDIN_FILENO);
	dup2(fds[1], STDOUT_FILENO);
	
	// TRANSFERING INPUT TO CHILD
	std::cout << io << std::endl;
	io = "";
	if (!id) {	
		execve("./testcgi", NULL, env);
		close(fds[0]);
		close(fds[1]);
		return 0;
	}
	else
	{
		// WAITING FOR THE CHILD PROCESS TO FINISH
		waitpid(id, &status, 0);

		// READING CHILD PROCESS' OUTPUT
		do {
			ret = read(fds[0], buffer, 512);
			for (int i = 0; i < ret ; i++)
				io += buffer[i];
		} while (ret == 512);
		// RESETING STDIN AND STDOUT BACK TO NORMAL
		dup2(saveStdin, STDIN_FILENO);
		dup2(saveStdout, STDOUT_FILENO);
		close(fds[0]);
		close(fds[1]);
		std::cout << io << std::endl;
		return 0;		
	}
	return 0;
}
