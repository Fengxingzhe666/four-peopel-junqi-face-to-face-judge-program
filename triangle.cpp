#include "triangle.h"
#include "ui_triangle.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QtGlobal> // 添加这一行

Triangle::Triangle(int x, int y, int width, int height, const QColor &color, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Triangle),triangleWidth(width), triangleHeight(height), triangleColor(color)
{
    //ui->setupUi(this);
    setGeometry(x, y, width, height);
}

Triangle::~Triangle()
{
    delete ui;
}

void Triangle::setTriangleColor(const QColor &color)
{
    triangleColor = color;
    update(); // 触发重绘
}

void Triangle::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPolygon triangle;
    triangle.append(QPoint(triangleWidth / 2, 0));
    triangle.append(QPoint(0, triangleHeight));
    triangle.append(QPoint(triangleWidth, triangleHeight));

    QBrush brush(triangleColor);
    painter.setBrush(brush);
    painter.drawPolygon(triangle);
}

void Triangle::mousePressEvent(QMouseEvent *event)
{
    // if (event->button() == Qt::LeftButton)
    // {
    //     qDebug() << "三角形被点击";
    //     // 这里可以添加点击后的其他逻辑，例如改变颜色
    //
    // }
}
