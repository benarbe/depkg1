/*
 * =====================================================================================
 *
 *       Filename:  devpkg.c
 *
 *    Description:  Where main function lives
 *
 *        Version:  1.0
 *        Created:  25/01/2015 15:07:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Benjamin Arbe (BA), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <apr_general.h>
#include <apr_getopt.h>
#include <apr_strings.h>
#include <apr_lib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#include "dbg.h"
#include "db.h"
#include "commands.h"
#include "shell.h"

int
main (int argc, const char const *argv[]) {
    apr_pool_t *p = NULL;
    apr_pool_initialize ();
    apr_pool_create (&p, NULL);

    apr_getopt_t *opt;
    apr_status_t rv;

    pid_t child_pid;
    int status;
    

    char ch = '\0';
    const char *optarg = NULL;
    const char *config_opts = NULL;
    const char *install_opts = NULL;
    const char *make_opts = NULL;
    const char *url = NULL;
    enum CommandType request = COMMAND_NONE;
    
    /* Create a new process */
    child_pid = vfork();
    check (child_pid >= 0, "vfork: didn't succeed");

    if (child_pid == 0) { /* vfork returns 0 for the child */
        setuid (getuid());
    
        rv = apr_getopt_init (&opt, p, argc, argv);

        while (apr_getopt (opt, "I:Lc:m:i:d:SF:B:C", &ch, &optarg) == APR_SUCCESS) {
            switch (ch) {
                case 'I':
                    request = COMMAND_INSTALL;
                    url = optarg;
                    break;

                case 'L':
                    request = COMMAND_LIST;
                    break;

                case 'c':
                    config_opts = optarg;
                    break;

                case 'm':
                    make_opts = optarg;
                    break;

                case 'i':
                    install_opts = optarg;
                    break;

                case 'S':
                    request = COMMAND_INIT;
                    break;

                case 'F':
                    request = COMMAND_FETCH;
                    url = optarg;
                    break;

                case 'B':
                    request = COMMAND_BUILD;
                    url = optarg;
                    break;

                case 'C':
                    request = COMMAND_CLEANUP;
                    break;

            }
        }


        switch (request) {
            case COMMAND_INSTALL:
                check (url, "You must at least give a URL.");
                Command_install (p, url, config_opts, make_opts, install_opts);
                break;

            case COMMAND_LIST:
                DB_list();
                break;

            case COMMAND_FETCH:
                check (url, "You must give a URL.");
                Command_fetch (p, url, 1);
                log_info ("Downloaded to %s and in /tmp/", BUILD_DIR);
                break;

            case COMMAND_BUILD:
                check (url, "You must at least give a URL.");
                Command_build (p, url, config_opts, make_opts, install_opts);
                break;

            case COMMAND_INIT:
                _exit (0);
                //rv = DB_init();
                //check (rv == 0, "Failed to make the database.");
                break;

            case COMMAND_CLEANUP:
                Command_cleanup ();
                break;


            default:
                sentinel ("Invalid command given.");

        }

        _exit(0);

    } else { /* Parent process */
        int rc = 0;
        wait (&status); /* Wait for child to exit */
        if (request == COMMAND_BUILD) {
            /*    rc = Shell_exec (INSTALL_SH,
                "TARGET", install_opts ? install_opts : "install", NULL);
                check (rc == 0, "Failed to install.");
                
                setuid (getuid());
                rc = Shell_exec (CLEANUP_SH, NULL);
                check (rc == 0, "Failed to cleanup after build.");

                rc = DB_update (url);
                check (rc == 0, "Failed to add this package to the database.")
                Shell_exec (CLEANUP_SH, NULL);
            */
            
        } else if (request == COMMAND_INIT) {
                rc = DB_init();
                check (rc == 0, "Failed to make the database.");
        }
        
        exit(0);
    }

error:
        Shell_exec (CLEANUP_SH, NULL);
        _exit(1);
}


