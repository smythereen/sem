/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2002-2026 John R. Smythe Jr. */
/******************************************************************************
 *
 *      This file defines the following function.
 *              SemTest( semkey ); 
 *                  return 0    - calling process doesn't have to wait
 *                  return zcnt - number of processes waiting on semaphore
 ******************************************************************************/
#include	"semlocal.h"

uchar	SemTest( u32 semkey )
{
	int	zcnt;
	int	val;
	int	idx;
 
	idx = SemGet( semkey );
	if( ( val = semctl( SemTbl[ idx ].semid, 0, GETVAL ) ) == -1 ) {
		ErrorLog( "SemTest failed: %s (errno=%u)",
                        strerror( errno ),
                        errno
                );
	}
	if( ( zcnt = semctl( SemTbl[ idx ].semid, 0, GETZCNT ) ) == -1 ) {
		ErrorLog( "SemTest failed: %s (errno=%u)",
                        strerror( errno ),
                        errno
                );
	}
	if( !val && !zcnt ) return( 0 );
	return( zcnt + 1 );
}
