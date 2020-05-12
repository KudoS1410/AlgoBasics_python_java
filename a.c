#include <stdio.h>
#include <stdlib.h>

typedef struct board{
    int* mat;
    int* rowsums;
    int* colsums;
    int* diags;
}board;

// helper functions
int game_end(board b){
    for(int i = 0; i < 3; i++){
        if(b.rowsums[i] == -3 || b.rowsums[i] == 3)
            return b.rowsums[i] / 3;
    }
    for(int i = 0; i < 3; i++){
        if(b.colsums[i] == -3 || b.colsums[i] == 3)
            return b.colsums[i] / 3;
    }
    for(int i = 0; i < 2; i++){
        if(b.diags[i] == 3 || b.diags[i] == -3) return b.diags[i] / 3;
    }
    return 0;
}

board play_move(board b, int index, int move){
    int r = index/3;
    int c = index%3;
    b.mat[index] = move;
    b.rowsums[r] += move;
    b.colsums[c] += move;
    if(r == c) b.diags[0] += move;
    if(r+c == 2) b.diags[1] += move;
    return b;
}

void show_state(board b){
    int* data = (int*)malloc(3*sizeof(int));
    for(int i = 0; i<9; i++){
        switch(b.mat[i]){
            case(0):{data[i] = ' '; break;};
            case(1):{data[i] = 'X'; break;};
            case(-1):{data[i] = 'O'; break;};
        };
    }
    printf("\n\n");
    printf("\t\t\t  %c | %c  | %c  \n", data[0], data[1], data[2]);
    printf("\t\t\t----+----+----\n");
    printf("\t\t\t  %c | %c  | %c  \n", data[3], data[4], data[5]);
    printf("\t\t\t----+----+---\n");
    printf("\t\t\t  %c | %c  | %c  \n", data[6], data[7], data[8]);
    free(data);
}


int get_human_move(board b){
    int move;
    do{
        printf("move: ");
        scanf("%d", &move);
    }while((move-1 < 0) || (move-1 > 9) || b.mat[move-1] !=0);
    return move-1;
}
int minimax(board b, int depth, int is_computer){
    int r = game_end(b);
    if(r!=0) return r;
    int result ;
    int best_move=0;
    int move ;
    int best_result = (is_computer)?-10:10;
    // would never be zero if depth is at root
	int c = 0;
    for(int i = 0; i < 9; i++){
        if(b.mat[i] == 0){
			c++;

            if(!move) best_move = move;

            move = i;

            b = play_move(b, move, (is_computer)?1:-1);
            result = minimax(b, depth+1, !is_computer);

            b = play_move(b, move, (is_computer)?-1:1);
            b.mat[move] = 0;
            if((is_computer)?(result>best_result):(result<best_result)){
				if(is_computer){if(result>best_result);else printf("asdfdddddddd");}
				else{if(result<best_result);else printf("cZXCZXVZXV");}
                best_result = result;
                best_move = move;
            }
        }
    }
	if(c==0) return 0;
    if(depth > 0) {
return best_result;};
    if(depth == 0) {
    // printf("at above state %d wins\n", best_move);
		while(b.mat[best_move]!=0){ best_move++;
            // printf("sdfasdfasdfsadfsdfsdfsdfsdf\n");
        }
		return best_move;
	};

}

int get_c_move(board b){
    int v = minimax(b, 0, 1);
    printf("asdf: %d\n",v );
    return v;
}
 // game_iteration
 int game(){

    board b;
    b.mat = (int*)malloc(9*sizeof(int));
    b.rowsums = (int*)malloc(3*sizeof(int));
    b.colsums = (int*)malloc(3*sizeof(int));
    b.diags = (int*)malloc(2*sizeof(int));
    for(int i = 0; i < 3; i++){b.mat[i] = 0; b.colsums[i] = 0; b.rowsums[i] = 0;}
    for(int i = 3; i < 9; i++)b.mat[i] = 0;
    b.diags[0] = 0;
    b.diags[1] = 0;
    int c = 0;
    int r = 0;
    int move;
    int is_human = 1;
    // show_state(b);
    while(c < 9){
            printf("move_number : %d\n", c+1);
            // if(!c) show_state(b);
        if(is_human) move = get_human_move(b);
        else move = get_c_move(b);
            printf("moved %s to : %d\n", (is_human)?"human(-1)":"comp(+1)", move+1);
        b = play_move(b, move, (is_human)?-1:1);
        r = game_end(b);
       // printf("r=%d\n", r);
        show_state(b);
        if(r != 0) break;
        c++;
        is_human = !is_human;
    }
    switch(r){
    case(0):{printf("No one wins\n");break;};
    case(1):{printf("one wins\n");break;};
    case(-1):{printf("minus one wins\n");break;};
    };
 }
int main(){
    game();
}
