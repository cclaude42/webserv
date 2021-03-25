#include <iostream>
#include <string>
#include <fstream>

int main()
{
	int err[] = {222, 400, 403, 404, 405, 410, 413};
	std::ofstream	file;

	for (int i = 0; err[i] <= 413; i++)
	{
		file.open(("srcs/config/files/default_error_pages/" + std::to_string(err[i]) + ".html").c_str(), std::ofstream::out | std::ofstream::trunc);
		file << "<!DOCTYPE html>\n<html>\n\t<title>" << err[i] << "</title>\n\t<body>\n\t\t<div>\n\t\t\t<p>This is our default custom " << err[i];
		file << " error page!</p>\n\t\t\t<p>This is great and deserves bonus points!</p>\n\t\t</div>\n\t</body>\n</html>";
		file.close();
	}

}