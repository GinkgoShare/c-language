/********************************************************************************
________________________________________________________________________________
                                                                                |
PROGRAM PURPOSE: Parse URLs from HTML documents. Supporting functions to parse  |
                 the fragments of a URL or to concatenate those fragments into  |
                 a functioning URL.                                             |
                                                                                |
AUTHOR: Christopher JW Elliott                                                  |
                                                                                |
HISTORY: 2014/12/07 Version 0.9                                                 |    
________________________________________________________________________________|


********************************************************************************
Begin #include statements
********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "ParseURL.h"

/********************************************************************************
PURPOSE: Parses URL domain/fragment from a string value 

INPUTS: starting address of a <base> or <a> tag within an HTML file input as a
        string value

OUTPUTS: the parsed string value of a domain or URL fragment

ALGORITHM: This function begins parsing within an HTML <base> or <a> tag. Using
           the strstr() function, it advances to the first character position
           following the "href" attribute. It then checks for the http:// protocol
           and if it is found the function will advance to the character position
           follwing the protocol. The function now assumes we are at the first
           character of the domain or url fragment. It then counts the number of
           characters until the closing '"' character and removes trailing characters
           for proper formatting. Finally it copies the string value into the 
           returned value.
********************************************************************************/

char *findURL(char *sourceHTML) {
  int i = 0;
  char *returnAddress = (char *)malloc(100);
  sourceHTML = strstr(sourceHTML, "href=\"") + 6;       // finds instance of href attribute and increments past
  // check for an http protocol
  if (*sourceHTML == 'h' && *(sourceHTML+1) == 't') {   
    sourceHTML += 7;
    if (*sourceHTML == '/')                             // In case of an https protocol, the extra '/' character is skipped over but we
      sourceHTML++;                                     // only want to remove the '/' if it is part of the http protocol so it is within 
  }                                                     // the http condition.
  // determine string length                                                 
  while (*(sourceHTML + i) != '"')
    i++; 
  // trim characters for proper formatting                                                  
  while (i != 0 && *(sourceHTML + i) == '"' || i != 0 && *(sourceHTML + i) == '/') { 
    i--;                                                
  }
  strncpy(returnAddress, sourceHTML, (i+1));
  return returnAddress;
}

/********************************************************************************
PURPOSE: Identify and store the domain and remaining fragment within a URL

INPUTS: The URL, and pointers to char which is used to store the domain and
        fragment

ALGORITHM: Searches for the first instance of a '/' character within the URL while 
           the function counts the number of characters leading up to it. The '/'
           defines the start of the fragment and the domain can be defined as 
           the string preceding it. 
********************************************************************************/

void urlSplit(char *completeURL, char *domain, char *fragment) {
  int i = 0;
  strcpy(fragment, "");                                     // initializes fragment to "" to ensure a proper url is defined;
  while (*(completeURL + i) && *(completeURL + i) != '/')   // finds the first instance of '/' and,
    i++;                                                    // stays within the bounds of the string value
  if (*(completeURL + i)) {
    strncpy(domain, completeURL, i);                        // domain = everything up to and including '/'
    strcpy(fragment, (completeURL + i));                    // fragment = everything after '/'
  }else
    strcpy(domain, completeURL);                            // domain = everything
}

/********************************************************************************
PURPOSE: Concatenates two string values to create a properly formatted URL

INPUTS: The domain name and the fragment string values to concatenate.

OUTPUTS: A pointer to char of the concatenated URL

ALGORITHM: Allocate memory for the URL and copy the domain into the URL value.
           Check if the fragment begins with a '/' character and if not, append one
           to the end of the domain. Concatenate the fragment to the domain and 
           return the value.
********************************************************************************/

char *urlCat(char *domain, char *fragment) {
  char *url = (char *)malloc(100);
  strcpy(url, domain);
  if (*fragment != '/')
    strcat(url, "/"); // ensure the url is properly formatted
  return strcat(url, fragment);
}

