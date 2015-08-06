/********************************************************************************
  Begin #include statements
********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "getHTMLPage.h"
#include "ParseURL.h"

/********************************************************************************

  Begin main()

ALGORITHM: Load the HTML file into a string format. Convert the string to lowercase
           for more consistent parsing. Search for a base tag and define the domain.
           Search for all of the anchor tags and parse the link address. Store all
           of the discovered links within the urls array. Prompt the user to choose
           a URL for processing. Continue looping until the user quits.

********************************************************************************/

int main ( void ) {
  int i = 0;
  char *searchURL = "www.tutorialspoint.com/c_standard_library/c_function_strstr.htm";
//  char *searchURL = "profchris.com/students/elli0208/assignment3/index.html";
  
  char *urls[500];
  char *domain = (char *)malloc(50);
  char *fragment = (char *)malloc(100);
  char *sourceHTML = (char *)malloc(800000);    

  do {                                           
                                       
    urlSplit(searchURL, domain, fragment);          // splits the URL into its domain and its trailing fragment 
    getHTML(domain, fragment, sourceHTML);          // gets the HTML source code which is stored in sourceHTML

    printf("\nAfter getHTML(): domain = %s fragment = %s\n", domain, fragment); // TEST PRINT***

    i = 0;
    while (*(sourceHTML + i))                       // sets the HTML source code to lower case characters for more consistent parsing
      *(sourceHTML+i) = tolower(*(sourceHTML + i++));
   
    i = 0;
    char *addr = strstr(sourceHTML, "<base ");      //  checks for a base tag 
    if (addr != NULL) {                         
      domain = findURL(addr);                       //  parses the domain from within the base tag
      printf("\nAfter findURL(): domain = %s fragment = %s\n", domain, fragment); // TEST PRINT***         
    }

    addr = strstr(sourceHTML, "<a ");               // finds the first anchor tag
    for (;;) {                                      // infinite loop checking for anchor tags                    
      if (addr != NULL) {                       
        urls[i] = findURL(addr++);                  // increments addr otherwise it keeps finding the same <a>
        if (strstr(urls[i], ".c") == NULL)
          urls[i] = urlCat(domain, urls[i]);
        printf("%d: %s\n\n", (i+1), urls[i]);
        i++;
      }else
        break;                                      // break out of loop once there are no more anchor tags left to parse
      addr = strstr(addr, "<a ");                   
    }

    // prompt user to continue program
    printf("Which web page would you like to parse next? Enter index # (0 to Exit): ");
    scanf("%d", &i);

    if (i) { searchURL = urls[(i-1)]; }             // user decides when to exit with a zero

  } while(i);                                       // end program loop

  return EXIT_SUCCESS;
}

