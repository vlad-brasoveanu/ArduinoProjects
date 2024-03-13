#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , r(445.0)
    , angleOffset(0.1)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    pix = QPixmap(":/src/radar.png");
    scene->addPixmap(pix);

    arduino = new QSerialPort;
    arduino_is_available = false;
    arduino_port_name = "";

    QPen outlineGreen(Qt:: darkGreen);
    QBrush fillGreen(Qt:: green);
    QPen outlineRed(Qt:: darkRed);
    QBrush fillRed(Qt:: red);
    detectedItem.append(QPointF(0,0));
    detectedItem.append(QPointF(0,0));
    detectedItem.append(QPointF(0,0));
    detectedItem.append(QPointF(0,0));
    needleDetected = scene->addPolygon(detectedItem, outlineRed, fillRed);
    needleDetected->setOpacity(0);
    t_up = angleOffset;
    t_lo = -angleOffset;
    triangle.append(QPointF(r*qCos(t_up) + 505, -r*qSin(t_up) + 495));
    triangle.append(QPointF(505,495));
    triangle.append(QPointF(r*qCos(t_lo) + 505, -r*qSin(t_lo) + 495));
    needle = scene->addPolygon(triangle, outlineGreen, fillGreen);
    needle->setOpacity(0.30);

    //check which port the arduino is on
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        if (serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier())
        {
            if (serialPortInfo.vendorIdentifier() == arduino_uno_vendorID)
            {
                if (serialPortInfo.productIdentifier() == arduino_uno_productID)
                {
                    arduino_port_name = serialPortInfo.portName();
                    arduino_is_available = true;
                    qDebug() << "Port available!";
                }
            }
        }
    }

    //setup port if available
    if (arduino_is_available)
    {
        //open and configure port
        arduino->setPortName(arduino_port_name);
        arduino->open(QSerialPort::ReadOnly);
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
        //slot for updating value
        QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));
    }
    else
    {
        QMessageBox::warning(this, "Port error", "Couldn't find arduino");
    }
}

float lastAngle = 1000;

struct data{
    float d, angle;
    int ok = 0;
    QGraphicsPolygonItem *p;
}dataRed[315];

void MainWindow::readSerial(){
    QStringList bufferSplit = serialBuffer.split("\r\n");
    if (bufferSplit.length() < 2)
    {
        serialData = arduino->readAll();
        serialBuffer += QString::fromStdString(serialData.toStdString());
    }
    else
    {
        std::string ch = bufferSplit[0].toStdString();
        char distance[5], angle[5];
        strncpy(distance, ch.c_str(), 4);
        strcpy(angle, ch.c_str()+5);
        if(strcmp(distance, "0.00"))
            ui->distance_value->setText(distance);
        else
            ui->distance_value->setText("Too far away");
        QString ang(angle);
        ui->angle_value->setText(ang);
        currAngle = ui->angle_value->text().toFloat();
        currAngle = qDegreesToRadians(currAngle);
        int k = currAngle*100;
        if(k == 10 || k == 300)
        {
            for(int t = 0; t <= 314; t++)
            {
                if(dataRed[t].ok == 1)
                {
                    t_up = dataRed[t].angle + angleOffset/2;
                    t_lo = dataRed[t].angle - angleOffset/2;
                    detectedItem[0]=QPointF(r*qCos(t_up) + 505, -r*qSin(t_up) + 495);
                    detectedItem[1]=QPointF(dataRed[t].d*10*qCos(t_up) + 505, -dataRed[t].d*10*qSin(t_up) + 495);
                    detectedItem[2]=QPointF(dataRed[t].d*10*qCos(t_lo) + 505, -dataRed[t].d*10*qSin(t_lo) + 495);
                    detectedItem[3]=QPointF(r*qCos(t_lo) + 505, -r*qSin(t_lo) + 495);
                    needleDetected->setPolygon(detectedItem);
                    scene->removeItem(dataRed[t].p);
                    dataRed[t].ok = 0;
                }
            }
        }
        float dist = 0;
        for(int i = 0; i < (int)strlen(distance)-2; i++)
        {
            dist += dist * 10 + (distance[i] - '0');
        }
        if(dist < 0 && dist > 30)
            dist = 0;
        if (dist < 30 && dist >= 1)
        {
            QPen outlineRed(Qt:: darkRed);
            QBrush fillRed(Qt:: red);
            if((currAngle < (lastAngle - angleOffset*0.75))  || (currAngle > (lastAngle + angleOffset*0.75)))
            {
                t_up = currAngle + angleOffset/2;
                t_lo = currAngle - angleOffset/2;
                detectedItem[0]=QPointF(r*qCos(t_up) + 505, -r*qSin(t_up) + 495);
                detectedItem[1]=QPointF(dist*10*qCos(t_up) + 505, -dist*10*qSin(t_up) + 495);
                detectedItem[2]=QPointF(dist*10*qCos(t_lo) + 505, -dist*10*qSin(t_lo) + 495);
                detectedItem[3]=QPointF(r*qCos(t_lo) + 505, -r*qSin(t_lo) + 495);
                needleDetected = scene->addPolygon(detectedItem, outlineRed, fillRed);
                needleDetected->setOpacity(0.7);
                int i = currAngle*100;
                lastAngle = currAngle;
                dataRed[i].angle = currAngle;
                dataRed[i].ok = 1;
                dataRed[i].d = dist;
                dataRed[i].p = needleDetected;
            }
        }
        t_up = currAngle + angleOffset;
        t_lo = currAngle - angleOffset;
        triangle[0] = QPointF(r*qCos(t_up) + 505, -r*qSin(t_up) + 495);
        triangle[2] = QPointF(r*qCos(t_lo) + 505, -r*qSin(t_lo) + 495);
        needle->setPolygon(triangle);
        serialBuffer = "";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
