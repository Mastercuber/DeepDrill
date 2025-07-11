// -----------------------------------------------------------------------------
// This file is part of DeepDrill
//
// A Mandelbrot generator based on perturbation and series approximation
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#include "Palette.h"
#include "Options.h"

#include <tgmath.h>

namespace dd {

const sf::Image &
Palette::getImage()
{
    if (const auto &path = Options::palette.image; path == "") {

        constexpr isize width = 8192;

        // Compute default palette programmatically
        palette.resize(sf::Vector2u(width, 1));

        /* Create default palette
         *
         * The formula is an adaption from https://www.shadertoy.com/view/tllSWj
         * It was used in an GLSL shader in the following form:
         *
         *     vec4 mapColor(float mcol) {
         *        return vec4(0.5 + 0.5*cos(2.7+mcol*30.0 + vec3(0.0,.6,1.0)),1.0);
         *     }
         */
        for (isize i = 0; i < width; i++) {

            const double v = static_cast<double>(i) / width * 2 * 3.14159;
            const auto rr = static_cast<isize>(255.0 * (0.5 + 0.5 * cos(v + 0.0 - 2.7)));
            const auto gg = static_cast<isize>(255.0 * (0.5 + 0.5 * cos(v + 0.6 - 2.7)));
            const auto bb = static_cast<isize>(255.0 * (0.5 + 0.5 * cos(v + 1.0 - 2.7)));
            palette.setPixel(sf::Vector2u(static_cast<int>(i), 0), sf::Color(static_cast<u8>(rr), static_cast<u8>(gg), static_cast<u8>(bb)));
        }

    } else {

        if (!palette.loadFromFile(path)) {
            throw Exception("Failed to load palette image");
        }
    }

    return palette;
}

const sf::Image &
Palette::getTextureImage()
{
    const auto &path = Options::texture.image;

    if (path == "") {

        // Compute a transparent image
        texture.resize(sf::Vector2u(1, 1));
        texture.setPixel(sf::Vector2u(0, 0), sf::Color(0, 0, 0, 0));

    } else {

        if (!texture.loadFromFile(path)) {
            throw Exception("Failed to load texture image");
        }
    }

    return texture;
}

}
