#include <ArrayExt.hpp>
ArrayExt ae;

void setup()
{
  //------------------------------
  // work
  //------------------------------
  uint16_t height = 3;
  uint16_t width = 3;
  float *src, *dst;
  src = new float[(height * width)];
  dst = NULL;

  //------------------------------
  // Serial.begin
  //------------------------------
  Serial.begin( 115200 ); delay(1000);

  //------------------------------
  // ArrayExt.begin
  //------------------------------
  ae.begin(height, width);
    
  //------------------------------
  // src data set
  //------------------------------
  uint16_t c = 1;
  for (uint16_t h = 0; h < height; h++) {
    for (uint16_t w = 0; w < width; w++) {
      uint16_t srcPos = (h * width) + w;
      src[srcPos] = c;
      c ++;
    }
  }
  //------------------------------
  // src dump
  //------------------------------
  ae.dump(src, height, width);

  //------------------------------
  // conv 8 * 8 => 15 * 15
  //------------------------------
  dst = ae.conv(src);

  //------------------------------
  // dst dump
  //------------------------------
  ae.dump(dst, ae.height(), ae.width());

  //------------------------------
  // free work
  //------------------------------
  ae.end();
  free(src);
}


void loop()
{

}
