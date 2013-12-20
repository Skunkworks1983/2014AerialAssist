#include "ThreadedCapture.h"

#include <pthread.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <unistd.h>

void *captureImageExternal(void *ptr) {
	((ThreadedCapture*) ptr)->captureInternal();
	return NULL;
}

ThreadedCapture::ThreadedCapture(int device) {
	// Create capture
	cap = new cv::VideoCapture(device);

	// Begin capture thread
	runTheThread = true;
	capturedOne = false;
	pthread_mutexattr_t mutexAttr;
	pthread_attr_t threadAttr;
	pthread_mutexattr_init(&mutexAttr);
	pthread_attr_init(&threadAttr);

	pthread_mutex_init(&imageMutex, &mutexAttr);
	pthread_create(&imageCaptureThread, &threadAttr, &(captureImageExternal), this);
}

ThreadedCapture::~ThreadedCapture() {
	delete cap;
}

void ThreadedCapture::captureInternal() {
	while (runTheThread) {
		pthread_mutex_lock(&imageMutex);
		*(cap) >> src;
		capturedOne = !src.empty();
		pthread_mutex_unlock(&imageMutex);
		usleep(10000);
	}
	return;
}

void ThreadedCapture::getCaptured(cv::Mat* dest) {
	pthread_mutex_lock(&imageMutex);
	src.copyTo(*(dest));
	pthread_mutex_unlock(&imageMutex);
}

void ThreadedCapture::stop() {
	runTheThread = false;
	void* returnValue;
	pthread_join(imageCaptureThread, &returnValue);
}
