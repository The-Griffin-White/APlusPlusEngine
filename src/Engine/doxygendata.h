/** \defgroup APPE-API APlusPlusEngine API
\brief These commands are available to APlusPlusEngine users
\par All engine functionality is accessible from and designed around these options.
 You can dive into the guts, but you might as well make a new engine at that point...
*/

/** \defgroup GAMEOBJECT GameObject
\ingroup APPE-API
\brief All game entities will be derived from GameObject. 
\par Every object in your game will use these functions in some way.
 All functionality must be registered manually before it can be used.
*/

/** \defgroup REGISTER GameObject Registration
\ingroup GAMEOBJECT
\brief All GameObjects have the same scene registration functions.
The user must Submit the GameObject for Entry or Exit from the Scene and define the SceneEntry and SceneExit functions.
*/

/** \defgroup UPDATE Updateable
\ingroup GAMEOBJECT
\brief All GameObjects have a built in Updateable parent class and functionality.
The GameObject must be registered manually for this Update() function to be called each frame.
Updateable also needs to be deregistered manually when an object no longer wants to be called for Update().
*/

/** \defgroup DRAW Drawable
\ingroup GAMEOBJECT
\brief All GameObjects have a built in Drawable parent class and functionality.
The GameObject must be registered manually for this Draw() function to be called each frame.
Drawable also needs to be deregistered manually when an object no longer wants to be called for Draw().
*/

/** \defgroup ALARM Alarmable
\ingroup GAMEOBJECT
\brief All GameObjects have a built in Alarmable parent class and functionality.
The GameObject must be registered manually for Alarms to be activated.
These alarms can be deregistered manually at any time.
*/

/** \defgroup INPUT Inputable
\ingroup GAMEOBJECT
\brief All GameObjects have a built in Inputable parent class and functionality.
The GameObject must register any keys it wants to use in order for them to checked at each frame.
Inputable keys also need to be deregistered manually when an object is no longer looking for input.
*/

/** \defgroup COLLISION Collidable
\ingroup GAMEOBJECT
\brief All GameObjects have a built in Collidable parent class and functionality.
The GameObject must register itself if it wants to be included in the collision system.
It must also deregister itself when it no longer wants to be included in the collision system.
The current Scene must also register pairs of GameObject child classes it wants to collide in the scene, otherwise even registered GameObjects will not be checked.
*/

/** \defgroup USER-DEFINED User Defined Engine Components
\ingroup APPE-API
\brief Engine functions available to be defined by the user.
*/

/** \defgroup GAME-INIT Game Initialization
\ingroup USER-DEFINED
\brief Functions available to help define the GameInitialization function.
*/

/** \defgroup ASSET-INIT Asset Initialization
\ingroup USER-DEFINED
\brief Functions available to help define the LoadAllResources function - specifically, to load Models, Textures, and Shaders from files.
*/

/** \defgroup SCENE Scene
\ingroup APPE-API
\brief A Scene is the space in which GameObjects exist. 

Scenes are the stages or levels that we place GameObjects in. 
You need only define the Initialization() function to start using it, but there are a few other functions available to be defined by the user.
*/

/** \defgroup SPRITE Sprites
\ingroup APPE-API
\brief A Sprite is a 2D Graphical object that appears in front of GameObjects (in the 'HUD').
*/

/** \defgroup TERRAIN Terrain
\ingroup APPE-API
\brief 3D Terrain that can be moved along or collided with
*/

/** \defgroup APPE-INTERNAL Internal to APlusPlusEngine
\brief Reference for internal components, these should not be messed with in normal use.
*/

/** \defgroup SCENE-MANAGE Scene Management
\ingroup APPE-INTERNAL
\brief Details the internals of the Scene superclass and management of multiple scenes with the SceneManager class.
*/

/** \defgroup EFFECTS Special Effects
\ingroup APPE-INTERNAL
\brief Details special effects like fog, lighting, and skyboxes.
*/

/** \defgroup SPRITE-MANAGE Sprite Management
\ingroup SCENE-MANAGE
\brief Details the frame-by-frame use of sprites.
\ref SPRITE
*/

/** \defgroup ALARM-MANAGE Alarm Management
\ingroup SCENE-MANAGE
\brief Details the management of GameObject Alarms.
*/

/** \defgroup CAM-MANAGE Camera Management
\ingroup SCENE-MANAGE
\brief Details the management of Cameras for use in a Scene.
*/

/** \defgroup COL-MANAGE Collision Management
\ingroup SCENE-MANAGE
\brief Details the management of GameObject collisions (does not discuss detection here).
\par 
- <b>Collidable Manager</b>: Iterates through each registered pair of Collidable's to test for collision each frame.
	
- <b>Collidable Group</b>: Holds each individual instance of a type of registered Collidable.

- <b>CollisionTestCommand</b>: Pair and Self, tests each instance in each pair of types to look for collision.

Uses Bounding sphere logic:
\ref UTIL
*/

/** \defgroup INPUT-MANAGE Input Management
\ingroup SCENE-MANAGE
\brief Details the matching of key presses and releases to the corresponding calls in GameObject.
\par Divided into the KeyboardEventManager, which handles a list of SingleKeyEventManagers for each individual registered key.
*/

/** \defgroup DRAW-MANAGE Draw Management
\ingroup SCENE-MANAGE
\brief Details the management of GameObject Draw() calls.
*/

/** \defgroup UPDATE-MANAGE Update Management
\ingroup SCENE-MANAGE
\brief Details the management of GameObject Update() calls.
*/

/** \defgroup SCENE-REGISTER Scene Registration
\ingroup SCENE-MANAGE
\brief Details the registration of various GameObject functionalities into the Scene and appropriate Managers.
\par Registration into the Scene is handled by a registration broker, which takes commands and processes them each frame.
*/

/** \defgroup TIME-MANAGE Time Management
\ingroup APPE-INTERNAL
\brief Details the internals of Time management within the game engine, including the FreezeTime debug tool.
*/

/** \defgroup UTIL Utilities
\ingroup APPE-INTERNAL
\brief Details the various utilities in the engine, such as math functions and premade values.
*/

/** \defgroup ASSET-MANAGE Asset Management
\ingroup APPE-INTERNAL
\brief Details the internals of Asset Management for Models, Textures, and Shaders. See Asset Initialization for details on how the user interacts with these.
\ref ASSET-INIT
*/

/** \defgroup VISUALIZE Visualizer
\ingroup APPE-INTERNAL
\brief Used to make collision models visible in demo.
*/

/** \defgroup APPE-CORE APlusPlusEngine Core
\ingroup APPE-INTERNAL
\brief Functions in the core of APlusPlusEngine.
*/

/**************************************************************************************************************/


/*! \mainpage About APlusPlusEngine

APlusPlusEngine is a basic 3D game engine that extends the AzulCore package designed by the DePaul staff (Andre Berthiaume and Ed Keenan).

\section features Features
APlusPlusEngine provides the following components:
	- A resource manager organize your external assets (textures, models, shaders). 
	- Base classes Scene and GameObject from which to derive your own levels and game entities.
	- A built-in game loop to update and draw the current Scene and its associated GameObjects.
	- A built-in collision system for GameObject with precise detection based on bounding spheres.
	- Callbacks for Collision events, alarms events, input events (keyboard, controller, mouse, etc.), window events (Focus, resize, etc.).
	
The engine is an ongoing project and will include more features as time goes on.

*/

/*! \page demo Demo Creation
Creating a new demo is easy in APlusPlusEngine

- <b>Step 1:</b> Fill in the User Define Engine Components (see the module for details)
	- Load in any models, textures, and shaders you want to use in the LoadAllResources() function in the LoadAllResources.cpp file.
	For Example:
	\code
	void APlusPlusEngine::LoadAllResources()
	{		
		ModelManagerAttorneyToEngine::Load("space_frigate", "space_frigate");
		TextureManagerAttorneyToEngine::Load("space_frigate", "space_frigate.tga");
		ShaderManagerAttorneyToEngine::Load("textureLightRender", "textureLightRender");
	}
	\endcode
	- Set up Window details in the GameInitialize() function in GameInitialize.cpp.
	For Example:
	\code
	void APlusPlusEngine::GameInitialize()
	{
		this->setWindowName("A++ Engine Demo");
		this->setWidthHeight(1200, 900);
		this->SetClearColor(Colors::CadetBlue, 1.0f);
	}
	\endcode
	- Choose the first scene you want to load in the SetStartScene() function in GameInitialize.cpp, and anything you want to delete when the game closes.
	For Example:
	\code
	void APlusPlusEngine::ClearUserContent()
	{
		BombFactory::Terminate();
		EnemyTankFactory::Terminate();
	}
	void APlusPlusEngine::SetStartScene()
	{
		SceneManager::SetNextScene(new Level1);
	}
	\endcode
	
	
- <b>Step 2</b>: Create your first Scene
	- Create a new class derived from Scene and name it whatever you want.
	- Fill in Initialize() in your new class to include whatever you need.
		- You should set up the perspective camera to the correct dimensions here.
		- You also NEED to set collision pairs here if you want collision to work. Of course GameObjects must also be individually registered.
	For Example:
	\code
		void Level1::Initialize()
		{		
			APlusPlusEngine::SetBackgroundColor(Colors::Blue, 1.0f);

			pTank = new Tank;
			pTank->Initialize(Vect(0, 1, 0));

			pPlane = new Plane;
			pPlane->Initialize();

			EnemyTankFactory::CreateEnemyTank(Vect(100, 1, 100));
			EnemyShipFactory::CreateEnemyShip(Vect(-100, 10, -100));

			SetCollisionPair<Bomb, EnemyTank>();
			SetCollisionPair<Bomb, EnemyShip>();
			SetCollisionPair<EnemyBomb, Tank>();
			SetCollisionPair<EnemyShip, Tank>();

			pCam3D = SceneManager::GetCurrentCamera();

			pCam3D->setViewport(0, 0, APlusPlusEngine::GetWindowWidth(), 
								APlusPlusEngine::GetWindowHeight());
			pCam3D->setPerspective(35.0f, 
								float(APlusPlusEngine::GetWindowWidth()) / float(APlusPlusEngine::GetWindowHeight()), 
								1.0f, 5000.0f);
		}
	\endcode

- <b>Step 3</b>: Create your first GameObject
	- Create a new class derived from GameObject.
	Example:
		- We need to construct the GameObject. You may want to split Construction up with an initializer, in case you use factories or othewise want to reuse an object.
		Example:
		\code
		Tank::Tank()
		{
			// Set up any variables that are won't need to change much (could also be class static)
			FirstPersonOffset = Vect(0, 10, -15);
			FirstPersonLookAt = Vect(0, 10, 10);
			ThirdPersonOffset = Vect(0, 30, -80);
			ThirdPersonLookAt = Vect(0, 10, 50);

			camOffset = &ThirdPersonOffset;
			camLookAt = &ThirdPersonLookAt;

			turretRotAngle = 0.03f;
			tankRotAngle = 0.05f;
			tankSpeed = 0.5f;

			// Create the models
			Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
			Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);

			pGObj_t99Turret = new GraphicsObject_TextureLight(ModelManager::Get("Turret"),
				ShaderManager::Get("textureLightRender"),
				TextureManager::Get("Body"),
				LightColor, LightPos);

			pGObj_t99Body = new GraphicsObject_TextureLight(ModelManager::Get("Body"),
				ShaderManager::Get("textureLightRender"),
				TextureManager::Get("Body"),
				TextureManager::Get("Track"),
				LightColor, LightPos);
				
			// set up Model for Collision use
			SetColliderModel(pGObj_t99Body->getModel());

			// Create a sprite we want
			xhair = SpriteFactory::CreateSprite(ImageManager::Get("xhair"), new Rect(100.0f, 0.0f, 150.0f, 150.0f));
			xhair->Pos(600, 600);
			xhairScale = 1.0f;
			xhair->Scale(xhairScale);
		}

		void Tank::Initialize()
		{
			// Set variables we need when the GameObject is reused
			currHealth = MaxHealth;

			// Set body world matrix
			Matrix world;
			scale.set(SCALE, 0.5f, 0.5f, 0.5f);
			rot.set(IDENTITY);
			pos.set(0, 1, 0);
			world = scale * rot * Matrix(TRANS, pos);
			pGObj_t99Body->SetWorld(world);

			// Set turret worldmatrix
			scale.set(SCALE, 0.5f, 0.5f, 0.5f);
			turretRot = rot;
			turretPos = pos + Vect(0, 6, 0);
			world = scale * turretRot * Matrix(TRANS, turretPos);
			pGObj_t99Turret->SetWorld(world);

			// Submit the object for registration in the scene
			this->SubmitEntry();
		}
		\endcode
		- Since this is C++, the GameObject must also be destroyed. Delete heap data and other normal C++ stuff here, don't deregister the GameObject or anything else.
		\code
		Tank::~Tank()
		{
			DebugMsg::out("Deleted Tank\n");
			delete xhair;
			delete pGObj_t99Body;
			delete pGObj_t99Turret;
		}
		\endcode
		- Next, register the GameObject for any functionality you plan to use it for in the Scene, and deregister when you want to leave the Scene.
		\code
		void Tank::SceneEntry()
		{
			// Register this GameObject's Update() function to be called
			Updateable::SubmitUpdateRegistration();
			// Register this GameObject's Draw() function to be called
			Drawable::SubmitDrawRegistration();

			// Register the GameObject's keys that you plan to use
			Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_Q, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
			Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_E, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
			Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_V, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
			Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_W, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
			Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_A, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
			Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_S, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
			Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_D, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
			Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_S, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
			Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_D, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
			Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_ARROW_LEFT, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
			Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_ARROW_RIGHT, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	
			// Register this object for collision; fill out type and the pointer to itself (IMPORTANT!)
			Collidable::CollisionRegistration<Tank>(this);
			// Submit the xhair to be registered (can also be done at the same time you submit the GameObject, if you prefer
			xhair->SubmitRegistration();
		}		

		void Tank::SceneExit()
		{
			// Deregister all the things you registered before
			Updateable::SubmitUpdateDeregistration();
			Drawable::SubmitDrawDeregistration();

			Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_Q, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
			Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_E, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
			Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_V, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
			Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_W, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
			Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_A, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
			Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_S, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
			Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_D, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
			Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_S, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
			Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_D, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
			Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_ARROW_LEFT, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
			Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_ARROW_RIGHT, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);

			Collidable::CollisionDeregistration<Tank>(this);
			xhair->SubmitDeregistration();
		}
		\encode
		- Update() and Draw() are the central functions of a GameObject, and most will use these. Draw() should be used for rendering graphics objects, and Update() should be used for any frame-by-frame changes (say, in position of the model).
		\code
		void Tank::Update()
		{
			if (!bCanFire)
			{
				xhairScale += 0.005f;
				xhair->Scale(xhairScale);
			}

			// Body adjust matrix
			Matrix world = scale * rot * Matrix(TRANS, pos);
			pGObj_t99Body->SetWorld(world);

			// Turret adjust matrix
			world = scale * turretRot * Matrix(TRANS, turretPos);
			pGObj_t99Turret->SetWorld(world);
	
			// Placing the camera relative to the tank
			Matrix TankRotPos = turretRot * Matrix(TRANS, turretPos);  // This is the worldmat without scaling
			Vect vNewCamPos = *camLookAt * TankRotPos;		// This moves the cam position relative to tank's position and rotation
			Vect vNewLookAt = *camOffset * TankRotPos;   // This moves the look-at point relative to tank's position and rotation
			SceneManager::GetCurrentCamera()->setOrientAndPosition(Vect(0, 1, 0), vNewCamPos, vNewLookAt);
			SceneManager::GetCurrentCamera()->updateCamera();
		
			this->UpdateCollisionData(world);
		}

		void Tank::Draw()
		{
			pGObj_t99Turret->Render(SceneManager::GetCurrentCamera());
			pGObj_t99Body->Render(SceneManager::GetCurrentCamera());
		}
		\endcode
		- Inputs should be all defined in the same class, built like this:
		\code
		void Tank::KeyPressed(AZUL_KEY k)
		{
			switch (k)
			{
			case AZUL_KEY::KEY_Q:
				camOffset = &FirstPersonOffset;
				camLookAt = &FirstPersonLookAt;
				turretRotAngle = 0.01f;
				xhair->Pos(600, 460);
				break;
			case AZUL_KEY::KEY_E:
				camOffset = &ThirdPersonOffset;
				camLookAt = &ThirdPersonLookAt;
				turretRotAngle = 0.03f;
				xhair->Pos(600, 600);
				break;
			case AZUL_KEY::KEY_V:
				if (bCanFire)
				{
					bCanFire = false;
					SubmitAlarmRegistration(AlarmableManager::ALARM_0, 1.0f);
					BombFactory::CreateBomb(turretPos, turretRot);
					xhairScale = 0.5f;
					xhair->Scale(xhairScale);
				}
				break;
			case AZUL_KEY::KEY_W:
				pos += Vect(0, 0, 1) * rot * tankSpeed;
				turretPos = pos + Vect(0, 6, 0);
				EnemyTankFactory::UpdateTarget(turretPos);
				EnemyShipFactory::UpdateTarget(turretPos);
				break;
			case AZUL_KEY::KEY_A:
				rot *= Matrix(ROT_Y, tankRotAngle);
				turretRot *= Matrix(ROT_Y, turretRotAngle);
				break;
			case AZUL_KEY::KEY_S:
				pos += Vect(0, 0, 1) * rot * -tankSpeed;
				turretPos = pos + Vect(0, 6, 0);
				EnemyTankFactory::UpdateTarget(pos);
				EnemyShipFactory::UpdateTarget(turretPos);
				break;
			case AZUL_KEY::KEY_D:
				rot *= Matrix(ROT_Y, -tankRotAngle);
				turretRot *= Matrix(ROT_Y, -turretRotAngle);
				break;
			case AZUL_KEY::KEY_ARROW_LEFT:
				turretRot *= Matrix(ROT_Y, turretRotAngle);
				break;
			case AZUL_KEY::KEY_ARROW_RIGHT:
				turretRot *= Matrix(ROT_Y, -turretRotAngle);
				break;
			}
		}
		\endcode
		- And alarms can be registered whenever you want, like so:
		\code
		SubmitAlarmRegistration(AlarmableManager::ALARM_0, 1.0f);
		\endcode
		- And should be defined something like this, with a different numbered alarm function for each:
		\code
		void Tank::Alarm0()
		{
			bCanFire = true;
			xhairScale = 1.0f;
			xhair->Scale(xhairScale);
		}
		\endcode
		- When defining an object as collidable, you need to define what type of collision volume it will use. This can be done in the constructor or initialization, but can be changed later on if desired.
		\code		
		SetColliderModel(pGObj_t99Body->getModel(), CollisionModels::OBB);
		\endcode
		- Finally, when defining collision, make sure the other GameObject has a corresponding Collision function:
		\code
		void Tank::Collision(EnemyBomb* p)
		{
			currHealth -= 1;
			if (currHealth < 0)
				SubmitExit();
			p;
		}
		void EnemyBomb::Collision(Tank* p)
		{
			p;
			SubmitExit();
		}
		\endcode
		- These are only examples of code - fill out the functions with any uses you see fit.
	- Create and Initialize this GameObject in the Scene you created.
		
- <b>Step 4</b>: Using Sprites
	- Sprites are less important to the system then Scenes and GameObjects, but are still a separate system.
	- They function like a simplified GameObject. Their only purpose is to be drawn on the screen, so all their functions help to do this one thing.
	- First, you must #include SpriteFactory.h and Sprite.h
		- SpriteFactory is used to create and recycle Sprites, like so:
		\code
			Sprite* mySprite = SpriteFactory::CreateSprite(MyImage, MyRectangle);
		\endcode
		- Notice that you need to have created an image in the asset initialization section and define a Rect* with the measurements of the sprite.
		- When you want to get rid of a sprite, recycle it:
		\code
			SpriteFactory::RecycleSprite(mySprite);
		\endcode
		- To make a sprite draw, register it:
		\code
			mySprite->SubmitRegistration();
		\endcode
		- And deregister it if you no longer want it to be drawn:
		\code
			mySprite->SubmitDeregistration();
		\endcode
		- For more information on Sprite functions (including changing its position onscreen), see \ref SPRITE
		
	
- <b>Step 5</b>: Set up Terrain
	- Terrain models should be loaded in with a heightmap. There are various ways to create these, but essentially it is a black and white image where the brighter pixels are higher then the darker pixels.
		- This image is loaded into the game and turned into a model, with input parameters in LoadAllResources like the following:
		\code
			TerrainManagerAttorneyToEngine::Load("ourTerrain", TextureManager::Get("ground"), 
				"../Assets/Textures/HMtest.tga", 10000, 1000, -8);
		\endcode
		- The parameters are as follows
			- referenceName, a string used to reference the terrain later (when you want to load it into the scene)
			- texture, The texture (previously loaded into texturemanager) you want to use on the terrain
			- heightmap, The filepath to the heightmap file (not loaded into texturemanager)
			- len, The length or width of the terrain (it should be square, so these are the same values)
			- maxheight, The maximum height of the terrain (for a perfectly white pixel)
			- ytrans, offset the terrains y value. Defaults to 0, does not need to be set.
			- firstU, Texture U value at the topleft corner. Defaults to 0, does not need to be set.
			- secondU, Texture U value at the bottomright corner. Defaults to 1, does not need to be set.
			- firstV, Texture V value at the topleft corner. Defaults to 0, does not need to be set.
			- secondV, Texture V value at the bottomright corner. Defaults to 1, does not need to be set.
			
	- Once you've loaded the terrain, all you need to do is cal SetTerrain(), but you can also modify the terrain's material (for use across multiple scenes)
		\code
		Scene::SetTerrain("tankTerrain");
		Scene::SetTerrainMaterial(Colors::Black, Colors::DarkOliveGreen, Vect(1, 1, 1));
		\endcode
	
	- There are two main features of terrain, collision and movement
		- To register GameObjects to collide with terrain, just call SetCollisionTerrain<C>()
			\code
			SetCollisionTerrain<Bomb>();
			\endcode
		- Setting up terrain movement requires a bit more work on the user end to cater to their specific needs, but everything can be delivered through the GetTerrainVector() function:
			- The function returns a boolean which is true if your model is over terrain, and has a return parameter which is the vector that stores the normal (new up vector for your model)
			- The function is called as follows:
				\code
					Vect up;
					bool overTerrain = SceneManager::GetTerrainVector(this, ip);
					if (overTerrain) this->ChangeUpVector(up);
				\endcode
			- Going from moving over terrain to empty space will cause some issues, so if you need that functionality you will have to reset height/up vector on your own.
		- Terrain also has a few additional features such as getting the height of terrain beneath a collidable or changing its lighting material.
			
- <b>Step 6</b>: Effects and Skyboxes
	- There are three more features to cover - Lighting, Fog, and Skyboxes.
		- For more information, see \ref EFFECTS
	- Lighting
		- Lighting uses the Phong model (ambient, diffuse, specular) with directional, point, and spotlights.
			- Directional lighting mimics the sun and casts light in a single direction, with no origin point
			- Point lights cast light around an origin point in a certain range
			- Spot lights cast light from an origin point at a specific direction in a certain range
		- Directional lighting is set in the scene by default, but can be set by the user as well
		- Point and spot lights need to be assigned, and can be modified after. So, for example:
			\code
				int lightNum;
				
				lightNum = SFXManager::AssignPointLighting(pos, 15, 0.5f * Vect(1, 1, 1),
					.1 * Vect(1, 1, 1), 2 * Vect(1, 1, 1), 1 * Vect(1, 1, 1));
					
				SFXManager::ChangePointLighting(lightNum, pos, 15, 0.5f * Vect(1, 1, 1),
					.1 * Vect(1, 1, 1), 2 * Vect(1, 1, 1), 1 * Vect(1, 1, 1));
			\endcode
	- Fog occludes models that use a lighting shader depending on distance from the camera.
		- To set fog, choose the distance fog starts to appear, the distance it completely occludes, the model, and the fog color.
			\code
				SFXManager::SetFogParameters(200, 1000, Colors::Gray);
			\endcode
		- To disable fog, just call SetDisableFog(), and to reset to the values before you disabled call ResetFogParameters()
			\code
				SFXManager::SetDisableFog();
				SFXManager::ResetFogParameters();
			\endcode
	- A Skybox is a box model with inwardly facing textures. Loading and setting the skybox is simple, just be sure that your camera draw distance is large enough that it can see the skybox.
		- To load a skybox, call Load() in LoadAllResources. Pass in a reference name to select the skybox later and a texture to draw on the skybox.
			\code
				SkyBoxManager::Load("sky", "NightSkyBox.tga");			
			\endcode
			- The texture needs to be a special skybox texture to appear seamless.
		- To draw the skybox, call Choose() with a reference name:
			\code
				SkyBoxManager::Choose("sky");
			\endcode
*/

/*! \page usingappe Using APlusPlusEngine
There are two documentation modules for APlusPlusEngine:

- \ref APPE-API "Module 1: APlusPlusEngine API": This is the most common case where you just want to use the framework

- \ref APPE-INTERNAL "Module 2: APlusPlusEngine's internal workings": This is provided only for those interested in looking inside 
	the framework and see how it works.

*/