#include <math.h>
#include "helpers.h"

// For reference
/*
typedef struct
{
    BYTE  rgbtBlue;
    BYTE  rgbtGreen;
    BYTE  rgbtRed;
} __attribute__((__packed__))
RGBTRIPLE;
*/

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE transform[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE rgb = image[i][j];
            int r = rgb.rgbtRed;
            int g = rgb.rgbtGreen;
            int b = rgb.rgbtBlue;

            float average = (r + g + b) / (float) 3;
            int average_rounded = round(average);

            transform[i][j].rgbtRed = average_rounded;
            transform[i][j].rgbtGreen = average_rounded;
            transform[i][j].rgbtBlue = average_rounded;
        }
    }   

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Using array referencing handles pointers
            image[i][j] = transform[i][j];
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE transform[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE rgb = image[i][j];
            int r = rgb.rgbtRed;
            int g = rgb.rgbtGreen;
            int b = rgb.rgbtBlue;

            // TODO: Define transform

            float rt = 0.393 * r + 0.769 * g + 0.189 * b;
            float gt = 0.349 * r + 0.686 * g + 0.168 * b;
            float bt = 0.272 * r + 0.534 * g + 0.131 * b;

            // Round and cap at 255
            int max = 255;
            int rt_rounded = (rt > 255) ? 255 : round(rt);
            int gt_rounded = (gt > 255) ? 255 : round(gt);
            int bt_rounded = (bt > 255) ? 255 : round(bt);

            transform[i][j].rgbtRed = rt_rounded;
            transform[i][j].rgbtGreen = gt_rounded;
            transform[i][j].rgbtBlue = bt_rounded;
        }
    }   

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Using array referencing handles pointers
            image[i][j] = transform[i][j];
        }
    }

    return;

}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE transform[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE rgb = image[i][width - j - 1];
            transform[i][j] = rgb;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Using array referencing handles pointers
            image[i][j] = transform[i][j];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE transform[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 0;
            int sum_r = 0;
            int sum_g = 0;
            int sum_b = 0;

            // Upper left
            if ((i != height - 1) && (j != width - 1))
            {
                count++;
                sum_r += image[i + 1][j + 1].rgbtRed;
                sum_g += image[i + 1][j + 1].rgbtGreen;
                sum_b += image[i + 1][j + 1].rgbtBlue;
            }

            // Upper center
            if (i != height - 1)
            {
                count++;
                sum_r += image[i + 1][j].rgbtRed;
                sum_g += image[i + 1][j].rgbtGreen;
                sum_b += image[i + 1][j].rgbtBlue;
            }

            // Upper right
            if ((i != height - 1) && (j != 0))
            {
                count++;
                sum_r += image[i + 1][j - 1].rgbtRed;
                sum_g += image[i + 1][j - 1].rgbtGreen;
                sum_b += image[i + 1][j - 1].rgbtBlue;
            }

            // Middle left
            if (j != width - 1)
            {
                count++;
                sum_r += image[i][j + 1].rgbtRed;
                sum_g += image[i][j + 1].rgbtGreen;
                sum_b += image[i][j + 1].rgbtBlue;
            }
            
            // Middle center
            count++;
            sum_r += image[i][j].rgbtRed;
            sum_g += image[i][j].rgbtGreen;
            sum_b += image[i][j].rgbtBlue;

            // Middle right
            if (j != 0)
            {
                count++;
                sum_r += image[i][j - 1].rgbtRed;
                sum_g += image[i][j - 1].rgbtGreen;
                sum_b += image[i][j - 1].rgbtBlue;
            }

            // Lower left
            if ((i != 0) && (j != width - 1))
            {
                count++;
                sum_r += image[i - 1][j + 1].rgbtRed;
                sum_g += image[i - 1][j + 1].rgbtGreen;
                sum_b += image[i - 1][j + 1].rgbtBlue;
            }

            // Lower center
            if (i != 0)
            {
                count++;
                sum_r += image[i - 1][j].rgbtRed;
                sum_g += image[i - 1][j].rgbtGreen;
                sum_b += image[i - 1][j].rgbtBlue;
            }

            // Lower right
            if ((i != 0) && (j != 0))
            {
                count++;
                sum_r += image[i - 1][j - 1].rgbtRed;
                sum_g += image[i - 1][j - 1].rgbtGreen;
                sum_b += image[i - 1][j - 1].rgbtBlue;
            }

            float average_r = (float) sum_r / count;
            float average_g = (float) sum_g / count;
            float average_b = (float) sum_b / count;

            int average_r_rounded = round(average_r);
            int average_g_rounded = round(average_g);
            int average_b_rounded = round(average_b);

            transform[i][j].rgbtRed = average_r_rounded;
            transform[i][j].rgbtGreen = average_g_rounded;
            transform[i][j].rgbtBlue = average_b_rounded;
        }
    }   

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Using array referencing handles pointers
            image[i][j] = transform[i][j];
        }
    }

    return;
}
