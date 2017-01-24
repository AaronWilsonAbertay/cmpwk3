#include "sprite_app.h"
#include <system/platform.h>
#include <graphics/sprite_renderer.h>
#include <graphics/font.h>
#include <maths/math_utils.h>
#include <input/sony_controller_input_manager.h>
#include <system/debug_log.h>

SpriteApp::SpriteApp(gef::Platform& platform) :
	Application(platform),
	sprite_renderer_(NULL),
	input_manager_(NULL),
	font_(NULL)
{
}

void SpriteApp::Init()
{
	// create a sprite renderer to draw your sprites
	sprite_renderer_ = gef::SpriteRenderer::Create(platform_);

	InitFont();

	my_sprite_.set_position(platform_.width()*0.5f, platform_.height()*0.5f, 0.0f);
	my_sprite_.set_width(32.0f);
	my_sprite_.set_height(32.0f);

	//create the input manager
	input_manager_ = gef::InputManager::Create(platform_);
}

void SpriteApp::CleanUp()
{
	CleanUpFont();
	
	// destroy input manager once you've finished using it
	delete input_manager_;
	input_manager_ = NULL;

	// destroy sprite renderer once you've finished using it
	delete sprite_renderer_;
	sprite_renderer_ = NULL;
}

bool SpriteApp::Update(float frame_time)
{
	// frame rate = 1 second / frame_delta_time
	fps_ = 1.0f / frame_time;
	
	rotation_speed_;

	//get the latest data from the input devices
	if (input_manager_)
	{
		input_manager_->Update();

		//get controller input data for all controllers
		gef::SonyControllerInputManager* controller_input = input_manager_->controller_input();
		if (controller_input)
		{
			//read controller data for controller 0
			const gef::SonyController* controller = controller_input->GetController(0);
			
			if (controller)
			{

				//TEST FOR ALL BUTTONS
				//test for X button (pressed)
				if (controller->buttons_pressed() & gef_SONY_CTRL_CROSS)
				{
					//do something
					gef::DebugOut("X is pressed\n");
				}
				//test for X button (released)
				if (controller->buttons_released() & gef_SONY_CTRL_CROSS)
				{
					//do something
					gef::DebugOut("X is released\n");
				}
				//test for O button (pressed)
				if (controller->buttons_pressed() & gef_SONY_CTRL_CIRCLE)
				{
					//do something
					gef::DebugOut("O is pressed\n");
				}
				//test for O button (released)
				if (controller->buttons_released() & gef_SONY_CTRL_CIRCLE)
				{
					//do something
					gef::DebugOut("O is released\n");
				}
				//test for Triangle button (pressed)
				if (controller->buttons_pressed() & gef_SONY_CTRL_TRIANGLE)
				{
					//do something
					gef::DebugOut("triangle is pressed\n");
					my_sprite_.set_position(platform_.width()*0.5f, platform_.height()*0.5f, 0.0f);
				}
				//test for triangle button (released)
				if (controller->buttons_released() & gef_SONY_CTRL_TRIANGLE)
				{
					//do something
					gef::DebugOut("triangle is released\n");
				}

				//test for Square button (pressed)
				if (controller->buttons_pressed() & gef_SONY_CTRL_SQUARE)
				{
					//do something
					gef::DebugOut("Square is pressed\n");
				}

				//test for L1 button (pressed)
				if (controller->buttons_pressed() & gef_SONY_CTRL_L2)
				{
					//do something
					gef::DebugOut("Left shoulder is pressed\n");
				}
				//test for R1 button (pressed)
				if (controller->buttons_pressed() & gef_SONY_CTRL_R2)
				{
					//do something
					gef::DebugOut("Right shoulder is pressed\n");
				}
				//test for select button (pressed)
				if (controller->buttons_pressed() & gef_SONY_CTRL_SELECT)
				{
					//do something
					gef::DebugOut("Select is pressed\n");
				}
				//test for start button (pressed)
				if (controller->buttons_pressed() & gef_SONY_CTRL_START)
				{
					//do something
					gef::DebugOut("Start is pressed\n");
				}
				

				//EXIT CODE
				//test for start and select both pressed
				if ((controller->buttons_down() & (gef_SONY_CTRL_START | gef_SONY_CTRL_SELECT))==(gef_SONY_CTRL_START | gef_SONY_CTRL_SELECT))
				{
					//exit program
					return 0;
				}



				//AXIS 
				//get the x- axis for left stick
				float left_x_axis = controller->left_stick_x_axis();	

				if (left_x_axis != 0) 
				{
					gef::DebugOut("lx: %f\n", left_x_axis);
				}
				//get the y- axis for left stick
				float left_y_axis = controller->left_stick_y_axis();

				if (left_y_axis != 0)
				{
					gef::DebugOut("ly: %f\n", left_y_axis);
				}
				
				//get the axis for right stick
				float right_x_axis = controller->right_stick_x_axis();
				float right_y_axis = controller->right_stick_y_axis();

				float anglex = 0;
				float angley = 0;

				//anglex += cos(right_x_axis) + sin(right_x_axis);
				//angley += -sin(right_y_axis) + cos(right_y_axis);

				//gef::DebugOut("rx: %f\n", anglex);

				//get angle
				//float angle = atan2(0 - right_y_axis, 0 - right_x_axis);

				//if (angle != 0) {
				//	gef::DebugOut("rx: %f\n", angle);
				//}



				//SPRITE MOVEMENT
				// move the sprite up the y-axis
				if (controller->buttons_down() & gef_SONY_CTRL_UP)
				{
					//move sprite up
					// get a copy of the current position of the sprite
					gef::Vector4 sprite_position = my_sprite_.position();

					// update the x-axis on the COPY of the current position
					sprite_position.set_y(sprite_position.y() - 1);

					// update the sprite with the new position
					my_sprite_.set_position(sprite_position);
				}
				// move the sprite down the y-axis
				if (controller->buttons_down() & gef_SONY_CTRL_DOWN)
				{
					//move sprite up
					// get a copy of the current position of the sprite
					gef::Vector4 sprite_position = my_sprite_.position();

					// update the x-axis on the COPY of the current position
					sprite_position.set_y(sprite_position.y() + 1);

					// update the sprite with the new position
					my_sprite_.set_position(sprite_position);
				}

				// move the sprite left along the X-axis
				if (controller->buttons_down() & gef_SONY_CTRL_LEFT)
				{
					//move sprite up
					// get a copy of the current position of the sprite
					gef::Vector4 sprite_position = my_sprite_.position();

					// update the x-axis on the COPY of the current position
					sprite_position.set_x(sprite_position.x() - 1);

					// update the sprite with the new position
					my_sprite_.set_position(sprite_position);
				}
				// move the sprite right along the X-axis
				if (controller->buttons_down() & gef_SONY_CTRL_RIGHT)
				{
					//move sprite up
					// get a copy of the current position of the sprite
					gef::Vector4 sprite_position = my_sprite_.position();

					// update the x-axis on the COPY of the current position
					sprite_position.set_x(sprite_position.x() + 1);

					// update the sprite with the new position
					my_sprite_.set_position(sprite_position);
				}



			}
		
		}
	}




	// update the sprite with the new position
	my_sprite_.set_rotation(+200*frame_time);


	

	return true;
}

void SpriteApp::Render()
{
	// draw all sprites between the Begin() and End() calls
	sprite_renderer_->Begin();

	// draw my sprite here
	sprite_renderer_->DrawSprite(my_sprite_);

	DrawHUD();
	sprite_renderer_->End();
}


void SpriteApp::InitFont()
{
	// create a Font object and load in the comic_sans font data
	font_ = new gef::Font(platform_);
	font_->Load("comic_sans");
}

void SpriteApp::CleanUpFont()
{
	// destroy the Font object
	delete font_;
	font_ = NULL;
}

void SpriteApp::DrawHUD()
{
	if(font_)
	{
		// display frame rate
		font_->RenderText(
			sprite_renderer_,						// sprite renderer to draw the letters
			gef::Vector4(650.0f, 510.0f, -0.9f),	// position on screen
			1.0f,									// scale
			0xffffffff,								// colour ABGR
			gef::TJ_LEFT,							// justification
			"FPS: %.1f xpos: %.1f",							// string of text to render
			fps_,									// any variables used in formatted text string http://www.cplusplus.com/reference/cstdio/printf/
			my_sprite_.position().x()
			);
	}
}

