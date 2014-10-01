/**
 * \class 	Display
 * \file 	Display.h
 * \author 	Daniel Holmes & Jonathan Gerrand
 * \date 	29 September 2014
 * \brief 	Class that handles all display functionality
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_
#include "Structures.h"
#include "SpriteDimensions.h"
#include "SFML/Graphics.hpp"
#include <string.h>
#include <memory>

class Display
{
public:
    /// Constructor with default window dimensions
    Display(int window_width = 800, int window_height = 600);

    bool isOpen();
    void pollEvents();
    void clear();
    void drawBackground();
    void drawEntity(const entity_type& entity, const sprite_draw_info& draw_info);
    void drawText(const draw_strings& strings);
    void display();

private:
    void loadTextures();
    void addSprites();
	void setupText(sf::Text& text);

    /// Display window dimensions
    int _window_width;
    int _window_height;
    sf::RenderWindow _window;

    SpriteDimensions _game_sprite_dimensions;
    textures _game_textures;

    /// Texture file names
	const std::string _tank1_texture_file = "tank1_red.png";
	const std::string _tank2_texture_file = "tank2_green.png";
	const std::string _missile_texture_file = "missile.png";
	const std::string _mine_texture_file = "mine.png";
 	const std::string _barrier_texture_file = "barrier.png";
 	const std::string _turret_texture_file = "turret.png";
 	const std::string _map_texture_file = "map.png";
 	const std::string _missile_turret_texture_file = "missile_turret.png";
 	const std::string _font_file = "futura_light.ttf";

    /// Map container for the sprites that will be drawn
	std::map<entity_type, std::shared_ptr<sf::Sprite>>  _sprites;

    sf::Sprite _map_sprite;
    sf::Texture _map_texture;
    sf::Text _game_time_text;
    sf::Text _p1_score_text;
    sf::Text _p2_score_text;
    sf::Font _font_style;
    const int _font_size = 20;

    const int _text_y_allignment = 0;
    const int _game_time_pos = 550;
    const int _p1_score_pos = 950;
    const int _p2_score_pos = 100;
};

#endif // DISPLAY_H_
