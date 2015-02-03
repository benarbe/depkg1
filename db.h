/*
 * =====================================================================================
 *
 *       Filename:  db.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/21/2014 04:08:18 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Benjamin F. Arbe (ba), benarbe@tuckerenergy.com
 *        Company:  Tucker Energy, Inc.
 *
 * =====================================================================================
 */

#ifndef _db_h
#define _db_h

#define DB_FILE "/usr/local/.devpkg/db"
#define DB_DIR "/usr/local/.devpkg"

int DB_init();
int DB_list();
int DB_update(const char *url);
int DB_find(const char *url);

#endif

