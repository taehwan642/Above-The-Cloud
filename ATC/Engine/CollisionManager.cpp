#include "DXUT.h"
#include "GameObject.h"
#include "Transform.h"
#include "CollisionManager.h"
USING(Engine)

void CollisionManager::PushData(ObjectTag _tag, GameObject* _data)
{
	colliderdatas[_tag].push_back(_data);
}

void CollisionManager::GetRay(D3DXMATRIX _world)
{
	const D3DSURFACE_DESC* backbuffer = DXUTGetD3D9BackBufferSurfaceDesc();
	D3DXMATRIX matproj;
	DXUTGetD3D9Device()->GetTransform(D3DTS_PROJECTION, &matproj);

	POINT point;
	GetCursorPos(&point);
	ScreenToClient(DXUTGetHWND(), &point);

	D3DXVECTOR3 v;
	v.x = (((2.0f * point.x) / backbuffer->Width) - 1) / matproj._11;
	v.y = -(((2.0f * point.y) / backbuffer->Height) - 1) / matproj._22;
	v.z = 1.0f;

	D3DXMATRIX matView;
	DXUTGetD3D9Device()->GetTransform(D3DTS_VIEW, &matView);
	D3DXMATRIX matWorld = _world;
	D3DXMATRIX WV = matWorld * matView;
	D3DXMATRIX m;
	D3DXMatrixInverse(&m, NULL, &WV);

	rayDir.x = v.x * m._11 + v.y * m._21 + v.z * m._31;
	rayDir.y = v.x * m._12 + v.y * m._22 + v.z * m._32;
	rayDir.z = v.x * m._13 + v.y * m._23 + v.z * m._33;

	rayPos.x = m._41;
	rayPos.y = m._42;
	rayPos.z = m._43;
}

void CollisionManager::GetWorldMouse(void)
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(DXUTGetHWND(), &pt);

	D3DXVECTOR3		mousePosition;

	// 정규좌표에서 스크린좌표 변환
	D3DVIEWPORT9		ViewPort;
	ZeroMemory(&ViewPort, sizeof(D3DVIEWPORT9));
	DEVICE->GetViewport(&ViewPort);

	mousePosition.x = pt.x / (ViewPort.Width * 0.5f) - 1.f;
	mousePosition.y = pt.y / (ViewPort.Height * -0.5f) + 1.f;
	mousePosition.z = 0.f;

	// 스크린좌표에서 뷰로 변환
	D3DXMATRIX matProj;
	DEVICE->GetTransform(D3DTS_PROJECTION, &matProj);
	D3DXMatrixInverse(&matProj, NULL, &matProj);
	D3DXVec3TransformCoord(&mousePosition, &mousePosition, &matProj);

	rayPos = D3DXVECTOR3(0.f, 0.f, 0.f);
	rayDir = mousePosition - rayPos;

	// 뷰에서 월드로 변환
	D3DXMATRIX matView;
	DEVICE->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matView, NULL, &matView);

	D3DXVec3TransformCoord(&rayPos, &rayPos, &matView);
	D3DXVec3TransformNormal(&rayDir, &rayDir, &matView);
}

bool CollisionManager::CheckSphereCollision(const D3DXVECTOR3& _srcpos, const FLOAT& _srcradius, const D3DXVECTOR3& _dstpos, const FLOAT& _dstradius)
{
	D3DXVECTOR3 dir = (_srcpos - _dstpos);
	FLOAT length = D3DXVec3Length(&dir);
	D3DXVec3Normalize(&dir, &dir);

	return length <= (_srcradius + _dstradius);
}

void CollisionManager::CheckCollision(ObjectTag _src, ObjectTag _dst)
{
	for (auto& srcobj : colliderdatas[_src])
	{
		for (auto& dstobj : colliderdatas[_dst])
		{
			if (srcobj == dstobj)
				continue;

			ColliderData* srcdata = srcobj->GetColliderData();
			ColliderData* dstdata = dstobj->GetColliderData();

			if (CheckSphereCollision(*srcdata->center, srcdata->radius, *dstdata->center, dstdata->radius))
			{
				srcobj->CollisionEvent(dstdata->tag, dstobj);
				dstobj->CollisionEvent(srcdata->tag, srcobj);
				
				srcdata->ishit = true;
				dstdata->ishit = true;
			}
		}
	}
}

bool CollisionManager::MouseRaySphereInteresection(out float& _distanceOut, out D3DXVECTOR3& _targetposition, in ObjectTag _dsttag)
{
	GetWorldMouse();
	for (auto& dst : colliderdatas[_dsttag])
	{
		D3DXVec3Normalize(&rayDir, &rayDir);

		D3DXVECTOR3  centerdirection = *dst->GetColliderData()->center - rayPos;
		float centerdistance = D3DXVec3LengthSq(&centerdirection);
		float dot = D3DXVec3Dot(&centerdirection, &rayDir);
		float radiusquare = powf(dst->GetColliderData()->radius, 2.f);

		float orthogonallengthsqare = centerdistance - (dot * dot);

		if (orthogonallengthsqare <= radiusquare)
		{
			_distanceOut = dot - sqrtf(radiusquare - orthogonallengthsqare);
			_targetposition = dynamic_cast<Transform*>(dst->GetComponent(L"Transform"))->position;
			dstObject = dst;
			return true;
		}
	}
	return false;
}

GameObject* CollisionManager::GetClosestObject(in ObjectTag _dsttag, in const D3DXVECTOR3& _srcpos, in const D3DXVECTOR3& _srcdir, in const float _angle)
{
	GameObject* result = nullptr;
	float distance = 99999.f;
	for (auto& dst : colliderdatas[_dsttag])
	{
		Component* transform = dst->GetComponent(L"Transform");
		D3DXVECTOR3 dstpos = dynamic_cast<Transform*>(transform)->position;
		D3DXVECTOR3 dir = _srcpos - dstpos;
		D3DXVECTOR3 dirnormalized;
		D3DXVec3Normalize(&dirnormalized, &dir);
		float a = D3DXVec3Dot(&_srcdir, &dirnormalized);
		if (a < _angle)
		{
			float dstsrcdistance = D3DXVec3Length(&dir);
			if (distance > dstsrcdistance)
			{
				result = dst;
				distance = dstsrcdistance;
			}
		}
	}
	return result;
}

void CollisionManager::UpdateData(void)
{
	for (int i = 0; i < OBJEND; ++i)
	{
		auto& iter = colliderdatas[i].begin();
		auto& iter_end = colliderdatas[i].end();

		for (; iter != iter_end;)
		{
			if ((*iter)->isActive == false)
				iter = colliderdatas[i].erase(iter);
			else
				++iter;
		}
	}
}

void CollisionManager::ClearData(void)
{
	for (int i = 0; i < OBJEND; ++i)
		colliderdatas[i].clear();
}