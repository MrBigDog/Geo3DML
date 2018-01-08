#include "GMCornerPointGrid.h"


#include "GMUnstructuredGrid.h"

 


#include "vtkCellArray.h"
#include "vtkFieldData.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkObjectFactory.h"
#include "vtkPolyData.h"
#include "vtkCharArray.h"
//#include "vtkUnstructuredGridreader.h"

#include <ctype.h>
#include <sys/stat.h>

vtkCxxRevisionMacro(GMCornerPointGrid, "$Revision: 1.8.6.1 $");
GMCornerPointGrid::GMCornerPointGrid(void)
{
	rendermode=2;
	ZValueType = "elevation";
}


GMCornerPointGrid::~GMCornerPointGrid(void)
{
	for(int i = 0; i < CellPropertyData.size(); i++)
		CellPropertyData[i]->Delete();
 }

GMCornerPointGrid* GMCornerPointGrid::New(void)
{
	return new GMCornerPointGrid;
}
	std::string GMCornerPointGrid::GetID()
		{
			return _ID;
	}
	void GMCornerPointGrid::SetID(std::string str)
	{
		_ID = str;
	}

	//--------
	std::string  GMCornerPointGrid:: GetZValueType()
	{
		return ZValueType;
	}
	 
	void GMCornerPointGrid::SetZValueType(std::string t)
	{

		  ZValueType=t;
	}

	//-------------�ǵ��������Ԫ���ϡ���ǵ������ά��Ϊ (Ni, Nj, Nk)����������������Ԫ����Ϊ (Ni * Nj * Nk)���˼�Ϊ����Ԫ��������Ԫ�ص���Ŀ��
	//	��I����Ϊ���С���J����Ϊ���С���K����Ϊ���㡱����Ԫ�ذ���-��-�����ȵ�˳��˳�μ�¼��Ԫ��λ�á����ȼ�¼����ֵΪ(Xi,0,0)������XiΪ��������������[0,Ni)������Ԫ�����ż�¼����ֵΪ(Xi,1,0)����Ԫ�����������ż�¼����ֵΪ(Xi,0,1)����Ԫ����������¼����ֵΪ(Xi,Nj - 1, Nk - 1)����Ԫ��

	//�ǵ��������������Ԫ����Ԫ�س��ֵĴ���Ϊ (Ni * Nj * Nk)��
	//	�ǵ�������ÿ����������Ԫ�����䶥��4���ǵ㼰����4���ǵ���ȷ��������Щ�ǵ��λ��Pillar���ϣ���˽����¼���ǵ��Z����ֵ�����ڶ�ӦPillar���Ͼ���Pillar���׶���ľ��뼴��ȷ���ǵ��λ�á�
	//	��������ϵI-J-K��ƽ�Ƹ���Ԫ��ʹ��һ������ԭ���غϣ���ʹ�ù��ö����������ֱ����Ӧ����������������غϣ�Ȼ��ֱ��Ը�������ĳ���Ϊ��λ���ȣ�����ԼǸ���Ԫ��8���ǵ������Ϊ(0,0,0)��(1,0,0)��(0,1,0)��(1,1,0)��(0,0,1)��(1,0,1)��(0,1,1)��(1,1,1)����Ԫ�ذ���˳���¼���ǵ�ĺ��θ߳�ֵ��Z���꣩����Pillar���׶���ľ��롣������Ԫ������ֵΪ(i,j,k)������i,j,k��Ϊ��0��ʼ������ֵ����������8���ǵ��������Ӧ��Pillar�ߵ�����ֵ�ֱ�Ϊ��(i,j)��(i + 1,j)��(i,j + 1)��(i + 1,j + 1)��(i,j)��(i + 1,j)��(i,j + 1)��(i + 1,j + 1)��</documentation>
	void GMCornerPointGrid::AddCell(double cell[8],char cellv)
	{
		for(int i = 0; i < 8; i++)
			Cells.push_back(cell[i]);

		ValidCells.push_back(cellv);
	}
	void GMCornerPointGrid::GetCell(int index,double cell[8])
	{
		for(int i = 0; i < 8; i++)
		{
			cell[i] = 0 ;
			
		 
		}
		if(index*8+7 < Cells.size())
		for(int i = 0; i < 8; i++)
		{
			 
				cell[i] = Cells[index*8+i];
		}
	}
	void GMCornerPointGrid::GetCell(int ni,int nj,int nk,double cell[8])
	{
		for(int i = 0; i < 8; i++)
		{
			cell[i] = 0 ;


		}

		int index = nk*Dimension[1]*Dimension[0] + nj*Dimension[0]+ ni;
		
			
			if(index*8+7 < Cells.size())		
			for(int i = 0; i < 8; i++)
			{

				cell[i] = Cells[index*8+i];
			}
	}

	//-------------------------
	void GMCornerPointGrid::GetPillar(int index,double HeadPos[3],	double TailPos[3])
	{
		

		Pillar &v = Pillars[index];
		HeadPos[0] = v.HeadPos[0];
		HeadPos[1] = v.HeadPos[1];
		HeadPos[2] = v.HeadPos[2];

		TailPos[0] = v.TailPos[0];
		TailPos[1] = v.TailPos[1];
		TailPos[2] = v.TailPos[2];
	}
	void GMCornerPointGrid::GetPillar(int ni,int nj,double HeadPos[3],	double TailPos[3])
	{
		int index = nj*(Dimension[0]+1)+ ni;//pillarÿ��ÿ�зֱ���Dimension[0]+1��Dimension[1]+1��
		Pillar &v = Pillars[index];

		HeadPos[0] = v.HeadPos[0];
		HeadPos[1] = v.HeadPos[1];
		HeadPos[2] = v.HeadPos[2];

		TailPos[0] = v.TailPos[0];
		TailPos[1] = v.TailPos[1];
		TailPos[2] = v.TailPos[2];
	}

	//-------------�ǵ������Pillar����ɵ����顣Pillar������K����չ��ֱ�߶Ρ�
	//	��ýǵ������ά��Ϊ (Ni, Nj, Nk)������I����Ϊ���С�����J����Ϊ���С����������Pillar�߿ɼ�Ϊ (Nj + 1) �С�(Ni + 1) �У�������Ϊ (Nj + 1) * (Ni + 1)��
	//	��Ԫ���ԡ��С����ȵķ�ʽ��¼���е�Pillar�ߣ����ȼ�¼��0�а����ĵ�0������Ni�еĹ� (Ni + 1) ��Pillar�ߣ�Ȼ���¼��1�а����ĵ�0������Ni�еĹ� (Ni + 1) ��Pillar�ߣ�����������¼��Nj�а����ĵ�0������Ni�еĹ� (Ni + 1) ��Pillar�ߡ�
	void GMCornerPointGrid::AddPillar(double HeadPos[3],	double TailPos[3]) //
	{
		Pillar v ;

		v.HeadPos[0] = HeadPos[0];
		v.HeadPos[1] = HeadPos[1];
		v.HeadPos[2] = HeadPos[2];


		v.TailPos[0] = TailPos[0];
		v.TailPos[1] = TailPos[1];
		v.TailPos[2] = TailPos[2];

		Pillars.push_back(v);
	}

	//---------------------------
	void GMCornerPointGrid::UpdateGrid()
	{

	}

	void   GMCornerPointGrid::AddCellPropertyData(vtkDataArray*v)
	{
		CellPropertyData.push_back(v);

	}

	vtkDataArray*   GMCornerPointGrid::GetCellPropertyData(int i)
	{
		if(i <  CellPropertyData.size())
		return CellPropertyData[i];

		return 0;
	}

	void GMCornerPointGrid::GetDimension(int dimension[3])
	{
		for(int i =0;i < 3; i++)
			dimension[i] = Dimension[i];
	}

	void  GMCornerPointGrid::SetDimension(int dimension[3])
	{
		for(int i =0;i < 3; i++)
			Dimension[i] = dimension[i];
	}
	int   GMCornerPointGrid::GetCountOfCellPropertyData()
	{
		return CellPropertyData.size();
	}

	int   GMCornerPointGrid::GetCellCount()
	{
		return Cells.size()/8;
	}
	 
	int   GMCornerPointGrid::GetPillarCount()
	{
		return Pillars.size();
	}
