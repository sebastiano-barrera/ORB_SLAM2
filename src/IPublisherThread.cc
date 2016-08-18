//
// Created by sebastiano on 8/18/16.
//

#include "IPublisherThread.h"

using namespace std;
using namespace ORB_SLAM2;

IPublisherThread::IPublisherThread() :
    mbStopped(false), mbStopRequested(false),
    mbFinishRequested(false), mbFinished(true)
{ }

// The virtual destructor forces the class to be abstract
IPublisherThread::~IPublisherThread()
{}

void IPublisherThread::RequestStop()
{
    unique_lock<mutex> lock(mMutexStop);
    if(!mbStopped)
        mbStopRequested = true;
}

bool IPublisherThread::isStopped()
{
    unique_lock<mutex> lock(mMutexStop);
    return mbStopped;
}

void IPublisherThread::Release()
{
    unique_lock<mutex> lock(mMutexStop);
    mbStopped = false;
}

bool IPublisherThread::Stop()
{
    unique_lock<mutex> lock(mMutexStop);
    unique_lock<mutex> lock2(mMutexFinish);

    if(mbFinishRequested)
        return false;
    else if(mbStopRequested)
    {
        mbStopped = true;
        mbStopRequested = false;
        return true;
    }

    return false;

}

bool IPublisherThread::isFinished()
{
    unique_lock<mutex> lock(mMutexFinish);
    return mbFinished;
}

void IPublisherThread::RequestFinish()
{
    unique_lock<mutex> lock(mMutexFinish);
    mbFinishRequested = true;
}

bool IPublisherThread::CheckFinish()
{
    unique_lock<mutex> lock(mMutexFinish);
    return mbFinishRequested;
}

void IPublisherThread::SetFinish(bool value)
{
    unique_lock<mutex> lock(mMutexFinish);
    mbFinished = value;
}
