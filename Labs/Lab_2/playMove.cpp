//
//  playMove.cpp
//  TicTacToe
//
//  Created by Tarek Abdelrahman on 2019-06-07.
//  Modified by Tarek Abdelrahman on 2020-09-17.
//  Copyright © 2019-2020 Tarek Abdelrahman. All rights reserved.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//
//  ECE244 Student: write your code for playMove in this file

#include "globals.h"
#include "GameState.h"

void playMove(GameState& game_state) {
    int row,col,val;
    bool turn;
    row = game_state.get_selectedRow();
    col = game_state.get_selectedColumn();
    val = game_state.get_gameBoard(row,col);
    turn = game_state.get_turn();
    if(val!=Empty){
      game_state.set_moveValid(false);
      return;
    }
    game_state.set_moveValid(true);
    game_state.set_gameBoard(row,col,(turn)?X:O);
    game_state.set_turn(!turn);

    for(int i = 0;i < boardSize;i++){
      int countRow = 0;
      for(int j = 0;j < boardSize;j++){
        int val = game_state.get_gameBoard(i,j);
        countRow+=val;
        if(countRow==3||countRow==-3){
          game_state.set_winCode(i+1);
          game_state.set_gameOver(true);
        }
      }
    }

    for(int i = 0;i < boardSize;i++){
      int countCol = 0;
      for(int j = 0;j < boardSize;j++){
        int val = game_state.get_gameBoard(j,i);
        countCol+=val;
        if(countCol==3||countCol==-3){
          game_state.set_winCode(i+4);
          game_state.set_gameOver(true);
        }
      }
    }

    int count1=0,count2=0;
    for(int i = 0;i < boardSize;i++){
      int val1 = game_state.get_gameBoard(i,i);
      int val2 = game_state.get_gameBoard(i,boardSize-1-i);
      count1 += val1;
      count2 += val2;
      if(count1==3||count1==-3){
        game_state.set_winCode(7);
        game_state.set_gameOver(true);
      }
      if(count2==3||count2==-3){
        game_state.set_winCode(8);
        game_state.set_gameOver(true);
      }
    }

    int countNonEmpty = 0;
    for(int i = 0;i < boardSize;i++){
      for(int j = 0;j < boardSize;j++){
        int val = game_state.get_gameBoard(i,j);
        if(val!=Empty){
          countNonEmpty++;
        }
      }
    }
    if(countNonEmpty==9){
      game_state.set_gameOver(true);
    }

    return;
}
