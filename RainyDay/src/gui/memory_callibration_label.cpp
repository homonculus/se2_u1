
#include "memory_callibration_label.h" 
#include <algorithm>

void MemoryCallibrationLabel::createPoints(){
	std::cout << "MemoryCallibrationLabel::createPoints\n";
	std::vector<QPoint> p;
	p.push_back(QPoint(100, 100));
	p.push_back(QPoint(412, 100));
	p.push_back(QPoint(100, 324));
	p.push_back(QPoint(412,324));
	for (int i=0;i<4;i++){
		QPoint *qpoint= new QPoint(p[i].x(), p[i].y());
		_points.push_back(qpoint);
		QPoint *qpointOuter= new QPoint(p[i].x(), p[i].y());
		_points_outer.push_back(qpointOuter);
	}
	_dragging = false;

}

bool MemoryCallibrationLabel::_pointIsWithinRadius(QPoint p1, QPoint p2, int r){
    if ((std::abs(p1.x() - p2.x())<r) && (std::abs(p1.y()-p2.y())<r)){
        return true;
    }
    return false;
}

std::vector<QPoint*> MemoryCallibrationLabel::getHandlePoints(){

	return _points;
}

MemoryCallibrationLabel::~MemoryCallibrationLabel(){

}
 
void MemoryCallibrationLabel::enterEvent ( QEvent *e ){
}
 
void MemoryCallibrationLabel::leaveEvent ( QEvent *e ){
}
 
void MemoryCallibrationLabel::mouseMoveEvent ( QMouseEvent *e ){
    std::cout << "MemoryCallibrationLabel :: mouseMoveEvent event XY : " << e->x() << ", " << e->y() << " \n";
    if (_dragging){
    	_points[_draggingIdx]->setX(e->x());
    	_points[_draggingIdx]->setY(e->y());

    	int x;
    	int y;
    	if (_draggingIdx == 0 || _draggingIdx == 2){
    		x = std::max(e->x() - 40, 0);
    	}
    	else{
    		x = std::min(e->x() + 40, this->width());
    	}
    	if (_draggingIdx <2){
    		y = std::max(e->y() - 40,0);
    	}
    	else{
    		y = std::min(e->y() + 40, this->height());
    	}
    	_points_outer[_draggingIdx]->setX(e->x());
    	_points_outer[_draggingIdx]->setY(e->y());
    	// _outerHandles[_draggingIdx]->move(x,y);
    	this->delegate->updateMemoryCallibrationLabelRects(this->idx);
    }
}
 
void MemoryCallibrationLabel::mousePressEvent ( QMouseEvent *e ){
	QPoint p = QPoint(e->x(), e->y());
	for (int i=0; i<_points.size(); i++){
		if (_pointIsWithinRadius(*_points[i],p, 30)){
			_dragging = true;
			_draggingIdx = i;
			break;
		}
		else{
		}
	}
}
 
void MemoryCallibrationLabel::mouseReleaseEvent ( QMouseEvent *e ){
	if (_dragging){
		_dragging = false;
		_draggingIdx = -1;
	}
}

