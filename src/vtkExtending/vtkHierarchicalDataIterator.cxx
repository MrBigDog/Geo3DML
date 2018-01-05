/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkHierarchicalDataIterator.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkHierarchicalDataIterator.h"

#include "vtkHierarchicalDataSet.h"
#include "vtkHierarchicalDataSetInternal.h"
#include "vtkObjectFactory.h"

vtkCxxRevisionMacro(vtkHierarchicalDataIterator, "$Revision: 1.3 $");
vtkStandardNewMacro(vtkHierarchicalDataIterator);

class vtkHierarchicalDataIteratorInternal
{
public:
  // We store two iterators.
  // DSIterator (DataSets) iterators over the levels
  // LDSIteator (LevelDataSets) iterates over the nodes in the current level
  vtkHierarchicalDataSetInternal::LevelDataSetsIterator LDSIterator;
  vtkHierarchicalDataSetInternal::DataSetsIterator DSIterator;
};

//----------------------------------------------------------------------------
vtkHierarchicalDataIterator::vtkHierarchicalDataIterator()
{
  this->DataSet = 0;
  this->Internal = new vtkHierarchicalDataIteratorInternal;
}

//----------------------------------------------------------------------------
vtkHierarchicalDataIterator::~vtkHierarchicalDataIterator()
{
  this->SetDataSet(0);
  delete this->Internal;
}

//----------------------------------------------------------------------------
void vtkHierarchicalDataIterator::SetDataSet(vtkHierarchicalDataSet* dataset)
{
  if (this->DataSet != dataset)
    {
    if (this->DataSet) 
      { 
      this->DataSet->UnRegister(this); 
      }
    this->DataSet = dataset;
    if (this->DataSet) 
      { 
      this->DataSet->Register(this); 
      this->GoToFirstItem();
      }
    this->Modified();
    }   
}

//----------------------------------------------------------------------------
void vtkHierarchicalDataIterator::GoToFirstItem()
{
  if (!this->DataSet)
    {
    vtkErrorMacro("No data object has been set.");
    return;
    }
  // Initialize to the first level
  this->Internal->DSIterator = this->DataSet->Internal->DataSets.begin();
  if ( !this->DataSet->Internal->DataSets.empty() )
    {
    // Initialize to the first node in the first level
    this->Internal->LDSIterator = this->Internal->DSIterator->begin();
    if (this->Internal->LDSIterator == this->Internal->DSIterator->end())
      {
      this->GoToNextNonEmptyLevel();
      }
    // Skip nodes with NULL dataset pointers.
    if (!this->IsDoneWithTraversal() && !this->GetCurrentDataObject())
      {
      this->GoToNextItem();
      }
    }
}

//----------------------------------------------------------------------------
void vtkHierarchicalDataIterator::GoToNextNonEmptyLevel()
{
  if (!this->IsDoneWithTraversal())
    {
    while (1)
      {
      this->Internal->DSIterator++;
      if (this->IsDoneWithTraversal())
        {
        break;
        }
      this->Internal->LDSIterator = this->Internal->DSIterator->begin();
      if (this->Internal->LDSIterator != this->Internal->DSIterator->end())
        {
        break;
        }
      }
    }
}

//----------------------------------------------------------------------------
void vtkHierarchicalDataIterator::GoToNextItem()
{
  if (!this->DataSet)
    {
    vtkErrorMacro("No data object has been set.");
    return;
    }
  if (!this->IsDoneWithTraversal())
    {
    // In case the first level is empty
    if (this->Internal->LDSIterator == this->Internal->DSIterator->end())
      {
      this->GoToNextNonEmptyLevel();
      if (this->IsDoneWithTraversal())
        {
        return;
        }
      }

    this->Internal->LDSIterator++;
    if (this->Internal->LDSIterator == this->Internal->DSIterator->end())
      {
      this->GoToNextNonEmptyLevel();
      if (this->IsDoneWithTraversal())
        {
        return;
        }
      }
    // Skip nodes with NULL dataset pointers.
    if (!this->GetCurrentDataObject())
      {
      this->GoToNextItem();
      }
    }
}

//----------------------------------------------------------------------------
int vtkHierarchicalDataIterator::IsDoneWithTraversal()
{
  if (!this->DataSet)
    {
    vtkErrorMacro("No data object has been set.");
    return 1;
    }

  if ( this->DataSet->Internal->DataSets.empty() || 
       this->Internal->DSIterator == this->DataSet->Internal->DataSets.end() )
    {
    return 1;
    }
  return 0;
}

//----------------------------------------------------------------------------
vtkDataObject* vtkHierarchicalDataIterator::GetCurrentDataObject()
{
  if ( !this->DataSet || this->DataSet->Internal->DataSets.empty() )
    {
    return 0;
    }
  return this->Internal->LDSIterator->GetPointer();
}

//----------------------------------------------------------------------------
void vtkHierarchicalDataIterator::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  os << indent << "DataSet: ";
  if (this->DataSet)
    {
    os << endl;
    this->DataSet->PrintSelf(os, indent.GetNextIndent());
    }
  else
    {
    os << "(none)" << endl;
    }
}

