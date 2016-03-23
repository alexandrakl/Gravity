// Joseph Gunderson & Alexandra Klimenko
// Homework 5
// Completed 10.Mar.2016


#ifndef GAME_H
#define	GAME_H

#include <SDL2/SDL.h>
//#include "SDL/SDL_mixer.h"	// -lSDL_mixer
#include <string>
#include <iostream>
#include <vector>

#include "Constants.h"
#include "Particle.h"
#include "Cat.h"

class Game : public Cat
{
private:
    // screen info
    int width;
    int height;
    
    // for timing frames
    unsigned int start;
    unsigned int last;
    unsigned int current;
    
    // for game status
    bool good;
    bool running;
    
    // SDL managed
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* particleTexture;
    SDL_Texture* catTexture;
    SDL_Texture* upcatTexture;
    SDL_Texture* downcatTexture;
    SDL_Texture* leftcatTexture;
    
    SDL_Surface* cat;
    SDL_Surface* upCat;
    SDL_Surface* downCat;
    SDL_Surface* leftCat;
    
    //The music that will be played
    //Mix_Music *music = NULL;
    
    // game data
    std::vector<Particle> particles;
    Cat myCat;
    
    // 2D particle collision table
    bool collisionTable[PARTICLE_COUNT][PARTICLE_COUNT]{{false}};
    
    
    // Handle game logic updates here
    void update(double dt);
    
    // Render the game contents to the screen here
    void render();
    
    // Handle any user input events here
    void handleEvent(const SDL_Event& event);

    // helper function for drawing particles to screen    
    void drawParticle(const Particle& p);
    
    void drawCat(const Cat& c);
    void drawCatup(const Cat& c);
    void drawCatdown(const Cat& c);
    void drawCatleft(const Cat& c);
    
    void apply_surface( int x, int y, SDL_Surface* source);
    
    // helper function for generating random particles
    Particle randomParticle() const;
    
    
    double angle(Point a, Point b) const;
    double distance(Point a, Point b) const;
    bool collision(const Particle& p1, const Particle& p2) const;
    bool collisionCat(const Cat& c, const Particle& p) const;

    
public:
    // This will act as our initialize function
    Game();
    
    // We don't want to be able to copy a game
    Game(const Game& other) = delete;
    Game& operator=(const Game& right) = delete;
    
    // This will act as our cleanup function
    ~Game();
    
    // Will handle actually running the game (the gameplay loop)
    int operator()();
    
    
};

#endif
