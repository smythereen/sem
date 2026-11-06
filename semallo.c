/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2002-2026 John R. Smythe Jr. */
/******************************************************************************
 *
 *      This file defines the following function.
 *              SemAllo( u32 semkey );
 ******************************************************************************/
#include	"semlocal.h"

uchar	SemAllo( u32 semkey )
{
struct	sembuf 		sops[ 2 ];	
	int		idx;
	int		ret;

	// Wait for semaphore to reach zero 
	sops[ 0 ].sem_num 	= 0; 
	sops[ 0 ].sem_op 	= 0; 		// Wait for semaphore flag to become zero
	sops[ 0 ].sem_flg 	= 0; 			
	sops[ 1 ].sem_num 	= 0;
	sops[ 1 ].sem_op 	= 1; 		// Increment semaphore
	sops[ 1 ].sem_flg 	= IPC_NOWAIT;	

	idx = SemGet( semkey );
	if( ( ret = semop( SemTbl[ idx ].semid, sops, 2 ) ) == -1 ) {
		ErrorLog( "SemAllo failed: %s (errno=%u)",
                        strerror( errno ),
                        errno
                );
	}
	return( ret );
}
