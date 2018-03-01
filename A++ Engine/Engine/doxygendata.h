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

/** \defgroup APPE-INTERNAL Internal to APlusPlusEngine
\brief Reference for internal components, these should not be messed with in normal use.
*/

/** \defgroup SCENE-MANAGE Scene Management
\ingroup APPE-INTERNAL
\brief Details the internals of the Scene superclass and management of multiple scenes with the SceneManager class.
*/

/** \defgroup ALARM-MANAGE Alarm Management
\ingroup SCENE-MANAGE
\brief Details the management of GameObject Alarms.
*/

/** \defgroup CAM-MANAGE Alarm Management
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
	- Set up Window details in the GameInitialize() function in GameInitialize.cpp.
	- Choose the first scene you want to load in the SetStartScene() function in GameInitialize.cpp.
	
- <b>Step 2</b>: Create your first Scene
	- Create a new class derived from Scene and name it whatever you want.
	- Fill in Initialize() in your new class to include whatever you need.

- <b>Step 3</b>: Create your first GameObject
	- Create a new class derived from GameObject.
	- Register it for whatever functions it needs (Update(), Draw(), Collision(), etc.).
	- Fill in the functions with any functionality you want.
	- Create and Initialize this GameObject in the Scene you created.
	
- <b>Step 4</b>: Go crazy!
	- Once you understand the GameObject and Scene classes, you're free to make whatever you like!

*/

/*! \page usingappe Using APlusPlusEngine
There are two documentation modules for APlusPlusEngine:

- \ref APPE-API "Module 1: APlusPlusEngine API": This is the most common case where you just want to use the framework

- \ref APPE-INTERNAL "Module 2: APlusPlusEngine's internal workings": This is provided only for those interested in looking inside 
	the framework and see how it works.

*/