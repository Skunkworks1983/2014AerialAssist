#ifndef __VISION_UTIL_H
#define __VISION_UTIL_H

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

double calcDistance(cv::Point &a, cv::Point &b);

cv::Point2f centerOfMass(std::vector<cv::Point>& contour);

// TODO Unimplemented
double matchParallelogram(std::vector<cv::Point>& contour);

/**
 * Compares the two contours' perimeters.  Good for evaluating how well
 * a polygon approximation did.
 */
double matchHeuristic(std::vector<cv::Point>& contour,
		std::vector<cv::Point>& cloud);

/**
 * Looks for a polygon that has a set of smaller sides and a set of larger sides.
 */
double twoSideLengthsHeuristic(std::vector<cv::Point>& contour);

#endif
