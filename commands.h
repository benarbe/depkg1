/*
 * =====================================================================================
 *
 *       Filename:  commands.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  22/10/2014 23:00:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Benjamin Arbe (BA), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef _commands_h
#define _commands_h

#include <apr_pools.h>

#define DEPENDS_PATH "/tmp/DEPENDS"
#define TAR_GZ_SRC "/tmp/pkg-src.tar.gz"
#define TAR_BZ2_SRC "/tmp/pkg-src.tar.bz2"
#define TAR_XZ_SRC "/tmp/pkg-src.tar.xz"
#define BUILD_DIR "/tmp/pkg-build"
#define GIT_PAT "*.git"
#define DEPEND_PAT "*DEPENDS"
#define TAR_GZ_PAT "*.tar.gz"
#define TAR_BZ2_PAT "*.tar.bz2"
#define TAR_XZ_PAT "*.tar.xz"
#define CONFIG_SCRIPT "/tmp/pkg-build/configure"

enum CommandType {
    COMMAND_NONE, COMMAND_INSTALL, COMMAND_LIST, COMMAND_FETCH,
    COMMAND_INIT, COMMAND_BUILD, COMMAND_CLEANUP
};

int Command_fetch (apr_pool_t *p, const char *url, int fetch_only);

int Command_install (apr_pool_t *p, const char *url, const char *configure_opts,
        const char *make_opts, const char *install_opts);

int Command_depends (apr_pool_t *p, const char *path);

int Command_build (apr_pool_t *p, const char *url, const char *configure_opts,
        const char *make_opts, const char *install_opts);
int Command_cleanup ();

#endif


