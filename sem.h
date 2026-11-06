/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2002-2026 John R. Smythe Jr. */
/*******************************************************************************
 * 
 *	Semaphore Header File
 *
 *	This file defines common structures, variables, and routines
 *	needed for semaphore access.
 ******************************************************************************/
#ifndef	SEM_H
#define	SEM_H

#if	defined( __cplusplus )
extern	"C"	{
#endif

#include	<sys/types.h>
#include	<common.h>

#define	SEM_TRC_LVL	0x08000000	/* SEM Unit's Trace Level */
#define	SEM_FREE	0	
#define	SEM_ALLO	1	

/*
 *	Global Data Prototypes
 */


/*
 *	Function Prototypes
 */

extern	uchar	SemAllo( u32 semkey );
extern	uchar	SemFree( u32 semkey );
extern	uchar	SemTest( u32 semkey );

#if	defined( __cplusplus )
}
#endif

#endif
