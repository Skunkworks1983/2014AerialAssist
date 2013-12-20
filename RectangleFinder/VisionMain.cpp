#define SHAPE_FIT_HEURISTIC_SAMPLE_RATE 1
#define SHAPE_FIT_HEURISTIC_MATCH_RATE 1

#define HEADLESS 0
#define ADAPTIVE 1
#define DEBUG 0
#define NETWORK 1
#define NETWORK_BUFFER 512

#if NETWORK
#include "SocketServer.h"
#endif

#include <string>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "VisionUtil.h"
#include "ThreadedCapture.h"

#include <vector>

const char windowName[] = "Rectangles";

static double matchAcceptanceLevel = 0.5;
static double areaAcceptanceLevel = 0.074074074;
static double rectangularAcceptanceLevel = 0.1;

typedef struct {
	cv::Point2f centerOfMass;
	double area;
	double matchLevel;
	double areaError;
	double rectangularMatchLevel;
} MatchedShape;

void findRectangle(cv::Mat &src, std::vector<MatchedShape>& results) {
	cv::Mat dst;
	src.copyTo(dst);

	cv::cvtColor(dst, dst, cv::COLOR_RGB2GRAY);
	cv::adaptiveThreshold(dst, dst, 255, CV_ADAPTIVE_THRESH_MEAN_C,
			CV_THRESH_BINARY_INV, 75, 10);
	std::vector<std::vector<cv::Point> > contours;
	std::vector<std::vector<cv::Point> > cleanContours;
	std::vector<std::vector<cv::Point> > dirtyContours;
	std::vector<cv::Vec4i> heirarchy;
	cv::findContours(dst, contours, heirarchy, CV_RETR_TREE,
			CV_CHAIN_APPROX_SIMPLE);
	for (size_t i = 0; i < contours.size(); i++) {
		double arc = cv::arcLength(contours[i], true);
		std::vector<cv::Point> newContour;
		cv::approxPolyDP(contours[i], newContour, arc * 0.03, true);
		double contourAreaRaw = cv::contourArea(contours[i]);
		if (contourAreaRaw < 1000 || newContour.size() != 4
				|| !cv::isContourConvex(newContour)) {
			continue;
		}

		dirtyContours.push_back(contours[i]);
		//cv::RotatedRect r = cv::minAreaRect(newContour);
		double newContourArea = cv::contourArea(newContour);
		double areaDiff = newContourArea - contourAreaRaw;
		if (fabs(areaDiff) / newContourArea > areaAcceptanceLevel) {
			continue;
		}

		double matchLevel = matchHeuristic(newContour, contours[i]);
		if (matchLevel > matchAcceptanceLevel) {
			continue;
		}
		double rectangularLevel = twoSideLengthsHeuristic(newContour);
		if (rectangularLevel > rectangularAcceptanceLevel) {
			continue;
		}
		cleanContours.push_back(newContour);
		MatchedShape m;
		m.centerOfMass = centerOfMass(newContour);
		m.centerOfMass.x -= src.cols / 2;
		m.centerOfMass.y -= src.rows / 2;
		m.centerOfMass.x /= (float) src.cols;
		m.centerOfMass.y /= (float) src.rows;

		m.area = newContourArea;
		m.areaError = fabs(areaDiff) / newContourArea;
		m.matchLevel = matchLevel;
		m.rectangularMatchLevel = rectangularLevel;
		results.push_back(m);
	}

#if ADAPTIVE
	if (cleanContours.size() > 1) {
		areaAcceptanceLevel /= 1.1;
		matchAcceptanceLevel /= 1.1;
		rectangularAcceptanceLevel /= 1.1;
	} else if (cleanContours.size() == 0) {
		areaAcceptanceLevel *= 1.1;
		matchAcceptanceLevel *= 1.1;
		rectangularAcceptanceLevel *= 1.1;
	}
#endif

#if !(HEADLESS)
	cv::drawContours(src, dirtyContours, -1, cv::Scalar(255, 0, 0));
	cv::drawContours(src, cleanContours, -1, cv::Scalar(0, 0, 255));
	cv::imshow(windowName, src);
#endif
}

int main(int argc, char** argv) {
#if !(HEADLESS)
	cv::namedWindow(windowName);
#endif

	std::vector<MatchedShape> results;
	size_t i;
	cv::Mat temporaryMaterial;
	ThreadedCapture threadedCapture(-1);

#if NETWORK
	SocketServer *network = new SocketServer(NULL, NULL);
	char *buffer = (char*) malloc(NETWORK_BUFFER);
	int bufferHead = 0;
#endif

#if !(HEADLESS)
	while (cv::waitKey(30) < 27) {
#else
		while (1) {
#endif
		if (threadedCapture.hasCaptured()) {
			threadedCapture.getCaptured(&temporaryMaterial);

			results.clear();
			findRectangle(temporaryMaterial, results);
#if DEBUG
			printf("Found %d rectangles!\n", (int) results.size());
			printf("Area\tMx\tMy\tMatch\tRectangle Match\n");
#endif
			for (i = 0; i < results.size(); i++) {
#if DEBUG
				printf("%d\t%f\t%f\t%f\t%f\n", (int) results[i].area,
						results[i].centerOfMass.x, results[i].centerOfMass.y,
						results[i].matchLevel, results[i].rectangularMatchLevel);
#endif
#if NETWORK
				bufferHead += sprintf(buffer + bufferHead,
						"%d/%d\t%d\t%f\t%f\t%f\t%f\n", (int) i,
						(int) results.size(), (int) results[i].area,
						results[i].centerOfMass.x, results[i].centerOfMass.y,
						results[i].matchLevel,
						results[i].rectangularMatchLevel);
				buffer[bufferHead] = 0;
				network->SendData(buffer);
				bufferHead = 0;
#endif
			}
		}
		usleep(10000);
	}
#if !(HEADLESS)
	cv::destroyAllWindows();
#endif
#if NETWORK
	delete network;
	free(buffer);
#endif
	threadedCapture.stop();
}
