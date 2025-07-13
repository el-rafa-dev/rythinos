#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::string;
using std::vector;

#define ERR_FILE_NOTSPEC 1
#define ERR_FILE_NOTOPEN 2
#define ERR_ARG_NOTSPEC 3

#define SUCESS 0

int main(int argc, const char *args[])
{
	vector<string> passarg;

	for (int i = 1; i < argc; i++)
	{
		passarg.push_back(args[i]);
	}

	if (passarg[0] == "-f")
	{
		// the size of an vector starts on the 0

		if (passarg.size() < 2) // if a file is not specified, the size of the passarg is 1. This one is the -f arg
		{
			cout << "err: A file path must be specified\n";

			return ERR_FILE_NOTSPEC;
		}
		else
		{
			std::fstream fi(passarg[1], std::ios::in);

			if (fi.is_open())
			{
				// the line new and the code
				string linen, code;

				while (std::getline(fi, linen))
				{
					if (!linen.empty())
					{
						if (passarg.size() > 2)
						{
							if (passarg[2] == "-il")
							{
								code += linen + " ";
							}
						}
						else
						{
							code += linen + "\n"; // add a column for more organized out
						}

						
					}
				}

				fi.close();
				// write out the file
				cout << code;
				return SUCESS;
			}
			else
			{
				cout << "err: could not open the specified file\n";
				return ERR_FILE_NOTOPEN;
			}
		}
	}
	else if (passarg[0] == "-h")
	{
		cout << "[RCat (Rhythin Cat) help]\n";
		cout << "Usage:\n\tcat [option] <file> [option]\n";
		cout << "Options:\n";
		cout << "\t[-f]: use to open a file\n\t[-il]: use to print the output in-line, without line breaks\n";
		cout << "Note:\n";
		cout << "\tThe Rhythin Cat (RCat) only accepts one file... in future i will add the multifiles concatenation";
		return SUCESS;
	}
	else
	{
		cout << "rcat: \"" << passarg[0] << "\" is not a valid argument!\n";
		cout << "err: no valid argument specified... See rcat -h\n";
		return ERR_ARG_NOTSPEC;
	}

	return 0;
}
