#include "stdafx.h"
#include "MeoSimpleMesh.h"
#include <iostream>

MeoSimpleMesh::MeoSimpleMesh()
{
}

MeoSimpleMesh::~MeoSimpleMesh()
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexedBuffer);
}

bool MeoSimpleMesh::Initialize(ID3D11Device* pDevice)
{
	m_rawMeshData.resize(3);
	m_rawMeshData[0].pos = { -0.5, 0, 0 };
	m_rawMeshData[0].color = { 1, 0, 0, 1 };

	m_rawMeshData[1].pos = { 0.5, 0, 0 };
	m_rawMeshData[1].color = { 0, 1, 0, 1 };

	m_rawMeshData[2].pos = { 0, 1, 0 };
	m_rawMeshData[2].color = { 0, 0, 1, 1 };

	m_rawIndexData.resize(3);
	m_rawIndexData[0] = 0;
	m_rawIndexData[1] = 1;
	m_rawIndexData[2] = 2;

	return CreateVertexBuffer(pDevice);
}

void MeoSimpleMesh::Shutdown()
{
}

void MeoSimpleMesh::Render(ID3D11DeviceContext* pContext)
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	pContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset );
	pContext->IASetIndexBuffer(m_pIndexedBuffer, DXGI_FORMAT_R32_UINT, 0);
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	pContext->DrawIndexed(3, 0, 0);
}

bool MeoSimpleMesh::CreateVertexBuffer(ID3D11Device* pDevice)
{
	HRESULT hr;

	D3D11_BUFFER_DESC vDesc; // vertex buffer
	vDesc.Usage = D3D11_USAGE_DEFAULT;
	vDesc.ByteWidth = sizeof(Vertex) * 3;
	vDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vDesc.CPUAccessFlags = 0;
	vDesc.MiscFlags = 0;
	vDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vData;
	vData.pSysMem = m_rawMeshData.data();
	vData.SysMemPitch = 0;
	vData.SysMemSlicePitch = 0;

	hr = pDevice->CreateBuffer(&vDesc, &vData, &m_pVertexBuffer);
	if (FAILED(hr))
	{
		std::cout << "Failed to create vertex buffer.";
	}

	D3D11_BUFFER_DESC iDesc; // index buffer
							 // Set up the description of the static index buffer.
	iDesc.Usage = D3D11_USAGE_DEFAULT;
	iDesc.ByteWidth = sizeof(unsigned long) * 3;
	iDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	iDesc.CPUAccessFlags = 0;
	iDesc.MiscFlags = 0;
	iDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	D3D11_SUBRESOURCE_DATA iData;
	iData.pSysMem = m_rawIndexData.data();
	iData.SysMemPitch = 0;
	iData.SysMemSlicePitch = 0;

	// Create the index buffer.
	hr = pDevice->CreateBuffer(&iDesc, &iData, &m_pIndexedBuffer);
	if (FAILED(hr))
	{
		std::cout << "Failed to create index buffer.";
	}

	return true;
}