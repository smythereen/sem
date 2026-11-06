/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2002-2026 John R. Smythe Jr. */
/******************************************************************************
 *
 *      This file defines the following internal library function.
 *              SemGet( u32 semkey );
 ******************************************************************************/
#include	"semlocal.h"

	sem_t 	SemTbl[ MAX_SEM_ENTRIES ];

int	SemGet( u32 semkey )
{
	int		i;
	s32 		nsems  = 1; 			// nsems to pass to semget()
	s32 		semflg = IPC_CREAT | 0666; 	// semflg to pass to semget()
	sem_t	*	p;
	sem_t	*	n;

	/*
	 *	Check the Sem Table Cache
	 */

	for( p = SemTbl, i = 0; i < MAX_SEM_ENTRIES; i++, p++ ) {
		if( p->semkey != semkey ) continue;
		p->stamp.tv_sec  = 0;           /* Mark As Used */
		p->stamp.tv_usec = 0;           /* Mark As Used */
		if( p->semid ) return( i );

		/*
	 	*	Get Semaphore For Slot Found	
	 	*/

		if( ( p->semid = semget( semkey, nsems, semflg ) ) == -1 ) {
			ErrorLog( "SemGet failed: %s (errno=%u)",
                        	strerror( errno ),
                        	errno
                	);
		} 
		return( i );
	}

	/*
	*	Get Semaphore And Create New Table Entry	
	*/

	n = NULL;
	for( p = SemTbl, i = 0; i < MAX_SEM_ENTRIES; i++, p++ ) {
		if( p->semkey != 0 ) {
			if( p->stamp.tv_sec == 0 ) continue;
			if(     n == NULL ||
				( (u32)n->stamp.tv_sec > (u32)p->stamp.tv_sec ) ||
				( ( (u32)n->stamp.tv_sec == (u32)p->stamp.tv_sec  ) &&
				( (u32)n->stamp.tv_usec > (u32)p->stamp.tv_usec ) )
			) n = p;
			continue;
		}
		p->stamp.tv_sec  = 0;           /* Mark As Used */
		p->stamp.tv_usec = 0;           /* Mark As Used */
		p->semkey = semkey;
		if( ( p->semid = semget( semkey, nsems, semflg ) ) == -1 ) {
			ErrorLog( "SemGet failed: %s (errno=%u)",
                        	strerror( errno ),
                        	errno
                	);
		} 
		return( i );
	}
	if( n != NULL ) {
		n->stamp.tv_sec  = 0;           /* Mark As Used */
		n->stamp.tv_usec = 0;           /* Mark As Used */
		n->semkey = semkey;
		if( ( n->semid = semget( semkey, nsems, semflg ) ) == -1 ) {
			ErrorLog( "SemGet failed: %s (errno=%u)",
                        	strerror( errno ),
                        	errno
                	);
		} 
		return( n - SemTbl );
	}
        ErrorLog(
                "SemGet(0x%08x) SemTbl: No Free Sem Table Entries!!!",
                semkey
        );
        return( -1 );
}
