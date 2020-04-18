#include "ai.h"
#include <QMessageBox>

//Проверка терминального состояния
bool ai::isTerminal(QVector<QVector<int> > matrix, int deph)
{
    //Условие глубины
    if(level < deph)
    {
        return true;
    }
    //Условие победы
    if(check_win(matrix))
    {
        return true;
    }
    return false;
}

//Проверка победы
bool ai::check_win(QVector<QVector<int>> matrix)
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
                //Вводи счетчик, для подсчета фишек в ряду
                int k = 2;
                //-------Проверки стоят ли фишки в ряд---------
                //Проверка сверху относительно фишки
                while((xx > 0 && xx < size) && k != 0)
                {
                    if(matrix[--xx][y] == matrix[x][y])
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

//Конструктор принимающий уровень глубины и код игрока
ai::ai(int lvl, int code)
{
    codeThisPlayer = code;
    isThisPlayer = true;
    level = lvl;
    cost_FirstPlayer = 0;
    cost_SecondPlayer = 0;
    size = 4;
    rmMatrix.resize(size);
    for (int i(0); i < size; i++)
    {
        rmMatrix[i].resize(size);
    }
}

int ai::cost_Of_Desk(QVector<QVector<int>> matrix)
{
    if(check_win(matrix))
        return 1000;
    else
    {
        return 0;
    }
}

void ai::generate_next_Turn(QVector<QVector<int>> matrix,  QVector<QVector<int>> &prev_X,  QVector<QVector<int>> &prev_Y,  QVector<QVector<int>> &new_X,  QVector<QVector<int>> &new_Y)
{
    //Фишка
    int i = -1;
    //Вариант хода
    int j = 0;
    //Если это компьютер
    if(isThisPlayer)
    {
        //То ищем его фигуру
        for(int x(0); x < size; x++)
        {
            for(int y(0); y < size; y++)
            {
                if(matrix[x][y] == codeThisPlayer)
                {
                    //Проверяем на выход за приделы
                    //И после ищем все возможные варианты ходов для этой фишки
                    i++; j = 0;
                    if(i >= size || j >= size)
                    {
                        x = size;
                        y = size;
                        break;
                    }
                    //Если фишка не у верхней границы
                    if(x > 0 && matrix[x - 1][y] == 0)
                    {
                        prev_X[i][j] = x;
                        prev_Y[i][j] = y;
                        new_X[i][j] = x - 1;
                        new_Y[i][j] = y;
                        j++;
                    }
                    //Если фишка не у нижней границы
                    if(x < size - 1 && matrix[x + 1][y] == 0)
                    {
                        prev_X[i][j] = x;
                        prev_Y[i][j] = y;
                        new_X[i][j] = x + 1;
                        new_Y[i][j] = y;
                        j++;
                    }
                    //Если фишка не у левой границы
                    if(y > 0 && matrix[x][y - 1] == 0)
                    {
                        prev_X[i][j] = x;
                        prev_Y[i][j] = y;
                        new_X[i][j] = x;
                        new_Y[i][j] = y - 1;
                        j++;
                    }
                    //Если фишка не у правой границы
                    if(y < size - 1 && matrix[x][y + 1] == 0)
                    {
                        prev_X[i][j] = x;
                        prev_Y[i][j] = y;
                        new_X[i][j] = x;
                        new_Y[i][j] = y + 1;
                        j++;
                    }
                }
            }
        }
    }
    else if(!isThisPlayer)
    {
        //То ищем его фигуру
        for(int x(0); x < size; x++)
            for(int y(0); y < size; y++)
            {
                if(matrix[x][y] == -codeThisPlayer)
                {
                    i++; j = 0;
                    if(i >= size || j >= size)
                    {
                        x = size;
                        y = size;
                        break;
                    }
                    //Если фишка не у верхней границы
                    if(x > 0 && matrix[x - 1][y] == 0)
                    {
                        prev_X[i][j] = x;
                        prev_Y[i][j] = y;
                        new_X[i][j] = x - 1;
                        new_Y[i][j] = y;
                        j++;
                    }
                    if(x < size - 1 && matrix[x + 1][y] == 0)
                    {
                        prev_X[i][j] = x;
                        prev_Y[i][j] = y;
                        new_X[i][j] = x + 1;
                        new_Y[i][j] = y;
                        j++;
                    }
                    if(y > 0 && matrix[x][y - 1] == 0)
                    {
                        prev_X[i][j] = x;
                        prev_Y[i][j] = y;
                        new_X[i][j] = x;
                        new_Y[i][j] = y - 1;
                        j++;
                    }
                    if(y < size - 1 && matrix[x][y + 1] == 0)
                    {
                        prev_X[i][j] = x;
                        prev_Y[i][j] = y;
                        new_X[i][j] = x;
                        new_Y[i][j] = y + 1;
                        j++;
                    }
                }
            }
    }
}

//Инициализатор массивов хранящих средний ход
void ai::init(QVector<QVector<int>> &prev_X, QVector<QVector<int>> &prev_Y, QVector<QVector<int>> &new_X, QVector<QVector<int>> &new_Y)
{

    //Нули не подходят так как можно ходить на клетку 0,0 в матрице
    //Поэтуму переписываем всё на -1
    for(int x(0); x < size; x++)
        for(int y(0); y < size; y++)
        {
            prev_X[x][y] = -1;
            prev_Y[x][y] = -1;
            new_X[x][y] = -1;
            new_Y[x][y] = -1;
        }
}

//Функиця минимума
int ai::min(QVector<QVector<int> > &matrix, int deph, int alpha, int beta)
{
    //Это не компьютер
    isThisPlayer = false;
    //Проверка терминального состояния
    if(isTerminal(matrix, deph))
    {
        return cost_Of_Desk(matrix);
    }
    //Объявление векторов для хранения следующих ходов
    QVector<QVector<int>> prev_X(size);
    QVector<QVector<int>> prev_Y(size);
    QVector<QVector<int>> new_X(size);
    QVector<QVector<int>> new_Y(size);
    for(int i(0); i < size; i++)
    {
        prev_X[i].resize(size);
        prev_Y[i].resize(size);
        new_X[i].resize(size);
        new_Y[i].resize(size);
    }

    //Иницциализация
    int score = beta;
    init( prev_X, prev_Y, new_X, new_Y);
    generate_next_Turn(matrix, prev_X, prev_Y, new_X, new_Y);

    //Перебираем сгенерированные ходы
    for(int x(0); x < size; x++)
        for(int y(0); y < size; y++)
        {
            if(prev_X[x][y] != -1 && prev_Y[x][y] != -1)
            {
                //Создаем временную матрицу
                QVector<QVector<int>> temp_Matrix(size);
                for (int i(0); i < size; i++)
                {
                    temp_Matrix[i].resize(size);
                }
                //Делаем копию оригинальной
                temp_Matrix = matrix;
                //Делаем ход
                temp_Matrix[prev_X[x][y]][prev_Y[x][y]] = 0;
                temp_Matrix[new_X[x][y]][new_Y[x][y]] = -codeThisPlayer;
                //Отправляем в рекурсию
                int s = max(temp_Matrix, deph + 1, alpha, score);
                isThisPlayer = false;
                //Проверяем рекорд, если лучше, устанавливаем
                if(s < score)
                    score = s;
                //Условие выхода по остечению
                if(score <= alpha)
                    return score;
            }
        }
    //Возвращаем рекорд
    return score;
}

//Функция макса
int ai::max(QVector<QVector<int>> &matrix, int deph, int alpha, int beta)
{
    //Это компьютер
    isThisPlayer = true;
    //Проверка терминального состояния
    if(isTerminal(matrix, deph))
    {
        return -cost_Of_Desk(matrix);
    }
    //Объявление векторов для хранения следующих ходов
    QVector<QVector<int>> prev_X(size);
    QVector<QVector<int>> prev_Y(size);
    QVector<QVector<int>> new_X(size);
    QVector<QVector<int>> new_Y(size);
    for(int i(0); i < size; i++)
    {
        prev_X[i].resize(size);
        prev_Y[i].resize(size);
        new_X[i].resize(size);
        new_Y[i].resize(size);
    }

    //Иницциализация
    int score = alpha;
    init( prev_X, prev_Y, new_X, new_Y);
    generate_next_Turn(matrix, prev_X, prev_Y, new_X, new_Y);

    //Перебираем сгенерированные ходы
    for(int x(0); x < size; x++)
        for(int y(0); y < size; y++)
        {
            if(prev_X[x][y] != -1 && prev_Y[x][y] != -1)
            {
                //Создаем временную матрицу
                QVector<QVector<int>> temp_Matrix(size);
                for (int i(0); i < size; i++)
                {
                    temp_Matrix[i].resize(size);
                }
                //Делаем копию оригинальной
                temp_Matrix = matrix;
                //Делаем ход
                temp_Matrix[prev_X[x][y]][prev_Y[x][y]] = 0;
                temp_Matrix[new_X[x][y]][new_Y[x][y]] = codeThisPlayer;
                //Проверяем не победа ли, если да и глубина 0, то сразу его выполняем без рекурсии
                if(deph == 0 && check_win(temp_Matrix))
                {
                    x = size;
                    y = size;
                    score = 10000;
                    rmMatrix = temp_Matrix;
                }
                //Если не победный ход
                else
                {
                    //Отправляем в рекурсию
                    int s = min(temp_Matrix, deph + 1, score, beta);
                    //Проверяем рекорд, если лучше, устанавливаемы
                    if(s > score)
                    {
                        //При 0 глубине отмечаем этот ход как лучший
                        if(deph == 0)
                            rmMatrix = temp_Matrix;
                        score = s;
                    }
                    //Условие выхода по остечению
                    if(score >= beta)
                    {
                        //При 0 глубине отмечаем этот ход как лучший и передаем в оригинальную матрицу
                        if(deph == 0)
                            matrix = temp_Matrix;
                        return score;
                    }
                }
            }
        }
    //При 0 глубине отмечаем этот ход как лучший и передаем в оригинальную матрицу
    if(deph == 0)
         matrix = rmMatrix;
    return score;
}
