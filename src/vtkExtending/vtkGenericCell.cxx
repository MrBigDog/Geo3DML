/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkGenericCell.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkGenericCell.h"
#include "vtkEmptyCell.h"
#include "vtkVertex.h"
#include "vtkPolyVertex.h"
#include "vtkLine.h"
#include "vtkPolyLine.h"
#include "vtkTriangle.h"
#include "vtkTriangleStrip.h"
#include "vtkQuad.h"
#include "vtkPixel.h"
#include "vtkPolygon.h"
#include "vtkTetra.h"
#include "vtkHexahedron.h"
#include "vtkVoxel.h"
#include "vtkWedge.h"
#include "vtkPyramid.h"
#include "vtkPentagonalPrism.h"
#include "vtkHexagonalPrism.h"
#include "vtkQuadraticEdge.h"
#include "vtkQuadraticTriangle.h"
#include "vtkQuadraticQuad.h"
#include "vtkQuadraticTetra.h"
#include "vtkQuadraticHexahedron.h"
#include "vtkQuadraticWedge.h"
#include "vtkQuadraticPyramid.h"
#include "vtkConvexPointSet.h"
#include "vtkObjectFactory.h"

vtkCxxRevisionMacro(vtkGenericCell, "$Revision: 1.1 $");
vtkStandardNewMacro(vtkGenericCell);

//----------------------------------------------------------------------------
// Construct cell.
vtkGenericCell::vtkGenericCell()
{
  this->Cell = vtkEmptyCell::New();
}  

//----------------------------------------------------------------------------
vtkGenericCell::~vtkGenericCell()
{
  this->Cell->Delete();
}

//----------------------------------------------------------------------------
void vtkGenericCell::ShallowCopy(vtkCell *c)
{
  this->Cell->ShallowCopy(c);
}

//----------------------------------------------------------------------------
void vtkGenericCell::DeepCopy(vtkCell *c)
{
  this->Cell->DeepCopy(c);
}

//----------------------------------------------------------------------------
int vtkGenericCell::GetCellType()
{
  return this->Cell->GetCellType();
}

//----------------------------------------------------------------------------
int vtkGenericCell::GetCellDimension()
{
  return this->Cell->GetCellDimension();
}

//----------------------------------------------------------------------------
int vtkGenericCell::IsLinear()
{
  return this->Cell->IsLinear();
}

//----------------------------------------------------------------------------
int vtkGenericCell::RequiresInitialization()
{
  return this->Cell->RequiresInitialization();
}

//----------------------------------------------------------------------------
void vtkGenericCell::Initialize()
{
  this->Cell->Initialize();
}

//----------------------------------------------------------------------------
int vtkGenericCell::GetNumberOfEdges()
{
  return this->Cell->GetNumberOfEdges();
}

//----------------------------------------------------------------------------
int vtkGenericCell::GetNumberOfFaces()
{
  return this->Cell->GetNumberOfFaces();
}

//----------------------------------------------------------------------------
vtkCell *vtkGenericCell::GetEdge(int edgeId)
{
  return this->Cell->GetEdge(edgeId);
}

//----------------------------------------------------------------------------
vtkCell *vtkGenericCell::GetFace(int faceId)
{
  return this->Cell->GetFace(faceId);
}

//----------------------------------------------------------------------------
int vtkGenericCell::CellBoundary(int subId, double pcoords[3], vtkIdList *pts)
{
  return this->Cell->CellBoundary(subId, pcoords, pts);
}

//----------------------------------------------------------------------------
int vtkGenericCell::EvaluatePosition(double x[3], double closestPoint[3], 
                                    int& subId, double pcoords[3], 
                                    double& dist2, double *weights)
{
  return this->Cell->EvaluatePosition(x, closestPoint, subId, 
                                      pcoords, dist2, weights);
}

//----------------------------------------------------------------------------
void vtkGenericCell::EvaluateLocation(int& subId, double pcoords[3], 
                                     double x[3], double *weights)
{
  this->Cell->EvaluateLocation(subId, pcoords, x, weights);
}

//----------------------------------------------------------------------------
void vtkGenericCell::Contour(double value, vtkDataArray *cellScalars, 
                             vtkPointLocator *locator, vtkCellArray *verts, 
                             vtkCellArray *lines, vtkCellArray *polys, 
                             vtkPointData *inPd, vtkPointData *outPd,
                             vtkCellData *inCd, vtkIdType cellId,
                             vtkCellData *outCd)
{
  this->Cell->Contour(value, cellScalars, locator, verts, lines, polys,
                      inPd, outPd, inCd, cellId, outCd);
}

//----------------------------------------------------------------------------
void vtkGenericCell::Clip(double value, vtkDataArray *cellScalars, 
                          vtkPointLocator *locator, vtkCellArray *connectivity,
                          vtkPointData *inPd, vtkPointData *outPd,
                          vtkCellData *inCd, vtkIdType cellId,
                          vtkCellData *outCd, int insideOut)
{
  this->Cell->Clip(value, cellScalars, locator, connectivity, inPd,
                   outPd, inCd, cellId, outCd, insideOut);
}

//----------------------------------------------------------------------------
int vtkGenericCell::IntersectWithLine(double p1[3], double p2[3], double tol,
                                      double& t, double x[3], double pcoords[3],
                                      int& subId)
{
  return this->Cell->IntersectWithLine(p1, p2, tol, t, x, pcoords, subId);
}

//----------------------------------------------------------------------------
int vtkGenericCell::Triangulate(int index, vtkIdList *ptIds, vtkPoints *pts)
{
  return this->Cell->Triangulate(index, ptIds, pts);
}

//----------------------------------------------------------------------------
void vtkGenericCell::Derivatives(int subId, double pcoords[3], double *values, 
                                 int dim, double *derivs)
{
  this->Cell->Derivatives(subId, pcoords, values, dim, derivs);
}

//----------------------------------------------------------------------------
int vtkGenericCell::GetParametricCenter(double pcoords[3])
{
  return this->Cell->GetParametricCenter(pcoords);
}

//----------------------------------------------------------------------------
double *vtkGenericCell::GetParametricCoords()
{
  return this->Cell->GetParametricCoords();
}

//----------------------------------------------------------------------------
int vtkGenericCell::IsPrimaryCell()
{
  return this->Cell->IsPrimaryCell();
}

//----------------------------------------------------------------------------
// Set the type of dereferenced cell. Checks to see whether cell type
// has changed and creates a new cell only if necessary.
void vtkGenericCell::SetCellType(int cellType)
{
  if ( this->Cell->GetCellType() != cellType )
    {
    this->Points->UnRegister(this);
    this->PointIds->UnRegister(this);
    this->PointIds = NULL;
    this->Cell->Delete();

    switch (cellType)
      {
      case VTK_EMPTY_CELL:
        this->Cell = vtkEmptyCell::New();
        break;
      case VTK_VERTEX:
        this->Cell = vtkVertex::New();
        break;
      case VTK_POLY_VERTEX:
        this->Cell = vtkPolyVertex::New();
        break;
      case VTK_LINE:
        this->Cell = vtkLine::New();
        break;
      case VTK_POLY_LINE:
        this->Cell = vtkPolyLine::New();
        break;
      case VTK_TRIANGLE:
        this->Cell = vtkTriangle::New();
        break;
      case VTK_TRIANGLE_STRIP:
        this->Cell = vtkTriangleStrip::New();
        break;
      case VTK_POLYGON:
        this->Cell = vtkPolygon::New();
        break;
      case VTK_PIXEL:
        this->Cell = vtkPixel::New();
        break;
      case VTK_QUAD:
        this->Cell = vtkQuad::New();
        break;
      case VTK_TETRA:
        this->Cell = vtkTetra::New();
        break;
      case VTK_VOXEL:
        this->Cell = vtkVoxel::New();
        break;
      case VTK_HEXAHEDRON:
        this->Cell = vtkHexahedron::New();
        break;
      case VTK_WEDGE:
        this->Cell = vtkWedge::New();
        break;
      case VTK_PYRAMID:
        this->Cell = vtkPyramid::New();
        break;
      case VTK_PENTAGONAL_PRISM:
        this->Cell = vtkPentagonalPrism::New();
        break;
      case VTK_HEXAGONAL_PRISM:
        this->Cell = vtkHexagonalPrism::New();
        break;
      case VTK_QUADRATIC_EDGE:
        this->Cell = vtkQuadraticEdge::New();
        break;
      case VTK_QUADRATIC_TRIANGLE:
        this->Cell = vtkQuadraticTriangle::New();
        break;
      case VTK_QUADRATIC_QUAD:
        this->Cell = vtkQuadraticQuad::New();
        break;
      case VTK_QUADRATIC_TETRA:
        this->Cell = vtkQuadraticTetra::New();
        break;
      case VTK_QUADRATIC_HEXAHEDRON:
        this->Cell = vtkQuadraticHexahedron::New();
        break;
      case VTK_QUADRATIC_WEDGE:
        this->Cell = vtkQuadraticWedge::New();
        break;
      case VTK_QUADRATIC_PYRAMID:
        this->Cell = vtkQuadraticPyramid::New();
        break;
      case VTK_CONVEX_POINT_SET:
        this->Cell = vtkConvexPointSet::New();
        break;
      default:
        vtkErrorMacro(<<"Unsupported cell type! Setting to vtkEmptyCell");
        this->SetCellType(VTK_EMPTY_CELL);
      }
    this->Points = this->Cell->Points;
    this->Points->Register(this);
    this->PointIds = this->Cell->PointIds;
    this->PointIds->Register(this);
    }//need to change cell type
}

//----------------------------------------------------------------------------
void vtkGenericCell::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
  
  os << indent << "Cell:\n";
  this->Cell->PrintSelf(os,indent.GetNextIndent());
}

