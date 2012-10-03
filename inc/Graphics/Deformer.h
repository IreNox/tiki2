#pragma once

#define FBXSDK_NEW_API
#include "fbxsdk.h"

class Deformer
{
public:
	static void ComputeShapeDeformation(FbxMesh* pMesh, 
		FbxTime& pTime, 
		FbxAnimLayer * pAnimLayer, 
		FbxVector4* pVertexArray);

	static void ComputeSkinDeformation(FbxAMatrix& pGlobalPosition, 
		FbxMesh* pMesh, 
		FbxTime& pTime, 
		FbxVector4* pVertexArray,
		FbxPose* pPose);

	static void ComputeLinearDeformation(FbxAMatrix& pGlobalPosition, 
		FbxMesh* pMesh, 
		FbxTime& pTime, 
		FbxVector4* pVertexArray,
		FbxPose* pPose);

	static void ComputeDualQuaternionDeformation(FbxAMatrix& pGlobalPosition, 
		FbxMesh* pMesh, 
		FbxTime& pTime, 
		FbxVector4* pVertexArray,
		FbxPose* pPose);

	static void ComputeClusterDeformation(FbxAMatrix& pGlobalPosition, 
		FbxMesh* pMesh,
		FbxCluster* pCluster, 
		FbxAMatrix& pVertexTransformMatrix,
		FbxTime pTime, 
		FbxPose* pPose);

private:

	static void MatrixScale(FbxAMatrix& pMatrix, double pValue);
	static void MatrixAddToDiagonal(FbxAMatrix& pMatrix, double pValue);
	static void MatrixAdd(FbxAMatrix& pDstMatrix, FbxAMatrix& pSrcMatrix);

	static FbxAMatrix GetGlobalPosition(FbxNode* pNode, const FbxTime& pTime, FbxPose* pPose = NULL, FbxAMatrix* pParentGlobalPosition = NULL);
	static FbxAMatrix GetPoseMatrix(FbxPose* pPose, int pNodeIndex);
	static FbxAMatrix GetGeometry(FbxNode* pNode);
};