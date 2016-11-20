#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "cmd.h"
#include "log.h"
#include <unistd.h>

Options* parse_cmd(int argc, char *argv[]) {
    Options* options = malloc(sizeof(Options));

    int c;
    while ((c = getopt (argc, argv, "d")) != -1) {
        switch(c) {
        case 'd':
   	    LOG_PRINT("DEBUG= Yes ");
            options->debug = 1;
            break;
        default:
   	    LOG_PRINT("DEBUG= No ");
            options->debug = 0;
            break;
        }
    }

   LOG_PRINT("****************************************************");
   LOG_PRINT("Starting simpol interpreter... ");
   LOG_PRINT("****************************************************");

    /* SIMPOL INTERPRETER */ 
    printf("******************************************************\n");
    printf("* Simpol Interpreter v0.1                            *\n");
    printf("*----------------------------------------------------*\n");
    printf("* Written in C, Lex, Yacc                            *\n");
    printf("* View logs: tail -f debug.log                       *\n");
    printf("* Run command:                                       *\n");
    printf("* ./simpol-interpreter programs/<input_file>         *\n");
    printf("* ./simpol-interpreter programs/<input_file> -d      *\n");
    printf("*----------------------------------------------------*\n");
    printf("* https://github.com/edwindvinas/simpol-interpreter  *\n");
    printf("*----------------------------------------------------*\n");
    printf("* Author: edwindvinas                                *\n");
    printf("* Date:   November 19, 2016                          *\n");
    printf("******************************************************\n");
    printf("******************************************************\n");



    if (optind >= argc) {
        LOG_PRINT("ERROR: No program file/path found!");
        printf("Please provide a path to a program as the first parameter!\n");
        exit(EXIT_FAILURE);
    }
    LOG_PRINT("SIMPOL FILE: %s", argv[optind]);

    	if( access( argv[optind], F_OK ) != -1 ) {
	    // file exists
		LOG_PRINT("OK: File exist!");
		LOG_PRINT("-----------INPUT CODES----------------------------");
		//print file to log for reference
		    FILE *fp;
		    const char *file;
		    //while ((file = argv[optind]) != 0)
		    //{
		    file = argv[optind];

			if ((fp = fopen(file, "r")) != 0)
			{
			    char   buffer[4096];
			    size_t nbytes;
			    while ((nbytes = fread(buffer, sizeof(char), sizeof(buffer), fp)) != 0)
				 //fwrite(buffer, sizeof(char), nbytes, stdout);
				LOG_PRINT(buffer);
			    fclose(fp);
			}
		    //}
		LOG_PRINT("------------------------------------------------");
			
	} else {
	    // file doesn't exist
		LOG_PRINT("ERROR: File does not exist!");
	}

    options->file = argv[optind];
    return options;
}
