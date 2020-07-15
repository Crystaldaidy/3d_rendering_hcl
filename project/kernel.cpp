// HASH:3859414510
#include <ap_int.h>
#include <ap_fixed.h>
#include <ap_int.h>
#include <ap_fixed.h>
#include <ap_axi_sdata.h>
#include <hls_stream.h>
#include <hls_math.h>
#include <stdint.h>
#include "kernel.h"
  void test(hls::stream<bit32 >& triangle_3ds_channel, hls::stream<bit32 >& angle_channel, hls::stream<bit32 >& frame_buffer_update_channel) {
  #pragma HLS INTERFACE axis port=triangle_3ds_channel offset=slave bundle=gmem0
  #pragma HLS INTERFACE axis port=frame_buffer_update_channel offset=slave bundle=gmem2
  #pragma HLS INTERFACE s_axilite port=return bundle=control
    bit32 frame_buffer[256][256];
    bit32 triangle_3ds[3191][9];
    for (bit32 triangle_3ds0 = 0; triangle_3ds0 < 3191; ++triangle_3ds0) {
      for (bit32 triangle_3ds1 = 0; triangle_3ds1 < 9; ++triangle_3ds1) {
        triangle_3ds[triangle_3ds0][triangle_3ds1] = triangle_3ds_channel.read();
      }
    }
    bit32 angle;
    angle = angle_channel.read();
    bit32 z_buffer[256][256];
    for (bit32 x = 0; x < 256; ++x) {
      for (bit32 y = 0; y < 256; ++y) {
        z_buffer[x][y] = 255;
      }
    }
    for (bit32 x1 = 0; x1 < 256; ++x1) {
      for (bit32 y1 = 0; y1 < 256; ++y1) {
        frame_buffer[x1][y1] = 0;
      }
    }
    bit32 main_body;
    for (bit32 m = 0; m < 3191; ++m) {
    #pragma HLS pipeline
      bit32 triangle_3d[9];
      for (bit32 x2 = 0; x2 < 9; ++x2) {
        triangle_3d[x2] = triangle_3ds[m][x2];
      }
      bit32 fragment[500][4];
      for (bit32 x3 = 0; x3 < 500; ++x3) {
        for (bit32 y2 = 0; y2 < 4; ++y2) {
          fragment[x3][y2] = 0;
        }
      }
      bit32 pixels[500][3];
      for (bit32 x4 = 0; x4 < 500; ++x4) {
        for (bit32 y3 = 0; y3 < 3; ++y3) {
          pixels[x4][y3] = 0;
        }
      }
      bit32 triangle_2d[7];
      for (bit32 x5 = 0; x5 < 7; ++x5) {
        triangle_2d[x5] = 0;
      }
      bit32 frag_cntr;
      frag_cntr = 0;
      bit32 size_pixels;
      size_pixels = 0;
      bit32 twod_update;
      for (bit32 x6 = 0; x6 < 7; ++x6) {
        if (x6 == 0) {
          if (angle == 2) {
            triangle_2d[0] = triangle_3d[2];
          } else {
            triangle_2d[0] = triangle_3d[0];
          }
        }
        if (x6 == 1) {
          if (angle == 1) {
            triangle_2d[1] = triangle_3d[2];
          } else {
            triangle_2d[1] = triangle_3d[1];
          }
        }
        if (x6 == 2) {
          if (angle == 2) {
            triangle_2d[2] = triangle_3d[5];
          } else {
            triangle_2d[2] = triangle_3d[3];
          }
        }
        if (x6 == 3) {
          if (angle == 1) {
            triangle_2d[3] = triangle_3d[5];
          } else {
            triangle_2d[3] = triangle_3d[4];
          }
        }
        if (x6 == 4) {
          if (angle == 2) {
            triangle_2d[4] = triangle_3d[8];
          } else {
            triangle_2d[4] = triangle_3d[6];
          }
        }
        if (x6 == 5) {
          if (angle == 1) {
            triangle_2d[5] = triangle_3d[8];
          } else {
            triangle_2d[5] = triangle_3d[7];
          }
        }
        if (x6 == 6) {
          if (angle == 0) {
            triangle_2d[6] = ((bit32)(((ap_int<34>)(((ap_int<33>)(triangle_3d[2] / 3)) + ((ap_int<33>)(triangle_3d[5] / 3)))) + ((ap_int<34>)(triangle_3d[8] / 3))));
          } else {
            if (angle == 1) {
              triangle_2d[6] = ((bit32)(((ap_int<34>)(((ap_int<33>)(triangle_3d[1] / 3)) + ((ap_int<33>)(triangle_3d[4] / 3)))) + ((ap_int<34>)(triangle_3d[7] / 3))));
            } else {
              if (angle == 2) {
                triangle_2d[6] = ((bit32)(((ap_int<34>)(((ap_int<33>)(triangle_3d[0] / 3)) + ((ap_int<33>)(triangle_3d[3] / 3)))) + ((ap_int<34>)(triangle_3d[6] / 3))));
              }
            }
          }
        }
      }
      bit32 fragment_update;
      bit32 x0;
      x0 = triangle_2d[0];
      bit32 y0;
      y0 = triangle_2d[1];
      bit32 x11;
      x11 = triangle_2d[2];
      bit32 y11;
      y11 = triangle_2d[3];
      bit32 x21;
      x21 = triangle_2d[4];
      bit32 y21;
      y21 = triangle_2d[5];
      bit32 z;
      z = triangle_2d[6];
      bit32 cw;
      cw = ((bit32)((((ap_int<66>)((ap_int<33>)(x21 - x0))) * ((ap_int<66>)((ap_int<33>)(y11 - y0)))) - (((ap_int<66>)((ap_int<33>)(y21 - y0))) * ((ap_int<66>)((ap_int<33>)(x11 - x0))))));
      if (cw == 0) {
        frag_cntr = 0;
      } else {
        if (cw < 0) {
          bit32 scalar0;
          scalar0 = x0;
          bit32 scalar1;
          scalar1 = y0;
          x0 = x11;
          y0 = y11;
          x11 = scalar0;
          y11 = scalar1;
        }
      }
      bit32 scalar2;
      scalar2 = 0;
      bit32 scalar3;
      scalar3 = 0;
      bit32 scalar4;
      scalar4 = 0;
      bit32 scalar5;
      scalar5 = 0;
      if (x0 < x11) {
        if (x21 < x0) {
          scalar2 = x21;
        } else {
          scalar2 = x0;
        }
      } else {
        if (x21 < x11) {
          scalar2 = x21;
        } else {
          scalar2 = x11;
        }
      }
      if (x11 < x0) {
        if (x0 < x21) {
          scalar3 = x21;
        } else {
          scalar3 = x0;
        }
      } else {
        if (x11 < x21) {
          scalar3 = x21;
        } else {
          scalar3 = x11;
        }
      }
      if (y0 < y11) {
        if (y21 < y0) {
          scalar4 = y21;
        } else {
          scalar4 = y0;
        }
      } else {
        if (y21 < y11) {
          scalar4 = y21;
        } else {
          scalar4 = y11;
        }
      }
      if (y11 < y0) {
        if (y0 < y21) {
          scalar5 = y21;
        } else {
          scalar5 = y0;
        }
      } else {
        if (y11 < y21) {
          scalar5 = y21;
        } else {
          scalar5 = y11;
        }
      }
      bit32 color;
      color = 100;
      bit32 scalar6;
      scalar6 = 0;
      bit32 S1;
      for (bit32 i = 0; i < (scalar5 - scalar4); ++i) {
      #pragma HLS loop_tripcount min=1 max=25 avg=13
	for (bit32 x7 = 0; x7 < (scalar3 - scalar2); ++x7) {
        #pragma HLS loop_tripcount min=1 max=29 avg=15
        #pragma HLS pipeline
          bit32 compute0;
          compute0 = ((bit32)((((ap_int<67>)((ap_int<34>)(((ap_int<33>)(x7 - x0)) + ((ap_int<33>)scalar2)))) * ((ap_int<67>)((ap_int<33>)(y11 - y0)))) - (((ap_int<67>)((ap_int<34>)(((ap_int<33>)(i - y0)) + ((ap_int<33>)scalar4)))) * ((ap_int<67>)((ap_int<33>)(x11 - x0))))));
          bit32 compute1;
          compute1 = ((bit32)((((ap_int<67>)((ap_int<34>)(((ap_int<33>)(x7 - x11)) + ((ap_int<33>)scalar2)))) * ((ap_int<67>)((ap_int<33>)(y21 - y11)))) - (((ap_int<67>)((ap_int<34>)(((ap_int<33>)(i - y11)) + ((ap_int<33>)scalar4)))) * ((ap_int<67>)((ap_int<33>)(x21 - x11))))));
          bit32 compute2;
          compute2 = ((bit32)((((ap_int<67>)((ap_int<34>)(((ap_int<33>)(x7 - x21)) + ((ap_int<33>)scalar2)))) * ((ap_int<67>)((ap_int<33>)(y0 - y21)))) - (((ap_int<67>)((ap_int<34>)(((ap_int<33>)(i - y21)) + ((ap_int<33>)scalar4)))) * ((ap_int<67>)((ap_int<33>)(x0 - x21))))));
          if (0 <= hls::min(hls::min(compute0, compute1), compute2)) {
            fragment[scalar6][0] = ((bit32)(((ap_int<33>)x7) + ((ap_int<33>)scalar2)));
            fragment[scalar6][1] = ((bit32)(((ap_int<33>)i) + ((ap_int<33>)scalar4)));
            fragment[scalar6][2] = z;
            fragment[scalar6][3] = color;
            scalar6 = (scalar6 + 1);
          }
        }
      }
      frag_cntr = scalar6;
      bit32 z_update;
      bit32 scalar7;
      scalar7 = 0;
      bit32 S2;
      for (bit32 n = 0; n < frag_cntr; ++n) {
      #pragma HLS loop_tripcount min=0 max=446 avg=223
      #pragma HLS pipeline
        bit32 scalar8;
        scalar8 = fragment[n][0];
        bit32 scalar9;
        scalar9 = fragment[n][1];
        bit32 scalar10;
        scalar10 = fragment[n][2];
        bit32 scalar11;
        scalar11 = fragment[n][3];
        if (scalar10 < z_buffer[((scalar8 / 256) + scalar9)][(scalar8 % 256)]) {
          pixels[scalar7][0] = scalar8;
          pixels[scalar7][1] = scalar9;
          pixels[scalar7][2] = scalar11;
          scalar7 = (scalar7 + 1);
          z_buffer[((scalar8 / 256) + scalar9)][(scalar8 % 256)] = scalar10;
        }
      }
      size_pixels = scalar7;
      bit32 buffer_update;
      for (bit32 x8 = 0; x8 < size_pixels; ++x8) {
      #pragma HLS loop_tripcount min=0 max=446 avg=223
      #pragma HLS pipeline
        bit32 scalar12;
        scalar12 = pixels[x8][0];
        bit32 scalar13;
        scalar13 = pixels[x8][1];
        frame_buffer[((scalar13 / 256) + scalar12)][(scalar13 % 256)] = pixels[x8][2];
      }
    }
    for (bit32 frame_buffer0 = 0; frame_buffer0 < 256; ++frame_buffer0) {
      for (bit32 frame_buffer1 = 0; frame_buffer1 < 256; ++frame_buffer1) {
        frame_buffer_update_channel.write(frame_buffer[frame_buffer0][frame_buffer1]);
      }
    }
  }
