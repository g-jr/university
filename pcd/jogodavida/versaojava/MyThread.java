import java.util.concurrent.Semaphore;

public class MyThread implements Runnable {
  private int grid[][];
  private int newgrid[][];
  final static int dim = 2048;
  Semaphore semaphore;
  private int id;
  private int totalThreads;

  public MyThread(int grid[][], int newgrid[][], Semaphore s, int id, int totalThreads) throws InterruptedException {
    this.grid = grid;
    this.newgrid = newgrid;
    this.semaphore = s;
    this.id = id;
    this.totalThreads = totalThreads;
  }

  int getNeighbors(int[][] grid, int i, int j) {
    int ret = 0, row, col;
    for (int k = i - 1; k <= i + 1; k++) {
      if (k < 0) row = dim - 1;
      else if (k == dim) row = 0;
      else row = k;
      for (int l = j - 1; l <= j + 1; l++) {
        if (k == i && l == j) continue; // verify if actual pos is equal to cell pos
        if (l < 0) col = dim - 1;
        else if (l == dim) col = 0;
        else col = l;
        if (grid[row][col] == 1) ret++;
      }
    }
    return ret;
  }
  @Override
  public void run() {
    int temp;
    int i, j, n;
    try {
      semaphore.acquire(1);
      n = dim / totalThreads;
      i = id * n;
      n = n * (id + 1);
    } catch (InterruptedException e) {
      e.printStackTrace();
      return;
    } finally {
      semaphore.release(1);
    }
    for (; i < n; i++) {
    //if (i == 2000) System.out.println("hello");
      for (j = 0; j < dim; j++) {
        temp = getNeighbors(grid, i, j);
        if (grid[i][j] == 1 && temp < 2) newgrid[i][j] = 0; //  A
        else if (grid[i][j] == 1 && (temp == 2 || temp == 3)) newgrid[i][j] = 1; // B
        else if (grid[i][j] == 1 && temp >= 4) newgrid[i][j] = 0; // C
        else if (grid[i][j] == 0 && temp == 3) newgrid[i][j] = 1; // D
        else newgrid[i][j] = 0;
      }
    }
  }
}
