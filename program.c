#include <stdio.h>
#include <windows.h>
#include <math.h>

#define MAX 100

typedef struct {
    int rows;
    int cols;
    char element[MAX][MAX];
    int visited[MAX][MAX];
} Layout;

typedef struct {
    int dx[MAX];
    int dy[MAX];
    int x; // row coordidnate
    int y; //col coordinate
    int isSafe;
} Warga;

typedef struct {
    int x;
    int y;
} Point;

int isSimulateEnd(Layout *layout) {
    int isGameEnd = 1;
    for (int i = 0;i < layout->rows;i++) {
        for (int j = 0;j < layout->cols;j++) {
            if (layout->element[i][j] == 'W') {
                isGameEnd = 0;
                break;    
            }
        }
        if (isGameEnd == 0) {
            break;
        }
    }
    return isGameEnd;   
} 

void getPath(Point end, Point start, Point parent[MAX][MAX], Warga *warga, int indexOfWarga) {
    Point path[MAX];
    int length = 0; 

    while (!(end.x == start.x && end.y == start.y)) {
        path[length++] = end;
        end = parent[end.x][end.y];
    }

    path[length++] = start;
    for (int i = length-1;i >= 0;i--) {
        warga[indexOfWarga].dx[length-1-i] = path[i].x;
        warga[indexOfWarga].dy[length-1-i] = path[i].y;
    }
}

void findShortestPath(Layout *layout, Warga *warga, int indexOfWarga, int startX, int startY) {
    Point queue[MAX * MAX];
    Point temp;
    Point parent[MAX][MAX];
    for (int i = 0;i < MAX;i++) {
        for (int j = 0;j < MAX;j++) {
            parent[i][j].x = -1;
            parent[i][j].y = -1;
        }
    }
    Point current;
    Point end;
    Point start;

    layout->visited[startX][startY] = 1;

    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};
    int front = 0;
    int rear = 0;
    int nx;
    int ny;

    start.x = startX;
    start.y = startY;
    queue[rear++] = start;

    while (front < rear) {
        current = queue[front++];
        if (layout->element[current.x][current.y] == 'S') {
            end = current;
            getPath(end, start, parent, warga, indexOfWarga);
            return;
        }

        for (int i = 0;i < 4;i++) {
            nx = current.x + dx[i];
            ny = current.y + dy[i];
            if ((nx >= 0 && nx < layout->rows && ny >= 0 && ny < layout->cols) && (layout->element[nx][ny] == '0' || layout->element[nx][ny] == 'W' 
                || layout->element[nx][ny] == 'S') && layout->visited[nx][ny] == 0 ) {
                layout->visited[nx][ny] = 1;
                parent[nx][ny] = current;
                temp.x = nx;
                temp.y = ny;
                queue[rear++] = temp;

            } 

        } 
                   
    }
}

void simulate(Layout *layout, Warga *warga, int indexOfWarga) {
    int safeX;
    int safeY;
    int fireX;
    int fireY;
    int step = 0;
    double range = 0;

    for (int i = 0;i < layout->rows;i++) {
        for (int j = 0;j < layout->cols;j++) {
            if (layout->element[i][j] == 'S' || layout->element[i][j] == 'F') {
                if (layout->element[i][j] == 'S') {
                    safeX = i;
                    safeY = j;
                }

                else {
                    fireX = i;
                    fireY = j;
                }
            }
        }
    } 

    while (!(isSimulateEnd(layout))) {     //iterate every 1 second    
        for (int i = 0;i < layout->rows;i++) {
            for (int j = 0;j < layout->cols;j++) {
                if (layout->element[i][j] == 'W') {
                    for (int k = 0;k <= indexOfWarga;k++) {
                        if (warga[k].x == i && warga[k].y == j) {
                            warga[k].x = warga[k].dx[step];
                            warga[k].y = warga[k].dy[step];

                            layout->element[i][j] = '0';                                

                            if (warga[k].x == safeX && warga[k].y == safeY) {
                                warga[k].isSafe = 1;
                            }
                            else {
                                layout->element[warga[k].x][warga[k].y] = 'W' ; 
                            }
                        }
  
                   }

                }
  
            }               
        }
        step += 1;

        //spreadFire
        if (fmod(range,1.0) == 0.0) {
            for (int i = fireX-range;i <= fireX+range;i++) {
                for (int j = fireY-range;j <= fireY+range;j++) {
                    if (i < 0 || i >= layout->rows || j < 0 || j >= layout->cols) {
                        continue; 
                    }

                    if (layout->element[i][j] == 'W') {
                        layout->element[i][j] = 'X';
                    }

                    else if (layout->element[i][j] != 'S' && layout->element[i][j] != 'F') {
                        layout->element[i][j] = 'X';
                    } 
                }      
            }
        }

        range += 0.5;

        
        //display layout
        for (int i = 0;i < layout->rows;i++) {
            for (int j = 0;j < layout->cols;j++) {
                printf("%c ", layout->element[i][j]);
            }
            printf("\n");
        }    
        printf("\n");
        Sleep(1000);
    } 
}
   
int main() {
    int row;
    int col;
    Layout layout;
    printf("Masukkan dimensi layout!\n");

    printf("Masukkan panjang layout: ");
    scanf("%d", &row);
    while (row < 1 || row > MAX) {
        printf("panjang layout harus berada di antara 1 sampai MAX\n");
        printf("Masukkan panjang layout: ");
        scanf("%d", &row);
    }

    printf("Masukkan lebar layout: ");
    scanf("%d", &col);
    while (col < 1 || col > MAX) {
        printf("lebar layout harus berada di antara 1 sampai MAX\n");
        printf("Masukkan lebar layout: ");
        scanf("%d", &col);
    }

    layout.rows = row;
    layout.cols = col;
    
    char val;
    printf("Masukkan MAP!\n");
    for (int i = 0;i < layout.rows;i++) {
        for (int j = 0;j < layout.cols;j++) {
            scanf(" %c", &val);
            layout.element[i][j] = val;
        }
    }

    printf("\n");

    Warga warga[MAX];
    int indexOfWarga = 0;
    for (int i = 0;i < layout.rows;i++) {
        for (int j = 0;j < layout.cols;j++) { 
            if (layout.element[i][j] == 'W') {
                warga[indexOfWarga].x = i;
                warga[indexOfWarga].y = j;
                for (int x = 0; x < layout.rows; x++) {
                    for (int y = 0; y < layout.cols; y++) {
                        layout.visited[x][y] = 0;
                    }
                }
                findShortestPath(&layout, warga, indexOfWarga, i, j);
                indexOfWarga += 1;          
            }

        }
    }    

    indexOfWarga = indexOfWarga-1;
        
    simulate(&layout, warga, indexOfWarga);

    int dead = 0;
    int safe = 0;
    for (int i = 0;i <= indexOfWarga;i++) {
        if (warga[i].isSafe == 1) {
            safe += 1;
        } 
        else {
            dead += 1;
        }
    }

    printf("jumlah warga yang selamat = %d\n", safe);
    printf("jumlah warga yang terbakar = %d", dead);

}
   
    
        


