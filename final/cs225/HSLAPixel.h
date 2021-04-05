/**
 * @file HSLAPixel.h
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#pragma once

#include <iostream>
#include <sstream>

namespace cs225 {
    class HSLAPixel {
    public:
        /**
         * public attributes
         * h as Hue of the pixel, in degrees [0, 360)
         * s as Saturation of the pixel, [0, 1].
         * l as Luminance of the pixel, [0, 1].
         * a as Alpha of the pixel, [0, 1].
        */
        double h, s, l, a;
        HSLAPixel();
        HSLAPixel(double hue, double saturation, double luminance);
        HSLAPixel(double hue, double saturation, double luminance, double alpha);
    };
}
