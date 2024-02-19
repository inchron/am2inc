/* -*- C++ -*-
 *
 * FILE: dllUtils.h
 *
 * URL: $HeadURL$
 *
 * @(#) $Id$
 *
 */
#ifndef _DLL_AMALTHEA_H
#define _DLL_AMALTHEA_H

#include <qglobal.h>

/*
 * Defines 3 preprocessor symbols:
 * - MAKE_AMALTHEA_DLL  set to 1 when building the dll, else unset
 * - USE_AMALTHEA_DLL    set to 1 when using the dll, else unset
 * - EXPORT_AMALTHEA_DLL	always set, import when using the dll,
 *			export when building dll
 *
 * Pattern taken from qglobal.h
 */

#if defined( __WIN32__ ) || defined( _WIN32 )

#	if defined( MAKE_AMALTHEA_DLL )
#		if defined( USE_AMALTHEA_DLL )
#			undef USE_AMALTHEA_DLL
#		endif

#		define EXPORT_AMALTHEA_DLL Q_DECL_EXPORT
#		define EXTERN_AMALTHEA_DLL Q_DECL_IMPORT

#	else
#		if !defined( USE_AMALTHEA_DLL )
#			define USE_AMALTHEA_DLL 1
#		endif

#		define EXPORT_AMALTHEA_DLL Q_DECL_IMPORT
#		define EXTERN_AMALTHEA_DLL Q_DECL_EXPORT

#	endif


#else

#	define EXPORT_AMALTHEA_DLL
#	define EXTERN_AMALTHEA_DLL

#endif

#endif	// ifndef _DLL_AMALTHEA_H
