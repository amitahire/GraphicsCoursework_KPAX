#include "Camera.h"

void Camera::UpdateCamera (float msec) {
	pitch -= (Window::GetMouse()->GetRelativePosition().y);
	yaw -= (Window::GetMouse()->GetRelativePosition().x);



	pitch = min(pitch,90.0f);
	pitch = max(pitch,-90.0f);

	if(yaw < 0) {
		yaw += 360.0f;
	}
	if(yaw > 360.0f) {
		yaw -= 360.0f;
	}

	if( Window::GetKeyboard()->KeyDown(KEYBOARD_W)) {
		position += Matrix4::Rotation(yaw , Vector3 (0.0f ,1.0f ,0.0f)) * Vector3 (0.0f ,0.0f , -1.0f) * msec ;
	}
	if( Window::GetKeyboard()->KeyDown(KEYBOARD_S)) {
		position -= Matrix4::Rotation(yaw , Vector3 (0.0f ,1.0f ,0.0f)) * Vector3 (0.0f ,0.0f , -1.0f) * msec ;
	}

	if( Window::GetKeyboard()->KeyDown(KEYBOARD_A)) {
		position += Matrix4::Rotation(yaw , Vector3 (0.0f ,1.0f ,0.0f)) *
		Vector3 ( -1.0f ,0.0f ,0.0f) * msec ;
	}

	if( Window::GetKeyboard()->KeyDown(KEYBOARD_D)) {
		position -= Matrix4::Rotation(yaw , Vector3 (0.0f ,1.0f ,0.0f)) *
		Vector3 ( -1.0f ,0.0f ,0.0f) * msec ;
	}

	if( Window::GetKeyboard()->KeyDown(KEYBOARD_SHIFT)) {
		position.y += msec;
	}

	if( Window :: GetKeyboard ()->KeyDown( KEYBOARD_SPACE )) {
		position.y -= msec ;
	}

	//cout << "Position:" << position.x << ":" << position.y << ":" << position.z << endl;
	//cout << "Pitch & yaw" << pitch << ":" << yaw << endl;

};

Matrix4 Camera::BuildViewMatrix(){

	return Matrix4::Rotation(-pitch , Vector3 (1 ,0 ,0)) *	Matrix4::Rotation (-yaw , Vector3 (0 ,1 ,0)) * 	Matrix4::Translation (-position);

	//return Matrix4::Translation (-position) * Matrix4::Rotation(-pitch , Vector3 (1 ,0 ,0)) *	Matrix4::Rotation (-yaw , Vector3 (0 ,1 ,0)); // Seems to be same. -- Maybe doesnt go too much on the left side.

	//return Matrix4::Rotation (-yaw , Vector3 (0 ,1 ,0)) * Matrix4::Translation (-position) * Matrix4::Rotation(-pitch , Vector3 (1 ,0 ,0)); // Doesnt go too much on the right side. (Or Vice versa )

};

Vector3 Camera::GetCamDir() {

	return Matrix4::Rotation(yaw , Vector3 (0.0f ,1.0f ,0.0f)) * Matrix4::Rotation(pitch , Vector3 (1.0f ,0.0f ,0.0f)) * Vector3(0, 0, -1);

}
