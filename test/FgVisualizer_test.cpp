//
// Created by dconsoli on 10-10-24.
//

#include "FgVisualizer.h"

int main(int argc, char** argv)
{
    FgVisualizer fgVisualizer;
    fgVisualizer.generate_icosahedron();
    fgVisualizer.interact(2.);
    return 0;
}

