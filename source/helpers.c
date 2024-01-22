#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average;
            double red = image[i][j].rgbtRed;
            double green = image[i][j].rgbtGreen;
            double blue = image[i][j].rgbtBlue;

            //computing average color of the 3x3 square
            average = round((red + green + blue) / 3);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        //iterating up to the half of total columns
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    //making a copy
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            temp[row][column] = image[row][column];
        }
    }

    //iterating through 2d array
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            int count;
            double r_total;
            double g_total;
            double b_total;
            count = r_total = g_total = b_total = 0;
            for (int h = -1; h < 2; h++)
            {
                for (int l = -1; l < 2; l++)
                {

                    if ((row + h < 0) || (row + h >= height))
                    {
                        continue;
                    }
                    if ((column + l < 0) || (column + l >= width))
                    {
                        continue;
                    }
                    r_total += temp[row + h][column + l].rgbtRed;
                    g_total += temp[row + h][column + l].rgbtGreen;
                    b_total += temp[row + h][column + l].rgbtBlue;
                    count++;
                }
            }
            image[row][column].rgbtRed = round(r_total / count);
            image[row][column].rgbtGreen = round(g_total / count);
            image[row][column].rgbtBlue = round(b_total / count);
        }
    }
    return;
}

// Detect edges
//Using Sobel Operator
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    //creating a copy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    //creating Sobel 3x3 2d arrays for calculation
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}}l;
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
	
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int row = 0; row < height; row++)
        for (int column = 0; column < width; column++) {

            //declaring variable of Gx and Gy squares
            //for better understanding search how Sobel Operator works
            double Gxr_total, Gxg_total, Gxb_total;
            double Gyg_total, Gyr_total, Gyb_total;
            Gxr_total = Gxg_total = Gxb_total = Gyr_total = Gyg_total = Gyb_total = 0;

            //itearting through 3x3 square
            for (int h = -1; h < 2; h++)
                for (int l = -1; l < 2; l++) {
                    //checking for edge and corner pixels
                    if ((row + h < 0) || (row + h >= height)) {
                        continue;
                    }
                    if ((column + l < 0) || (column + l >= width)) {
                        continue;
                    }
                    //calculating total gx and gy for each color
                    Gxr_total += temp[row + h][column + l].rgbtRed * Gx[h + 1][l + 1];
                    Gxg_total += temp[row + h][column + l].rgbtGreen * Gx[h + 1][l + 1];
                    Gxb_total += temp[row + h][column + l].rgbtBlue * Gx[h + 1][l + 1];
                    Gyr_total += temp[row + h][column + l].rgbtRed * Gy[h + 1][l + 1];
                    Gyg_total += temp[row + h][column + l].rgbtGreen * Gy[h + 1][l + 1];
                    Gyb_total += temp[row + h][column + l].rgbtBlue * Gy[h + 1][l + 1];
                }

	        // using Sobel formula
          int r = (round(sqrt(Gxr_total * Gxr_total + Gyr_total * Gyr_total)));
          int g = (round(sqrt(Gxg_total * Gxg_total + Gyg_total * Gyg_total)));
          int b = (round(sqrt(Gxb_total * Gxb_total + Gyb_total * Gyb_total)));

          //max value to 255
          if (r > 255)
          {
             r = 255;
          }
          if (g > 255)
          {
              g = 255;
          }
          if (b > 255)
         {
            b = 255;
         }

         image[row][column].rgbtRed = r;
         image[row][column].rgbtGreen = g;
         image[row][column].rgbtBlue = b;
         }
         return;
}
