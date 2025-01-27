



#include "../../Engine/engine.h"
#include <iostream>
#include <cstdlib>
void start();
void update();

int main()
{
  // RenderEngine::setAwake(awake);
  RenderEngine::setStart(start);
  RenderEngine::setUpdate(update);
  // RenderEngine::setFixedUpdate(fixedUpdate);
  RenderEngine::Enabled(true);
}

GameObject dvd;

GameObject vWalls[2];
GameObject hWalls[2];

void start()
{
  dvd.rigidbody.velocity       = Vector3(0.01, 0.001);

  vWalls[0].transform.position = Vector3(-1,  0);
  vWalls[0].transform.scale    = Vector3(0.01, 2);
  
  vWalls[1].transform.position = Vector3( 1,  0);
  vWalls[1].transform.scale    = Vector3(0.01, 2);

  hWalls[0].transform.position = Vector3( 0, -1);
  hWalls[0].transform.scale    = Vector3(2, 0.01);
  
  hWalls[1].transform.position = Vector3( 0,  1);
  hWalls[1].transform.scale    = Vector3(2, 0.01);
}

void update()
{
  bool collided = false;
  RenderEngine::background(0);

  dvd.transform.position += dvd.rigidbody.velocity;
  dvd.show();

  for (GameObject& wall : vWalls)
  {
    wall.show();
    if(dvd.collides(wall))
    {
      dvd.rigidbody.velocity.x = -dvd.rigidbody.velocity.x;
      collided = true;
    }
  }

  for (GameObject& wall : hWalls)
  {
    if(dvd.collides(wall))
    {
      dvd.rigidbody.velocity.y = -dvd.rigidbody.velocity.y;
      collided = true;
    }
  }

  if(collided)
  {
   int result = system("python Modules/arduino/turn_on_led.py");

    if (result == 0) {
        std::cout << "Successfully turned on the LED." << std::endl;
    } else {
        std::cout << "Failed to turn on the LED." << std::endl;
    }
  }

  if(GameEngine::Input::getKeyDown(GameEngine::KEY_R))
  {
    dvd.transform.position = Vector3::zero;
  }


}









