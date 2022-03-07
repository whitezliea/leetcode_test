/*
 * @lc app=leetcode.cn id=37 lang=cpp
 *
 * [37] 解数独
 */

// @lc code=start
class Solution {
public:
void solveSudoku(vector<vector<char>>& board) {

        backtrack(board,0,0);
    }

    //判断borad[height][width]处能否放下字符ch
    bool isVaild(vector<vector<char>>& board, int height, int width,char ch)
    {

        //判断3x3表格里是否有重复
        for (int i=0;i<9;i++)
        {
            //判断行是否有重复
            if (board[height][i] == ch)
                return false;
            //判断列是否有重复
            if (board[i][width] == ch)
                return false;
            //判断3x3表格里是否有重复
            if (board[(height/3)*3 + i/3][(width/3)*3+i%3]==ch)
                return false;
        }
        return true;
    }

    bool backtrack(vector<vector<char>>& board,int i,int j)
    {   
        //当前行已经遍历，开始遍历下一行,状态重置
        if (j==board[0].size())
        {
            return backtrack(board,i+1,0);
        }
        //已经遍历完所有行了
        if (i==board.size())
        {
            return true;
        }

        //当前已有预设数字，继续递归遍历下一个空格
        if (board[i][j] != '.')
        {
            return backtrack(board,i,j+1);
        }
        //对board[i][j]进行穷举，i为行，j为列
        for (char ch = '1';ch<='9';ch++ )
        {
            //如果遇到不合理的情况，跳过，剪枝操作
            if (!isVaild(board,i,j,ch))
            {
                continue;
            }
            //做选择
            board[i][j] = ch;
            //继续穷举下一个,如果找到下一个情况
            if (backtrack(board,i,j+1))
                return true;
            //撤销选择
            board[i][j] ='.';
        }
        return false;

    }
};

// @lc code=end

