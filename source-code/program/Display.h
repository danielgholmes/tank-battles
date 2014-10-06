//! Handles all draw and display functionality.
/*! This class interfaces with SFML. It receives
    all information to draw via the DisplayManager.
    It also contains information such as the
    file names of all sprite textures.
    \file       Display.h
    \author     Daniel Holmes & Jonathan Gerrand
    \version    2.0
    \date       29 September 2014
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
    Display(int window_width = 800, int window_height = 600); /////// *****

    bool isOpen();
    void pollEvents();
    void clear();
    void drawBackground();
    void drawEntity(const entity_type& entity, const sprite_draw_info& draw_info);
    void drawText(const draw_strings& strings);
    void drawEndScreen();
    void display();

private:
    void loadTextures();
    void addSprites();
	void setupText(sf::Text& text);

    /// Display window width
    int _window_width;
    /// Display window height
    int _window_height;
    /// SFML window where all sprites are drawn
    sf::RenderWindow _window;

    /// Holds information about all the sprite dimensions
    SpriteDimensions _game_sprite_dimensions;
    /// Struct of all textures in the game
    textures _game_textures;

    /// Tank 1 texture file name
	const std::string _tank1_texture_file = "tank_blue.png";
    /// Tank 2 texture file name
	const std::string _tank2_texture_file = "tank_red.png";
    /// Tanks missile texture file name
	const std::string _missile_texture_file = "missile.png";
    /// Mine texture file name
	const std::string _mine_texture_file = "mine.png";
    /// Barrier texture file name
 	const std::string _barrier_texture_file = "barrier.png";
    /// Turret texture file name
 	const std::string _turret_texture_file = "turret.png";
    /// Map (background) texture file name
 	const std::string _map_texture_file = "map.png";
    /// Turret missile texture file name
 	const std::string _missile_turret_texture_file = "missile_turret.png";
    /// Font file name
 	const std::string _font_file = "futura_light.ttf";
    /// End screen texture file name
    const std::string _end_texture_file = "end_screen.png";

    /// Map container for the sprites that will be drawn
	std::map<entity_type, std::shared_ptr<sf::Sprite>>  _sprites;

    /// Map (background) SFML sprite
    sf::Sprite _map_sprite;
    /// End game screen sprite
    sf::Sprite _end_map_sprite;

    /// Map (background) SFML texture
    sf::Texture _map_texture;
    /// End game screen texture
    sf::Texture _end_map_texture;
    /// Runtime SFML text
    sf::Text _game_time_text;
    /// Player 1 SFML score text
    sf::Text _p1_score_text;
    /// Player 2 SFML score text
    sf::Text _p2_score_text;
    /// SFML font style
    sf::Font _font_style;
    /// Constant size for all window fonts
    const int _font_size = 20;

    /// Vertical alignment for runtime and player scores
    const int _text_y_allignment = 0;
    /// Horzontal position of game time text
    const int _game_time_pos = 550;
    /// Horizontal position of player 1 score text
    const int _p1_score_pos = 950;
    /// Horizontal position of player 2 score text
    const int _p2_score_pos = 100;
};

#endif // DISPLAY_H_
