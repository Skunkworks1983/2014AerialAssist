#include "VisionUtil.h"

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

double calcDistance(cv::Point &a, cv::Point &b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

cv::Point2f centerOfMass(std::vector<cv::Point>& contour) {
	cv::Point2f pt;
	pt.x = pt.y = 0;
	size_t i;
	for (i = 0; i < contour.size(); i++) {
		pt.x += contour[i].x;
		pt.y += contour[i].y;
	}
	pt.x /= contour.size();
	pt.y /= contour.size();
	return pt;
}

// Checks the point cloud against the contour using a perimeter comparison.
double matchHeuristic(std::vector<cv::Point>& contour,
		std::vector<cv::Point>& cloud) {
	double matchDistance = cv::arcLength(cloud, false);
	double myDistance = cv::arcLength(contour, false);
	return fabs(matchDistance - myDistance) / myDistance;
}

// Looks for parallelograms
// TODO
double matchParallelogram(std::vector<cv::Point>& contour) {
	double angles[contour.size()];
	size_t i, j, k;
	double x1, x2, y1, y2;
	double l1, l2;

	for (i = 0; i < contour.size(); i++) {
		j = i - 1;
		k = i + 1;
		if (j < 0) {
			j += contour.size();
		}
		if (k >= contour.size()) {
			k -= contour.size();
		}

		x1 = contour[j].x - contour[i].x;
		y1 = contour[j].y - contour[i].y;
		l1 = sqrt(x1 * x1 + y1 * y1);

		x2 = contour[k].x - contour[i].x;
		y2 = contour[k].y - contour[i].y;
		l2 = sqrt(x2 * x2 + y2 * y2);

		angles[i] = acos((x1 * x2 + y1 * y2) / l1 / l2);
	}
	return 0.0;
}


// Looks for rectangular contours
double twoSideLengthsHeuristic(std::vector<cv::Point>& contour) {
	double sideLength[contour.size()];
	double minLength = 1e100;
	double maxLength = 0;
	double totalLength = 0;
	for (size_t i = 0; i < contour.size(); i++) {
		double len = calcDistance(contour[i],
				contour[(i + 1) % contour.size()]);
		sideLength[i] = len;
		if (len < minLength) {
			minLength = len;
		}
		if (len > maxLength) {
			maxLength = len;
		}
		totalLength += len;
	}
	double total = 0, diffA, diffB;
	for (size_t i = 0; i < contour.size(); i++) {
		diffA = fabs(sideLength[i] - maxLength);
		diffB = fabs(sideLength[i] - minLength);
		total += diffA > diffB ? diffB : diffA;
	}
	return total / totalLength;
}
