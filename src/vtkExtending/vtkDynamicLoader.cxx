/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkDynamicLoader.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDynamicLoader.h"

#include "vtkDebugLeaks.h"

// This file is actually 3 different implementations.
// 1. HP machines which uses shl_load
// 2. Apple OSX which uses NSLinkModule
// 3. Windows which uses LoadLibrary
// 4. Most unix systems which use dlopen (default )
// Each part of the ifdef contains a complete implementation for
// the static methods of vtkDynamicLoader.  

vtkCxxRevisionMacro(vtkDynamicLoader, "$Revision: 1.21 $");

//----------------------------------------------------------------------------
// Needed when we don't use the vtkStandardNewMacro.
vtkInstantiatorNewMacro(vtkDynamicLoader);

//----------------------------------------------------------------------------
vtkDynamicLoader* vtkDynamicLoader::New()
{
#ifdef VTK_DEBUG_LEAKS
  vtkDebugLeaks::ConstructClass("vtkDynamicLoader");
#endif    
  return new vtkDynamicLoader;
}


// ---------------------------------------------------------------
// 1. Implementation for HPUX  machines
#ifdef __hpux
#define VTKDYNAMICLOADER_DEFINED 1
#include <dl.h>

vtkLibHandle vtkDynamicLoader::OpenLibrary(const char* libname )
{
  return shl_load(libname, BIND_DEFERRED | DYNAMIC_PATH, 0L);
}

int vtkDynamicLoader::CloseLibrary(vtkLibHandle lib)
{
  return 0;
}

void* vtkDynamicLoader::GetSymbolAddress(vtkLibHandle lib, const char* sym)
{ 
  void* addr;
  int status;
  
  status = shl_findsym (&lib, sym, TYPE_PROCEDURE, &addr);
  return (status < 0) ? (void*)0 : addr;
}

const char* vtkDynamicLoader::LibPrefix()
{ 
  return "lib";
}

const char* vtkDynamicLoader::LibExtension()
{
  return ".sl";
}

const char* vtkDynamicLoader::LastError()
{
  return 0;
}
#endif



// ---------------------------------------------------------------
// 2. Implementation for Darwin (including OSX) Machines

#ifdef __APPLE__
#define VTKDYNAMICLOADER_DEFINED

// Visual Age Compiler for Mac OSX does not understand this extension.
#if defined(__IBMCPP__) && !defined(__private_extern__)
# define __private_extern__
#endif

#include <mach-o/dyld.h>

vtkLibHandle vtkDynamicLoader::OpenLibrary(const char* libname )
{
  NSObjectFileImageReturnCode rc;
  NSObjectFileImage image;

  rc = NSCreateObjectFileImageFromFile(libname, &image);
  return NSLinkModule(image, libname, TRUE);
}

int vtkDynamicLoader::CloseLibrary(vtkLibHandle)
{
  return 0;
}

void* vtkDynamicLoader::GetSymbolAddress(vtkLibHandle, const char* sym)
{
  void *result = 0;
  // global 'C' symbols names are preceded with an underscore '_'
  char *_sym = new char[ strlen(sym) + 2 ];
  strcpy( _sym + 1, sym );
  _sym[0] = '_';
  if( NSIsSymbolNameDefined(_sym) )
    {
    cout << _sym << " is defined!" << endl;
    NSSymbol symbol = NSLookupAndBindSymbol(_sym);
    if(symbol)
      {
      result = NSAddressOfSymbol(symbol);
      }
    }
  else
    {
    cout << _sym << " is not defined!" << endl;
    }

  delete[] _sym;
  return result;
}

const char* vtkDynamicLoader::LibPrefix()
{
  return "lib";
}

const char* vtkDynamicLoader::LibExtension()
{
  return ".so";
}

const char* vtkDynamicLoader::LastError()
{
  return 0;
}

#endif




// ---------------------------------------------------------------
// 3. Implementation for Windows win32 code
#ifdef _WIN32
# include "vtkWindows.h"
#define VTKDYNAMICLOADER_DEFINED 1

vtkLibHandle vtkDynamicLoader::OpenLibrary(const char* libname )
{
#ifdef UNICODE
  wchar_t *libn = new wchar_t [mbstowcs(NULL, libname, 32000)+1];
  mbstowcs(libn, libname, 32000);
  vtkLibHandle ret = LoadLibrary(libn);
  delete [] libn;
  return ret;
#else
  return LoadLibrary(libname);
#endif
}

int vtkDynamicLoader::CloseLibrary(vtkLibHandle lib)
{
  return (int)FreeLibrary(static_cast<HMODULE>(lib));
}

void* vtkDynamicLoader::GetSymbolAddress(vtkLibHandle lib, const char* sym)
{ 
#if defined (UNICODE) && !defined(_MSC_VER)
  wchar_t *wsym = new wchar_t [mbstowcs(NULL, sym, 32000)+1];
  mbstowcs(wsym, sym, 32000);
  // Force GetProcAddress to return void* with a c style cast
  // This is because you can not cast a function to a void* without
  // an error on gcc 3.2 and ANSI C++, 
  void *ret = (void*)GetProcAddress(lib, wsym);
  delete [] wsym;
  return ret;
#else
  return (void*)GetProcAddress(static_cast<HMODULE>(lib), sym);
#endif
}

const char* vtkDynamicLoader::LibPrefix()
{ 
  return "";
}

const char* vtkDynamicLoader::LibExtension()
{
  return ".dll";
}

const char* vtkDynamicLoader::LastError()
{
  LPVOID lpMsgBuf;

  FormatMessage( 
                FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                NULL,
                GetLastError(),
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                (LPTSTR) &lpMsgBuf,
                0,
                NULL 
                );
  
  // Free the buffer.
  static char* str = 0;
  delete [] str;
  if (lpMsgBuf)
    {
    str = strcpy(new char[strlen((char*)lpMsgBuf)+1], (char*)lpMsgBuf);
    LocalFree( lpMsgBuf );
    }
  return str;
}

#endif

// ---------------------------------------------------------------
// 4. Implementation for default UNIX machines.
// if nothing has been defined then use this
#ifndef VTKDYNAMICLOADER_DEFINED
#define VTKDYNAMICLOADER_DEFINED
// Setup for most unix machines
#include <dlfcn.h>

vtkLibHandle vtkDynamicLoader::OpenLibrary(const char* libname )
{
  return dlopen(libname, RTLD_LAZY);
}

int vtkDynamicLoader::CloseLibrary(vtkLibHandle lib)
{
  // dlclose returns 0 on success, and non-zero on error.
  return !((int)dlclose(lib));
}

void* vtkDynamicLoader::GetSymbolAddress(vtkLibHandle lib, const char* sym)
{ 
  return dlsym(lib, sym);
}

const char* vtkDynamicLoader::LibPrefix()
{ 
  return "lib";
}

const char* vtkDynamicLoader::LibExtension()
{
  return ".so";
}

const char* vtkDynamicLoader::LastError()
{
  return dlerror(); 
}
#endif
