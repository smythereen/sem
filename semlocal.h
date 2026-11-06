/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2002-2026 John R. Smythe Jr. */
/*******************************************************************************
 * 
 *	Semaphore Local Header File
 *
 *	This file defines private structures, variables, and routines
 *	required for semaphore functions.
 ******************************************************************************/
#ifndef	SEMLOCAL_H
#define	SEMLOCAL_H

#if	defined( __cplusplus )
extern	"C"	{
#endif

#include	<fcntl.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<sys/ipc.h>
#include	<sys/mman.h>
#include	<sys/sem.h>
#include	<sys/stat.h>
#include	<sys/types.h>
#include	<sys/time.h>
#include	<unistd.h>

#include	<sem.h>

#define		MAX_SEM_ENTRIES		10

/*
 *	Semaphore Internal Structure
 */

typedef	struct	timeval	tv_t;

typedef	struct	sem_s	{
	u32		semkey;	/* Semaphore Key */
	u32		semid;	/* Semaphore ID - Zero Means call SemGet */
	tv_t		stamp;	/* A non-Zero Means Semaphore is Unused */
}	sem_t;

extern	sem_t	SemTbl[ ];

/*
 *	Sem Unit Private Functions
 */

extern	int	SemGet( u32 semkey );
extern	uchar	SemRm( u32 semkey );

#if	defined( __cplusplus )
}
#endif

#endif
