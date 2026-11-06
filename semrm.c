/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2002-2026 John R. Smythe Jr. */
/******************************************************************************
 *
 *      This file defines the following function.
 *              SemRm( u32 semkey );
 ******************************************************************************/
#include	"semlocal.h"

uchar	SemRm( u32 semkey )
{
	u32	semid;	
	int	idx;
	int	ret;
 
	idx = SemGet( semkey );
	semid = SemTbl[ idx ].semid;
	if( !semid ) return( 0 ); 

	if( ( ret = semctl( semid, 0, IPC_RMID ) ) == -1 ) {
		ErrorLog( "SemRm failed: %s (errno=%u)",
                        strerror( errno ),
                        errno
                );
	}
	SemTbl[ idx ].semid = 0;
	gettimeofday( &( SemTbl[ idx ].stamp ), NULL );
	return( ret );
}
