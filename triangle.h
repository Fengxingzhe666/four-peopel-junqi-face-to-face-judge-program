#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QWidget>
#include <QColor>

namespace Ui {
class Triangle;
}

class QPainterPath;

class Triangle : public QWidget
{
    Q_OBJECT

public:
    explicit Triangle(int x, int y, int width, int height, const QColor &color = Qt::red, QWidget *parent = nullptr);
    ~Triangle();
    void setTriangleColor(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::Triangle *ui;
    QColor triangleColor;
    int triangleWidth;
    int triangleHeight;
};

#endif // TRIANGLE_H
