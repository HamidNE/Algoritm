#include <iostream>
#include <vector>
#include<queue>
#include <math.h>
#include <algorithm>

using namespace std;

struct Matrix{
    vector < vector <int> > problem;
    vector < vector <int> > goal;
    int gn;
};

class Compare_Values    {
    public: 
        bool operator()(Matrix& M1, Matrix& M2){
            return( M1.gn >  M2.gn);
        }
};


int total_nodes = 0;
Matrix UP(Matrix& M, int i, int j){
    swap(M.problem[i][j], M.problem[i+1][j]);
    M.gn= M.gn + 1;
    total_nodes++;
    return M;
}

Matrix DN(Matrix& M, int i, int j){
    swap(M.problem[i][j],M.problem[i-1][j]);
    M.gn = M.gn+1;
    total_nodes++;
    return M;
}

Matrix RT(Matrix& M, int i, int j){
    swap(M.problem[i][j], M.problem[i][j-1]);
    M.gn = M.gn+1;
    total_nodes++;
    return M;
}

Matrix LF(Matrix& M, int i, int j){
    swap(M.problem[i][j], M.problem[i][j+1]);
    M.gn = M.gn+1;
    total_nodes++;
    return M;
}

void expand(Matrix M, priority_queue<Matrix, vector<Matrix>, Compare_Values> &nodes){

    Matrix M1; 
    M1.problem.push_back(std::vector<int>(3, 1));
    M1.problem.push_back(std::vector<int>(3, 2));
    M1.problem.push_back(std::vector<int>(3, 3));

    Matrix M2;
    M2.problem.push_back(std::vector<int>(3, 1));
    M2.problem.push_back(std::vector<int>(3, 2));
    M2.problem.push_back(std::vector<int>(3, 3));

    Matrix M3;
    M3.problem.push_back(std::vector<int>(3, 1));
    M3.problem.push_back(std::vector<int>(3, 2));
    M3.problem.push_back(std::vector<int>(3, 3));

    Matrix M4;
    M4.problem.push_back(std::vector<int>(3, 1));
    M4.problem.push_back(std::vector<int>(3, 2));
    M4.problem.push_back(std::vector<int>(3, 3));

    M1 = M;
    M2 = M;
    M3 = M;
    M4 = M; 

    int row,column;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(M.problem[i][j] == 0){
                row = i;
                column = j;
                break;
            }
        }
    }

  
    if(column == 2 && row == 0){
        nodes.push(LF(M1,row, column-1));
        nodes.push(DN(M2,row+1,column));
    }
    else if(column == 2 && row == 1){
        nodes.push(UP(M1,row-1,column));
        nodes.push(LF(M2, row, column-1));
        nodes.push(DN(M3, row+1, column));
    }
    else if(column ==2 && row ==2){
        nodes.push(UP(M1, row-1, column));
        nodes.push(LF(M2, row, column -1));
    }
    else if(column == 0 && row == 0){
        nodes.push(RT(M1,row, column+1));
        nodes.push(DN(M2,row+1,column));
    }
    else if(column == 0 && row == 1){
        nodes.push(UP(M1,row-1,column));
        nodes.push(RT(M2, row, column+1));
        nodes.push(DN(M3, row+1, column));
    }
    else if(column ==0 && row ==2){
        nodes.push(UP(M1, row-1, column));
        nodes.push(RT(M2, row, column+1));
    }
    else if(column == 1 && row == 0){
        nodes.push(LF(M1,row, column-1));
        nodes.push(DN(M2,row+1,column));
        nodes.push(RT(M3, row, column+1));
    }
    else if(column == 1 && row == 1){
        nodes.push(UP(M1,row-1,column));
        nodes.push(LF(M2, row, column-1));
        nodes.push(DN(M3, row+1, column));
        nodes.push(RT(M4, row, column+1));
    }
    else if(column ==1 && row ==2){
        nodes.push(UP(M1, row-1, column));
        nodes.push(LF(M2, row, column -1));
        nodes.push(RT(M3, row, column + 1));
    }

} 

bool checkIfGoal(vector <vector<int> > M)
{
    if(M[0][0] ==1 && M[0][1] ==2 && M[0][2] ==3 && M[1][0] ==4 && M[1][1] == 5 && M[1][2] == 6 && M[2][0] == 7 && M[2][1] == 8 && M[2][2] == 0) 
        return true;
    return false;
}
void generalSearch(Matrix M){
	
    priority_queue <Matrix, vector<Matrix>, Compare_Values> nodes;
    nodes.push(M);

    cout << "Expanding state: " << endl;
    for(int i = 0; i < 3; ++i){
        cout << "\t";
        for(int j = 0; j < 3; ++j)
            cout << nodes.top().problem[i][j] << "\t" ;
        cout<<endl;
    }
    cout << endl;

    int max_queue=0;
    int notEmpty = 0; 
    do{    
        if(nodes.empty()){
            cout <<  "Failure. There is no solution to this problem." << endl;
            break;
        }

        Matrix node;
        node.problem.push_back(std::vector<int>(3, 1));
        node.problem.push_back(std::vector<int>(3, 2));
        node.problem.push_back(std::vector<int>(3, 3));

        node.goal.push_back(std::vector<int>(3, 1));
        node.goal.push_back(std::vector<int>(3, 2));
        node.goal.push_back(std::vector<int>(3, 3));
        node = nodes.top();
        nodes.pop();
        if(checkIfGoal(node.problem)){
            cout << "Goal node reached!" << endl;
            cout << endl << endl;
            cout << "To solve this problem, the algorithm expanded a total of " << total_nodes << "  nodes." << endl;
            cout << "The maximum number of nodes in the queue at any one time was " << max_queue << "." << endl;
            cout << "Depth of goal node was " << node.gn << "." << endl;
            notEmpty = 1;
			getchar();
            return;
        }
        expand(node,nodes);
        int curr_queue = nodes.size();
        max_queue = max(max_queue, curr_queue);
        cout << "The best state to expand with a g(n)=" << nodes.top().gn  << " is..." << endl;
        for(int f = 0; f < 3; ++f){
            cout << "\t";
            for(int e = 0; e < 3; ++e)
                cout << nodes.top().problem[f][e] << "\t" ;
            cout <<  endl;
        }
        cout << "\t\t\t\tExpanding this state..." << endl;
        cout << endl;
		getchar();
    }while(!nodes.empty() && !notEmpty);
    return;
	
}

int main(){

    Matrix M;
    M.goal.push_back(std::vector<int>(3, 1));
    M.goal.push_back(std::vector<int>(3, 2));
    M.goal.push_back(std::vector<int>(3, 3));

    M.goal[0][0]=1;
    M.goal[0][1]=2;
    M.goal[0][2]=3;
    M.goal[1][0]=4;
    M.goal[1][1]=5;
    M.goal[1][2]=6;
    M.goal[2][0]=7;
    M.goal[2][1]=8;
    M.goal[2][2]=0;

    M.gn = 0;

    M.problem.push_back(std::vector<int>(3, 1));
    M.problem.push_back(std::vector<int>(3, 2));
    M.problem.push_back(std::vector<int>(3, 3));
    
        M.problem[0][0]=1;
        M.problem[0][1]=2;
        M.problem[0][2]=3;
        M.problem[1][0]=4;
        M.problem[1][1]=8;
        M.problem[1][2]=0;
        M.problem[2][0]=7;
        M.problem[2][1]=6;
        M.problem[2][2]=5;
    
	cout << "Welcome to 8 Puzzle Solver!" << endl;
    generalSearch(M);

    return 0;
	
}

