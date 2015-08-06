#include <sys/ioctl.h>
#include <stdio.h>

struct winsize w;

// return the screen width in characters
int getConsoleWidthChars(void){
   ioctl(0, TIOCGWINSZ, &w);
   return(w.ws_col);
}

// return the screen height in characters
int getConsoleHeightChars(void){
   ioctl(0, TIOCGWINSZ, &w);
   return(w.ws_row);
}

// return the screen width in pixels (graphics mode only)
int getConsoleWidthPixels(void){
   ioctl(0, TIOCGWINSZ, &w);
   return(w.ws_xpixel);
}

// return the screen height in pixels (graphics mode only)
int getConsoleHeightPixels(void){
   ioctl(0, TIOCGWINSZ, &w);
   return(w.ws_ypixel);
}

