//
//  Pacman.hpp
//  Pac-Sphere
//
//  Created by Gabriel Brown on 10/22/18.
//

#ifndef Pacman_hpp
#define Pacman_hpp

#include <stdio.h>
#include <BasicGraphics.h>

class Pacman {
public:
    Pacman(float mazeRadius);
    //virtual ~Pacman();
    
    // TODO: swap this out with sphere mesh similar to earth once hw3 is done
    std::unique_ptr<basicgraphics::Sphere> _mesh;
    
private:
    
    static constexpr float PAC_RADIUS = 1.0f;
    
};

#endif /* Pacman_hpp */
