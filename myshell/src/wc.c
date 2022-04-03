/* 
 * File:   wc.c
 * Author: subhrendu
 *
 * Created on 28 October, 2012, 11:16 PM
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "main_header.h"

/* Increase character and, if necessary, line counters */
     #define COUNT(c)       \
           ccount++;        \
           if ((c) == '\n') \
             lcount++;
     
     typedef unsigned long count_t;  /* Counter type */
     
     /* Current file counters: chars, words, lines */
     count_t ccount;
     count_t wcount;
     count_t lcount;
     
     /* Totals counters: chars, words, lines */
     count_t total_ccount = 0;
     count_t total_wcount = 0;
     count_t total_lcount = 0;
     
     /* Print error message and exit with error status. If PERR is not 0,
        display current errno status. */
     static void error_print (int perr, char *fmt, va_list ap){
       vfprintf (stderr, fmt, ap);
       if (perr)
         perror (" ");
       else
         fprintf (stderr, "\n");
       exit (1);  
     }
     
     /* Print error message and exit with error status. */
     static void errf (char *fmt, ...){
       va_list ap;
       
       va_start (ap, fmt);
       error_print (0, fmt, ap);
       va_end (ap);
     }
     
     /* Print error message followed by errno status and exit
        with error code. */
     static void perrf (char *fmt, ...){
       va_list ap;
       
       va_start (ap, fmt);
       error_print (1, fmt, ap);
       va_end (ap);
     }
     
     /* Output counters for given file */
     void report (char *file, count_t ccount, count_t wcount, count_t lcount){
       printf ("%6lu %6lu %6lu %s\n", lcount, wcount, ccount, file);
     }
     
     /* Return true if C is a valid word constituent */
     static int isword (unsigned char c){
       return isalpha (c);
     }
     
     
     
     int getword (FILE *fp){
       int c;
       int word = 0;
       
       if (feof (fp))
         return 0;
           
       while ((c = getc (fp)) != EOF)
         {
           if (isword (c))
             {
               wcount++;
               break;
             }
           COUNT (c);
         }
     
       for (; c != EOF; c = getc (fp))
         {
           COUNT (c);
           if (!isword (c))
             break;
         }
     
       return c != EOF;
     }
           
     /* Process file FILE. */
     void counter (char *file){
       FILE *fp = fopen (file, "r");
       
       if (!fp)
         perrf ("cannot open file `%s'", file);
     
       ccount = wcount = lcount = 0;
       while (getword (fp))
         ;
       fclose (fp);
     
       report (file, ccount, wcount, lcount);
       total_ccount += ccount;
       total_wcount += wcount;
       total_lcount += lcount;
     }
       
     int main (int argc, char **argv){
       int i;
       
       if (argc < 2)
         errf ("usage: wc FILE [FILE...]");
       
       for (i = 1; i < argc; i++)
         counter (argv[i]);
       
       if (argc > 2)
         report ("total", total_ccount, total_wcount, total_lcount);
       return 0;
     }