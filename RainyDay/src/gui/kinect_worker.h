
#ifndef KINECTWORKER_H
#define KINECTWORKER_H

#include "kinect_controller.h"
#include <QObject>

class KinectWorker : public QObject {
	    Q_OBJECT
	public:
	    KinectWorker();
	    ~KinectWorker();
	public slots:
	    void process();
	signals:
	    void finished();
	    void error(QString err);
	private:
		KinectController* _kinectController;
};

#endif // KINECTWORKER_H
