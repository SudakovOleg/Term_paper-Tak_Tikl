#ifndef DESK_H
#define DESK_H

#include <QDialog>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include "ai.h"

class Desk : public QDialog
{
    Q_OBJECT
private:
    //Слой для размещения виджетов
    QGridLayout *lay;
    //Клетки поля
    QPushButton **cell;
    //Размер поля
    int size;
    //Матрица игры
    QVector<QVector<int>> matrix;
    //Флаг и переменные временного хранения
    bool isClicked;
    int mX, mY;
    //Бот
    ai *botRobert;
private:
    //Стиль поля
    QString genericStyleSheet(bool isWhite, int num_Player);
    //Проверка победы
    bool check_win();
public:
    //Конструктор
    Desk(QWidget *parent);
    //Отрисовка поля
    void drow_Desk();
    //Диструктор
    ~Desk();
public slots:
    //Слот хода игрока
    void Turn();
};

#endif // WIDGET_H
