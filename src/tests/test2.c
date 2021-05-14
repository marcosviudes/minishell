#include <unistd.h>		//necesarioi para fork;
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <sys/wait.h>	//necesario para wait();
#include <sys/ioctl.h>
#include <sys/types.h>
#include <dirent.h>
#include <signal.h>
#include <errno.h>
#include <term.h>
#include <termios.h>
#include <curses.h>

