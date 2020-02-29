#include "ai.h"
#include <QMessageBox>

bool ai::isTerminal(int **matrix, int deph)
{
    if(level < deph)
    {
        return true;
    }
    if(check_win(matrix))
    {
        return true;
    }
    return false;
}

bool ai::check_win(int** matrix)
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

void ai::clear(int** prev_X, int** prev_Y, int** new_X, int** new_Y)
{
    for(int x(0); x < size; x++)
        for(int y(0); y < size; y++)
        {
            prev_X[x][y] = -1;
            prev_Y[x][y] = -1;
            new_X[x][y] = -1;
            new_Y[x][y] = -1;
        }
}

ai::ai(int lvl, int code)
{
    codeThisPlayer = code;
    isThisPlayer = true;
    level = lvl;
    cost_FirstPlayer = 0;
    cost_SecondPlayer = 0;
    size = 4;
    rmMatrix = new int*[size];
    for (int i(0); i < size; i++)
    {
        rmMatrix[i] = new int[size];
    }
}

ai::~ai()
{
    for (int i(0); i < size; i++)
    {
        delete [] rmMatrix[i];
    }
    delete [] rmMatrix;
}

int ai::cost_Of_Desk(int **matrix)
{
    if(check_win(matrix))
        return 1000;
    else
    {
        return 0;
    }
}

void ai::generate_next_Turn(int **matrix, int** prev_X, int** prev_Y, int** new_X, int** new_Y)
{
    int i = -1;
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

void ai::copyMatrix(int **old_Matrix, int **new_Matrix,int size)
{
    for(int x(0); x < size; x++)
        for(int y(0); y < size; y++)
        {
            new_Matrix[x][y] = old_Matrix[x][y];
        }
}

int ai::min(int **matrix,int deph, int alpha, int beta)
{
    isThisPlayer = false;
    if(isTerminal(matrix, deph))
    {
        return cost_Of_Desk(matrix);
    }
    int **prev_X = new int*[size];
    int **prev_Y = new int*[size];
    int **new_X = new int*[size];
    int **new_Y = new int*[size];
    for (int i(0); i < size; i++)
    {
        prev_X[i] = new int[size];
        prev_Y[i] = new int[size];
        new_X[i] = new int[size];
        new_Y[i] = new int[size];
    }
    int score = beta;
    clear(prev_X, prev_Y, new_X, new_Y);
    generate_next_Turn(matrix, prev_X, prev_Y, new_X, new_Y);
    for(int x(0); x < size; x++)
        for(int y(0); y < size; y++)
        {
            if(prev_X[x][y] != -1 && prev_Y[x][y] != -1)
            {
                int** temp_Matrix = new int*[size];
                for (int i(0); i < size; i++)
                {
                    temp_Matrix[i] = new int[size];
                }
                copyMatrix(matrix, temp_Matrix, size);
                temp_Matrix[prev_X[x][y]][prev_Y[x][y]] = 0;
                temp_Matrix[new_X[x][y]][new_Y[x][y]] = -codeThisPlayer;
                int s = max(temp_Matrix, deph + 1, alpha, score);
                isThisPlayer = false;
                for (int i(0); i < size; i++)
                {
                    delete [] temp_Matrix[i];
                }
                delete [] temp_Matrix;
                if(s < score)
                    score = s;
                if(score <= alpha)
                    return score;
            }
        }
    for (int i(0); i < size; i++)
    {
        delete [] prev_X[i];
        delete [] prev_Y[i];
        delete [] new_X[i];
        delete [] new_Y[i];
    }
    delete[] prev_X;
    delete[] prev_Y;
    delete[] new_X;
    delete[] new_Y;
    return score;
}

int ai::max(int **matrix, int deph, int alpha, int beta)
{
    isThisPlayer = true;
    if(isTerminal(matrix, deph))
    {
        return -cost_Of_Desk(matrix);
    }
    int **prev_X = new int*[size];
    int **prev_Y = new int*[size];
    int **new_X = new int*[size];
    int **new_Y = new int*[size];
    for (int i(0); i < size; i++)
    {
        prev_X[i] = new int[size];
        prev_Y[i] = new int[size];
        new_X[i] = new int[size];
        new_Y[i] = new int[size];
    }
    int score = alpha;
    clear(prev_X, prev_Y, new_X, new_Y);
    generate_next_Turn(matrix, prev_X, prev_Y, new_X, new_Y);
    for(int x(0); x < size; x++)
        for(int y(0); y < size; y++)
        {
            if(prev_X[x][y] != -1 && prev_Y[x][y] != -1)
            {
                int** temp_Matrix = new int*[size];
                for (int i(0); i < size; i++)
                {
                    temp_Matrix[i] = new int[size];
                }
                copyMatrix(matrix, temp_Matrix, size);
                temp_Matrix[prev_X[x][y]][prev_Y[x][y]] = 0;
                temp_Matrix[new_X[x][y]][new_Y[x][y]] = codeThisPlayer;
                int s = min(temp_Matrix, deph + 1, score, beta);
                isThisPlayer = true;
                for (int i(0); i < size; i++)
                {
                    delete [] temp_Matrix[i];
                }
                delete [] temp_Matrix;
                if(s > score)
                    score = s;
                if(score >= beta)
                    return score;
            }
        }
    for (int i(0); i < size; i++)
    {
        delete [] prev_X[i];
        delete [] prev_Y[i];
        delete [] new_X[i];
        delete [] new_Y[i];
    }
    delete[] prev_X;
    delete[] prev_Y;
    delete[] new_X;
    delete[] new_Y;
    return score;
}

void ai::ai_turn(int **matrix)
{
    int **prev_X = new int*[size];
    int **prev_Y = new int*[size];
    int **new_X = new int*[size];
    int **new_Y = new int*[size];
    for (int i(0); i < size; i++)
    {
        prev_X[i] = new int[size];
        prev_Y[i] = new int[size];
        new_X[i] = new int[size];
        new_Y[i] = new int[size];
    }
    isThisPlayer = true;
    int score = -10000;
    clear(prev_X, prev_Y, new_X, new_Y);
    generate_next_Turn(matrix, prev_X, prev_Y, new_X, new_Y);
    for(int x(0); x < size; x++)
        for(int y(0); y < size; y++)
        {
            if(prev_X[x][y] != -1 && prev_Y[x][y] != -1)
            {
                int** temp_Matrix = new int*[size];
                for (int i(0); i < size; i++)
                {
                    temp_Matrix[i] = new int[size];
                }
                copyMatrix(matrix, temp_Matrix, size);
                temp_Matrix[prev_X[x][y]][prev_Y[x][y]] = 0;
                temp_Matrix[new_X[x][y]][new_Y[x][y]] = codeThisPlayer;
                if(check_win(temp_Matrix))
                {
                    x = size;
                    y = size;
                    score = 10000;
                    copyMatrix(temp_Matrix, rmMatrix, size);
                }
                else
                {
                    int s = min(temp_Matrix, 0, score, 10000);
                    if(s > score)
                    {
                        score = s;
                        copyMatrix(temp_Matrix, rmMatrix, size);
                    }
                    for (int i(0); i < size; i++)
                    {
                        delete [] temp_Matrix[i];
                    }
                    delete [] temp_Matrix;
                }
            }
        }
    copyMatrix(rmMatrix, matrix, size);
    for (int i(0); i < size; i++)
    {
        delete [] prev_X[i];
        delete [] prev_Y[i];
        delete [] new_X[i];
        delete [] new_Y[i];
    }
    delete[] prev_X;
    delete[] prev_Y;
    delete[] new_X;
    delete[] new_Y;
}
