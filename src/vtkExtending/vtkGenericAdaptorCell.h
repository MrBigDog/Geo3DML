/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkGenericAdaptorCell.h,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkGenericAdaptorCell - defines cell interface
// .SECTION Description
// In VTK, spatial-temporal data is defined in terms of a dataset which is
// composed of cells. The cells are topological entities over which an 
// interpolation field is applied. Cells are defined in terms of a topology
// (e.g., vertices, lines, triangles, polygons, tetrahedra, etc.), points
// that instantiate the geometry of the cells, and interpolation fields
// (in the general case one interpolation field is for geometry, the other
// is for attribute data associated with the cell).
//
// Currently most algorithms in VTK use vtkCell and vtkDataSet, which make 
// assumptions about the nature of datasets, cells, and attributes. In
// particular, this abstraction assumes that cell interpolation functions
// are linear, or products of linear functions. Further, VTK implements
// most of the interpolation functions. This implementation starts breaking
// down as the complexity of the interpolation (or basis) functions
// increases. 
//
// vtkGenericAdaptorCell addresses these issues by providing more general
// abstraction for cells. It also adopts modern C++ practices including using
// iterators. The vtkGenericAdaptorCell is designed to fit within the adaptor
// framework; meaning that it is meant to adapt VTK to external simulation
// systems (see the GenericFiltering/README.html).
//
// Please note that most cells are defined in terms of other cells (the
// boundary cells). They are also defined in terms of points, which are
// not the same as vertices (vertices are a 0-D cell; points represent a
// position in space).
//
// Another important concept is the notion of DOFNodes. These concept
// supports cell types with complex interpolation functions. For example,
// higher-order p-method finite elements may have different functions on each
// of their topological features (edges, faces, region). The coefficients of
// these polynomial functions are associated with DOFNodes. (There is a
// single DOFNode for each topological feature.) Note that from this
// perspective, points are used to establish the topological form of the 
// cell; mid-side nodes and such are considered DOFNodes.

// .SECTION See Also
// vtkGenericDataSet

#ifndef __vtkGenericAdaptorCell_h
#define __vtkGenericAdaptorCell_h


#include "vtkObject.h"

class vtkLine;
class vtkTetra;
class vtkPoints;
class vtkPointLocator;
class vtkVertex;
class vtkTriangle;
class vtkCellData;
class vtkPointData;
class vtkCellArray;
class vtkDoubleArray;
class vtkGenericCellIterator;
class vtkPointLocator;
class vtkContourValues;
class vtkImplicitFunction;
class vtkGenericCellTessellator;
class vtkGenericAttributeCollection;
class vtkGenericAttribute;
class vtkGenericPointIterator;
class vtkIdList;
class vtkOrderedTriangulator;
class vtkPolygon;
class vtkUnsignedCharArray;
class vtkQuad;
class vtkHexahedron;

class VTKEXTENDING_EXPORT vtkGenericAdaptorCell : public vtkObject
{
public:
  vtkTypeRevisionMacro(vtkGenericAdaptorCell,vtkObject);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Unique identification number of the cell over the whole
  // data set. This unique key may not be contiguous.
  virtual vtkIdType GetId() = 0;

  // Description:
  // Does `this' a cell of a dataset? (otherwise, it is a boundary cell)
  virtual int IsInDataSet()=0;
  
  // Description:
  // Return the type of the current cell.
  // \post (result==VTK_HIGHER_ORDER_EDGE)||
  //       (result==VTK_HIGHER_ORDER_TRIANGLE)||
  //       (result==VTK_HIGHER_ORDER_TETRAHEDRON)
  virtual int GetType()=0;

  // Description:
  // Return the topological dimension of the current cell.
  // \post valid_result: result>=0 && result<=3
  virtual int GetDimension() = 0;

  // Description:
  // Return the interpolation order of the geometry.
  // \post positive_result: result>=0
  virtual int GetGeometryOrder()=0;
  
  // Description:
  // Does the cell have a non-linear interpolation for the geometry?
  // \post definition: result==(GetGeometryOrder()==1)
  int IsGeometryLinear();
  
  // Description:
  // Return the Interpolation order of attribute `a' on the cell
  // (may differ by cell).  
  // \pre a_exists: a!=0 
  // \post positive_result: result>=0
  virtual int GetAttributeOrder(vtkGenericAttribute *a)=0;
  
  // Description:
  // Return the index of the first point centered attribute with the highest
  // order in `ac'.
  // \pre ac_exists: ac!=0
  // \post valid_result: result>=-1 && result<ac->GetNumberOfAttributes()
  virtual int GetHighestOrderAttribute(vtkGenericAttributeCollection *ac);
  
  // Description:
  // Does the attribute `a' have a non-linear interpolation?
  // \pre a_exists: a!=0
  // \post definition: result==(GetAttributeOrder()==1)
  int IsAttributeLinear(vtkGenericAttribute *a);
  
  // Description:
  // Is the cell primary (i.e. not composite) ?
  virtual int IsPrimary()=0;

  // Description:
  // Return the number of points that compose the cell.
  // \post positive_result: result>=0
  virtual int GetNumberOfPoints()=0;

  // Description:
  // Return the number of boundaries of dimension `dim' (or all dimensions
  // greater than 0 and less than GetDimension() if -1) of the cell.
  // When \a dim is -1, the number of vertices is not included in the
  // count because vertices are a special case: a vertex will have
  // at most a single field value associated with it; DOF nodes may have
  // an arbitrary number of field values associated with them.
  // \pre valid_dim_range: (dim==-1) || ((dim>=0)&&(dim<GetDimension()))
  // \post positive_result: result>=0
  virtual int GetNumberOfBoundaries(int dim=-1)=0;

  // Description:
  // Accumulated number of DOF nodes of the current cell. A DOF node is
  // a component of cell with a given topological dimension. e.g.: a triangle
  // has 4 DOF: 1 face and 3 edges. An hexahedron has 19 DOF:
  // 1 region, 6 faces, and 12 edges.
  //
  // The number of vertices is not included in the
  // count because vertices are a special case: a vertex will have
  // at most a single field value associated with it; DOF nodes may have
  // an arbitrary number of field values associated with them.
  // \post valid_result: result==GetNumberOfBoundaries(-1)+1
  virtual int GetNumberOfDOFNodes()=0;
  
  // Description:
  // Return the points of cell into `it'.
  // \pre it_exists: it!=0
  virtual void GetPointIterator(vtkGenericPointIterator *it)=0;
  
  // Description:
  // Create an empty cell iterator. The user is responsible for deleting it.
  // \post result_exists: result!=0
  virtual vtkGenericCellIterator *NewCellIterator()=0;
 
  // Description:
  // Return the `boundaries' the cells of dimension `dim' (or all dimensions
  // less than GetDimension() if -1) that are part of the boundary of the cell.
  // \pre valid_dim_range: (dim==-1) || ((dim>=0)&&(dim<GetDimension()))
  // \pre boundaries_exist: boundaries!=0
  virtual void GetBoundaryIterator(vtkGenericCellIterator *boundaries,
                                   int dim=-1)=0;
  
  // Description:
  // Number of cells (dimension>boundary->GetDimension()) of the dataset
  // that share the boundary `boundary' of `this'.
  // `this' IS NOT INCLUDED.
  // \pre boundary_exists: boundary!=0
  // \pre real_boundary: !boundary->IsInDataSet()
  // \pre cell_of_the_dataset: IsInDataSet()
  // \pre boundary: HasBoundary(boundary)
  // \post positive_result: result>=0
  virtual int CountNeighbors(vtkGenericAdaptorCell *boundary)=0;
  virtual void CountEdgeNeighbors( int* sharing ) = 0;

  // Description:
  // Put into `neighbors' the cells (dimension>boundary->GetDimension())
  // of the dataset that share the boundary `boundary' with this cell.
  // `this' IS NOT INCLUDED.
  // \pre boundary_exists: boundary!=0
  // \pre real_boundary: !boundary->IsInDataSet()
  // \pre cell_of_the_dataset: IsInDataSet()
  // \pre boundary: HasBoundary(boundary)
  // \pre neighbors_exist: neighbors!=0
  virtual void GetNeighbors(vtkGenericAdaptorCell *boundary,
                            vtkGenericCellIterator *neighbors)=0;

  // Description:
  // Compute the closest boundary of the current sub-cell `subId' for point
  // `pcoord' (in parametric coordinates) in `boundary', and return whether
  // the point is inside the cell or not. `boundary' is of dimension
  // GetDimension()-1.
  // \pre positive_subId: subId>=0
  virtual int FindClosestBoundary(int subId,
                                  double pcoords[3],
                                  vtkGenericCellIterator* &boundary)=0;

  // Description:
  // Is `x' inside the current cell? It also evaluate parametric coordinates
  // `pcoords', sub-cell id `subId' (0 means primary cell), distance squared
  // to the sub-cell in `dist2' and closest corner point `closestPoint'.
  // `dist2' and `closestPoint' are not evaluated if `closestPoint'==0.
  // If a numerical error occurred, -1 is returned and all other results
  // should be ignored.
  // \post valid_result: result==-1 || result==0 || result==1
  // \post positive_distance: result!=-1 implies (closestPoint!=0 implies
  //                                               dist2>=0)
  virtual int EvaluatePosition(double x[3],
                               double *closestPoint, 
                               int &subId,
                               double pcoords[3], 
                               double &dist2)=0;
  
  // Description:
  // Determine the global coordinates `x' from sub-cell `subId' and parametric
  // coordinates `pcoords' in the cell.
  // \pre positive_subId: subId>=0
  // \pre clamped_pcoords: (0<=pcoords[0])&&(pcoords[0]<=1)&&(0<=pcoords[1])
  // &&(pcoords[1]<=1)&&(0<=pcoords[2])&&(pcoords[2]<=1)
  virtual void EvaluateLocation(int subId,
                                double pcoords[3],
                                double x[3])=0;
  
  // Description:
  // Interpolate the attribute `a' at local position `pcoords' of the cell into
  // `val'.
  // \pre a_exists: a!=0
  // \pre a_is_point_centered: a->GetCentering()==vtkPointCentered
  // \pre clamped_point: pcoords[0]>=0 && pcoords[0]<=1 && pcoords[1]>=0 &&
  //                     pcoords[1]<=1 && pcoords[2]>=0 && pcoords[2]<=1
  // \pre val_exists: val!=0
  // \pre valid_size: sizeof(val)==a->GetNumberOfComponents()
  virtual void InterpolateTuple(vtkGenericAttribute *a, double pcoords[3],
                                double *val) = 0;

  // Description:
  // Interpolate the whole collection of attributes `c' at local position
  // `pcoords' of the cell into `val'. Only point centered attributes are
  // taken into account.
  // \pre c_exists: c!=0
  // \pre clamped_point: pcoords[0]>=0 && pcoords[0]<=1 && pcoords[1]>=0 &&
  //                     pcoords[1]<=1 && pcoords[2]>=0 && pcoords[2]<=1
  // \pre val_exists: val!=0
  // \pre valid_size: sizeof(val)==c->GetNumberOfPointCenteredComponents()
  virtual void InterpolateTuple(vtkGenericAttributeCollection *c,
                                double pcoords[3],
                                double *val) = 0;
  
  // Description:
  // Generate a contour (contouring primitives) for each `values' or with
  // respect to an implicit function `f'. Contouring is performed on the
  // scalar attribute (`attributes->GetActiveAttribute()'
  // `attributes->GetActiveComponent()').  Contouring interpolates the
  // `attributes->GetNumberOfattributesToInterpolate()' attributes
  // `attributes->GetAttributesToInterpolate()'.  The `locator', `verts',
  // `lines', `polys', `outPd' and `outCd' are cumulative data arrays over
  // cell iterations: they store the result of each call to Contour():
  // - `locator' is points list that merges points as they are inserted (i.e.,
  // prevents duplicates).
  // - `verts' is an array of generated vertices
  // - `lines' is an array of generated lines
  // - `polys' is an array of generated polygons
  // - `outPd' is an array of interpolated point data along the edge (if
  // not-NULL)
  // - `outCd' is an array of copied cell data of the current cell (if 
  // not-NULL)
  // `internalPd', `secondaryPd' and `secondaryCd' are initialized by the
  // filter that call it from `attributes'.
  // - `internalPd' stores the result of the tessellation pass: the
  // higher-order cell is tessellated into linear sub-cells.
  // - `secondaryPd' and `secondaryCd' are used internally as inputs to the
  // Contour() method on linear sub-cells.
  // Note: the CopyAllocate() method must be invoked on both `outPd' and
  // `outCd', from `secondaryPd' and `secondaryCd'.
  //
  // NOTE: `vtkGenericAttributeCollection *attributes' will be replaced by a
  //       `vtkInformation'.
  //
  // \pre values_exist: (values!=0 && f==0) || (values==0 && f!=0)
  // \pre attributes_exist: attributes!=0
  // \pre tessellator_exists: tess!=0
  // \pre locator_exists: locator!=0
  // \pre verts_exist: verts!=0
  // \pre lines_exist: lines!=0
  // \pre polys_exist: polys!=0
  // \pre internalPd_exists: internalPd!=0
  // \pre secondaryPd_exists: secondaryPd!=0
  // \pre secondaryCd_exists: secondaryCd!=0
  virtual void Contour(vtkContourValues *values,
                       vtkImplicitFunction *f,
                       vtkGenericAttributeCollection *attributes,
                       vtkGenericCellTessellator *tess,
                       vtkPointLocator *locator,
                       vtkCellArray *verts,
                       vtkCellArray *lines,
                       vtkCellArray *polys,
                       vtkPointData *outPd,
                       vtkCellData *outCd,
                       vtkPointData *internalPd,
                       vtkPointData *secondaryPd,
                       vtkCellData *secondaryCd);

  // Description:
  // Cut (or clip) the current cell with respect to the contour defined by
  // the `value' or the implicit function `f' of the scalar attribute
  // (`attributes->GetActiveAttribute()',`attributes->GetActiveComponent()').
  // If `f' exists, `value' is not used. The output is the part of the
  // current cell which is inside the contour.  The output is a set of zero,
  // one or more cells of the same topological dimension as the current
  // cell. Normally, cell points whose scalar value is greater than "value"
  // are considered inside. If `insideOut' is on, this is reversed.  Clipping
  // interpolates the `attributes->GetNumberOfattributesToInterpolate()'
  // attributes `attributes->GetAttributesToInterpolate()'.  `locator',
  // `connectivity', `outPd' and `outCd' are cumulative data arrays over cell
  // iterations: they store the result of each call to Clip():
  // - `locator' is points list that merges points as they are inserted (i.e.,
  // prevents duplicates).
  // - `connectivity' is an array of generated cells
  // - `outPd' is an array of interpolated point data along the edge (if
  // not-NULL)
  // - `outCd' is an array of copied cell data of the current cell (if
  // not-NULL)
  // `internalPd', `secondaryPd' and `secondaryCd' are initialized by the
  // filter that call it from `attributes'.
  // - `internalPd' stores the result of the tessellation pass: the
  // higher-order cell is tessellated into linear sub-cells.
  // - `secondaryPd' and `secondaryCd' are used internally as inputs to the
  // Clip() method on linear sub-cells.
  // Note: the CopyAllocate() method must be invoked on both `outPd' and
  // `outCd', from `secondaryPd' and `secondaryCd'.
  //
  // NOTE: `vtkGenericAttributeCollection *attributes' will be replaced by a
  //       `vtkInformation'.
  //
  // \pre attributes_exist: attributes!=0
  // \pre tessellator_exists: tess!=0
  // \pre locator_exists: locator!=0
  // \pre connectivity_exists: connectivity!=0
  // \pre internalPd_exists: internalPd!=0
  // \pre secondaryPd_exists: secondaryPd!=0
  // \pre secondaryCd_exists: secondaryCd!=0
  virtual void Clip(double value, 
                    vtkImplicitFunction *f,
                    vtkGenericAttributeCollection *attributes,
                    vtkGenericCellTessellator *tess,
                    int insideOut,
                    vtkPointLocator *locator, 
                    vtkCellArray *connectivity,
                    vtkPointData *outPd,
                    vtkCellData *outCd,
                    vtkPointData *internalPd,
                    vtkPointData *secondaryPd,
                    vtkCellData *secondaryCd);
  
  // Description:
  // Is there an intersection between the current cell and the ray (`p1',`p2')
  // according to a tolerance `tol'? If true, `x' is the global intersection,
  // `t' is the parametric coordinate for the line, `pcoords' are the
  // parametric coordinates for cell. `subId' is the sub-cell where
  // the intersection occurs.
  // \pre positive_tolerance: tol>0
  virtual int IntersectWithLine(double p1[3],
                                double p2[3], 
                                double tol,
                                double &t,
                                double x[3], 
                                double pcoords[3],
                                int &subId)=0;

  // Description:
  // Compute derivatives `derivs' of the attribute `attribute' (from its
  // values at the corner points of the cell) given sub-cell `subId' (0 means
  // primary cell) and parametric coordinates `pcoords'.
  // Derivatives are in the x-y-z coordinate directions for each data value.
  // \pre positive_subId: subId>=0
  // \pre clamped_pcoords: (0<=pcoords[0])&&(pcoords[0]<=1)&&(0<=pcoords[1])
  // &&(pcoords[1]<=1)&&(0<=pcoords[2])%%(pcoords[2]<=1)
  // \pre attribute_exists: attribute!=0
  // \pre derivs_exists: derivs!=0
  // \pre valid_size: sizeof(derivs)>=attribute->GetNumberOfComponents()*3
  virtual void Derivatives(int subId,
                           double pcoords[3],
                           vtkGenericAttribute *attribute,
                           double *derivs)=0;

  // Description:
  // Compute the bounding box of the current cell in `bounds' in global
  // coordinates.
  // THREAD SAFE
  virtual void GetBounds(double bounds[6])=0;

  // Description:
  // Return the bounding box of the current cell in global coordinates.
  // NOT THREAD SAFE
  // \post result_exists: result!=0
  // \post valid_size: sizeof(result)>=6
  virtual double *GetBounds();

  // Description:
  // Return the bounding box diagonal squared of the current cell.
  // \post positive_result: result>=0
  virtual double GetLength2();

  // Description:
  // Get the center of the current cell (in parametric coordinates)and place
  // in the `pcoords'.  If the current cell is a composite, the return value
  // is the sub-cell id that the center is in.  \post valid_result:
  // (result>=0) && (IsPrimary() implies result==0)
  virtual int GetParametricCenter(double pcoords[3])=0;

  // Description:
  // Return the distance of the parametric coordinate `pcoords' to the
  // current cell.  If inside the cell, a distance of zero is returned. This
  // is used during picking to get the correct cell picked. (The tolerance
  // will occasionally allow cells to be picked who are not really
  // intersected "inside" the cell.)  \post positive_result: result>=0
  virtual double GetParametricDistance(double pcoords[3])=0;

  // Description:
  // Return a contiguous array of parametric coordinates of the points defining
  // the current cell. In other words, (px,py,pz, px,py,pz, etc..) The
  // coordinates are ordered consistent with the definition of the point
  // ordering for the cell. Note that 3D parametric coordinates are returned
  // no matter what the topological dimension of the cell. It includes the DOF
  // nodes.
  // \post valid_result_exists: ((IsPrimary()) && (result!=0)) ||
  //                             ((!IsPrimary()) && (result==0))
  //                     result!=0 implies sizeof(result)==GetNumberOfPoints()
  virtual double *GetParametricCoords()=0;

  // Description:
  // Tessellate the cell if it is not linear or if at least one attribute of
  // `attributes' is not linear. The output are linear cells of the same
  // dimension than than cell. If the cell is linear and all attributes are
  // linear, the output is just a copy of the current cell.
  // `points', `cellArray', `pd' and `cd' are cumulative output data arrays
  // over cell iterations: they store the result of each call to Tessellate().
  // `internalPd' is initialized by the calling filter and stores the
  // result of the tessellation.
  // If it is not null, `types' is fill with the types of the linear cells.
  // `types' is null when it is called from vtkGenericGeometryFilter and not
  // null when it is called from vtkGenericDatasetTessellator.
  // \pre attributes_exist: attributes!=0
  // \pre tessellator_exists: tess!=0
  // \pre points_exist: points!=0
  // \pre cellArray_exists: cellArray!=0
  // \pre internalPd_exists: internalPd!=0
  // \pre pd_exist: pd!=0
  // \pre cd_exists: cd!=0
  virtual void Tessellate(vtkGenericAttributeCollection *attributes, 
                          vtkGenericCellTessellator *tess,
                          vtkPoints *points,
                          vtkPointLocator *locator,
                          vtkCellArray* cellArray,
                          vtkPointData *internalPd,
                          vtkPointData *pd, vtkCellData* cd,
                          vtkUnsignedCharArray *types);

  // The following methods are for the internals of the tesselation algorithm
  // (the hash table in particular)
  
  // Description:
  // Is the face `faceId' of the current cell on a exterior boundary of the
  // dataset?
  // \pre 3d: GetDimension()==3
  virtual int IsFaceOnBoundary(vtkIdType faceId) = 0;
  
  // Description:
  // Is the cell on the exterior boundary of the dataset?
  // \pre 2d: GetDimension()==2
  virtual int IsOnBoundary() = 0;

  // Description:
  // Put into `id' the list of ids the point of the cell.
  // \pre id_exists: id!=0
  // \pre valid_size: sizeof(id)==GetNumberOfPoints();
  virtual void GetPointIds(vtkIdType *id) = 0;

  // Description:
  // Tessellate face `index' of the cell. See Tessellate() for further
  // explanations.
  // \pre cell_is_3d: GetDimension()==3
  // \pre attributes_exist: attributes!=0
  // \pre tessellator_exists: tess!=0
  // \pre valid_face: index>=0
  // \pre points_exist: points!=0
  // \pre cellArray_exists: cellArray!=0
  // \pre internalPd_exists: internalPd!=0
  // \pre pd_exist: pd!=0
  // \pre cd_exists: cd!=0
  virtual void TriangulateFace(vtkGenericAttributeCollection *attributes,
                               vtkGenericCellTessellator *tess, int index, 
                               vtkPoints *points,
                               vtkPointLocator *locator,
                               vtkCellArray *cellArray,
                               vtkPointData *internalPd,
                               vtkPointData *pd, vtkCellData *cd );
  
  // Description:
  // Return the ids of the vertices defining face `faceId'.
  // \pre is_3d: this->GetDimension()==3
  // \pre valid_faceId_range: faceId>=0 && faceId<this->GetNumberOfBoundaries(2)
  // \post result_exists: result!=0
  // \post valid_size: sizeof(result)>=GetNumberOfVerticesOnFace(faceId)
  virtual int *GetFaceArray(int faceId)=0;
  
  // Description:
  // Return the number of vertices defining face `faceId'.
  // \pre is_3d: this->GetDimension()==3
  // \pre valid_faceId_range: faceId>=0 && faceId<this->GetNumberOfBoundaries(2)
  // \post positive_result: && result>0
  virtual int GetNumberOfVerticesOnFace(int faceId)=0;
  
  // Description:
  // Return the ids of the vertices defining edge `edgeId'.
  // \pre valid_dimension: this->GetDimension()>=2
  // \pre valid_edgeId_range: edgeId>=0 && edgeId<this->GetNumberOfBoundaries(1)
  // \post result_exists: result!=0
  // \post valid_size: sizeof(result)==2
  virtual int *GetEdgeArray(int edgeId)=0;
  
protected:
  vtkGenericAdaptorCell();
  virtual ~vtkGenericAdaptorCell();

  // Description:
  // Reset internal structures.
  void Reset();
  
  // Description:
  // Allocate some memory if Tuples does not exist or is smaller than size.
  // \pre positive_size: size>0
  void AllocateTuples(int size);
  
  //Internal tetra used for the contouring/clipping algoirthm
  vtkTetra       *Tetra;
  vtkTriangle    *Triangle;
  vtkLine        *Line;
  vtkVertex      *Vertex; //is it used ?
  vtkQuad *Quad;
  vtkHexahedron *Hexa;

  // Internal locator when tessellating on a cell basis, this is different
  // from the main locator used in contour/clip filter, this locator is used for
  // points for
  // Be carefull the use of a vtkLocator in conjuction with the table fast
  // tessellator is very sensitive, we need to keep all the points we used
  vtkDoubleArray  *InternalPoints;
  vtkCellArray    *InternalCellArray;
  vtkDoubleArray  *InternalScalars;
  vtkDoubleArray  *PointDataScalars;
  
  vtkIdList        *InternalIds; // used by Tessellate() and TriangulateFace()
  
  //Attributes to mimic the vtk cell look and feel, internal use only
  vtkDoubleArray  *Scalars;
  vtkPointData    *PointData;
  vtkCellData     *CellData;
  
  // Scalar buffer to store the attributes values at some location
  // There are variable members to reduce memory allocations.
  double *Tuples;
  int TuplesCapacity;
  
  // Cached Bounds.
  double Bounds[6];
  
private:
  vtkGenericAdaptorCell(const vtkGenericAdaptorCell&);  // Not implemented.
  void operator=(const vtkGenericAdaptorCell&);  // Not implemented.
};

#endif