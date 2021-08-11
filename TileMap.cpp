#include "TileMap.h"

    void TileMap::resetMap()
    {
        xVel = 0;
        yVel = 0;
        xSpeed = 0.1;
        ySpeed = 0.1;
        xDir = 0;
        yDir = 0;
        maxSpeed = 3.5;
    }

    bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, 
    unsigned int height, Entity ship, std::vector<Entity*> collidableEntities, bool movementLocked)
    {
        
        memcpy(tileArray, tiles, sizeof(tileArray));
        // load the tileset texture
        if (!m_tileset.loadFromFile(tileset))
            return false;
            
        if (movementLocked)
            return true;

        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);

        // populate the vertex array, with one quad per tile
        for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < height; ++j)
            {
                // get the current tile number
                int tileNumber = tiles[i + j * width];

                // find its position in the tileset texture
                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                // get a pointer to the current tile's quad
                sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

                // define its 4 corners 
                               
	        curSpeed = sqrt((xDir*xDir) + (yDir*yDir));
	        
	        /*for(auto i:collidableEntities)
	        {
                    if (ship.isCollide(&ship, i))
                    {
                        collision =  true;
                        break;
                    } else if (i == collidableEntities.back()) {
                        collision = false;
                        firstCollide = false;
                    }
                }*/
                
                /*if (thrust and !collision)
	        {
	            xDir += cos((ship.getAngle() + 90) * PI/180) * 0.001;
                    yDir += sin((ship.getAngle() + 90) * PI/180) * 0.001;
	            if (curSpeed > maxSpeed){
	                xDir *= maxSpeed/curSpeed;
	                yDir *= maxSpeed/curSpeed;}
		} else if (backThrust and !collision) {
		    if (curSpeed > 0){
	                xDir *= 0.999;
	                yDir *= 0.999;}
		
		} else if (collision and firstCollide == false) {
                   xDir = -xDir * .5;
                   yDir = -yDir * .5;
                   firstCollide = true;

		}*/

                xVel = xVel + xDir;
                yVel = yVel + yDir;                
                
                xPos = (i * tileSize.x) + (xVel * .01);
                yPos = (j * tileSize.y) + (yVel * .01);
                float xSize = ((i + 1) * tileSize.x) + (xVel * .01);
                float ySize = ((j + 1) * tileSize.y) + (yVel * .01);
                quad[0].position = sf::Vector2f(xPos, yPos);
                quad[1].position = sf::Vector2f(xSize, yPos);
                quad[2].position = sf::Vector2f(xSize, ySize);
                quad[3].position = sf::Vector2f(xPos, ySize);

                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            }

        return true;
    }

    void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

