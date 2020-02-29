#ifndef AI_H
#define AI_H

/*TODO
 * Ввести альфа бета отсичени и сделать максимально глубокое раскрытие
 * Ревью в новый проект
 * В ревью добавить новое стартовое меню
*/

class ai
{
private:
    int codeThisPlayer;
    bool isThisPlayer;
    int level;
    int size;
    int cost_FirstPlayer;
    int cost_SecondPlayer;
    int** rmMatrix;
    bool isTerminal(int **matrix, int deph);
    bool check_win(int **matrix);
    void clear(int** prev_X, int** prev_Y, int** new_X, int** new_Y);
public:
    ai(int lvl, int code);
    ~ai();
    int cost_Of_Desk(int** matrix);
    void generate_next_Turn(int** matrix, int** prev_X, int** prev_Y, int** new_X, int** new_Y);
    static void copyMatrix(int** old_Matrix, int** new_Matrix, int size);
    int min(int** matrix,int deph, int alpha, int beta);
    int max(int** matrix, int deph, int alpha, int beta);
    int minimax(int** matrix,int deph, int player);
    void ai_turn(int** matrix);
};

#endif // AI_H
