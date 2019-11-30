/*      
 *      Santa Racer
 *      goblin.cpp
 *      
 *      Copyright (C) 2010 Julian Valentin.
 *      
 *      This program is free software: you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation, either version 3 of the License, or
 *      (at your option) any later version.
 *      
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *      
 *      You should have received a copy of the GNU General Public License
 *      along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "globals.hpp"
#include "goblin.hpp"
#include "level_object.hpp"
#include "draw.hpp"

Santa::Goblin::Goblin(void *parent) {
    m_parent = parent;
}

Santa::Goblin::~Goblin(void) {
    return;
}

void Santa::Goblin::reinit(int tile_x, int tile_y) {
    LevelObject *object;
    SDL_Surface *surface;
    
    object = (LevelObject *)m_parent;
    surface = Setup::images["goblin"];
    
    m_level_x = (tile_x + 0.5) * Setup::game->level->tile_width -
                (surface->w / frame_count) / 2;
    m_y = (tile_y + 0.5) * Setup::game->level->tile_height -
          surface->h / 2;
    
    object->set_surface(surface);
    object->set_frame_count(frame_count);
    
    m_time = SDL_GetTicks();
    m_frame = 0;
    m_snowball_thrown = false;
    m_snowball_thrown_query = false;
}

void Santa::Goblin::draw(void) {
    LevelObject *object;
    SDL_Surface *surface;
    int frame;
    int width;
    int height;
    
    int level_x;
    int y;
    
    object = (LevelObject *)m_parent;
    surface = object->get_surface();
    width = object->get_width();
    height = object->get_height();
    
    level_x = get_level_x();
    y = get_y();
    frame = get_frame();
    
    Draw::blit(surface, width * frame, 0, width, height,
               Setup::screen, level_x - Setup::game->level->get_offset(), y);
}

void Santa::Goblin::move(void) {
    int frame;
    int i;
    LevelObject *parent;
    LevelObject *object;
    
    frame = get_frame();
    parent = (LevelObject *)m_parent;
    
    //Output::debug("frame %i\n", frame);
    
    if (frame == 13 && !m_snowball_thrown) {
        m_snowball_thrown = true;
        m_snowball_thrown_query = true;
        //Output::debug("new snowball %i\n", SDL_GetTicks());
        
        for (i = 0; i < Level::max_level_object_count; i++) {
            object = Setup::game->level->get_level_object(i);
            if (!object->exists()) {
                object->reinit(parent->get_tile_x(), parent->get_tile_y(), 200);
                return;
            }
        }
        
    } else if (frame != 13) {
        m_snowball_thrown = false;
    }
}

int Santa::Goblin::get_level_x(void) {
    return m_level_x;
}

int Santa::Goblin::get_y(void) {
    return m_y;
}

int Santa::Goblin::get_frame(void) {
    float time_diff;
    int frame;
    
    time_diff = (SDL_GetTicks() - m_time) / 1000.0;
    frame = int(time_diff * frame_speed + m_frame) % frame_count;
    
    return frame;
}

bool Santa::Goblin::query_snowball_thrown(void) {
    if (m_snowball_thrown_query) {
        m_snowball_thrown_query = false;
        return true;
    } else {
        return false;
    }
}
