// Joseph Gunderson & Alexandra Klimenko
// Homework 5
// Completed 10.Mar.2016


#include <cmath>
#include <cstdlib>
#include <ctime>

#include "Game.h"
#include "Cat.h"

int catDirection = 0;


Game::Game() 
    : width(DEFAULT_WIDTH), height(DEFAULT_HEIGHT), 
      start(0), last(0), current(0), 
      good(true), running(false), 
      particles(std::vector<Particle>()),
      myCat()
{
    
    
    // Seed the random number generator
    srand(time(0));
    
    // initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        good = false;
        return;
    }
    
    // initialize SDL window
    window = SDL_CreateWindow("Gravity", SDL_WINDOWPOS_UNDEFINED,
            			SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        good = false;
        return;
    }
    
    // initialize SDL renderer
    renderer = SDL_CreateRenderer(window, -1, 
            SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        good = false;
        return;
    }
    
    // initialize particle texture
    SDL_Surface* bmp = SDL_LoadBMP("particle.bmp");
    if (bmp == NULL)
    {
        good = false;
        return;
    }
    
    //Load the cat image
    cat = SDL_LoadBMP( "catR.bmp" );
    upCat = SDL_LoadBMP( "catU.bmp" );
    downCat = SDL_LoadBMP( "catD.bmp" );
    leftCat = SDL_LoadBMP( "catL.bmp" );

    //If there was a problem in loading the cat
    if( cat == NULL || upCat == NULL || downCat == NULL || leftCat == NULL)
    {
        good = false;
        return;
    }
    
    /*
    //Load the music
    music = Mix_LoadMUS( "soda.wav" );

    //If there was a problem loading the music
    if( music == NULL )
    {
    	std::cout << "NO MUSIC" << std::endl;
        good = false;
        return;
    }
    
    //Initialize SDL_mixer
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    //if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
    	std::cout << "Unable to Open Audio" << std::endl;
        good = false;
        return;
    } 
    */
    
    
    particleTexture = SDL_CreateTextureFromSurface(renderer, bmp);
    SDL_FreeSurface(bmp);
    if (particleTexture == NULL)
    {
        good = false;
        return;
    }
    
    
    catTexture = SDL_CreateTextureFromSurface(renderer, cat);
    SDL_FreeSurface(cat);
    if (particleTexture == NULL)
    {
        good = false;
        return;
    }
    
    upcatTexture = SDL_CreateTextureFromSurface(renderer, upCat);
    SDL_FreeSurface(upCat);
    if (particleTexture == NULL)
    {
        good = false;
        return;
    }
    downcatTexture = SDL_CreateTextureFromSurface(renderer, downCat);
    SDL_FreeSurface(downCat);
    if (particleTexture == NULL)
    {
        good = false;
        return;
    }
    leftcatTexture = SDL_CreateTextureFromSurface(renderer, leftCat);
    SDL_FreeSurface(leftCat);
    if (particleTexture == NULL)
    {
        good = false;
        return;
    }
    
    
    
    // initialize our particles
    for (int i = 0; i < PARTICLE_COUNT; ++i)
    {
    	particles.push_back(randomParticle());
    }

}

Game::~Game()
{
    if (!good)
    {
        std::cout << "SDL Error: " << SDL_GetError() << std::endl;
    }
    if (particleTexture != NULL)
    {
        SDL_DestroyTexture(particleTexture);
    }
    
    
    if (catTexture != NULL)
    {
        SDL_DestroyTexture(catTexture);
    }
    if (upcatTexture != NULL)
    {
        SDL_DestroyTexture(catTexture);
    }
    if (downcatTexture != NULL)
    {
        SDL_DestroyTexture(catTexture);
    }
    if (leftcatTexture != NULL)
    {
        SDL_DestroyTexture(catTexture);
    }
    
   
    if (renderer != NULL)
    {
        SDL_DestroyRenderer(renderer);
    }
    if (window != NULL)
    {
        SDL_DestroyWindow(window);
    }

    //Free the music
    //Mix_FreeMusic( music );
    //music = NULL;
    
    
    SDL_Quit();
}

int Game::operator()()
{
    if (!good)
    {
        return -1;
    }
    running = true;
    SDL_Event event;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    start = SDL_GetTicks();
    last = start;
    

    while (running) // every iteration is 1 frame
    {
        current = SDL_GetTicks();
        
        while (SDL_PollEvent(&event))
        {
            handleEvent(event);
            
        }
        
        /*
        // If there is no music playing
        if( Mix_PlayingMusic() == 0 )
        {
		//Play the music    
        	Mix_PlayMusic( music, -1 );
        }
        */
        
        update((current - last) / 1000.0);
        
        render();
        
        last = current;
    }

    return 0;
}

// dt is time since last frame in seconds
void Game::update(double dt)
{
    //std::cout << dt << " sec since last frame.\n";

    ///////////// Replace with your game logic! ///////////////////
	
	
	//Move the cat left or right
	double catX = myCat.getPos().getX() + myCat.getVelocity().getX();
	
	//Move the cat up or down
	double catY = myCat.getPos().getY() + myCat.getVelocity().getY();    
	
	//If the cat tries to scurry off screen
	if( ( myCat.getPos().getX() - CAT_WIDTH  < 0 )  )
	{
		myCat.setPos( CAT_WIDTH, myCat.getPos().getY()  );
	}
	else if ( myCat.getPos().getX() > DEFAULT_WIDTH )
	{
	    	myCat.setPos( DEFAULT_WIDTH, myCat.getPos().getY()  );
	}
	else if( ( myCat.getPos().getY() - CAT_HEIGHT < 0 ) )
	{
		myCat.setPos( myCat.getPos().getX(), CAT_HEIGHT );
	}
	else if ( myCat.getPos().getY() > DEFAULT_HEIGHT ) 
	{
	    	myCat.setPos( myCat.getPos().getX(), DEFAULT_HEIGHT);
	}
	else
	{
		// update position of cat //
		myCat.setPos( catX, myCat.getPos().getY() );
		myCat.setPos( myCat.getPos().getX(), catY );
	    
	}
	
	

	// compare each particle to every other particle
	// 1) update collision Table
	// 2) calculate each particles gravity
	// 3) seperate particles from overlapping
	for(int i = 0; i<particles.size(); ++i)
	{
		for(int j = 0; j<particles.size(); ++j)
		{
			// passing by reference
			Particle& p1 = particles[i];
			Particle& p2 = particles[j];
			
				
			double theta = angle(p1.getPos(),p2.getPos());
			// do not comparing particle to itself && no collision detected
			if( (p1!=p2) && !(collision(p1,p2)) && p1.isAlive() && p2.isAlive() )
			{
				// update collision table
				collisionTable[i][j] = false;
				
				// calculate acceleration due to gravitational pull
				double d = distance(p1.getPos(),p2.getPos());
				double a = (G * p2.getMass()) / (d*d) ;
				
				// add velocity to current velocity
				p1.setVelocity( p1.getVelocity().getX() + (a*cos(theta)*dt), p1.getVelocity().getY() + (a*sin(theta)*dt) );
			}
			else if ( (p1!=p2) && collision(p1,p2) )
			{
				// update collision table
				collisionTable[i][j] = true;
				
		
				// seperate by overlap
				double shiftDistance = ( p2.getRadius() + p1.getRadius() - distance(p1.getPos(),p2.getPos()) )/2;
				double shiftx1 = shiftDistance * cos(theta + PI);
				double shifty1= shiftDistance * sin(theta + PI);
				double shiftx2 = shiftDistance * cos(theta);
				double shifty2 = shiftDistance * sin(theta);
				
				double x1 = p1.getPos().getX() + shiftx1;
				double y1 = p1.getPos().getY() + shifty1;
				double x2 = p2.getPos().getX() + shiftx2;
				double y2 = p2.getPos().getY() + shifty2;
				
				p1.setPos(x1, y1);
				p2.setPos(x2, y2);
				
			}
		}
	}
	
	
	
	// compare each particle to every other particle
	// Calculate & Apply elastic collision
	for(int i = 0; i<particles.size(); ++i)
	{
		for(int j = 0; j<particles.size(); ++j)
		{
			// passing by reference
			Particle& p1 = particles[i];
			Particle& p2 = particles[j];
			
			// remove particle from vector
			
			if ( collisionCat( myCat, p1 ) )
			{
				p1.kill();
			}
			if ( collisionCat( myCat, p2 ) )
			{
				p2.kill();
			}
			
			
			// and alive
			if( collisionTable[i][j] && p1.isAlive() && p2.isAlive() )
			{
				double phi = angle(p1.getPos(),p2.getPos());
				double theta1 = atan2(p1.getVelocity().getY(), p1.getVelocity().getX());
				double theta2 = atan2(p2.getVelocity().getY(), p2.getVelocity().getX());
				double v1 = sqrt( (p1.getVelocity().getY() * p1.getVelocity().getY()) + (p1.getVelocity().getX()*p1.getVelocity().getX()) );
				double v2 = sqrt( (p2.getVelocity().getY() * p2.getVelocity().getY()) + (p2.getVelocity().getX()*p2.getVelocity().getX()) );
				
				double massDiff1 = p1.getMass() - p2.getMass();
				double massSum = p1.getMass() + p2.getMass();
				double angleDiff1 = theta1 - phi;
				double angleDiff2 = theta2 - phi;				
				double numerator1 = (v1*cos(angleDiff1)*massDiff1) + (2*p2.getMass()*v2*cos(angleDiff2));
				double velocityX1 = ((numerator1*cos(phi))/massSum) + (v1*sin(angleDiff1)*cos(phi + (PI/2)));
				double velocityY1 = ((numerator1*sin(phi))/massSum) + (v1*sin(angleDiff1)*sin(phi + (PI/2)));
				
				p1.setVelocity(velocityX1, velocityY1);
				
				phi += PI;

				double massDiff2 = p2.getMass() - p1.getMass();
				double numerator2 = (v2*cos(angleDiff2)*massDiff2) + (2*p1.getMass()*v1*cos(angleDiff1));
				double velocityX2 = ((numerator2*cos(phi))/massSum) + (v2*sin(angleDiff2)*cos(phi + (PI/2)));
				double velocityY2 = ((numerator2*sin(phi))/massSum) + (v2*sin(angleDiff2)*sin(phi + (PI/2)));
				
				p2.setVelocity(velocityX2, velocityY2);
				
								
				// set to false because collision calculation has already been done
				// so we want to skip when nested for loop reaches collision[j][i]
				collisionTable[j][i] = false;
			}
		}
	}
	


    
    // update position of each particle 
    for (Particle& p : particles)
    {
    	// if particle stuck in screen
    	double r = p.getRadius();
    	double x = p.getPos().getX();
    	double y = p.getPos().getY();
    	
       	if( x-r < -1 )
       	{
       		p.setPos( (x+r), y ); 
       	}
       	else if ( x+r > DEFAULT_WIDTH+1 )
       	{
       		p.setPos( (x-r), y ); 
       	}
       	if( y-r < -1 )
       	{
       		p.setPos( x, (y+r) ); 
       	}
       	else if ( y+r > DEFAULT_HEIGHT+1 )
       	{
       		p.setPos( x, (y-r) ); 
       	}
    	
    	
    	// if particle collides with screen, reverse particle's velocity
    	if( x-r <= 0 || x+r >= DEFAULT_WIDTH )
        {
        	p.setVelocity( -p.getVelocity().getX(), p.getVelocity().getY()  );
        	
	}
	if( y-r <= 0 || y+r >= DEFAULT_HEIGHT )
        {
        	p.setVelocity( p.getVelocity().getX(), -p.getVelocity().getY() );
	}

	
	
	
	// then update position based on its own velocity
	p.shiftPos( p.getVelocity(), dt );

    }

}


void Game::render()
{
    SDL_RenderClear(renderer);
    
    // rendering here would place objects beneath the particles
    
    for (const Particle& p : particles)
    {
    	if ( p.isAlive() )
    	{
        	drawParticle(p);
        }
    }
    
    // rendering here would place objects on top of the particles

    //Show the cat on the screen
    switch (catDirection)
    {
    	case 0: drawCat(myCat); break;
    	case 1: drawCatup(myCat); break;
    	case 2: drawCatdown(myCat); break;
    	case 3: drawCatleft(myCat); break;
    	default: break;
    }

    SDL_RenderPresent(renderer);
}

void Game::handleEvent(const SDL_Event& event)
{
    double catVelocity = 4;
	
    switch (event.type)
    {
    // Add your own event handling here if desired
    
    
    
    //Handle events for the cat
    //If a key was pressed
        case SDL_KEYDOWN:
	
            //Adjust the velocity && direction of Cat
            switch( event.key.keysym.sym )
            {
            	
                case SDLK_UP: 
                {
                	myCat.setVelocity( myCat.getVelocity().getX(), -catVelocity ); 
                	catDirection = 1; break;
                }
                case SDLK_DOWN: 
                {
                	myCat.setVelocity( myCat.getVelocity().getX(), catVelocity ); 
                	catDirection = 2; break;
                }
                case SDLK_LEFT: 
                {
                	myCat.setVelocity( -catVelocity, myCat.getVelocity().getY() ); 
                	catDirection = 3; break;
                }
                case SDLK_RIGHT: 
                {
                	myCat.setVelocity( catVelocity, myCat.getVelocity().getY() ); 
                	catDirection = 0; break;
                }
                default: break;
            }
            
            break;
        
        //If a key was released
        case SDL_KEYUP:

            // Adjust the velocity
            // when key is relesed, cat stops moving 
            switch( event.key.keysym.sym )
            {
                case SDLK_UP:
                	myCat.setVelocity( 0, 0 ); break;
                case SDLK_DOWN: 
                	myCat.setVelocity( 0, 0 ); break;
                case SDLK_LEFT: 
                	myCat.setVelocity( 0, 0 ); break;
                case SDLK_RIGHT: 
                	myCat.setVelocity( 0, 0 ); break;
                default: break;
            }
            
        break;

    
    case SDL_QUIT:
        running = false;
        break;
    default:
        break;
    }
}

void Game::drawParticle(const Particle& p)
{
    SDL_Rect dst;
    double shift = p.getRadius();
    dst.x = (int) (p.getPos().getX() - shift);
    dst.y = (int) (p.getPos().getY() - shift);
    dst.w = shift * 2;
    dst.h = shift * 2;
    SDL_RenderCopy(renderer, particleTexture, NULL, &dst);
}


void Game::drawCat(const Cat& c)
{
    SDL_Rect dst;
    dst.x = (int) (myCat.getPos().getX() - CAT_WIDTH);
    dst.y = (int) (myCat.getPos().getY() - CAT_HEIGHT);
    dst.w = CAT_WIDTH;
    dst.h = CAT_HEIGHT;
    SDL_RenderCopy(renderer, catTexture, NULL, &dst);

}

void Game::drawCatup(const Cat& c)
{
    SDL_Rect dst;
    dst.x = (int) (myCat.getPos().getX() - CAT_WIDTH);
    dst.y = (int) (myCat.getPos().getY() - CAT_HEIGHT);
    dst.w = CAT_WIDTH;
    dst.h = CAT_HEIGHT;
    SDL_RenderCopy(renderer, upcatTexture, NULL, &dst);

}

void Game::drawCatdown(const Cat& c)
{
    SDL_Rect dst;
    dst.x = (int) (myCat.getPos().getX() - CAT_WIDTH);
    dst.y = (int) (myCat.getPos().getY() - CAT_HEIGHT);
    dst.w = CAT_WIDTH;
    dst.h = CAT_HEIGHT;
    SDL_RenderCopy(renderer, downcatTexture, NULL, &dst);

}

void Game::drawCatleft(const Cat& c)
{
    SDL_Rect dst;
    dst.x = (int) (myCat.getPos().getX() - CAT_WIDTH);
    dst.y = (int) (myCat.getPos().getY() - CAT_HEIGHT);
    dst.w = CAT_WIDTH;
    dst.h = CAT_HEIGHT;
    SDL_RenderCopy(renderer, leftcatTexture, NULL, &dst);

}



Particle Game::randomParticle() const
{
    Point pos(rand() % width, rand() % height);
    
    // using random percentage of MAX_MASS
    double mass = ((double) rand() / RAND_MAX) * MAX_MASS + 1.0;
    
    return Particle(pos, mass);
}




// return distance between two points
double Game::distance(Point a, Point b) const
{
	double a2 = b.getX() - a.getX();
	double b2 = b.getY() - a.getY();
	return sqrt( (a2*a2) + (b2*b2) );
}

// return angle between two points
double Game::angle(Point a, Point b) const
{
	return atan2( (b.getY() - a.getY()), (b.getX() - a.getX()) );
}

// return true if collision occurs
bool Game::collision(const Particle& p1, const Particle& p2) const
{
	return ( distance(p1.getPos(),p2.getPos()) <= (p1.getRadius() + p2.getRadius()) );
}


// return true if collision occurs
bool Game::collisionCat(const Cat& c, const Particle& p) const
{
	return ( distance(c.getPos(),p.getPos()) <= ( (CAT_WIDTH) + p.getRadius()) );
}












