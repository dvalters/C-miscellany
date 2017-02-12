/* 

A C-code that mimics the Hillshade function in LSDRaster,
but designed to be inter-operable with numpy and callable from python

Author: DAV 2017

*/

#include <stdio.h>
#include <math.h>

void hillshade(float altitude, float azimuth, float z_factor, \
		const int m, const int n,\
		float **RasterData, float **Hillshade, \
		float NoDataValue, \
                float DataResolution)
/* altitude, float and z_factor are parameters to create the hillshade
 m and n are the rows and cols
 float **RasterData is a pointer to a pointer of type double...(input raster)
 float **Hillshade is the output array (hillshade)
*/
{
    printf("Hillshading with altitude %f, azimuth: %f, and z-factor: %f \n", \
           altitude, azimuth, z_factor);

    /* convert zenith and azimuth into radians for calculation */
    float zenith_rad = (90 - altitude) * M_PI / 180.0;
    float azimuth_math = 360-azimuth + 90;
    if (azimuth_math >= 360.0) azimuth_math = azimuth_math - 360;
    float azimuth_rad = azimuth_math * M_PI /180.0;

    /* calculate hillshade value for every non nodata value in the input raster */
    int i, j;
    for (i = 1; i < m - 1; ++i) {
        for (j = 1; j < n - 1; ++j) {
            float slope_rad = 0;
            float aspect_rad = 0;
            float dzdx = 0;
            float dzdy = 0;

            if (RasterData[i][j] != NoDataValue){
                dzdx = ((RasterData[i][j+1] + 2*RasterData[i+1][j] + RasterData[i+1][j+1]) -
                       (RasterData[i-1][j-1] + 2*RasterData[i-1][j] + RasterData[i-1][j+1]))
                        / (8 * DataResolution);
                dzdy = ((RasterData[i-1][j+1] + 2*RasterData[i][j+1] + RasterData[i+1][j+1]) -
                       (RasterData[i-1][j-1] + 2*RasterData[i][j-1] + RasterData[i+1][j-1]))
                       / (8 * DataResolution);

                slope_rad = atan(z_factor * sqrt((dzdx*dzdx) + (dzdy*dzdy)));

                if (dzdx != 0){
                    aspect_rad = atan2(dzdy, (dzdx*-1));
                    if (aspect_rad < 0) aspect_rad = 2*M_PI + aspect_rad;
                }
                else{
                    if (dzdy > 0) aspect_rad = M_PI/2;
                    else if (dzdy < 0) aspect_rad = 2 * M_PI - M_PI/2;
                    else aspect_rad = aspect_rad;
                }
                Hillshade[i][j] = 255.0 * ((cos(zenith_rad) * cos(slope_rad)) +
                                  (sin(zenith_rad) * sin(slope_rad) *
                                  cos(azimuth_rad - aspect_rad)));

                if (Hillshade[i][j] < 0) Hillshade[i][j] = 0;
            }
        }
    }
}
