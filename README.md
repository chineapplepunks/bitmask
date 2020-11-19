# bitmask
Pixel perfect collison library using bitmasks, written in C++.

This code is based around around Danny van Bruggen's Java port of Ulf Ekstrom's C Bitmask library.

Original C bitmask library can be found at:
https://github.com/matozoid/rudl 

Danny van Bruggen's Java port can be found at:
https://github.com/laamella-gad/bitmask

## To use:

1. Create some Bitmask objects:
```
    Bitmask mask1(4,8);
    Bitmask mask2(4,8);
    Bitmask mask3(4,8);
```
2. Set some pixels in the mask (these represent the pixel on/off state of the original image / bitmap / surface etc) by calling
the `set_bit()` function:
```
   mask1.set_bit(2,2); // Indicates there is a pixel at the location 2,2 in the original image.
   mask2.set_bit(2,2);
   mask3.set_bit(1,1);
```
3. Compare two masks to see if there are any overlapping pixels by calling the `overlaps()` function:
```
    mask1.overlaps(mask2,0,0); //returns true.
    mask1.overlaps(mask3,0,0); //returns false.
```
