/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2002-2026 John R. Smythe Jr. */
/******************************************************************************
 *
 *      This file defines the following function.
 *              SemFree( u32 semkey );
 ******************************************************************************/
#include	"semlocal.h"

uchar	SemFree( u32 semkey )
{
struct	sembuf 		sops[ 2 ];	
	int		i;
	int		ret;
	s32		semid;
	sem_t	*	p;

	sops[ 0 ].sem_num 	= 0;
	sops[ 0 ].sem_op 	= -1; 		// Decrement semaphore
	sops[ 0 ].sem_flg 	= IPC_NOWAIT;	// Take off semaphore

	semid = 0;
	for( p = SemTbl, i = 0; i < MAX_SEM_ENTRIES; i++, p++ ) {
		if( p->semkey != semkey ) continue;
		gettimeofday( &( p->stamp ), NULL );
		if( p->semid == 0 ) return( 0 );
		semid = p->semid;
		p->semid = 0;
		break;
	}
	if( semid <= 0 ) {
		if( ( semid = semget( semkey, 1, 0 ) ) == -1 ) {
			/*
	 		*  If semaphore does not exist, return 
	 		*/
			return( 0 );
		}
	}
	if( ( semctl( semid, 0, GETVAL ) ) != 1 ) {
		/*
	 	*  If semaphore is not allocated, return 
	 	*/
		return( 0 );
	}
	if( ( ret = semop( semid, sops, 1 ) ) == -1 ) {
		ErrorLog( "SemFree failed: %s (errno=%u)",
                       	strerror( errno ),
                       	errno
               	);
	}
	return( ret );
}
