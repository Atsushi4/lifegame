/**
 * @file
 * @brief アプリケーションのエントリポイント
 */
#include <iostream>
#include <cstdlib>

using namespace std;

const int RowCount = 20;
const int ColumnCount = 30;
char world[RowCount][ColumnCount] = {};
char nextWorld[RowCount][ColumnCount] = {};

static void update();
static void addScore(int row, int column);
static void draw();
static bool isAlive(int row, int column);
static int random(int max, int min = 0)
{
    return static_cast<long long>(::rand()) * (max - min) / RAND_MAX + min;
}

/**
 * @brief ライフゲームのボードを表示する
 * @return
 */
int main()
{
//    unsigned seed = 512;
//    ::srand(seed);
//    int count = 100;
//    while (count--)
//    {
//        world[random(RowCount)][random(ColumnCount)] = 5;
//    }

    world[10][10] = 5;
    world[10][11] = 5;
    world[10][14] = 5;
    world[10][15] = 5;
    world[10][16] = 5;
    world[8][11] = 5;
    world[9][13] = 5;

    char c = 100;
    while (c--)
    {
        draw();
        update();

        ::usleep(500000);
    }
    return EXIT_SUCCESS;
}

/**
 * @brief 各セルの状態を1世代進める
 * @note
 *      生きているセルを基準に更新する。
 */
void update()
{
    for (int i = 0; i < RowCount; ++i)
        for (int j = 0; j < ColumnCount; ++j)
            if (isAlive(i, j))
                addScore(i, j);

    memcpy(world, nextWorld, sizeof(world));
    memset(nextWorld, 0, sizeof(nextWorld));
}

void draw()
{
    for (int i = 0; i < RowCount; ++i)
    {
        for (int j = 0; j < ColumnCount; ++j)
            putchar(isAlive(i, j) ? '#' : '_');

        putchar('\n');
    }
    putchar('\n');
    fflush(stdout);
}

bool valid(int row, int column)
{
    return row >= 0 && row < RowCount
            && column >= 0 && column < ColumnCount;
}

void addScore(int row, int column)
{
    for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j)
            if (valid(row + i, column + j))
                nextWorld[row + i][column + j] += 2;

    nextWorld[row][column] -= 1;
}

bool isAlive(int row, int column)
{
    switch (world[row][column])
    {
    case 5:
    case 6:
    case 7:
        return true;
    default:
        return false;
    }
}

