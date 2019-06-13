
#include "memory_callibration_label.h" 

MemoryCallibrationLabel::~MemoryCallibrationLabel()
{
}
 
void MemoryCallibrationLabel::enterEvent ( QEvent *e )
{
}
 
void MemoryCallibrationLabel::leaveEvent ( QEvent *e )
{
}
 
void MemoryCallibrationLabel::mouseMoveEvent ( QMouseEvent *e )
{
    std::cout << "MemoryCallibrationLabel :: mouseMoveEvent event XY : " << e->x() << ", " << e->y() << " \n";

}
 
void MemoryCallibrationLabel::mousePressEvent ( QMouseEvent *e )
{
        std::cout << "MemoryCallibrationLabel :: mousePressEvent event XY : " << e->x() << ", " << e->y() << " \n";

}
 
void MemoryCallibrationLabel::mouseReleaseEvent ( QMouseEvent *e )
{
    std::cout << "MemoryCallibrationLabel :: mouseReleaseEvent event XY : " << e->x() << ", " << e->y() << " \n";

}