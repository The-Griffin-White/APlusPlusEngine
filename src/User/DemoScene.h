#ifndef _DemoScene
#define _DemoScene

#include <malloc.h>

#include "APPEcore.h"
#include "Scene.h"

class Model;
class Texture;
class FlatPlane_Object;
class SkyBox_Object;

class DemoScene : public Scene
{
public:
	DemoScene();
	virtual ~DemoScene();

	virtual void Initialize() override;

	virtual void Update();
	virtual void Draw();

private:
	// lighting values to keep track of...
	int pnt1, pnt2, pnt3, pnt4;
	int spt1, spt2;

	// Demo specific additions
	Camera* mCam;
	FlatPlane_Object* pPlane;
	Matrix planeMat;
	Matrix planeMat2;

	Model* pModel1;
	Matrix mWorld1;

	Model* pModel2;
	Matrix mWorld2;
	Vect pos2;

	//	Terrain Stuff
//	TerrainObject* pTerrain;
	Texture* ground;
	SkyBox_Object* pSkybox;
	Texture* sky;
	Texture* marble;
	Texture* ambulance;
	//

	// Final Scene Tests ******************************
	Model* mPickup;
	Matrix mPickupW;
	GraphicsObject_ColorNoTextureLight* Pickup;

	Model* mBirchTree;
	Matrix mBirchTreeW;
	GraphicsObject_ColorNoTextureLight* BirchTree;

	Model* mLittlePineTree;
	Matrix Tree1;
	Matrix Tree2;
	GraphicsObject_ColorNoTextureLight* PineTree;

	Model* mSubaru;
	Vect subaruPos;
	Matrix mSubaruW;
	GraphicsObject_ColorNoTextureLight* Subaru;

	Model* mOldCar;
	Matrix mOldCarW;
	GraphicsObject_ColorNoTextureLight* OldCar;

	Model* mAmbulance;
	Matrix mAmbulanceW;
	GraphicsObject_TextureLight* Ambulance;
	Vect SirenPos;

	Model* mApartments;
	Matrix mApartmentsW;
	GraphicsObject_ColorNoTextureLight* Apartments;

	Model* mCat;
	Matrix mCatW;
	GraphicsObject_TextureLight* CatStatue;
	Model* mStatueBase;
	Matrix mStatueBaseW;
	GraphicsObject_TextureLight* StatueBase;
	Model* BoxWrap;
	Matrix mSpikeBase;
	GraphicsObject_TextureLight* SpikeBase;
	Model* Pyramid;
	Matrix mSpike;
	GraphicsObject_TextureLight* Spike;
	Matrix mBall;
	GraphicsObject_TextureLight* Ball;

	Model* mHouse;
	Matrix mHouseW;
	GraphicsObject_ColorNoTextureLight* House;

	Model* mMcD;
	Matrix mMcDW;
	GraphicsObject_ColorNoTextureLight* McDSign;
	Model* mSignPost;
	Matrix mSignPostW;
	GraphicsObject_TextureLight* SignPost;

	Model* mStreetLamp;
	Texture* LampPostTex;
	Texture* LampHeadTex;
	Texture* LampConnectTex;
	GraphicsObject_ColorNoTexture* LampLight;
	Vect LampOffset;
	float LampScale;
	Matrix mStreetLampW1;
	Vect Light1Pos;
	Matrix mStreetLampW2;
	Vect Light2Pos;
	Matrix mStreetLampW3;
	Vect Light3Pos;
	Matrix mStreetLampW4;
	Vect Light4Pos;
	GraphicsObject_TextureLight* StreetLamp;
	// *************************************************

	ShaderColor* pShaderCol;
	ShaderColorLight* pShaderColLight;
	Texture* pTex;
	ShaderTexLight* pShaderTexLight;

};

#endif