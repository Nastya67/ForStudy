#include "stdio.h"
#include "math.h"
#include "stdlib.h"

int main()
{
    int i;
    int moveslen = 5;
    int reslen = moveslen;
    int moves[5] = {10, 105, 15, 15, 6};
    int res[5]={0};
    run(moves, moveslen,res,reslen);
    for(i=0; i<reslen; i++){
        printf("%i ", moves[i]);
    }
    printf("\n");
    for(i=0; i<reslen; i++){
        printf("%i ", res[i]);
    }
    printf("\n%i", run(moves, moveslen,res,reslen));
}

int run(int moves[], int movesLen, int res[], int resLen){

enum operations { Pop, Push, Break, Repeat, Continue, nothing };

struct Move
{
	enum operations doing;//operation
	int wright;//state
} automat[4][4];
	int nowS = 0;
	int move;
	int j = 0, i = 0;
	int x = 0;// break
	int resNumbers = 0;

	automat[0][0].doing = Pop;
	automat[0][0].wright = 1;
	automat[0][1].doing = 1;
	automat[0][1].wright = 1;
	automat[0][2].doing = Break;
	automat[0][2].wright = Break;
	automat[0][3].doing = 6;
	automat[0][3].wright = 0;
	automat[1][0].doing = Pop;
	automat[1][0].wright = 2;
	automat[1][1].doing = Continue;
	automat[1][1].wright = 0;
	automat[1][2].doing = 2;
	automat[1][2].wright = 2;
	automat[1][3].doing = Repeat;
	automat[1][3].wright = 3;
	automat[2][0].doing = nothing;
	automat[2][0].wright = nothing;
	automat[2][1].doing = 4;
	automat[2][1].wright = 3;
	automat[2][2].doing = nothing;
	automat[2][2].wright = nothing;
	automat[2][3].doing = 3;
	automat[2][3].wright = 3;
	automat[3][0].doing = Break;
	automat[3][0].wright = Break;
	automat[3][1].doing = 7;
	automat[3][1].wright = 0;
	automat[3][2].doing = 5;
	automat[3][2].wright = 2;
    automat[3][3].doing = Continue;
	automat[3][3].wright = 3;

	while (1){
		switch (moves[j]){
            case 6: move = 0;
                break;
            case 10: move = 1;
                break;
            case 15: move = 2;
                break;
            case 105: move = 3;
                break;
            default: x = 1;
                break;
		}
        if (x == 1){
            break;
        }
        switch (automat[nowS][move].doing){
			case Break: x = 1;
				break;
			case Pop:
				if (i>0){
					res[i - 1] = 0;
					i--;
					j++;
					nowS = automat[nowS][move].wright;
					break;
				}
				else{
					x = 1;
					break;
				}
			case Repeat: nowS = automat[nowS][move].wright;
				break;
			case Continue: j++;
				nowS = automat[nowS][move].wright;
				break;
			default: res[i] = automat[nowS][move].wright;
				i++;
				j++;
				nowS = automat[nowS][move].wright;
				break;
			}
			if (x == 1)
				break;
	}
	for (i = 0; i<resLen; i++){
		if (res[i] != 0){
			resNumbers++;
		}
	}
	return resNumbers;
}

