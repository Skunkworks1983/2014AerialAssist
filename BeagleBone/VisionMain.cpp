#define SHAPE_FIT_HEURISTIC_SAMPLE_RATE 1
#define SHAPE_FIT_HEURISTIC_MATCH_RATE 1

#define HEADLESS 0
#define ADAPTIVE 1
#define DEBUG 0
#define NETWORK 1
#define SENSORS 0
#define VISION 1
#define NETWORK_BUFFER 512

#if NETWORK
#include "SocketServer.h"
#endif

#if SENSORS
#include "sensors/internal/smbus.h"
#include "sensors/BMP180.h"
#include "sensors/L3GD20.h"
#include "sensors/LSM303_ACC.h"
#include "sensors/LSM303_MAG.h"
#include "sensors/kalman/Kalman.h"
#endif

#include <string>
#include <stdlib.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "VisionUtil.h"
#include "ThreadedCapture.h"
#include <sys/time.h>

#include <vector>

const char windowName[] = "Rectangles";
const char windowName2[] = "Rectanglez";

static double matchAcceptanceLevel = 1.25;
static double areaAcceptanceLevel = 0.5;
static double rectangularAcceptanceLevel = 0.125;

typedef struct {
	cv::Point2f centerOfMass;
	double area;
	double matchLevel;
	double areaError;
	double rectangularMatchLevel;
} MatchedShape;

int milliTime() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void findRectangle(cv::Mat &src, std::vector<MatchedShape>& results) {
	cv::Mat dst;
	cv::Mat tmp;
	src.copyTo(tmp);

	// 147,232,182 = Search color
	cv::subtract(src, cv::Scalar(88 - 127, 243 - 127, 186 - 127), src);
	// 60,60,60 -> 200,200,200 = Search range
	cv::Scalar meanMask = cv::mean(src);
	double avgMask = (meanMask.val[0] + meanMask.val[1] + meanMask.val[2])
			/ 3.0;
	cv::inRange(src, cv::Scalar(0, 0, 0),
			cv::Scalar(avgMask * 2.2, avgMask * 2.2, avgMask * 2.2), src);

	// Masked
	tmp.copyTo(src, src);

	cv::Scalar meanMasked = cv::mean(src);
	double avgMasked = (meanMasked.val[0] + meanMasked.val[1]
			+ meanMasked.val[2]) / 3.0;
	cv::inRange(src, cv::Scalar(0, 0, 0), cv::Scalar(1, 1, 1), tmp);
	tmp.copyTo(dst);

	std::vector<std::vector<cv::Point> > contours;
	std::vector<std::vector<cv::Point> > cleanContours;
	std::vector<std::vector<cv::Point> > dirtyContours;
	std::vector<cv::Vec4i> heirarchy;
	cv::findContours(dst, contours, heirarchy, CV_RETR_TREE,
			CV_CHAIN_APPROX_SIMPLE);
	for (size_t i = 0; i < contours.size(); i++) {
		double arc = cv::arcLength(contours[i], true);
		std::vector<cv::Point> newContour;
		cv::approxPolyDP(contours[i], newContour, arc * 0.01, true);

		cv::Rect rect = cv::boundingRect(newContour);
		if (rect.width < rect.height * 5.0) {
			continue;
		}

		uchar cc = dst.at<uchar>((int) (rect.x + (rect.width / 2)),
				(int) (rect.y + (rect.height / 2)));

		double contourAreaRaw = cv::contourArea(contours[i]);
		if (cc <= 0 || contourAreaRaw < 1000 || newContour.size() > 5
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
		printf("%f\t%f\t%f\n", areaDiff / newContourArea, matchLevel,
				rectangularLevel);
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
	cv::drawContours(src, dirtyContours, -1, cv::Scalar(255, 0, 0), 5);
	cv::drawContours(src, cleanContours, -1, cv::Scalar(0, 0, 255), 5);
	cv::cvtColor(tmp, tmp, cv::COLOR_GRAY2RGB);
	cv::drawContours(tmp, dirtyContours, -1, cv::Scalar(255, 0, 0), 5);
	cv::drawContours(tmp, cleanContours, -1, cv::Scalar(0, 0, 255), 5);
	cv::imshow(windowName, src);
	cv::imshow(windowName2, tmp);
#endif
}

int main(int argc, char** argv) {
#if !(HEADLESS)
	cv::namedWindow(windowName);
	cv::namedWindow(windowName2);
#endif

#if VISION
	std::vector<MatchedShape> results;
	size_t i;
	cv::Mat temporaryMaterial;
	ThreadedCapture threadedCapture(1);	//, atoi(argv[1]), atoi(argv[2]));
	int lastFrame = milliTime();
	int frames = 0;
#endif

#if SENSORS
	BMP180 *bmp = new BMP180();
	bmp->calibrate();

	L3GD20 *gyro = new L3GD20();
	gyro->calibrate();

	LSM303_ACC *acc = new LSM303_ACC();
	acc->setup();

	LSM303_MAG *mag = new LSM303_MAG();
	mag->setup();

	FreeIMU *imu = new FreeIMU();
	imu->gyro = gyro;
	imu->baro = bmp;
	imu->acc = acc;
	imu->mag = mag;

	sleep(1);
	imu->init();

	float ypr[3];
#endif

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
#if NETWORK && SENSORS
		imu->getYawPitchRoll(ypr);
		bufferHead += sprintf(buffer + bufferHead,
				"%d/%d\t%d\t%f\t%f\t%f\t%f\n", 1337, 1337, 0, 0.0, ypr[0],
				ypr[1], ypr[2]);
		buffer[bufferHead] = 0;
		network->SendData(buffer);
		bufferHead = 0;
#endif
#if VISION
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
				int ctime = milliTime();
				frames++;
				if (ctime > lastFrame + 5000) {
					// Seconds passed
					printf("FPS: %f\n",
							(float) frames * 1000.0
									/ (float) (ctime - lastFrame));
					lastFrame = ctime;
					frames = 0;
				}
			}
		} else {
			usleep(1000);
		}
#else
		usleep(5000);
#endif
	}
#if !(HEADLESS)
	cv::destroyAllWindows();
#endif
#if NETWORK
	delete network;
	free(buffer);
#endif
#if VISION
	threadedCapture.stop();
#endif
}
