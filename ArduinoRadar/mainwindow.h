#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QtWidgets>
#include <QtGui>
#include <QtMath>
#include <QObject>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void readSerial();

private:
    QGraphicsScene *scene;
    QPixmap pix;
    float currAngle;
    const float r;
    const float angleOffset;
    float t_up;
    float t_lo;
    QPolygonF triangle, detectedItem;
    QGraphicsPolygonItem *needle, *needleDetected;
    QSerialPort *arduino;
    Ui::MainWindow *ui;
    static const quint16 arduino_uno_vendorID = 9025;
    static const quint16 arduino_uno_productID = 67;
    QString arduino_port_name;
    bool arduino_is_available;
    QByteArray serialData;
    QString serialBuffer;
    QString servoSetting;
};
#endif // MAINWINDOW_H
