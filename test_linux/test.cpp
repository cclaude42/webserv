/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francisco <francisco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 19:30:14 by francisco         #+#    #+#             */
/*   Updated: 2021/03/12 12:28:30 by francisco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iostream"
#include <map>
#include <string>

int main(int argc, char const *argv[])
{
    // for (int i = 0; env[i]; i++)
    //     std::cout << env[i] << std::endl;
    std::map<std::string,std::string> env;

    env["PATH_INFO"] = "/directory/youpi.bla";

    char **envv = (char**)malloc(sizeof(char*) * 10);

    int i = 0;
    for (auto it = env.begin(); it != env.end(); it++) {
        env[i] = malloc(sizeof(char) * )
    }
    return 0;
}
