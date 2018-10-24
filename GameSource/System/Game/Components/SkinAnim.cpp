#include "SkinAnim.h"


//í∏ì_êÈåæ
void	SkinAnim::VertexDeclaration()
{
	D3DVERTEXELEMENT9	decArray[] =
	{
		{0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0},
		{ 0,12,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_BLENDWEIGHT,0 },
		{ 0,24,D3DDECLTYPE_FLOAT4,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_BLENDINDICES,0 },
		D3DDECL_END()
	};

	LPDIRECT3DVERTEXDECLARATION9	decl = 0;
	
}


//É{Å[ÉìÇÃê∂ê¨
void	SkinAnim::CreateBone()
{
	Bone* bones = new Bone[7];

	bones[0].firstChild = &bones[1];
	bones[1].firstChild = &bones[2];
	bones[3].firstChild = &bones[4];
	bones[5].firstChild = &bones[6];
	bones[1].sibling = &bones[3];
	bones[3].sibling = &bones[5];
}