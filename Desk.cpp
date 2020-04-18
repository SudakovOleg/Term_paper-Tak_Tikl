#include "Desk.h"
#include <QGridLayout>
#include <QMessageBox>
#include "style.cpp"

//Генерирует таблицу стилей для каждой кнопки
//Принимает цвет клетки и номер игрока
//Возвращает строку с кодом стиля
QString Desk::genericStyleSheet(bool isWhite, int num_Player)
{
    QString color_Of_Cell;
    QString player_Color;
    //Присваеваем цвет клетке
    if(isWhite)
    {
        color_Of_Cell = COLOR_WHITE;
    }
    else
    {
        color_Of_Cell = COLOR_BLACK;
    }
    //Присваиваем цвет фишке
    if(num_Player == 1)
    {
        player_Color = WHITE_PLAYER_COLOR;
    }
    else {
        player_Color = BLACK_PLAYER_COLOR;
    }
    QString css ("QPushButton {"
                "border: 1px solid #000000;"
                "border-radius: 1px;"
                "text-align: center;"
                "color: " + player_Color + ";"
                "background-color: " + color_Of_Cell + ";"
                "}"

                "QPushButton:disabled {"
                "border: 1px solid #000000;"
                "border-radius: 1px;"
                "color: " + player_Color + ";"
                "background-color: #f80000;"
                "}" );
    return css;
}

//Проверка на конец игры(Победу)
//Возвращает булево значение
bool Desk::check_win()
{
    //Ищем фишку
    for(int x(0); x < size; x++)
    {
        for(int y(0); y < size; y++)
        {
            if(matrix[x][y] != 0)
            {
                //Запоминаем координаты фишки
                int xx = x;
                int yy = y;
                //Вводим счетчик, для подсчета фишек в ряду
                int k = 2;
                //-------Проверки стоят ли фишки в ряд---------
                //Проверка сверху относительно фишки
                while((xx > 0 && xx < size) && k != 0)
                {
                    //Если есть фишка
                    if(matrix[--xx][y] == matrix[x][y])
                    {
                        //Уменьшаем счетчик и проверяем достаточно ли фишек
                        //для победы
                        if(--k == 0)
                        {
                            return true;
                        }
                    }
                    //Если фишек больше нету, выходим из цикла
                    else
                    {
                        break;
                    }
                }
                //Восполняем временные переменные
                xx = x;
                k = 2;
                //Проверка снизу относительно фишки
                while((xx >= 0 && xx < size - 1) && k != 0)
                {
                    if(matrix[++xx][y] == matrix[x][y])
                    {
                        if(--k == 0)
                        {
                            return true;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                xx = x;
                k = 2;
                //Проверка слева относительно фишки
                while((yy > 0 && yy < size) && k != 0)
                {
                    if(matrix[x][--yy] == matrix[x][y])
                    {
                        if(--k == 0)
                        {
                            return true;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                yy = y;
                k = 2;
                //Проверка справа относительно фишки
                while((yy >= 0 && yy < size - 1) && k != 0)
                {
                    if(matrix[x][++yy] == matrix[x][y])
                    {
                        if(--k == 0)
                        {
                            return true;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                yy = y;
                k = 2;
                //Проверка вниз по второстепенной диагонали относительно фишки
                while((yy > 0 && yy < size) && (xx > 0 && xx < size) && k != 0)
                {
                    if(matrix[--xx][--yy] == matrix[x][y])
                    {
                        if(--k == 0)
                        {
                            return true;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                yy = y;
                xx = x;
                k = 2;
                //Проверка вверх по второстепенной диагонали относительно фишки
                while((yy >= 0 && yy < size - 1) && (xx >= 0 && xx < size - 1) && k != 0)
                {
                    if(matrix[++xx][++yy] == matrix[x][y])
                    {
                        if(--k == 0)
                        {
                            return true;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                yy = y;
                xx = x;
                k = 2;
                //Проверка вниз по главной диагонали относительно фишки
                while((yy > 0 && yy < size) && (xx >= 0 && xx < size - 1) && k != 0)
                {
                    if(matrix[++xx][--yy] == matrix[x][y])
                    {
                        if(--k == 0)
                        {
                            return true;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                yy = y;
                xx = x;
                k = 2;
                //Проверка вверх по главной диагонали относительно фишки
                while((yy >= 0 && yy < size - 1) && (xx > 0 && xx < size) && k != 0)
                {
                    if(matrix[--xx][++yy] == matrix[x][y])
                    {
                        if(--k == 0)
                        {
                            return true;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                //------------
            }
        }
    }
    //Если ни одна из проверок не пройдена, игра не окончена
    return false;
}

//Конструктор
//Принимает указатель на виджет-родителя, имена игроков
Desk::Desk(QWidget *parent)
    : QDialog(parent)
{
    botRobert = new ai(6, -1);
    //Фишка не выбрана
    isClicked = false;
    //Задаем размер поля
    size = 4;
    //Выделяем память под слоя, кнопки и матрицу
    lay = new QGridLayout;
    cell = new QPushButton*[size];
    matrix.resize(size);
    for (int i(0); i < size ; i++)
    {
        cell[i] = new QPushButton[size];
        matrix[i].resize(size);
        for(int j(0); j < size; j++)
        {
            connect(&cell[i][j], SIGNAL(clicked()), SLOT(Turn()));
        }
    }
    //Инициализируем матрицу (Начальное положение фишек)
    int temp_count_player = 1;
    for (int i(0); i < size ; i++)
    {
        for(int j(0); j < size; j++)
        {
            if(i == 0)
            {
                if(temp_count_player == 1)
                {
                    temp_count_player-=2;
                    matrix[i][j] = temp_count_player;
                }
                else
                {
                    temp_count_player+=2;
                    matrix[i][j] = temp_count_player;
                }
            }
            else if (i == size - 1)
            {
                if(temp_count_player == 1)
                {
                    matrix[i][j] = temp_count_player;
                    temp_count_player-=2;
                }
                else
                {
                    matrix[i][j] = temp_count_player;
                    temp_count_player+=2;
                }
            }
            else
            {
                matrix[i][j] = 0;
            }
        }
    }
    //Отрисовываем поле
    drow_Desk();
}

//Отрисовка поля
void Desk::drow_Desk()
{
    for (int i(0); i < size ; i++)
    {
        for(int j(0); j < size; j++)
        {
            //Ставим фишку
            if(matrix[i][j] != 0)
            {
                cell[i][j].setText(QString::fromUtf8("•"));
            }
            else
            {
                cell[i][j].setText("");
            }
            //Устанавливаем шрифт (Размер фишки)
            QFont font;
            font.setPixelSize(SIZE_FONT);
            cell[i][j].setFont(font);
            //Фиксируем размер клетки
            cell[i][j].setFixedSize(SIZE_CELL,SIZE_CELL);
            //Генерируем на основе данных цвет фишки и клетки
            cell[i][j].setStyleSheet(genericStyleSheet((i+j)%2, matrix[i][j]));
            //Подставляем клетку в слой
            lay->addWidget(&cell[i][j], i, j);
        }
    }
    //Делаем нулевой отступ между клетками
    lay->setSpacing(0);
    //Устанавливаем слой на окно
    this->setLayout(lay);
}

//Слот принимающий сигнал нажатия на клетку поля
void Desk::Turn()
{
    //Если фишка ещё не нажата
    if(!isClicked)
    {
        //Ищем кнопку отправившую сигнал
        for(int x(0); x < size; x++)
            for(int y(0); y < size; y++)
            {
                //Запоминаем ее координаты
                if((QPushButton*)sender() == &cell[x][y])
                {
                    mX = x;
                    mY = y;
                    //Если фишка не первого игрока
                    if(matrix[x][y] != 1)
                        return;
                    //Выходим из цикла
                    x = size + 1;
                    break;
                }
            }
        //Блокируем все кнопки кроме доступных для хода
        for(int x(0); x < size; x++)
            for(int y(0); y < size; y++)
            {
                if(!((x == mX + 1 && mY == y) || (x == mX - 1 && mY == y) || (y == mY + 1 && mX == x) || (y == mY - 1 && mX == x)) || matrix[x][y] != 0)
                {
                    //Блокируем кнопки
                    cell[x][y].setEnabled(false);
                }
            }
        cell[mX][mY].setEnabled(true);
        //Поднимаем флаг
        isClicked = true;
    }
    //Если фишка уже выбрана
    else
    {
        //Ищем кнопку отправившую сигнал
        for(int x(0); x < size; x++)
            for(int y(0); y < size; y++)
            {
                if((QPushButton*)sender() == &cell[x][y])
                {
                    if(x == mX && y == mY)
                    {
                        //Если это таже самая кнопка
                        isClicked = false;
                        for(int i(0); i < 4; i++)
                            for(int j(0); j < 4; j++)
                            {
                                //Разблокируем все кнопки
                                cell[i][j].setEnabled(true);
                            }
                        //Выходим из слота
                        return;
                    }
                    else
                    {
                        //Иначе ставим фишку и выходим из цикла
                        matrix[x][y] = 1;
                        //Выходим из цикла
                        x = size + 1;
                        break;
                    }
                }
            }

        //Убираем фишку с клетки нажатой до этого
        matrix[mX][mY] = 0;
        //Опускаем флаг
        isClicked = false;
        for(int i(0); i < 4; i++)
            for(int j(0); j < 4; j++)
            {
                //Разблокируем кнопки
                cell[i][j].setEnabled(true);
            }

        //Проверяем есть ли победа
        if(check_win())
        {
            for(int i(0); i < 4; i++)
                for(int j(0); j < 4; j++)
                {
                    //Блокируем кнопки
                    cell[i][j].setEnabled(false);
                }
            QMessageBox::information(nullptr, "Победа", "Белые победили");
        }
        //Ход бота
        botRobert->max(matrix, 0, -10000, 10000);
        //Проверяем есть ли победа
        if(check_win())
        {
            for(int i(0); i < 4; i++)
                for(int j(0); j < 4; j++)
                {
                    //Блокируем кнопки
                    cell[i][j].setEnabled(false);
                }
            QMessageBox::information(nullptr, "Победа", "Черные победили");
        }
        //Рисуем поле
        drow_Desk();
    }
}

//Диструктор
Desk::~Desk()
{
    for(int i(0); i < size; i++)
    {
        delete[]cell[i];
    }
    delete cell;
    delete lay;
    delete botRobert;
}
