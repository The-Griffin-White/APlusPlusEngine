#include "DemoScene.h"

#include "FlatPlane.h"
#include "SkyBox_Object.h"
#include "FlatPlane_Object.h"

#include "SFXManager.h"
#include "SkyBoxManager.h"

#include "APlusPlusEngine.h"
#include "SceneManager.h"

#include "ModelManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"

void DemoScene::Initialize()
{
	// *************************************************************************************
	// Set up all the shaders
	// *************************************************************************************
	pShaderCol = ShaderManager::GetShaderColor();
	// Set Color Light shader...
	pShaderColLight = ShaderManager::GetShaderColorLight();

	// Set Texture light shader...
	pShaderTexLight = ShaderManager::GetShaderTexLight();

	SFXManager::AddShader(pShaderCol);
	SFXManager::AddShader(pShaderColLight);
	SFXManager::AddShader(pShaderTexLight);

	// There has to be a better way!
	Light1Pos.set(8, 10, 20);
	Light2Pos.set(-8, 10, 20);
	Light3Pos.set(8, 10, -20);
	Light4Pos.set(-8, 10, -20);
	SirenPos.set(6, 2, 16);

	SFXManager::ChangeDirectionalLighting(Vect(0, -.75f, 0).getNorm(),
		0.1f * Vect(1, 1, 1), 1 * Vect(1, 1, 1), 0.1f * Vect(1, 1, 1));

	pnt1 = SFXManager::AssignPointLighting(Light1Pos, 15, 0.5f * Vect(1, 1, 1),
		.1 * Vect(1, 1, 1), 2 * Vect(1, 1, 1), 1 * Vect(1, 1, 1));

	pnt2 = SFXManager::AssignPointLighting(Light2Pos, 15, 0.5f * Vect(1, 1, 1),
		.1 * Vect(1, 1, 1), 2 * Vect(1, 1, 1), 1 * Vect(1, 1, 1));

	pnt3 = SFXManager::AssignPointLighting(Light3Pos, 15, 0.5f * Vect(1, 1, 1),
		.1 * Vect(1, 1, 1), 2 * Vect(1, 1, 1), 1 * Vect(1, 1, 1));

	pnt4 = SFXManager::AssignPointLighting(Light4Pos, 15, 0.5f * Vect(1, 1, 1),
		.1 * Vect(1, 1, 1), 2 * Vect(1, 1, 1), 1 * Vect(1, 1, 1));

	spt1 = SFXManager::AssignSpotLighting(SirenPos, 400, .5 * Vect(1, 0, 0),
		pos2 - Vect(0, 1, 0), 50,
		.2 * Vect(1, 1, 1), 30 * Colors::Red, 1 * Vect(1, 1, 1, 150));
	spt2 = SFXManager::AssignSpotLighting(SirenPos, 400, .5 * Vect(1, 0, 0),
		-pos2 + Vect(0, 2, 0), 50,
		.2 * Vect(1, 1, 1), 30 * Colors::Blue, 1 * Vect(1, 1, 1, 150));

	// *********************************************************************************
	// And all our textures...
	// *********************************************************************************
	pTex = new Texture(L"../Assets/Textures/brick.tga");
	sky = new Texture(L"../Assets/Textures/NightSkyBox.tga");
	ground = new Texture(L"../Assets/Textures/ground1.tga");
	marble = new Texture(L"../Assets/Textures/smoothmarble.tga");
	ambulance = TextureManager::Get("Ambulance");
	LampPostTex = new Texture(L"../Assets/Textures/LampPostMetal.tga");
	LampHeadTex = new Texture(L"../Assets/Textures/LampHeadMetal.tga");
	LampConnectTex = new Texture(L"../Assets/Textures/Fiberglass.tga");

	// *********************************************************************************
	// get the models...
	// *********************************************************************************
	// ******************************************************************************** Trees
	mBirchTree = new Model("../Assets/Models/BirchTree.azul");
	mBirchTreeW = Matrix(TRANS, -6.5f, -3, 8);
	BirchTree = new GraphicsObject_ColorNoTextureLight(mBirchTree);
	BirchTree->SetWorld(mBirchTreeW);
	BirchTree->SetMaterial(Colors::DarkGreen, Colors::Green, Vect(0, 0, 0, 1), 0);
	BirchTree->SetMaterial(Colors::Brown, Colors::AntiqueWhite, Vect(0, 0, 0, 1), 1);
	mLittlePineTree = new Model("../Assets/Models/LittlePineTree.azul");
	Tree1 = Matrix(TRANS, -15, -4, 16);
	Tree2 = Matrix(TRANS, 16, -4, -26);
	PineTree = new GraphicsObject_ColorNoTextureLight(mLittlePineTree);
	PineTree->SetMaterial(Colors::Brown, Colors::Brown, Vect(0, 0, 0, 1), 0);
	PineTree->SetMaterial(Colors::DarkGreen, Colors::DarkGreen, Vect(0, 0, 0, 1), 1);
	// ******************************************************************************** Pickup truck
	mPickup = new Model("../Assets/Models/Pickup.azul");
	mPickupW = Matrix(ROT_X, -1.5f) * Matrix(ROT_Y, .3f) * Matrix(TRANS, 13, -2.3f, 15.5f);
	Pickup = new GraphicsObject_ColorNoTextureLight(mPickup);
	Pickup->SetWorld(mPickupW);
	Pickup->SetMaterial(Colors::Black, Colors::MidnightBlue, Vect(1, 1, 1, 1));
	// ******************************************************************************** Subaru
	mSubaru = new Model("../Assets/Models/Subaru.azul");
	subaruPos = Vect(-2, -3, -30);
	mSubaruW = Matrix(TRANS, subaruPos);									// Subaru should roll through the scene , sooo...
	Subaru = new GraphicsObject_ColorNoTextureLight(mSubaru);
	Subaru->SetWorld(mSubaruW);
	Subaru->SetMaterial(Colors::DarkGoldenrod, Colors::Goldenrod, Vect(1, 1, 1, 100));
	// ******************************************************************************** Old car 
	mOldCar = new Model("../Assets/Models/OldCar.azul");
	mOldCarW = Matrix(TRANS, 5, -3, 5);
	OldCar = new GraphicsObject_ColorNoTextureLight(mOldCar);
	OldCar->SetWorld(mOldCarW);
	OldCar->SetMaterial(Colors::DarkRed, Colors::Black, Vect(1, 1, 1, 1));
	// ******************************************************************************** Ambulance
	mAmbulance = ModelManager::Get("Ambulance");
	mAmbulanceW = Matrix(ROT_Y, .5f) * Matrix(TRANS, 5, -2, 15);
	Ambulance = new GraphicsObject_TextureLight(mAmbulance);
	Ambulance->SetWorld(mAmbulanceW);
	Ambulance->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 100));
	Ambulance->SetTexture(ambulance);
	// ******************************************************************************** Apartments building
	mApartments = new Model("../Assets/Models/Apartments.azul");
	mApartmentsW = Matrix(ROT_Y, 89.55f) * Matrix(TRANS, 15, -3, -10);
	Apartments = new GraphicsObject_ColorNoTextureLight(mApartments);
	Apartments->SetWorld(mApartmentsW);
	Apartments->SetMaterial(Colors::Brown, Colors::Firebrick, Vect(0, 0, 0, 1));
	// ******************************************************************************** Cat statue / stand / pyramid & stand
	mCat = new Model("../Assets/Models/Cat2.azul");
	mCatW = Matrix(ROT_Y, 45.0f) * Matrix(TRANS, -10, -1.5f, -6);
	CatStatue = new GraphicsObject_TextureLight(mCat);
	CatStatue->SetWorld(mCatW);
	CatStatue->SetTexture(marble);
	CatStatue->SetMaterial(Colors::White, 1 * Colors::White, Vect(1, 1, 1, 100));
	mStatueBase = new Model(Model::PreMadedeModels::UnitBoxRepeatedTexture);
	mStatueBaseW = Matrix(SCALE, 7, 7, 7) * Matrix(TRANS, -10, -5, -6);
	StatueBase = new GraphicsObject_TextureLight(mStatueBase);
	StatueBase->SetWorld(mStatueBaseW);
	StatueBase->SetTexture(marble);
	StatueBase->SetMaterial(Colors::Black, Colors::DarkGray, Vect(1, 1, 1, 100));
	BoxWrap = new Model(Model::PreMadedeModels::UnitBoxSixFacesTexture);
	mSpikeBase = Matrix(TRANS, -7, -1, -3);
	SpikeBase = new GraphicsObject_TextureLight(BoxWrap);
	SpikeBase->SetWorld(mSpikeBase);
	SpikeBase->SetTexture(marble);
	SpikeBase->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 100));
	Pyramid = new Model(Model::PreMadedeModels::UnitPyramid);
	mSpike = Matrix(TRANS, -7, 0, -3);
	Spike = new GraphicsObject_TextureLight(Pyramid);
	Spike->SetWorld(mSpike);
	Spike->SetTexture(marble);
	Spike->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 100));
	pModel1 = new Model(Model::PreMadedeModels::UnitSphere);
	mBall = Matrix(TRANS, -7, 1, -3);
	Ball = new GraphicsObject_TextureLight(pModel1);
	Ball->SetWorld(mBall);
	Ball->SetTexture(marble);
	Ball->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 100));
	// ******************************************************************************** House/McDonalds
	mHouse = new Model("../Assets/Models/House.azul");
	mHouseW = Matrix(ROT_Y, -1.55f) * Matrix(TRANS, 17, -3, 8);
	House = new GraphicsObject_ColorNoTextureLight(mHouse);
	House->SetWorld(mHouseW);
	House->SetMaterial(Colors::RosyBrown, Colors::RosyBrown, Vect(1, 1, 1, 1));
	// ******************************************************************************** McDonalds sign
	mSignPost = new Model("../Assets/Models/SignPost.azul");
	mSignPostW = Matrix(TRANS, 7.5f, -3.3f, 8);
	SignPost = new GraphicsObject_TextureLight(mSignPost);
	SignPost->SetWorld(mSignPostW);
	SignPost->SetMaterial(Colors::DarkGray, Colors::DarkGray, Vect(0, 0, 0, 1), 0);
	SignPost->SetTexture(LampPostTex, 0);
	SignPost->SetMaterial(Colors::White, Colors::White, Vect(0, 0, 0, 1), 1);
	SignPost->SetTexture(LampConnectTex, 1);
	mMcD = new Model("../Assets/Models/McDSign.azul");
	mMcDW = mSignPostW * Matrix(TRANS, 0, 4, 0);
	McDSign = new GraphicsObject_ColorNoTextureLight(mMcD);
	McDSign->SetMaterial(Colors::Red, Colors::Yellow, Vect(1, 1, 1, 100));
	// ******************************************************************************** Streetlamp
	mStreetLamp = new Model("../Assets/Models/StreetLamp.azul");
	Vect LampModelOffset(-2, 13.5, 0);
	mStreetLampW1 = Matrix(TRANS, Light1Pos - LampModelOffset);
	mStreetLampW2 = Matrix(TRANS, Light2Pos - LampModelOffset);
	mStreetLampW3 = Matrix(TRANS, Light3Pos - LampModelOffset);
	mStreetLampW4 = Matrix(TRANS, Light4Pos - LampModelOffset);
	StreetLamp = new GraphicsObject_TextureLight(mStreetLamp);
	StreetLamp->SetMaterial(Colors::DarkGray, Colors::DarkGray, Vect(0, 0, 0, 1), 0);
	StreetLamp->SetTexture(LampPostTex, 0);
	StreetLamp->SetMaterial(Colors::DarkSlateGray, Colors::DarkSlateGray, Vect(0, 0, 0, 1), 1);
	StreetLamp->SetTexture(LampHeadTex, 1);
	StreetLamp->SetMaterial(Colors::White, Colors::White, Vect(0, 0, 0, 1), 2);
	StreetLamp->SetTexture(LampConnectTex, 2);
	// ******************************************************************************** LightSpheres
	mWorld1 = Matrix(TRANS, 0, 0, 0);
	LampLight = new GraphicsObject_ColorNoTexture(pModel1);
	Vect LampColor = Colors::Yellow;
	LampColor.W() = 0.1f;
	LampOffset = Vect(0, 4, 0);
	LampScale = .8f;
	LampLight->SetColor(LampColor);
	// ******************************************************************************** Road/Plane
	float scale = 30;
	pPlane = new FlatPlane_Object(scale, 1, 1);
	planeMat = Matrix(TRANS, 0, -3, 0);
	pPlane->SetWorld(Matrix(TRANS, 0, -3, 0));
	pPlane->SetMaterial(Colors::Black, 1 * Colors::White, Vect(1, 1, 1, 100));
	pPlane->SetTexture(pTex);

	planeMat2 = Matrix(ROT_X, -3.1415 / 2) * Matrix(TRANS, scale / 4, 0, scale / 4);

	pModel2 = new Model(Model::PreMadedeModels::UnitBoxRepeatedTexture);
	pos2 = Vect(0, 0, -4);
	mWorld2 = Matrix(TRANS, SirenPos) * Matrix(TRANS, pos2);

	/******************************************************************************** Terrain and Skybox
	pTerrain = new TerrainObject(L"../Assets/Textures/HMtest.tga", 1000, 100, -200, 0, 1, 0, 1);
	pTerrain->SetTexture(ground);
	pTerrain->SetWorld(planeMat * Matrix(TRANS, 0, -1, 0));
	pTerrain->SetMaterial(Colors::White, 1 * Colors::Green, Vect(1, 1, 1, 100));
	//*/

	Scene::SetTerrain("ourTerrain");

	SkyBoxManager::Choose("sky");

	mCam = SceneManager::GetCurrentCamera();
	// Initialize the projection matrix
	mCam->setPerspective(3.14159 / 3, 
		(float)APlusPlusEngine::GetWindowWidth() / (float)APlusPlusEngine::GetWindowHeight(), 
		1.0f, 10000.0f);
	mCam->setOrientAndPosition(Vect(0, 1, 0), Vect(0, 0, 0), Vect(-10, 8, -8));
}

DemoScene::DemoScene()
{	
	mCam = nullptr;
}

DemoScene::~DemoScene()
{
	SkyBoxManager::Terminate();

	delete pPlane;
	delete pModel1;
	delete pModel2;
//	delete pTerrain;
	delete ground;
//	delete pSkybox;
	delete sky;
	delete marble;
//	delete ambulance;

	delete Pickup;
	delete mPickup;

	delete mBirchTree;
	delete BirchTree;
	delete mLittlePineTree;
	delete PineTree;

	delete mSubaru;
	delete Subaru;

	delete mOldCar;
	delete OldCar;

//	delete mAmbulance;
	delete Ambulance;

	delete mApartments;
	delete Apartments;

	delete mCat;
	delete CatStatue;
	delete mStatueBase;
	delete StatueBase;
	delete BoxWrap;
	delete SpikeBase;
	delete Pyramid;
	delete Spike;
	delete Ball;

	delete mHouse;
	delete House;

	delete mMcD;
	delete McDSign;
	delete mSignPost;
	delete SignPost;

	delete mStreetLamp;
	delete LampPostTex;
	delete LampHeadTex;
	delete LampConnectTex;
	delete LampLight;
	delete StreetLamp;

	delete pTex;
}

void DemoScene::Update()
{
	mWorld2 *= Matrix(ROT_Y, .005f);  // Simple slow rotation about y axis
	pos2 = mWorld2.get(MatrixRowType::ROW_3);
	mMcDW = Matrix(ROT_Y, .0005f) * mMcDW;
	subaruPos += Vect(0, 0, .8f);
	if (subaruPos.Z() > 150)
		subaruPos.Z() = -150;
	mSubaruW = Matrix(TRANS, subaruPos);

	float camSpeed = 0.35f;
	if (Keyboard::IsKeyActive(KEY_W))
	{
		mCam->TranslateFwdBack(camSpeed);
	}
	else if (Keyboard::IsKeyActive(KEY_S))
	{
		mCam->TranslateFwdBack(-camSpeed);
	}

	if (Keyboard::IsKeyActive(KEY_A))
	{
		mCam->TranslateLeftRight(-camSpeed);
	}
	else if (Keyboard::IsKeyActive(KEY_D))
	{
		mCam->TranslateLeftRight(camSpeed);
	}

	float rotSpeed = 0.035f;
	if (Keyboard::IsKeyActive(KEY_ARROW_LEFT))
	{
		mCam->TurnLeftRight(rotSpeed);
	}
	else if (Keyboard::IsKeyActive(KEY_ARROW_RIGHT))
	{
		mCam->TurnLeftRight(-rotSpeed);
	}

	if (Keyboard::IsKeyActive(KEY_ARROW_UP))
	{
		mCam->TiltUpDown(rotSpeed);
	}
	else if (Keyboard::IsKeyActive(KEY_ARROW_DOWN))
	{
		mCam->TiltUpDown(-rotSpeed);
	}

	mCam->updateCamera();

	SFXManager::ChangeSpotLighting(spt1, SirenPos, 400, .5 * Vect(1, 0, 0),
		pos2 - Vect(0, 1, 0), 50,
		.2 * Vect(1, 1, 1), 30 * Colors::Red, 1 * Vect(1, 1, 1, 150));
	SFXManager::ChangeSpotLighting(spt2, SirenPos, 400, .5 * Vect(1, 0, 0),
		-pos2 + Vect(0, 2, 0), 50,
		.2 * Vect(1, 1, 1), 30 * Colors::Blue, 1 * Vect(1, 1, 1, 150));
}

void DemoScene::Draw()
{
	//*
	// Plane/box display
	pShaderTexLight->SetToContext();

	SFXManager::SetDisableFog();

	// render Terrain
	// Turn fog on...
	SFXManager::SetDisableFog();
//	pTerrain->Render();

	SFXManager::SetFogParameters(25, 35, Colors::Black);
	// Render Cat Statue and Base
	CatStatue->Render();
	StatueBase->Render();
	SpikeBase->Render();
	Spike->Render();
	Ball->Render();

	// Render StreetLamps...
	// 1
	StreetLamp->SetWorld(mStreetLampW1);
	StreetLamp->Render();
	// 2
	StreetLamp->SetWorld(mStreetLampW2);
	StreetLamp->Render();
	// 3
	StreetLamp->SetWorld(mStreetLampW3);
	StreetLamp->Render();
	// 4
	StreetLamp->SetWorld(mStreetLampW4);
	StreetLamp->Render();

	SignPost->Render();

	// Render Ambulance...
	Ambulance->Render();

	// **************************************************************************************
	// Set colorlight to context, update spotlights
	pShaderColLight->SetToContext();
	// ***************************************************************************************

	// Render Trees
	BirchTree->Render();
	PineTree->SetWorld(Tree1);
	PineTree->Render();
	PineTree->SetWorld(Tree2);
	PineTree->Render();

	// Render McDSign...
	McDSign->SetWorld(mMcDW);
	McDSign->Render();

	// Render Apartment building...
	Apartments->SetWorld(mApartmentsW);
	Apartments->Render();

	// Render Old car...
	OldCar->Render();

	// Render Pickup...
	// Render with color, black or blue idk
	Pickup->Render();

	// Render Subaru...
	Subaru->SetWorld(mSubaruW);
	Subaru->Render();

	// Render House...
	House->Render();

	pShaderTexLight->SetToContext();
	// Brick ground
	pPlane->SetWorld(planeMat);										// beep
	pPlane->Render();
	pPlane->SetWorld(planeMat * Matrix(TRANS, 0, 0, -30));			// beep
	pPlane->Render();
	pPlane->SetWorld(planeMat * Matrix(TRANS, 0, 0, -60));			// beep
	pPlane->Render();
	pPlane->SetWorld(planeMat * Matrix(TRANS, 0, 0, -90));			// beep
	pPlane->Render();
	pPlane->SetWorld(planeMat * Matrix(TRANS, 0, 0, 30));			// beep
	pPlane->Render();
	pPlane->SetWorld(planeMat * Matrix(TRANS, 0, 0, 60));			// beep
	pPlane->Render();
	pPlane->SetWorld(planeMat * Matrix(TRANS, 0, 0, 90));			// beep
	pPlane->Render();
	// turn off fog...												// beep
	SFXManager::SetDisableFog();

	// Render the four street lights...
	pShaderCol->SetToContext();
	LampLight->SetWorld(Matrix(SCALE, LampScale, LampScale, LampScale) * Matrix(TRANS, Light1Pos - LampOffset));
	LampLight->Render();
	LampLight->SetWorld(Matrix(SCALE, LampScale, LampScale, LampScale) * Matrix(TRANS, Light2Pos - LampOffset));
	LampLight->Render();
	LampLight->SetWorld(Matrix(SCALE, LampScale, LampScale, LampScale) * Matrix(TRANS, Light3Pos - LampOffset));
	LampLight->Render();
	LampLight->SetWorld(Matrix(SCALE, LampScale, LampScale, LampScale) * Matrix(TRANS, Light4Pos - LampOffset));
	LampLight->Render();
}