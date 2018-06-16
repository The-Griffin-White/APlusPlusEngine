#ifndef GAME_H
#define GAME_H

#include "APPECore.h"

class APlusPlusEngine : public Engine
{
private:
	static APlusPlusEngine* gameInstance;				// Engine set up as singleton

	APlusPlusEngine() { };								// Private constructor
	APlusPlusEngine(const APlusPlusEngine&) = delete;				// Prevent copy-construction
	APlusPlusEngine& operator=(const APlusPlusEngine&) = delete;	// Prevent assignment
	~APlusPlusEngine() = default;						// Only this class can delete

	static APlusPlusEngine& Instance()	    // Access reference (all public methods will be static)
	{
		if (!gameInstance)
			gameInstance = new APlusPlusEngine;
		return *gameInstance;
	};

	virtual void Initialize();
	/// \brief User defined to set up basic Engine details such as windows size & name or background color
	/// \ingroup USER-DEFINED
	///
	/// \par EXAMPLE:
	///		\code
	///		void APlusPlusEngine::GameInitialize()
	///		{
	///			this->setWindowName("A++ Engine Demo");
	///			this->setWidthHeight(1200, 900);
	///			this->SetClearColor(Colors::CadetBlue, 1.0f);
	///		}
	///		\endcode
	virtual void GameInitialize();
	/// \brief Used to LoadContent, including user resources and the first scene.
	/// \ingroup APPE-CORE
	virtual void LoadContent();
	/// \brief User defined to load all resources the player might want into the appropriate managers
	/// \ingroup USER-DEFINED
	///
	///	\par EXAMPLE:
	///		\code
	///		void APlusPlusEngine::LoadAllResources()
	///		{
	///			ModelManagerAttorneyToEngine::Load("Axis", "Axis");
	///			TextureManagerAttorneyToEngine::Load("space_frigate", "space_frigate.tga");
	///			ShaderManagerAttorneyToEngine::Load("textureFlatRender", "textureFlatRender");
	///		}
	///		\endcode
	virtual void LoadAllResources();
	/// \brief Used to Call the Update cycle each frame.
	/// \ingroup APPE-CORE
	virtual void Update();
	/// \brief Used to Call the Draw cycle each frame.
	/// \ingroup APPE-CORE
	virtual void Draw();
	/// \brief Deletes all loaded content from managers on shutdown.
	/// \ingroup APPE-CORE
	virtual void UnLoadContent();
	/// \brief User defined to delete any stray managers or singletons the user has defined outside the scope of a single Scene
	/// \ingroup USER-DEFINED
	///
	/// \par EXAMPLE:
	///		\code
	///		void APlusPlusEngine::ClearUserContent()
	///		{
	///			BombFactory::Terminate();
	///		}
	///		\endcode
	virtual void ClearUserContent();
	/// \brief User defined to choose which scene we start at
	/// \ingroup USER-DEFINED
	///
	/// \par EXAMPLE:
	///		\code
	///		void APlusPlusEngine::SetStartScene()
	///		{
	///			SceneManager::SetNextScene(new MovementDemoScene);
	///		}
	///		\endcode
	virtual void SetStartScene();

	/// \brief Sets the background color from the GameInitialize function
	/// \ingroup GAME-INIT
	///
	/// \param red Red value for background color
	/// \param green Green value for background color
	/// \param blue Blue value for background color
	/// \param alpha Alpha value for background color
	void SetClearColor(const float& red, const float& green, const float& blue, float alpha = 1.0f);
	/// \brief Sets the background color from the GameInitialize function
	/// \ingroup GAME-INIT
	///
	/// \param col 3D Vector Representing the colors red, green, and blue for the background color
	/// \param alpha Alpha value for background color
	void SetClearColor(const Vect& col, float alpha = 1.0f);

	friend class APlusPlusEngineAttorneyToTimeManager;
	friend class APlusPlusAttorneyToFreezeTime;
	static float GameTimeInSeconds() { return Instance().GetTimeInSeconds(); };

public:

	/// \brief Starts the game.
	/// \ingroup APPE-CORE
	static int RunGame(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
	{
		return Instance().privRun(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	}
	/// \brief Ends the game.
	/// \ingroup APPE-CORE
	static void TerminateGame();

	/// \brief Used to set Window Width and Height
	///
	/// \param width Width in pixels
	/// \param height Height in pixels
	static void SetWindowDimensions(const int width, const int height) 
									{ Instance().setWidthHeight(width, height); };
	/// \brief Used to define the Name of the game window
	///
	/// \param pWindowName String used to name the window
	static void SetWindowName(const char *pWindowName) 
									{ Instance().SetWindowName(pWindowName); };
	/// \brief Sets the background color
	///
	/// \param red Red value for background color
	/// \param green Green value for background color
	/// \param blue Blue value for background color
	/// \param alpha Alpha value for background color
	static void SetBackgroundColor(float red, float green, float blue, float alpha) 
									{ Instance().SetClearColor(red, green, blue, alpha); };
	/// \brief Sets the background color
	///
	/// \param col 3D Vector Representing the colors red, green, and blue for the background color
	/// \param alpha Alpha value for background color
	static void SetBackgroundColor(const Vect& col, float alpha)
									{ Instance().SetClearColor(col, alpha); };

	/// \brief Returns the Height of the window in pixels
	static int GetWindowHeight() { return Instance().getHeight(); };
	/// \brief  Returns the Width of the window in pixels
	static int GetWindowWidth() { return Instance().getWidth(); };

	static void SetSolidRendering();
	static void SetWireFrameRendering();

private:	
	// legacy
	APlusPlusEngine( const char* windowName, const int Width,const int Height);


};

#endif