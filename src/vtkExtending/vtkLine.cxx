/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkLine.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkLine.h"

#include "vtkCellArray.h"
#include "vtkCellData.h"
#include "vtkMath.h"
#include "vtkObjectFactory.h"
#include "vtkPointData.h"
#include "vtkPointLocator.h"
#include "vtkPoints.h"

vtkCxxRevisionMacro(vtkLine, "$Revision: 1.1 $");
vtkStandardNewMacro(vtkLine);

//----------------------------------------------------------------------------
// Construct the line with two points.
vtkLine::vtkLine()
{
  this->Points->SetNumberOfPoints(2);
  this->PointIds->SetNumberOfIds(2);
  for (int i = 0; i < 2; i++)
    {
    this->Points->SetPoint(i, 0.0, 0.0, 0.0);
    this->PointIds->SetId(i,0);
    }
}

//----------------------------------------------------------------------------
static const int VTK_NO_INTERSECTION=0;
static const int VTK_YES_INTERSECTION=2;
static const int VTK_ON_LINE=3;

int vtkLine::EvaluatePosition(double x[3], double* closestPoint, 
                             int& subId, double pcoords[3],
                             double& dist2, double *weights)
{
  double a1[3], a2[3];

  subId = 0;
  pcoords[1] = pcoords[2] = 0.0;

  this->Points->GetPoint(0, a1);
  this->Points->GetPoint(1, a2);

  if (closestPoint)
    {
    // DistanceToLine sets pcoords[0] to a value t, 0 <= t <= 1
    dist2 = this->DistanceToLine(x,a1,a2,pcoords[0],closestPoint);
    }

  // pcoords[0] == t, need weights to be 1-t and t
  weights[0] = 1.0 - pcoords[0];
  weights[1] = pcoords[0];

  if ( pcoords[0] < 0.0 || pcoords[0] > 1.0 )
    {
    return 0;
    }
  else
    {
    return 1;
    }
}

//----------------------------------------------------------------------------
void vtkLine::EvaluateLocation(int& vtkNotUsed(subId), double pcoords[3], 
                               double x[3], double *weights)
{
  int i;
  double a1[3], a2[3];
  this->Points->GetPoint(0, a1);
  this->Points->GetPoint(1, a2);

  for (i=0; i<3; i++) 
    {
    x[i] = a1[i] + pcoords[0]*(a2[i] - a1[i]);
    }

  weights[0] = 1.0 - pcoords[0];
  weights[1] = pcoords[0];
}

//----------------------------------------------------------------------------
// Performs intersection of two finite 3D lines. An intersection is found if
// the projection of the two lines onto the plane perpendicular to the cross
// product of the two lines intersect. The parameters (u,v) are the 
// parametric coordinates of the lines at the position of closest approach.
int vtkLine::Intersection (double a1[3], double a2[3], 
                           double b1[3], double b2[3],
                           double& u, double& v)
{
  double a21[3], b21[3], b1a1[3];
  double c[2];
  double *A[2], row1[2], row2[2];
  
  //  Initialize 
  u = v = 0.0;

  //   Determine line vectors.
  a21[0] = a2[0] - a1[0];   b21[0] = b2[0] - b1[0];   b1a1[0] = b1[0] - a1[0];
  a21[1] = a2[1] - a1[1];   b21[1] = b2[1] - b1[1];   b1a1[1] = b1[1] - a1[1];
  a21[2] = a2[2] - a1[2];   b21[2] = b2[2] - b1[2];   b1a1[2] = b1[2] - a1[2];

  //   Compute the system (least squares) matrix.
  A[0] = row1;
  A[1] = row2;
  row1[0] = vtkMath::Dot ( a21, a21 );
  row1[1] = -vtkMath::Dot ( a21, b21 );
  row2[0] = row1[1];
  row2[1] = vtkMath::Dot ( b21, b21 );

  //   Compute the least squares system constant term.
  c[0] = vtkMath::Dot ( a21, b1a1 );
  c[1] = -vtkMath::Dot ( b21, b1a1 );

  
  //  Solve the system of equations
  if ( vtkMath::SolveLinearSystem(A,c,2) == 0 )
    {
    return VTK_ON_LINE;
    }
  else 
    {
    u = c[0];
    v = c[1];
    }

  //  Check parametric coordinates for intersection.
  if ( (0.0 <= u) && (u <= 1.0) && (0.0 <= v) && (v <= 1.0) )
    {
    return VTK_YES_INTERSECTION;
    }
  else
    {
    return VTK_NO_INTERSECTION;
    }
}

//----------------------------------------------------------------------------
int vtkLine::CellBoundary(int vtkNotUsed(subId), double pcoords[3], 
                          vtkIdList *pts)
{
  pts->SetNumberOfIds(1);

  if ( pcoords[0] >= 0.5 )
    {
    pts->SetId(0,this->PointIds->GetId(1));
    if ( pcoords[0] > 1.0 )
      {
      return 0;
      }
    else
      {
      return 1;
      }
    }
  else
    {
    pts->SetId(0,this->PointIds->GetId(0));
    if ( pcoords[0] < 0.0 )
      {
      return 0;
      }
    else
      {
      return 1;
      }
    }
}

//----------------------------------------------------------------------------
//
// marching lines case table
//
typedef int VERT_LIST;

typedef struct {
  VERT_LIST verts[2];
} VERT_CASES;

static VERT_CASES vertCases[4]= {
  {{-1,-1}},
  {{1,0}},
  {{0,1}},
  {{-1,-1}}};

//----------------------------------------------------------------------------
void vtkLine::Contour(double value, vtkDataArray *cellScalars, 
                      vtkPointLocator *locator, vtkCellArray *verts, 
                      vtkCellArray *vtkNotUsed(lines), 
                      vtkCellArray *vtkNotUsed(polys), 
                      vtkPointData *inPd, vtkPointData *outPd,
                      vtkCellData *inCd, vtkIdType cellId, vtkCellData *outCd)
{
  static int CASE_MASK[2] = {1,2};
  int index, i, newCellId;
  VERT_CASES *vertCase;
  VERT_LIST *vert;
  double t, x[3], x1[3], x2[3];
  vtkIdType pts[1];

  //
  // Build the case table
  //
  for ( i=0, index = 0; i < 2; i++)
    {
    if (cellScalars->GetComponent(i,0) >= value) 
      {
      index |= CASE_MASK[i];
      }
    }

  vertCase = vertCases + index;
  vert = vertCase->verts;

  if ( vert[0] > -1 )
    {
    t = (value - cellScalars->GetComponent(vert[0],0)) /
        (cellScalars->GetComponent(vert[1],0) - 
         cellScalars->GetComponent(vert[0],0));
    this->Points->GetPoint(vert[0], x1);
    this->Points->GetPoint(vert[1], x2);
    for (i=0; i<3; i++)
      {
      x[i] = x1[i] + t * (x2[i] - x1[i]);
      }

    if ( locator->InsertUniquePoint(x, pts[0]) )
      {
      if ( outPd ) 
        {
        vtkIdType p1 = this->PointIds->GetId(vert[0]);
        vtkIdType p2 = this->PointIds->GetId(vert[1]);
        outPd->InterpolateEdge(inPd,pts[0],p1,p2,t);
        }
      }
    newCellId = verts->InsertNextCell(1,pts);
    outCd->CopyData(inCd,cellId,newCellId);
    }
}

//----------------------------------------------------------------------------
// Compute distance to finite line. Returns parametric coordinate t 
// and point location on line.
double vtkLine::DistanceToLine(double x[3], double p1[3], double p2[3], 
                              double &t, double closestPoint[3])
{
  double p21[3], denom, num;
  double *closest;
  double tolerance;
  //
  //   Determine appropriate vectors
  // 
  p21[0] = p2[0]- p1[0];
  p21[1] = p2[1]- p1[1];
  p21[2] = p2[2]- p1[2];

  //
  //   Get parametric location
  //
  num = p21[0]*(x[0]-p1[0]) + p21[1]*(x[1]-p1[1]) + p21[2]*(x[2]-p1[2]);
  denom = vtkMath::Dot(p21,p21);

  // trying to avoid an expensive fabs
  tolerance = VTK_TOL*num;
  if (tolerance < 0.0)
    {
    tolerance = -tolerance;
    }
  if ( -tolerance < denom && denom < tolerance ) //numerically bad!
    {
    closest = p1; //arbitrary, point is (numerically) far away
    }
  //
  // If parametric coordinate is within 0<=p<=1, then the point is closest to
  // the line.  Otherwise, it's closest to a point at the end of the line.
  //
  else if ( (t=num/denom) < 0.0 )
    {
    closest = p1;
    }
  else if ( t > 1.0 )
    {
    closest = p2;
    }
  else
    {
    closest = p21;
    p21[0] = p1[0] + t*p21[0];
    p21[1] = p1[1] + t*p21[1];
    p21[2] = p1[2] + t*p21[2];
    }

  closestPoint[0] = closest[0]; 
  closestPoint[1] = closest[1]; 
  closestPoint[2] = closest[2]; 
  return vtkMath::Distance2BetweenPoints(closest,x);
}

//----------------------------------------------------------------------------
//
// Determine the distance of the current vertex to the edge defined by
// the vertices provided.  Returns distance squared. Note: line is assumed
// infinite in extent.
//
double vtkLine::DistanceToLine (double x[3], double p1[3], double p2[3])
{
  int i;
  double np1[3], p1p2[3], proj, den;

  for (i=0; i<3; i++) 
    {
    np1[i] = x[i] - p1[i];
    p1p2[i] = p1[i] - p2[i];
    }

  if ( (den=vtkMath::Norm(p1p2)) != 0.0 )
    {
    for (i=0; i<3; i++)
      {
      p1p2[i] /= den;
      }
    }
  else
    {
    return vtkMath::Dot(np1,np1);
    }

  proj = vtkMath::Dot(np1,p1p2);

  return (vtkMath::Dot(np1,np1) - proj*proj);
}

//----------------------------------------------------------------------------
// Line-line intersection. Intersection has to occur within [0,1] parametric
// coordinates and with specified tolerance.
int vtkLine::IntersectWithLine(double p1[3], double p2[3], double tol, double& t,
                               double x[3], double pcoords[3], int& subId)
{
  double a1[3], a2[3];
  double projXYZ[3];
  int i;

  subId = 0;
  pcoords[1] = pcoords[2] = 0.0;

  this->Points->GetPoint(0, a1);
  this->Points->GetPoint(1, a2);

  if ( this->Intersection(p1, p2, a1, a2, t, pcoords[0]) == 
       VTK_YES_INTERSECTION )
    {
    // make sure we are within tolerance
    for (i=0; i<3; i++)
      {
      x[i] = a1[i] + pcoords[0]*(a2[i]-a1[i]);
      projXYZ[i] = p1[i] + t*(p2[i]-p1[i]);
      }
    if ( vtkMath::Distance2BetweenPoints(x,projXYZ) <= tol*tol )
      {
      return 1;
      }
    else
      {
      return 0;
      }
    }

  else //check to see if it lies within tolerance
    {
    // one of the parametric coords must be outside 0-1
    if (t < 0.0)
      {
      t = 0.0;
      if (vtkLine::DistanceToLine(p1,a1,a2,pcoords[0],x) <= tol*tol)
        {
        return 1;
        }
      else
        {
        return 0;
        }
      }
    if (t > 1.0)
      {
      t = 1.0;
      if (vtkLine::DistanceToLine(p2,a1,a2,pcoords[0],x) <= tol*tol)
        {
        return 1;
        }
      else
        {
        return 0;
        }
      }
    if (pcoords[0] < 0.0)
      {
      pcoords[0] = 0.0;
      if (vtkLine::DistanceToLine(a1,p1,p2,t,x) <= tol*tol)
        {
        return 1;
        }
      else
        {
        return 0;
        }
      }
    if (pcoords[0] > 1.0)
      {
      pcoords[0] = 1.0;
      if (vtkLine::DistanceToLine(a2,p1,p2,t,x) <= tol*tol)
        {
        return 1;
        }
      else
        {
        return 0;
        }
      }
    }
  return 0;
}

//----------------------------------------------------------------------------
int vtkLine::Triangulate(int vtkNotUsed(index), vtkIdList *ptIds, 
                         vtkPoints *pts)
{
  pts->Reset();
  ptIds->Reset();

  ptIds->InsertId(0,this->PointIds->GetId(0));
  pts->InsertPoint(0,this->Points->GetPoint(0));

  ptIds->InsertId(1,this->PointIds->GetId(1));
  pts->InsertPoint(1,this->Points->GetPoint(1));

  return 1;
}

//----------------------------------------------------------------------------
void vtkLine::Derivatives(int vtkNotUsed(subId), 
                          double vtkNotUsed(pcoords)[3], 
                          double *values, 
                          int dim, double *derivs)
{
  double x0[3], x1[3], deltaX[3];
  int i, j;

  this->Points->GetPoint(0, x0);
  this->Points->GetPoint(1, x1);

  for (i=0; i<3; i++)
    {
    deltaX[i] = x1[i] - x0[i];
    }
  for (i=0; i<dim; i++) 
    {
    for (j=0; j<3; j++)
      {
      if ( deltaX[j] != 0 )
        {
        derivs[3*i+j] = (values[2*i+1] - values[2*i]) / deltaX[j];
        }
      else
        {
        derivs[3*i+j] =0;
        }
      }
    }
}


//----------------------------------------------------------------------------
// support line clipping
typedef int LINE_LIST;
typedef struct {
       LINE_LIST lines[2];
} LINE_CASES;
 
static LINE_CASES lineCases[] = { 
{{ -1,  -1}},   // 0
{{100,   1}},   // 1
{{  0, 101}},   // 2
{{100, 101}}};  // 3

// Clip this line using scalar value provided. Like contouring, except
// that it cuts the line to produce other lines.
void vtkLine::Clip(double value, vtkDataArray *cellScalars, 
                   vtkPointLocator *locator, vtkCellArray *lines,
                   vtkPointData *inPd, vtkPointData *outPd,
                   vtkCellData *inCd, vtkIdType cellId, vtkCellData *outCd,
                   int insideOut)
{
  static int CASE_MASK[3] = {1,2};
  LINE_CASES *lineCase;
  int i, j, index, *vert, newCellId;
  vtkIdType pts[3];
  int vertexId;
  double t, x1[3], x2[3], x[3];

  // Build the case table
  if ( insideOut )
    {    
    for ( i=0, index = 0; i < 2; i++)
      {
      if (cellScalars->GetComponent(i,0) <= value)
        {
        index |= CASE_MASK[i];
        }
      }
    }    
  else
    {
    for ( i=0, index = 0; i < 2; i++)
      {
      if (cellScalars->GetComponent(i,0) > value)
        {
        index |= CASE_MASK[i];
        }
      }
    }

  // Select the case based on the index and get the list of lines for this case
  lineCase = lineCases + index;
  vert = lineCase->lines;

  // generate clipped line
  if ( vert[0] > -1 )
    {
    for (i=0; i<2; i++) // insert line
      {
      // vertex exists, and need not be interpolated
      if (vert[i] >= 100)
        {
        vertexId = vert[i] - 100;
        this->Points->GetPoint(vertexId, x);
        if ( locator->InsertUniquePoint(x, pts[i]) )
          {
          outPd->CopyData(inPd,this->PointIds->GetId(vertexId),pts[i]);
          }
        }

      else //new vertex, interpolate
        {
        t = (value - cellScalars->GetComponent(0,0)) /
            (cellScalars->GetComponent(1,0) - cellScalars->GetComponent(0,0));

        this->Points->GetPoint(0, x1);
        this->Points->GetPoint(1, x2);
        for (j=0; j<3; j++)
          {
          x[j] = x1[j] + t * (x2[j] - x1[j]);
          }

        if ( locator->InsertUniquePoint(x, pts[i]) )
          {
          vtkIdType p1 = this->PointIds->GetId(0);
          vtkIdType p2 = this->PointIds->GetId(1);
          outPd->InterpolateEdge(inPd,pts[i],p1,p2,t);
          }
        }
      }
    // check for degenerate lines
    if ( pts[0] != pts[1] ) 
      {
      newCellId = lines->InsertNextCell(2,pts);
      outCd->CopyData(inCd,cellId,newCellId);
      }
    }
}

//----------------------------------------------------------------------------
//
// Compute interpolation functions
//
void vtkLine::InterpolationFunctions(double pcoords[3], double weights[2])
{
  weights[0] = 1.0 - pcoords[0];
  weights[1] = pcoords[0];
}

//----------------------------------------------------------------------------
static double vtkLineCellPCoords[6] = {0.0,0.0,0.0, 1.0,0.0,0.0};
double *vtkLine::GetParametricCoords()
{
  return vtkLineCellPCoords;
}

//----------------------------------------------------------------------------
void vtkLine::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}

