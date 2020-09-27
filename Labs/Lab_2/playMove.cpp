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
    }else{
      game_state.set_moveValid(true);
      game_state.set_gameBoard(row,col,(turn)?X:O);

      game_state.set_turn(!turn);
    }
    return;
}
