#ifndef CAMERA_H
#define CAMERA_H

#include <malloc.h>
#include "Align16.h"

#include "Vect.h"
#include "Matrix.h"

class CameraProjCmd;

class Camera : public Align16
{

public:

	enum class Type
	{
		PERSPECTIVE_3D,
		ORTHOGRAPHIC_2D
	};

	// Default constructor
	Camera() = delete;
	~Camera();

	Camera(Camera::Type type);

	// Setup on single camera
	void setPerspective(const float FieldOfView_Degs, const float AspectRatio, const float NearDist, const float FarDist);
	void setOrthographic(const float top, const float bot, const float left, const float right, const float NearDist, const float FarDist);
	void setOrientAndPosition(const Vect &Up_vect, const Vect &inLookAt_pt, const Vect &pos_pt);

	// update camera system
	void updateCamera(void);

	// Get the matrices for rendering
	Matrix& getViewMatrix();
	Matrix& getProjMatrix();

	// accessors
	void getPos(Vect &outPos) const;
	void getDir(Vect &outDir) const;
	void getUp(Vect &outUp) const;
	void getLookAt(Vect &outLookAt) const;
	void getRight(Vect &outRight) const;

	void TranslateUpDown(float delta);
	void TranslateLeftRight(float delta);
	void TranslateFwdBack(float delta);
	void TiltUpDown(float ang);
	void TurnLeftRight(float ang);

	// Why no SETS for Pos, Dir, Up, LookAt and Right?
	//   They have to be adjusted _together_ in setOrientAndPosition()

private:  // methods should never be public
	void privUpdateProjectionMatrix(void);
	void privUpdateViewMatrix(void);

	friend class CameraAttorneyToCommands;
	void privUpdatePerspective(void);
	void privUpdateOrthographic(void);

private:  // data  (Keep it private)

		  // Projection Matrix
	Matrix	projMatrix;
	Matrix	viewMatrix;
	Matrix  NDCConvert;

	// camera unit vectors (up, dir, right)
	Vect	vUp;
	Vect	vDir;
	Vect	vRight;  // derived by up and dir
	Vect	vPos;
	Vect	vLookAt;

	Camera::Type camType;
	CameraProjCmd* cmd;

	// Define the frustum inputs
	float	nearDist;
	float	farDist;
	// perspective info
	float	fovy;  // aka view angle along y axis
	float	aspectRatio;
	// orthographic info
	float topClip;
	float botClip;
	float leftClip;
	float rightClip;
};

#endif