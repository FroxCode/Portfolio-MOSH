//Created By Jason Hannon, Dale Sinnott
#include "CheckShaders.h"

void CheckShaders::initalize()
{
	for (int i = 0; i < MAX_FLASHES; i++)
	{ //create multiple shapes for flashing effect
		CircleShape shape;
		shape.setFillColor(sf::Color::Transparent);
		shape.setPosition(sf::Vector2f(0, 0));
		shape.setRadius(0);
		flashes.push_back(shape); //make a new flash thats not showing
		ShaderEffect shade;
		shaderEffects.push_back(shade); //new shader effect for a flash
		bool temp = false;
		up.push_back(temp); //bool for a flash
	}
	shader.loadFromFile("Frag_Shader.txt", sf::Shader::Fragment); //load frag shader
}
void CheckShaders::update()
{
	for (int i = 0; i < MAX_FLASHES; i++)
	{ 
		if (flashes.at(i).getRadius() > 0)
		{ //if the flash is active
			if (up.at(i) && flashes.at(i).getRadius() < endRadius)
			{ //if its ascending its flash
				flashes.at(i).setRadius(flashes.at(i).getRadius() * 2); //double the radius
				flashes.at(i).setOrigin(flashes.at(i).getRadius(), flashes.at(i).getRadius()); //set the new origin of the flash shader
			}
			else
			{
				up.at(i) = false;
				flashes.at(i).setRadius(flashes.at(i).getRadius() / 1.5); //reduce the radius gradually
				flashes.at(i).setOrigin(flashes.at(i).getRadius(), flashes.at(i).getRadius()); //reset origin
				if (flashes.at(i).getRadius() <= 20)
				{ //if it gets small enough,
					flashes.at(i).setRadius(0);
				}
			}
			
		}
	}
	
}
void CheckShaders::render(sf::RenderWindow &window)
{

	for (int i = 0; i < MAX_FLASHES; i++)
	{ //draw each effect
		shaderEffects.at(i).draw(window);
		shader.setParameter("frag_LightOrigin", shaderEffects.at(i).getPosition());
		shader.setParameter("frag_LightColor", shaderEffects.at(i).getColor());
		shader.setParameter("frag_LightAttenuation", shaderEffects.at(i).getIntensity());
		sf::RenderStates states;
		states.shader = &shader;
		states.blendMode = sf::BlendAdd;
		window.draw(flashes.at(i), states);
	}

}
void CheckShaders::flash(Vector2f position)
{
	for (int i = 0; i < MAX_FLASHES; i++)
	{ //start a new flash
		if (flashes.at(i).getRadius() == 0) //get one that isnt flashing yet
		{
			up.at(i) = true;
			flashes.at(i).setRadius(startRadius);
			flashes.at(i).setOrigin(startRadius, startRadius);
			flashes.at(i).setPosition(position);
			shaderEffects.at(i).reload(flashes.at(i), sf::Color(255, 214, 170), 160); //reapply the parameters to the specific shader effect
			break;
		}
	}
	
}

CheckShaders::CheckShaders() {}

CheckShaders::~CheckShaders() {}