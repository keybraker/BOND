#ifndef PASS_READ_H
#define PASS_READ_H

#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string>

int
getch()
{
	int ch;
	struct termios t_old, t_new;

	tcgetattr(STDIN_FILENO, &t_old);
	t_new = t_old;
	t_new.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &t_new);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
	return ch;
}

std::string
getpass(bool show_asterisk=true)
{
	const char BACKSPACE=127;
	const char RETURN=10;

	std::string password;
	unsigned char ch=0;

	while((ch=getch())!=RETURN)
	{
		if(ch==BACKSPACE)
		{
			if(password.length()!=0)
			{
				if(show_asterisk)
				std::cout <<"\b \b";
				password.resize(password.length()-1);
			}
		}
		else
		{
			password+=ch;
			if(show_asterisk)
				std::cout <<'*';
		}
	}

	std::cout << std::endl;
	return password;
}

#endif