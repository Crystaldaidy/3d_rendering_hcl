# 3d_rendering_hcl
# After installing HeteroCL on your computer, set the mode to 'csim|csyn' and run the command:
python hcl_3d_rendering.py

# Then you will have all generated files as well as the report.

# To have the estimated latency, you should add tripcount pragmas in the HLSC file (kernel.cpp) by hand:
#pragma HLS loop_tripcount min=1 max=25 avg=13 (line 217)

#pragma HLS loop_tripcount min=1 max=29 avg=15 (line 219)

#pragma HLS loop_tripcount min=0 max=446 avg=223 (line 242)

#pragma HLS loop_tripcount min=0 max=446 avg=223 (line 263)

# Then before running vivado HLS, you need to comment the csim mode in the run.tcl file (this is because of an unresolved bug):
#csim_design -O

# Finally, run vivado HLS:
vivado_hls -f run.tcl

# Get the result in 3d_rendering_hcl/project/out.prj/solution1/syn/report/test_csynth.rpt.
