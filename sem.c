/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2002-2026 John R. Smythe Jr. */
/*******************************************************************************
 * 
 *	Program To Verify Semaphore Library Functions
 ******************************************************************************/
#include	"semlocal.h"

static	void	sem_get( int ac, char *av[ ] )
{
	if( ac != 1 ) return;
	SemGet( strtoul( av[ 0 ], 0, 16 ) );
	exit( 0 );
}

static	void	sem_allo( int ac, char *av[ ] )
{
	if( ac != 1 ) return;
	SemAllo( strtoul( av[ 0 ], 0, 16 ) );
	exit( 0 );
}

static	void	sem_free( int ac, char *av[ ] )
{
	if( ac != 1 ) return;
	SemFree( strtoul( av[ 0 ], 0, 16 ) );
	exit( 0 );
}

static	void	sem_test( int ac, char *av[ ] )
{
	int	ret;	
	u32	semkey;

	if( ac != 1 ) return;
	semkey = strtoul( av[ 0 ], 0, 16 );
	ret = SemTest( semkey );
	Trace( 0, "SemTest( 0x%08x ) = %u", semkey, ret );
	exit( 0 );
}

static	void	sem_rm( int ac, char *av[ ] )
{
	if( ac != 1 ) return;
	SemRm( strtoul( av[ 0 ], 0, 16 ) );
	exit( 0 );
}

static	struct	list_s	{
	char *	cmd;
	void (*func)( int ac, char *av[ ] );
}	list[ ]	=	{
	{	"get",		sem_get		},
	{	"allo",		sem_allo	},
	{	"free",		sem_free	},
	{	"test",		sem_test	},
	{	"rm",		sem_rm		},
	{	(char *)0,		(void (*)( int, char *[ ] ))0	}
};

static	void	usage( char * av[ ] )
{
	fprintf( stderr,
		 "\n\tSemaphore ( sem ) - Verification Program\n\n"
		 "Usage:\n"
		 "\t%s\t a[llo]   sem_key\n"
		 "\t  \t f[ree]   sem_key\n"
		 "\t  \t g[et]    sem_key\n"
		 "\t  \t rm       sem_key\n"
		 "\t  \t t[est]   sem_key\n"
		 "\n",
		 av[ 0 ]
	);
	fflush( stderr );
	exit( 1 );
}

int	main( int ac, char * av[ ] )
{
struct	list_s	*	l;
	int		len;

	LocalName = av[ 0 ];
	TraceLevel = SEM_TRC_LVL;
	switch( ac ) {
	default:	len = strlen( av[ 1 ] );
			for( l = list; l->cmd != (char *)0; l++ ) {
				if( strncmp( av[ 1 ], l->cmd, len ) ) continue;
				l->func( ( ac - 2 ), &av[ 2 ] );
				break;
			}
	case  2:
	case  1:
	case  0:	usage( av );
	}
	exit( 0 );
}
