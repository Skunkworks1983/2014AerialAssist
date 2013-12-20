#ifndef __THREADED_CAPTURE_H
#define __THREADED_CAPTURE_H

#include <pthread.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class ThreadedCapture {
private:
	pthread_mutex_t imageMutex;
	pthread_t imageCaptureThread;
	cv::Mat src;
	cv::VideoCapture *cap;
	bool runTheThread;
	bool capturedOne;
public:
	ThreadedCapture(int device = -1);
	~ThreadedCapture();
	void getCaptured(cv::Mat *dest);
	inline bool hasCaptured() {
		return capturedOne;
	}
	void stop();
	void captureInternal();
};
#endif
