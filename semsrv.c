/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2002-2026 John R. Smythe Jr. */
/*******************************************************************************
 * 
 *	Program To Verify Semaphore Library Functions
 ******************************************************************************/
#include	"semlocal.h"

int	main( int ac, char * av[ ] )
{
	int		idx;
	int 		i;
	int 		s;
	int		val;
	sem_t	*	p;
	
	for( s = 0; s < 11; s++ ) {
		SemGet( s + 10 );
		for( p = SemTbl, i = 0; i < MAX_SEM_ENTRIES; i++, p++ ) {
			Trace( 0, "SemTbl[ %u ] = 0x%08x, %d, %d, %d", 
				i,
				p->semkey, 
				p->semid,
				p->stamp.tv_sec,
				p->stamp.tv_usec
			);
		}
		Trace( 0, "" );
	}
	for( s = 0; s < 5; s++ ) {
		SemFree( s + 10 );
		for( p = SemTbl, i = 0; i < MAX_SEM_ENTRIES; i++, p++ ) {
			Trace( 0, "SemTbl[ %u ] = 0x%08x, %d, %d, %d", 
				i,
				p->semkey, 
				p->semid,
				p->stamp.tv_sec,
				p->stamp.tv_usec
			);
		}
		Trace( 0, "" );
	}
	for( s = 3; s < 7; s++ ) {
		idx = SemGet( s + 10 );
		Trace( 0, "SemTbl[ %u ] = 0x%08x, %d, %d, %d", 
			idx,
			SemTbl[ idx ].semkey, 
			SemTbl[ idx ].semid, 
			SemTbl[ idx ].stamp.tv_sec,
			SemTbl[ idx ].stamp.tv_usec
		);
	}
	Trace( 0, "" );
	for( p = SemTbl, i = 0; i < MAX_SEM_ENTRIES; i++, p++ ) {
		Trace( 0, "SemTbl[ %u ] = 0x%08x, %d, %d, %d", 
			i,
			p->semkey, 
			p->semid,
			p->stamp.tv_sec,
			p->stamp.tv_usec
		);
	}
	idx = SemGet( 25 );
	Trace( 0, "" );
	for( p = SemTbl, i = 0; i < MAX_SEM_ENTRIES; i++, p++ ) {
		Trace( 0, "SemTbl[ %u ] = 0x%08x, %d, %d, %d", 
			i,
			p->semkey, 
			p->semid,
			p->stamp.tv_sec,
			p->stamp.tv_usec
		);
	}
	Trace( 0, "" );
	for( s = 0; s < 10; s++ ) {
		SemFree( s + 10 );
		for( p = SemTbl, i = 0; i < MAX_SEM_ENTRIES; i++, p++ ) {
			Trace( 0, "SemTbl[ %u ] = 0x%08x, %d, %d, %d", 
				i,
				p->semkey, 
				p->semid,
				p->stamp.tv_sec,
				p->stamp.tv_usec
			);
		}
		Trace( 0, "" );
	}

	SemAllo( 25 );
	val = SemTest( 25 );
	Trace( 0, "SemTest( %u ) = %u", 25, val );
	//sleep( 30 );
	SemFree( 25 );
	val = SemTest( 25 );
	Trace( 0, "SemTest( %u ) = %u", 25, val );
	//SemFree( 25 );
	exit( 0 );
}
