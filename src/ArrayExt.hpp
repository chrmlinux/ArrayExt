//====================================================
//
// program name   : ArrayExt.h
// date/author    : 2022/04/06  @chrmlinux03
// update/author  : 2022/04/06  @chrmlinux03
// version        : 0.0.1
// License        : MIT
//
//====================================================
//====================
//   1.0,   2.0,   3.0,
//   4.0,   5.0,   6.0,
//   7.0,   8.0,   9.0,
//
//====================
//   1.0,   1.5,   2.0,   2.5,   3.0,
//   2.5,   3.0,   3.5,   4.0,   4.5,
//   4.0,   4.5,   5.0,   5.5,   6.0,
//   5.5,   6.0,   6.5,   7.0,   7.5,
//   7.0,   7.5,   8.0,   8.5,   9.0,
//
// Expand the array and set the average 
// value of front, back, left and right
//

#ifndef _ARRAYEXT_HPP_
#define _ARRAYEXT_HPP_

//==============================
// ArreyExt define
//------------------------------
//==============================
class ArrayExt {
  public:
    uint16_t begin(uint16_t, uint16_t);
    uint16_t end(void);
    float *conv(float *);
    uint16_t width(void);
    uint16_t height(void);
    uint16_t dump(float *, uint16_t, uint16_t);

  private:
    uint32_t _height;
    uint32_t _width;
    uint32_t _size;
    float *_dst;

};

//==============================
// begin
//------------------------------
// From the height width of the input array
// Get the new array and height width to be output
//==============================
uint16_t ArrayExt::begin(uint16_t width, uint16_t height)
{
  uint16_t rtn = 0;

  _width = (width * 2) - 1;
  _height = (height * 2) - 1;
  _size = (_height * _width);
  _dst = new float[_size];

  return rtn;
}

//==============================
// end
//------------------------------
// Free the array
//==============================
uint16_t ArrayExt::end(void)
{
  uint16_t rtn = 0;
  free(_dst);
  return rtn;
}

//==============================
// dump
//------------------------------
// Display an array
//==============================
uint16_t ArrayExt::dump(float *dt, uint16_t height, uint16_t width)
{
  uint16_t rtn = 0;

  Serial.println("====================");
  for (uint16_t h = 0; h < height; h++) {
    for (uint16_t w = 0; w < width; w++) {
      uint16_t pos = h * width + w;
      Serial.printf("%6.1f,", dt[pos]);
    }
    Serial.println();
  }
  Serial.println();

  return rtn;
}

//==============================
// conv
//------------------------------
// Expand the array and set the average 
// value of front, back, left and right
//==============================
float *ArrayExt::conv(float *src)
{
  //src -> _dst
  //
  // +--+--+    +--+--+--+
  // |10|20|    |10|  |20|
  // +--+--+ => +--+--+--+
  // |30|40|    |  |  |  |
  // +--+--+    +--+--+--+
  //            |30|  |40|
  //            +--+--+--+
  //
  uint16_t srcPos = 0;
  for (uint16_t h = 0; h < _height; h += 2) {
    for (uint16_t w = 0; w < _width; w += 2) {
      uint16_t dstPos = (h * _width) + w;
      _dst[dstPos] = src[srcPos];
      srcPos ++;
    }
  }

  //_dst -> _dst (width)
  //
  // +--+--+--+
  // |10|15|20|
  // +--+--+--+
  // |  |  |  |
  // +--+--+--+
  // |30|35|40|
  // +--+--+--+
  //

  for (uint16_t h = 0; h < _height; h += 2) {
    for (uint16_t w = 1; w < _width - 1; w += 2) {
      uint16_t dstPos = (h * _width) + w;
      float d = 0.0;
      d = (_dst[dstPos - 1] + _dst[dstPos + 1]);
      if (d) _dst[dstPos] = d / 2;
    }
  }


  //_dst -> _dst (hight)
  //
  // +--+--+--+
  // |10|15|20|
  // +--+--+--+
  // |20|25|30|
  // +--+--+--+
  // |30|35|40|
  // +--+--+--+
  //
  for (uint16_t w = 0; w < _width; w ++) {
    for (uint16_t h = 1; h < _height - 1; h += 2) {
      uint16_t dstPos = (h * _width) + w;
      uint16_t preraw = ((h - 1) * _width) + w;
      uint16_t pstraw = ((h + 1) * _width) + w;
      float d = 0.0;
      d = (_dst[preraw] + _dst[pstraw]);
      if (d) _dst[dstPos] =  d / 2;
    }
  }

  return _dst;
}

//==============================
// width
//------------------------------
// Get the width of the extended array
//==============================
uint16_t ArrayExt::width(void)
{
  return _width;
}


//==============================
// height
//------------------------------
// Get the height of the extended array
//==============================
uint16_t ArrayExt::height(void)
{
  return _height;
}

#endif
