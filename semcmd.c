/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2002-2026 John R. Smythe Jr. */
/*******************************************************************************
 * 
 *	Program To Enable Command-Line Access to Semaphore Library Functions
 ******************************************************************************/
#include	"semlocal.h"

static	void	sem_allo( int ac, char *av[ ] )
{
	u32	semkey;
	uchar	ret;

	if( ac != 1 ) return;
	semkey = strtoul( av[ 0 ], 0, 10 );
	( (u16 *)&semkey )[ 1 ] = (u16) geteuid() & 0xFFFF;
	Trace( 0, "SemAllo( 0x%08x )", semkey );
	ret = SemAllo( semkey );
	Trace( 0, "SemAllo( 0x%08x ) = %u", semkey, ret );
	exit( ret );
}

static	void	sem_free( int ac, char *av[ ] )
{
	u32	semkey;
	uchar	ret;

	if( ac != 1 ) return;
	semkey = strtoul( av[ 0 ], 0, 10 );
	( (u16 *)&semkey )[ 1 ] = (u16) geteuid() & 0xFFFF;
	Trace( 0, "SemFree( 0x%08x )", semkey );
	ret = SemFree( semkey );
	Trace( 0, "SemFree( 0x%08x ) = %u", semkey, ret );
	exit( ret );
}

static	void	sem_test( int ac, char *av[ ] )
{
	u32	semkey;
	uchar	val;

	if( ac != 1 ) return;
	semkey = strtoul( av[ 0 ], 0, 10 );
	( (u16 *)&semkey )[ 1 ] = (u16) geteuid() & 0xFFFF;
	Trace( 0, "SemTest( 0x%08x )", semkey );
	val = SemTest( semkey );
	Trace( 0, "SemTest( 0x%08x ) = %u", semkey, val );
	exit( val );
}

static	struct	list_s	{
	char *	cmd;
	void (*func)( int ac, char *av[ ] );
}	list[ ]	=	{
	{	"semallo",	sem_allo	},
	{	"semfree",	sem_free	},
	{	"semtest",	sem_test	},
	{	(char *)0,		(void (*)( int, char *[ ] ))0	}
};

main( int ac, char * av[ ] )
{
struct	list_s		*	l;
	char		*	cp;
	int			len;

	// Trim PATH out of av[0], leaving just the file name
	if( ( cp = strrchr( av[ 0 ], '/' ) ) != NULL ) av[ 0 ] = &cp[ 1 ];

	LocalName = av[ 0 ];
	TraceLevel = SEM_TRC_LVL;
	switch( ac ) {
	default:	len = strlen( av[ 0 ] );
			for( l = list; l->cmd != (char *)0; l++ ) {
				if( strncmp( av[ 0 ], l->cmd, len ) ) continue;
				l->func( ( ac - 1 ), &av[ 1 ] );
				break;
			}
	case  1:
	case  0:	exit( 1 );
	}
}
