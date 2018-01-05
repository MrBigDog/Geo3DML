/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkIndent.h,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

// .NAME vtkIndent - a simple class to control print indentation
// .SECTION Description
// vtkIndent is used to control indentation during the chaining print 
// process. This way nested objects can correctly indent themselves.

#ifndef __vtkIndent_h
#define __vtkIndent_h

#include "vtkSystemIncludes.h"

class vtkIndent;
VTKEXTENDING_EXPORT ostream& operator<<(ostream& os, const vtkIndent& o);

class VTKEXTENDING_EXPORT vtkIndent
{
public:
  void Delete() {delete this;};
  vtkIndent(int ind=0) {this->Indent=ind;};
  static vtkIndent *New();

  // Description:
  // Determine the next indentation level. Keep indenting by two until the 
  // max of forty.
  vtkIndent GetNextIndent();

  //BTX
  // Description:
  // Print out the indentation. Basically output a bunch of spaces.
  friend VTKEXTENDING_EXPORT ostream& operator<<(ostream& os, const vtkIndent& o);
  //ETX

protected:
  int Indent;
  
};

#endif