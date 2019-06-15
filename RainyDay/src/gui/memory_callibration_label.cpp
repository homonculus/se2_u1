
#include "memory_callibration_label.h" 
#include <algorithm>

void MemoryCallibrationLabel::createPoints(){

 //    _p1 = new QLabel();
	// _p1->setStyleSheet("QLabel { background-color : red; color : blue; }");
 //    _p1->setFixedHeight(30);
	// _p1->setFixedWidth(30);
	// // _p1->move(50, 50);
	// _p1->setGeometry(50,50,50,50);
	for (int y=0;y<2;y++){
		for (int x=0;x<2;x++){
			CallibrationPoint *p = new CallibrationPoint();
			p->center.x = x*100;
			p->center.y = y*100;
			p->idx = x*2 + y; 
			_points.push_back(p);

			CallibrationPoint *p2 = new CallibrationPoint();
			p2->idx = x*2 + y; 
			_outerPoints.push_back(p2);

			QLabel *label1 = new QLabel(this);
			label1->setStyleSheet("QLabel { background-color : red; color : blue; border-radius: 10px}");
			label1->setFixedHeight(20);
			label1->setFixedWidth(20);
		    label1->move(x*100, y*100);
		    label1->show();
		    _handles.push_back(label1);

		    QLabel *label2 = new QLabel(this);
			label2->setStyleSheet("QLabel { background-color : green; color : blue; border-radius: 10px}");
			label2->setFixedHeight(20);
			label2->setFixedWidth(20);
		    label2->move(x*100, y*100);
		    label2->show();
		    _outerHandles.push_back(label2);
		}
	}
	_dragging = false;

}

std::vector<CallibrationPoint*>* MemoryCallibrationLabel::getPoints(){
	return &_points;
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
    	_draggingPoint->center.x = e->x();
    	_draggingPoint->center.y = e->y();
    	_draggingHandle->move( e->x(),  e->y());

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


    	_outerHandles[_draggingIdx]->move(x,y);
    }
}
 
void MemoryCallibrationLabel::mousePressEvent ( QMouseEvent *e ){
	Point p = {e->x(), e->y()};
    std::cout << "MemoryCallibrationLabel :: mousePressEvent event XY : " << e->x() << ", " << e->y() << " \n";
	for (int i=0; i<_points.size(); i++){
		if (_points[i]->pointIsWithinRadius(p, 30)){
			std::cout << "MemoryCallibrationLabel :: mousePressEvent WITHIN: " << i << " \n";
			_dragging = true;
			_draggingPoint = _points[i];
			_draggingHandle = _handles[i];
			_draggingIdx = i;
			break;
		}
		else{
			std::cout << "MemoryCallibrationLabel :: mousePressEvent NOT IN: " << i << " \n";
		}
	}
}
 
void MemoryCallibrationLabel::mouseReleaseEvent ( QMouseEvent *e ){
	if (_dragging){
		_dragging = false;
		_draggingIdx = -1;
	}
    std::cout << "MemoryCallibrationLabel :: mouseReleaseEvent event XY : " << e->x() << ", " << e->y() << " \n";
}

