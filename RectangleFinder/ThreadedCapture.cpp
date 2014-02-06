#include "ThreadedCapture.h"

#include <pthread.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <unistd.h>
#include <stdio.h>

void *captureImageExternal(void *ptr) {
	((ThreadedCapture*) ptr)->captureInternal();
	return NULL;
}

ThreadedCapture::ThreadedCapture(int device, int width, int height) {
	// Create capture
	this->width = width;
	this->height = height;
	cap = new cv::VideoCapture(device);
	printf("FRAME WIDTH TO %dx%d\n", width, height);
	cap->set(CV_CAP_PROP_FRAME_WIDTH, 960);
	cap->set(CV_CAP_PROP_FRAME_HEIGHT, 540);
	if (!cap->isOpened()) {
		printf("Failed to connect to the camera.\n");
		return;
	}

	// Begin capture thread
	runTheThread = true;
	capturedOne = false;
	pthread_mutexattr_t mutexAttr;
	pthread_attr_t threadAttr;
	pthread_mutexattr_init(&mutexAttr);
	pthread_attr_init(&threadAttr);

	pthread_mutex_init(&imageMutex, &mutexAttr);
	pthread_create(&imageCaptureThread, &threadAttr, &(captureImageExternal),
			this);
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
		//usleep(5000);
	}
	return;
}

void ThreadedCapture::getCaptured(cv::Mat* dest) {
	pthread_mutex_lock(&imageMutex);
	cv::resize(src, *(dest), cv::Size(width, height), (float) width / src.cols,
			(float) height / src.rows);
	capturedOne = false;
	pthread_mutex_unlock(&imageMutex);
}

void ThreadedCapture::stop() {
	runTheThread = false;
	void* returnValue;
	pthread_join(imageCaptureThread, &returnValue);
}
