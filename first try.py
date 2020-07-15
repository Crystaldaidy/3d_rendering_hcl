# import heterocl as hcl 
import numpy as np 
import pandas as pd

MAX_X = 256;
MAX_Y = 256;
#triangle_3d is an array of the 3D triangle with (x0,y0,z0,x1,y1,z1,x2,y2,z2)
#triangle_2d is an array of the 2D triangle with (x0,y0,x1,y1,x2,y2,z2)
def projection(triangle_3d, angle):
    x0,y0,z0,x1,y1,z1,x2,y2,z2 = triangle_3d;
    triangle_2d = np.zeros(7);
    if angle==0 :
        triangle_2d[0] = x0;
        triangle_2d[1] = y0;
        triangle_2d[2] = x1;
        triangle_2d[3] = y1;
        triangle_2d[4] = x2;
        triangle_2d[5] = y2;
        triangle_2d[6] = (z0+z1+z2)/3;
    
    elif angle==1 :
        triangle_2d[0] = x0;
        triangle_2d[1] = z0;
        triangle_2d[2] = x1;
        triangle_2d[3] = z1;
        triangle_2d[4] = x2;
        triangle_2d[5] = z2;
        triangle_2d[6] = (y0+y1+y2)/3;

    elif angle==2:
        triangle_2d[0] = z0;
        triangle_2d[1] = y0;
        triangle_2d[2] = z1;
        triangle_2d[3] = y1;
        triangle_2d[4] = z2;
        triangle_2d[5] = y2;
        triangle_2d[6] = (x0+x1+x2)/3;
    
    return triangle_2d;

#fragment is a 500*4 array: candidate pixels' x,y,z,color
def rasterization(triangle_2d,fragment):
    x0,y0,x1,y1,x2,y2,z = triangle_2d;
    fragment = np.zeros([500,4])
    #   Determine whether three vertices of a trianlge 
    #   (x0,y0) (x1,y1) (x2,y2) are in clockwise order by Pineda algorithm
    #   if so, return a number > 0
    #   else if three points are in line, return a number == 0
    #   else in counterclockwise order, return a number < 0
    cw = (x2 - x0) * (y1 - y0) - (y2 - y0) * (x1 - x0); 
    if cw == 0: return fragment,0;
    elif cw < 0:
        tmp_x = x0; tmp_y = y0;
        x0 = x1; y0 = y1;
        x1 = tmp_x; y1 = tmp_y;

    min_x = int(min( x0, x1, x2 ));
    max_x = int(max( x0, x1, x2 ));
    min_y = int(min( y0, y1, y2 ));
    max_y = int(max( y0, y1, y2 ));
    color = 100;

    # i: size of pixels in the triangle
    i = 0;
    for y in range(min_y,max_y):
        for x in range(min_x,max_x):
            pi0 = (x - x0) * (y1 - y0) - (y - y0) * (x1 - x0); 
            pi1 = (x - x1) * (y2 - y1) - (y - y1) * (x2 - x1); 
            pi2 = (x - x2) * (y0 - y2) - (y - y2) * (x0 - x2); 
            if (pi0 >= 0 and pi1 >= 0 and pi2 >= 0):
                fragment[i][0] = x;
                fragment[i][1] = y;
                fragment[i][2] = z;
                fragment[i][3] = color;
                i += 1;

    # triangle_2d = x0,y0,x1,y1,x2,y2,z;
    return fragment,i;

# Input:  fragements, array of candidata pixels for multiple triangles
# Input:  size,  
# Output: pixels, 500*3 array: pixels' x,y,color
def zculling(z_buffer,fragment,pixels,size):
    pixel_cntr = 0;
    pixels = np.zeros([500,3])
    
    for n in range(size):
        x,y,z,color = fragment[n]
        y = int(y)
        x = int(x)
        if( z < z_buffer[y][x] ):
            pixels[pixel_cntr][0] = x
            pixels[pixel_cntr][1] = y
            pixels[pixel_cntr][2] = color
            pixel_cntr += 1
            z_buffer[y][x] = z

    return z_buffer,pixels,pixel_cntr
        
def coloringFB(size_pixels,pixels,frame_buffer):
    
    for i in range(size_pixels):
        x,y,color = pixels[i]
        x = int(x)
        y = int(y)
        frame_buffer[x][y] = color
    
    return frame_buffer;

def rendering(input,angle):
    triangle_3d = input
    num_3d_triangles = triangle_3d.shape[0]
    z_buffer = np.zeros([MAX_X,MAX_Y])
    for i in range(MAX_X):
            for j in range(MAX_Y):
                z_buffer[i][j] = 255

    frame_buffer = np.zeros([MAX_X,MAX_Y])

    for i in range(num_3d_triangles):
        # 1st Stage Projection
        triangle_2d = projection(triangle_3d[i],angle)

        # 2nd Stage Rasterization
        fragment,frag_cntr = rasterization(triangle_2d)
        
        # 3rd Stage Z-culling
        z_buffer,pixels,size_pixels = zculling(z_buffer,fragment,frag_cntr)
        
        # coloring frame buffer
        frame_buffer = coloringFB(size_pixels,pixels,frame_buffer)

    return frame_buffer


input_data = np.array(pd.read_csv('data.csv'))
output = rendering(input_data,0).astype(int)
for j in range(MAX_X-1,-1,-1):
    for i in range(MAX_Y):
        if (output[i][j] < 10):
            print(output[i][j],end='  ')
        elif(output[i][j] < 100):
            print(output[i][j],end=' ')
        elif(output[i][j] < 1000):
            print(output[i][j],end='')
    print()