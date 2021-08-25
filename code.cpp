#include <iostream>
#include <vector>

using namespace std;

void printSudoku(int arr[9][9]){
    cout << "--------------------------" << endl;

    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            cout << arr[i][j] <<" " ;
        }
        cout << endl;
    }

    cout << "--------------------------" << endl;

}

bool canPlace(int arr[9][9], int row, int col, int num){
    if(arr[row][col]!=0) return false;
    int gridy= (row/3) * 3, gridx= (col/3) * 3;

    for(int i=0;i<9;i++){
        if(arr[i][col]==num) return false;
        if(arr[row][i]==num) return false;
        if(arr[gridy+i/3][gridx+i%3]==num) return false;
    }
    return true;
}

std::vector<int> findPlaceables(int arr[9][9] , int row, int col){
     vector<int> cps;
     for(int i=1;i<=9;i++){
         if(canPlace(arr, row, col, i)){
             cps.push_back(i);
         }
     }
     return cps;
}

void copyArr(int arr[9][9], int arrcpy[9][9]){
     for(int i=0;i<9;i++){
         for(int j=0;j<9;j++){
             arrcpy[i][j]=arr[i][j];
         }
     }
}
void nextCell(int arr[9][9], int row, int col, int& nrow, int& ncol){
    //int index=9*9;
    for(int i= row*9+col+1;i<81;i++){
        if(arr[i/9][i%9]==0){
            nrow=i/9;
            ncol=i%9;
            break;
        }
    }
}

bool solveSudoku(int arr[9][9], int row, int col){
    //system("cls");
    //printSudoku(arr);
    if(row>8) return true;
    if(arr[row][col]!=0){
        int nextRow, nextCol;
        nextCell(arr,row,col, nextRow, nextCol);
        return solveSudoku(arr, nextRow, nextCol);
            
    }

    std::vector<int> placeables= findPlaceables(arr, row, col);
    if(placeables.size()==0) return false;

    for(int i=0;i< placeables.size();i++){
        int n= placeables[i];
        int arrcpy[9][9];
        copyArr(arr, arrcpy);

        int nextRow, nextCol;
        arrcpy[row][col]=n;
        nextCell(arrcpy,row,col, nextRow, nextCol);
        if(solveSudoku(arrcpy, nextRow, nextCol)){
            copyArr(arrcpy, arr);
            return true;
        }
    }
    return false;

} 

int main(int argc, char** argv){
   /* int board[9][9]= {
        {5,3,0,0,7,0,0,0,0},
		{6,0,0,1,9,5,0,0,0},
		{0,9,8,0,0,0,0,6,0},
		{8,0,0,0,6,0,0,0,3},
		{4,0,0,8,0,3,0,0,1},
		{7,0,0,0,2,0,0,0,6},
		{0,6,0,0,0,0,2,8,0},
		{0,0,0,4,1,9,0,0,5},
		{0,0,0,0,8,0,0,7,9}

    };
    */
    //printSudoku(board);
    int board[9][9];
    cout << " Give Sudoku to solve:" << endl;
    cout << "--------------------------" << endl;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            cin >> board[i][j];
        }
    }
    solveSudoku(board, 0, 0);
    cout << "--------------------------" << endl;
    cout << "Solved Sudoku is:" << endl;
    printSudoku(board);
    return 0;
}