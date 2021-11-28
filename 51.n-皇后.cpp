/*
 * @lc app=leetcode.cn id=51 lang=cpp
 * 题型：回溯算法
 * [51] N 皇后
 */
#include<vector>
#include<string>
using namespace std;
// @lc code=start
class Solution {
public:
    //存储结果
    vector<vector<string>> res;
    // 输入棋盘边长 n ,返回所有合法的放置
    vector<vector<string>> solveNQueens(int n) {
        // '.'表示空，'Q'表示皇后，初始化n x n 空棋盘
        vector<string> board(n,string(n,'.'));
        backtrack(board,0);
        return res;
    }

    void backtrack(vector<string>& board,int row)
    {
        //每一行都成功放置了皇后，记录成果
        if(row == board.size())
        {
            res.push_back(board);
            return ;
        }
        //row 行  col 列 
        int n = board[row].size();
        // 在当前行的每一列都可能放置皇后
        for(int col = 0;col<n;col++)
        {
            //排除可以互相攻击的格子,进行剪枝
            if(!isValid(board,row,col))
                continue;
            //做选择
            board[row][col] = 'Q';
            //进入下一行放皇后
            backtrack(board,row+1);
            //撤销选择
            board[row][col] = '.';
        }
    }

    //是否在 board[row][col] 放皇后？
    bool isValid(vector<string>& board,int row,int col)
    {
        int n = board.size();
        //检查列是否有皇后互相冲突
        for (int i=0;i<n;i++)
        {
            if(board[i][col] == 'Q')
                return false;
        }

        //检查右上放是否有皇后冲突
        for (int i = row - 1,j = col + 1;
             i>=0&&j<n;i--,j++)
             {
                 if(board[i][j] == 'Q')
                    return false;
             }
        
        //检查左上放是否有皇后冲突
        for(int i = row-1,j = col -1;
            i>=0&&j>=0;i--,j--)
            {
                if(board[i][j] == 'Q')
                    return false;
            }

        return true;

    }
};
// @lc code=end

