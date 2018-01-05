/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkNonLinearCell.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkNonLinearCell.h"
#include "vtkPolyData.h"
#include "vtkUnstructuredGrid.h"
#include "vtkDataSet.h"
#include "vtkObjectFactory.h"

vtkCxxRevisionMacro(vtkNonLinearCell, "$Revision: 1.1 $");

vtkNonLinearCell::vtkNonLinearCell()
{
  this->Error = 0.10;
}

void vtkNonLinearCell::Tessellate(vtkIdType vtkNotUsed(cellId), 
                                  vtkDataSet* vtkNotUsed(input), 
                                  vtkPolyData* vtkNotUsed(output), 
                                  vtkPointLocator* vtkNotUsed(locator))
{
  vtkWarningMacro(<<"This method should be implemented by a subclass");
}

void vtkNonLinearCell::Tessellate(vtkIdType vtkNotUsed(cellId), 
                                  vtkDataSet* vtkNotUsed(input), 
                                  vtkUnstructuredGrid* vtkNotUsed(output), 
                                  vtkPointLocator* vtkNotUsed(locator))
{
  vtkWarningMacro(<<"This method should be implemented by a subclass");
}
  
void vtkNonLinearCell::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  os << indent << "Error: " << this->Error << "\n";
}

