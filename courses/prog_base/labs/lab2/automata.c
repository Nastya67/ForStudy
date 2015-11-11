#include "stdio.h"
#include "math.h"
#include "stdlib.h"

int main()
{
    int i;
    int moveslen = 4;
    int reslen = 4;
    int moves[4] = {10, 105, 15, 6};
    int res[4]={0};
    run(moves, moveslen,res,reslen);
    for(i=0; i<reslen; i++){
        printf("%i ", res[i]);
    }
    printf("\n%i", run(moves, moveslen,res,reslen));
}

int run(int moves[], int movesLen, int res[], int resLen){

enum operations { Pop, Push, Break, Repeat, Continue, nothing };

struct Move
{
	enum operations left;//operation
	int right;//state
};

	movesLen = 4;
	resLen = movesLen;
	int nowS = 0;
	int Move;
	int j = 0, i = 0;
	int x;// cheking break
	int resNumbers = 0;
	struct Move automat[4][4];

	automat[0][0].left = Pop;
	automat[0][0].right = 1;
	automat[0][1].left = 1;
	automat[0][1].right = 1;
	automat[0][2].left = Break;
	automat[0][2].right = Break;
	automat[0][3].left = 6;
	automat[0][3].right = 0;
	automat[1][0].left = Pop;
	automat[1][0].right = 2;
	automat[1][1].left = Continue;
	automat[1][1].right = 0;
	automat[1][2].left = 2;
	automat[1][2].right = 2;
	automat[1][3].left = Repeat;
	automat[1][3].right = 3;
	automat[2][0].left = nothing;
	automat[2][0].right = nothing;
	automat[2][1].left = 4;
	automat[2][1].right = 3;
	automat[2][2].left = nothing;
	automat[2][2].right = nothing;
	automat[2][3].left = 3;
	automat[2][3].right = 3;
	automat[3][0].left = Break;
	automat[3][0].right = Break;
	automat[3][1].left = 7;
	automat[3][1].right = 0;
	automat[3][2].left = 5;
	automat[3][2].right = 2;
    automat[3][3].left = Continue;
	automat[3][3].right = 3;

	while (1){
		switch (moves[j]){
		case 6: Move = 0;
			break;
		case 10: Move = 1;
			break;
		case 15: Move = 2;
			break;
		case 105: Move = 3;
			break;
		default: x = 1;
			break;
		}
        if (x == 1){
            break;
        }
        switch (automat[nowS][Move].left){
			case Break: x = 1;
				break;
			case Pop:
				if (i>0){
					res[i - 1] = 0;
					i--;
					j++;
					nowS = automat[nowS][Move].right;
					break;
				}
				else{
					x = 1;
					break;
				}
			case Repeat: nowS = automat[nowS][Move].right;
				break;
			case Continue: j++;
				nowS = automat[nowS][Move].right;
				break;
			default: res[i] = automat[nowS][Move].right;
				i++;
				j++;
				nowS = automat[nowS][Move].right;
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

