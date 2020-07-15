
#include <sys/ipc.h>
#include <sys/shm.h>

// standard C/C++ headers
#include <cstdio>
#include <cstdlib>
#include <getopt.h>
#include <string>
#include <time.h>
#include <sys/time.h>
#include <cassert>

// vivado hls headers
#include <ap_int.h>
#include <ap_fixed.h>
#include <hls_stream.h>
#include "kernel.h"

#include <ap_int.h>
#include <ap_fixed.h>
#include <ap_axi_sdata.h>
#include <hls_stream.h>
#include <hls_math.h>
#include <stdint.h>

int main(int argc, char ** argv) {
  std::cout << " Initialize shared memory...";
  int32_t* arg_0 = (int32_t*)shmat(/*triangle_3ds*/59, nullptr, 0);
  auto triangle_3ds = new ap_int<32>[3191][9];
  for (size_t i0 = 0; i0 < 3191; i0++) {
    for (size_t i1 = 0; i1 < 9; i1++) {
      triangle_3ds[i0][i1] = (int32_t)(arg_0[i1 + i0*9]);
    }
  }

  int32_t* arg_1 = (int32_t*)shmat(/*angle*/60, nullptr, 0);
  auto angle = new ap_int<32>[1];
  for (size_t i0 = 0; i0 < 1; i0++) {
    angle[i0] = (int32_t)(arg_1[i0]);
  }

  int32_t* arg_2 = (int32_t*)shmat(/*frame_buffer_update*/61, nullptr, 0);
  auto frame_buffer = new ap_int<32>[256][256];
  for (size_t i0 = 0; i0 < 256; i0++) {
    for (size_t i1 = 0; i1 < 256; i1++) {
      frame_buffer[i0][i1] = (int32_t)(arg_2[i1 + i0*256]);
    }
  }

  std::cout << " Initialize RTE...";

  // compute and kernel call from host
  ap_int<32> _top;
  hls::stream<ap_int<32> > triangle_3ds_channel;
  for (ap_int<32> triangle_3ds0 = 0; triangle_3ds0 < 3191; ++triangle_3ds0) {
    for (ap_int<32> triangle_3ds1 = 0; triangle_3ds1 < 9; ++triangle_3ds1) {
      triangle_3ds_channel.write(triangle_3ds[triangle_3ds0][triangle_3ds1]);
    }
  }
  hls::stream<ap_int<32> > angle_channel;
  angle_channel.write(angle[0]);
  hls::stream<ap_int<32> > frame_buffer_update_channel;
  test(triangle_3ds_channel, angle_channel, frame_buffer_update_channel);
  ap_int<32> frame_buffer_update[256][256];
  for (ap_int<32> frame_buffer0 = 0; frame_buffer0 < 256; ++frame_buffer0) {
    for (ap_int<32> frame_buffer1 = 0; frame_buffer1 < 256; ++frame_buffer1) {
      frame_buffer_update[frame_buffer0][frame_buffer1] = frame_buffer_update_channel.read();
    }
  }

  for (size_t i0 = 0; i0 < 3191; i0++) {
    for (size_t i1 = 0; i1 < 9; i1++) {
      arg_0[i1 + i0*9] = (int32_t)(triangle_3ds[i0][i1]);
    }
  }
  shmdt(arg_0);
  for (size_t i0 = 0; i0 < 1; i0++) {
    arg_1[i0] = (int32_t)(angle[i0]);
  }
  shmdt(arg_1);
  for (size_t i0 = 0; i0 < 256; i0++) {
    for (size_t i1 = 0; i1 < 256; i1++) {
      arg_2[i1 + i0*256] = (int32_t)(frame_buffer_update[i0][i1]);
    }
  }
  shmdt(arg_2);


  }
