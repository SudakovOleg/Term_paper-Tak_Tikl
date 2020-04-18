#ifndef AI_H
#define AI_H

#include <QVector>

class ai
{
private:
    int codeThisPlayer;
    bool isThisPlayer;
    int level;
    int size;
    int cost_FirstPlayer;
    int cost_SecondPlayer;
    QVector<QVector<int> > rmMatrix;
    bool isTerminal(QVector<QVector<int>> matrix, int deph);
    bool check_win(QVector<QVector<int> > matrix);
public:
    ai(int lvl, int code);
    int cost_Of_Desk(QVector<QVector<int>> matrix);
    void generate_next_Turn(QVector<QVector<int>> matrix, QVector<QVector<int>> &prev_X, QVector<QVector<int>> &prev_Y, QVector<QVector<int>> &new_X, QVector<QVector<int>> &new_Y);
    int min(QVector<QVector<int>> &matrix,int deph, int alpha, int beta);
    int max(QVector<QVector<int>> &matrix, int deph, int alpha, int beta);
    void ai_turn(QVector<QVector<int>> &matrix);
    void init(QVector<QVector<int> > &prev_X, QVector<QVector<int> > &prev_Y, QVector<QVector<int> > &new_X, QVector<QVector<int> > &new_Y);
};

#endif // AI_H
