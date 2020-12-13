import java.util.Random;
import java.util.Scanner;
import java.util.concurrent.Semaphore;

public class Main {
  final static int dim = 2048;

  static void initGeneration(int mat [][]) {
    Random generator = new Random(1985);
    for (int i = 0; i<dim; i++)
      for (int j = 0; j<dim; j++)
        mat[i][j] = generator.nextInt(2147483647) % 2;
  }

  public static int countCell(int mat[][]) {
    int ret = 0;
    for (int i = 0; i < dim; i++)
      for (int j = 0; j < dim; j++)
        if (mat[i][j] == 1) ret += 1;
    return ret;
  }

  public static void main(String[] args) throws InterruptedException {
    int grid[][] = new int[dim][dim];
    int newgrid[][] = new int[dim][dim];
    int temp[][];
    initGeneration(grid);
    Semaphore semaphore = new Semaphore(1, true);

    int numThreads;
    int generation;
    Scanner input = new Scanner(System.in);
    System.out.println("enter with the number of threads");
    numThreads = input.nextInt();
    System.out.println("enter with the number of generations: ");
    generation = input.nextInt();

    System.out.println("Initil condition: " + countCell(grid));
    Thread th[] = new Thread[numThreads];
    while (generation > 0) {
      generation -= 1;
      for (int i = 0; i < numThreads; i++) {
        th[i] = new Thread(new MyThread(grid, newgrid, semaphore, i, numThreads));
        th[i].start();
      }
      for (int i = 0; i < numThreads; i++)
        th[i].join();

      temp = grid;
      grid = newgrid;
      newgrid = temp;
    }
    System.out.println("Final condition: " + countCell(grid));
  }
}
