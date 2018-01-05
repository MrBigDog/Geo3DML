#pragma once
#include "vtkUnstructuredGrid.h"
#include<string>
#include<vector>

struct Pillar
{
	Pillar() {};
	Pillar(const Pillar& v)
	{
		HeadPos[0] = v.HeadPos[0];
		HeadPos[1] = v.HeadPos[1];
		HeadPos[2] = v.HeadPos[2];

		TailPos[0] = v.TailPos[0];
		TailPos[1] = v.TailPos[1];
		TailPos[2] = v.TailPos[2];

	}
	Pillar& operator =  (const Pillar& v)//��ֵ
	{
		HeadPos[0] = v.HeadPos[0];
		HeadPos[1] = v.HeadPos[1];
		HeadPos[2] = v.HeadPos[2];

		TailPos[0] = v.TailPos[0];
		TailPos[1] = v.TailPos[1];
		TailPos[2] = v.TailPos[2];
	}
	double HeadPos[3];
	double TailPos[3];
};

class vtkDataArray;
class VTKEXTENDING_EXPORT GMCornerPointGrid : public vtkUnstructuredGrid
{
public:
	GMCornerPointGrid(void);
	~GMCornerPointGrid(void);
	vtkTypeRevisionMacro(GMCornerPointGrid, vtkUnstructuredGrid);
	static GMCornerPointGrid *New();
	std::string GetID();
	void SetID(std::string);

	//--------
	std::string                  ZValueType; // "elevation"  or "length"
	std::string GetZValueType();
	void SetZValueType(std::string ztype);//// "elevation"  or "length"


	//-------------�ǵ��������Ԫ���ϡ���ǵ������ά��Ϊ (Ni, Nj, Nk)����������������Ԫ����Ϊ (Ni * Nj * Nk)���˼�Ϊ����Ԫ��������Ԫ�ص���Ŀ��
	//	��I����Ϊ���С���J����Ϊ���С���K����Ϊ���㡱����Ԫ�ذ���-��-�����ȵ�˳��˳�μ�¼��Ԫ��λ�á����ȼ�¼����ֵΪ(Xi,0,0)������XiΪ��������������[0,Ni)������Ԫ�����ż�¼����ֵΪ(Xi,1,0)����Ԫ�����������ż�¼����ֵΪ(Xi,0,1)����Ԫ����������¼����ֵΪ(Xi,Nj - 1, Nk - 1)����Ԫ��

	//�ǵ��������������Ԫ����Ԫ�س��ֵĴ���Ϊ (Ni * Nj * Nk)��
	//	�ǵ�������ÿ����������Ԫ�����䶥��4���ǵ㼰����4���ǵ���ȷ��������Щ�ǵ��λ��Pillar���ϣ���˽����¼���ǵ��Z����ֵ�����ڶ�ӦPillar���Ͼ���Pillar���׶���ľ��뼴��ȷ���ǵ��λ�á�
	//	��������ϵI-J-K��ƽ�Ƹ���Ԫ��ʹ��һ������ԭ���غϣ���ʹ�ù��ö����������ֱ����Ӧ����������������غϣ�Ȼ��ֱ��Ը�������ĳ���Ϊ��λ���ȣ�����ԼǸ���Ԫ��8���ǵ������Ϊ(0,0,0)��(1,0,0)��(0,1,0)��(1,1,0)��(0,0,1)��(1,0,1)��(0,1,1)��(1,1,1)����Ԫ�ذ���˳���¼���ǵ�ĺ��θ߳�ֵ��Z���꣩����Pillar���׶���ľ��롣������Ԫ������ֵΪ(i,j,k)������i,j,k��Ϊ��0��ʼ������ֵ����������8���ǵ��������Ӧ��Pillar�ߵ�����ֵ�ֱ�Ϊ��(i,j)��(i + 1,j)��(i,j + 1)��(i + 1,j + 1)��(i,j)��(i + 1,j)��(i,j + 1)��(i + 1,j + 1)��</documentation>
	void AddCell(double cell[8], char valid);
	void GetCell(int index, double cell[8]);
	void GetCell(int ni, int nj, int nk, double cell[8]);
	int  GetCellCount();
	//-------------------------


	//-------------�ǵ������Pillar����ɵ����顣Pillar������K����չ��ֱ�߶Ρ�
	//	��ýǵ������ά��Ϊ (Ni, Nj, Nk)������I����Ϊ���С�����J����Ϊ���С����������Pillar�߿ɼ�Ϊ (Nj + 1) �С�(Ni + 1) �У�������Ϊ (Nj + 1) * (Ni + 1)��
	//	��Ԫ���ԡ��С����ȵķ�ʽ��¼���е�Pillar�ߣ����ȼ�¼��0�а����ĵ�0������Ni�еĹ� (Ni + 1) ��Pillar�ߣ�Ȼ���¼��1�а����ĵ�0������Ni�еĹ� (Ni + 1) ��Pillar�ߣ�����������¼��Nj�а����ĵ�0������Ni�еĹ� (Ni + 1) ��Pillar�ߡ�
	void AddPillar(double HeadPos[3], double TailPos[3]); // 

	void GetPillar(int index, double HeadPos[3], double TailPos[3]);
	void GetPillar(int ni, int nj, double HeadPos[3], double TailPos[3]);
	int  GetPillarCount();


	void AddCellPropertyData(vtkDataArray*);
	vtkDataArray* GetCellPropertyData(int i);
	int GetCountOfCellPropertyData();
	std::vector<char>            ValidCells; // NumberofCells = Cells.size();

	//---------------------------
	void UpdateGrid();
	void GetDimension(int dimension[3]);
	void SetDimension(int dimension[3]);

	std::vector<double>red;
	std::vector<double>gre;
	std::vector<double>blue;

	int rendermode;
	//void ReadFile(char* filename);
protected:
	std::string         _ID;
	int                 Dimension[3];//Ni*Nj*Nk;
	std::vector<Pillar>       Pillars; //Pillars.size() = Ni*Nj;
	std::vector<double>          Cells; // NumberofCells = Cells.size()/8;



	std::vector<vtkDataArray*>   CellPropertyData; // 

};

