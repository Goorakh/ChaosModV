#pragma once

#include "Natives.h"

namespace Util
{
	inline void GetGameplayCamMatrix(Vector3 *forward, Vector3 *right, Vector3 *up)
	{
		// Thanks to scripthookvdotnet!
		Vector3 vRot = GET_GAMEPLAY_CAM_ROT(2);
		*forward = vRot.GetDirectionForRotation();

		static const double c_dD2R = 0.01745329251994329576923690768489;

		float fNum1 = cos(vRot.y * c_dD2R);
		float fX = fNum1 * cos(-vRot.z * c_dD2R);
		float fY = fNum1 * sin(vRot.z * c_dD2R);
		float fZ = sin(-vRot.y * c_dD2R);

		*right = Vector3::Init(fX, fY, fZ);
		*up = Vector3::Cross(*right, *forward);
	}

	inline Vector3 GetGameplayCamOffsetInWorldCoords(const Vector3& vOffset)
	{
		Vector3 vForward, vRight, vUp;
		GetGameplayCamMatrix(&vForward, &vRight, &vUp);

		return GET_GAMEPLAY_CAM_COORD() + (vRight * vOffset.x) + (vForward * vOffset.y) + (vUp * vOffset.z);
	}

	inline Vector3 DegToRadian(const Vector3& angles)
	{
		return Vector3::Init(
			angles.x * .0174532925199433F,
			angles.y * .0174532925199433F,
			angles.z * .0174532925199433F
		);
	}

	inline Vector3 GetCoordsFromGameplayCam(float fDistance)
	{
		Vector3 vRot = DegToRadian(GET_GAMEPLAY_CAM_ROT(2));
		Vector3 vCoords = GET_GAMEPLAY_CAM_COORD();

		vRot.y = fDistance * cos(vRot.x);
		vCoords.x = vCoords.x + vRot.y * std::sin(vRot.z * -1.f);
		vCoords.y = vCoords.y + vRot.y * std::cos(vRot.z * -1.f);
		vCoords.z = vCoords.z + fDistance * sin(vRot.x);

		return vCoords;
	}
}