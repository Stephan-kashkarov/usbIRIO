#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include "keyreader.h"

namespace
{
    struct termios oldSettings, newSettings;

}

KeyReader::KeyReader()
{
    tcgetattr( fileno( stdin ), &oldSettings );
    newSettings = oldSettings;
    newSettings.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr( fileno( stdin ), TCSANOW, &newSettings );    
}

KeyReader::~KeyReader()
{
    tcsetattr( fileno( stdin ), TCSANOW, &oldSettings );
}

bool  KeyReader::readKey(char& key)
{
    fd_set set;
    struct timeval tv;

    tv.tv_sec = 10;
    tv.tv_usec = 0;

    FD_ZERO( &set );
    FD_SET( fileno( stdin ), &set );

    int res = select( fileno( stdin )+1, &set, NULL, NULL, &tv );

    if( res > 0 )
    {
        read( fileno( stdin ), &key, 1 );
        return true;
    }
    else if( res < 0 )
    {
        perror( "select error" );
    }
    else
    {
        printf( "\nSelect timeout\n" );
    }
    return false;
}
