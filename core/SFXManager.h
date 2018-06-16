#ifndef _SFXManager
#define _SFXManager

#include <malloc.h>
#include "Align16.h"

#include <list>
#include "Vect.h"

#include "LightStructs.h"

class ShaderBase;

class SFXManager : public Align16
{
private:
	static SFXManager *ptrInstance;

	SFXManager();
	SFXManager(const SFXManager&) = delete;
	SFXManager& operator=(const SFXManager&) = delete;
	~SFXManager();

	static SFXManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new SFXManager;
		return *ptrInstance;
	}

	std::list<ShaderBase*> shaderList;
	void privSetFogParameters(const float& fogstart, const float& fogrange, const Vect& fogcolor);
	void privResetFogParameters();
	void privSetDisableFog();

	float fogStart;
	float fogRange;
	Vect fogColor;

	void privChangeDirectionalLighting(const Vect& dir, const Vect& amb, const Vect& dif, const Vect& sp);
	void privChangePointLighting(int n, const Vect& pos, float r, const Vect& att,
		const Vect& amb, const Vect& dif, const Vect& sp);
	void privChangeSpotLighting(int n, const Vect& pos, float r, const Vect& att,
		const Vect& dir, float spotExp, const Vect& amb, const Vect& dif, const Vect& sp);

	void privDeactivatePointLight(int n);
	void privDeactivateSpotLight(int n);

	int privAssignPointLighting(const Vect& pos, float r, const Vect& att,
		const Vect& amb, const Vect& dif, const Vect& sp);
	int privAssignSpotLighting(const Vect& pos, float r, const Vect& att,
		const Vect& dir, float spotExp, const Vect& amb, const Vect& dif, const Vect& sp);

	DirectionalLight privGetDirectionalLighting();
	PointLight privGetPointLighting(int n);
	SpotLight privGetSpotLighting(int n);	

	DirectionalLight DirLightData;
	PointLight PointLightData[POINTARRAY_SIZE];
	SpotLight SpotLightData[SPOTARRAY_SIZE];

	int numPointLights;
	int numSpotLights;

public:
	static void Terminate();

	/// \brief Set the fog parameters
	/// \ingroup EFFECTS
	///
	/// \param fogstart	The distance from the camera where fog will start to appear
	/// \param fogrange The distance from the camera where fog will completely fill the rendered space
	/// \param fogcolor	The color of the fog
	static void SetFogParameters(const float& fogstart, const float& fogrange, const Vect& fogcolor) { Instance().privSetFogParameters(fogstart, fogrange, fogcolor); };
	/// \brief Used internally to reset to chosen parameters after disabling fog
	/// \ingroup EFFECTS
	static void ResetFogParameters() { Instance().privResetFogParameters(); }
	/// \brief Turns off fog
	/// \ingroup EFFECTS
	static void SetDisableFog() { Instance().privSetDisableFog(); };
	/// \brief Adds a shader to the manager. If this is not done, objects using the shader will not be updated with fog or lighting info.
	/// \ingroup EFFECTS
	///
	/// \param s The shader being added to the manager
	static void AddShader(ShaderBase* s);

	// Change pre-existing lights
	/// \brief Change the directional lighting (Should ALWAYS be initialized)
	/// \ingroup EFFECTS
	///
	/// \param dir Direction the lighting is shining in
	/// \param amb Ambient light color
	/// \param dif Diffuse light color
	/// \param sp Specularity value
	static void ChangeDirectionalLighting(const Vect& dir, const Vect& amb = Vect(1, 1, 1), 
		const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1)) 
	{ Instance().privChangeDirectionalLighting(dir, amb, dif, sp); };
	/// \brief Change a previously defined point light
	/// \ingroup EFFECTS
	///
	/// \param n The point light number (Returned when you assign a point light)
	/// \param pos The position of the center of the point light
	/// \param r The range of the point light
	/// \param att The attentuation of the point light
	/// \param dir Direction the lighting is shining in
	/// \param amb Ambient light color
	/// \param dif Diffuse light color
	/// \param sp Specularity value
	static void ChangePointLighting(int n, const Vect& pos, float r, const Vect& att,
		const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1))
	{ Instance().privChangePointLighting(n, pos, r, att, amb, dif, sp); };
	/// \brief Change a previously defined spot light
	/// \ingroup EFFECTS
	///
	/// \param n The spot light number (Returned when you assign a spot light)
	/// \param pos The position of the center of the spot light
	/// \param r The range of the spot light
	/// \param att The attentuation of the spot light
	/// \param dir The direction of the spot light
	/// \param spotExp The spotlight falloff (around the edges)
	/// \param dir Direction the lighting is shining in
	/// \param amb Ambient light color
	/// \param dif Diffuse light color
	/// \param sp Specularity value
	static void ChangeSpotLighting(int n, const Vect& pos, float r, const Vect& att,
		const Vect& dir, float spotExp, const Vect& amb = Vect(1, 1, 1), 
		const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1)) 
	{ Instance().privChangeSpotLighting(n, pos, r, att, dir, spotExp, amb, dif, sp); };

	/// \brief Turns off a previously defined point light
	/// \ingroup EFFECTS
	/// \param n The number of the point light
	static void DeactivatePointLight(int n) { Instance().privDeactivatePointLight(n); };
	/// \brief Turns off a previously defined spot light
	/// \ingroup EFFECTS
	/// \param n The number of the spot light
	static void DeactivateSpotLight(int n) { Instance().privDeactivateSpotLight(n); };

	// Assign new lights
	/// \brief Assigns a new point light
	/// \ingroup EFFECTS
	///
	/// \return The point light number
	/// \param pos The position of the center of the point light
	/// \param r The range of the point light
	/// \param att The attentuation of the point light
	/// \param dir Direction the lighting is shining in
	/// \param amb Ambient light color
	/// \param dif Diffuse light color
	/// \param sp Specularity value
	static int AssignPointLighting(const Vect& pos, float r, const Vect& att,
		const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1))
	{
		return Instance().privAssignPointLighting(pos, r, att, amb, dif, sp);
	};
	/// \brief Assign a spotlight
	/// \ingroup EFFECTS
	///
	/// \return The spot light number
	/// \param pos The position of the center of the spot light
	/// \param r The range of the spot light
	/// \param att The attentuation of the spot light
	/// \param dir The direction of the spot light
	/// \param spotExp The spotlight falloff (around the edges)
	/// \param dir Direction the lighting is shining in
	/// \param amb Ambient light color
	/// \param dif Diffuse light color
	/// \param sp Specularity value
	static int AssignSpotLighting(const Vect& pos, float r, const Vect& att,
		const Vect& dir, float spotExp, const Vect& amb = Vect(1, 1, 1),
		const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1))
	{
		return Instance().privAssignSpotLighting(pos, r, att, dir, spotExp, amb, dif, sp);
	};

	// Get the new lighting (used by shaders...)
	static DirectionalLight GetDirectionalLighting()
	{ return Instance().privGetDirectionalLighting(); };
	
	static PointLight GetPointLighting(int n) 
	{ return Instance().privGetPointLighting(n); };
	
	static SpotLight GetSpotLighting(int n) 
	{ return Instance().privGetSpotLighting(n); };

};

#endif