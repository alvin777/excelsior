/**
 * Created by alvin777 on 13/11/14.
 */
public class SeamCarver {

    private final int BORDER_ENERGY = 255*255*3;

    private Picture picture;
    private final double[][] energyArray;
    private final int[][][] pictureMap;
    private int currentWidth;
    private int currentHeight;
    private boolean pictureDirty = false;

    public SeamCarver(Picture picture)                // create a seam carver object based on the given picture
    {
        this.picture = new Picture(picture);

        energyArray = new double[height()][width()];
        pictureMap = new int[height()][width()][2];

        currentWidth = picture.width();
        currentHeight = picture.height();

        for (int y = 0; y < height(); y++) {
            for (int x = 0; x < width(); x++) {
                energyArray[y][x] = energy(x, y);
            }
        }
    }

    public Picture picture() {
        if (!pictureDirty) return picture;

        Picture newPicture = new Picture(currentWidth, currentHeight);

        int xx = 0;
        int yy = 0;

        for (int y = 0; y < picture.height(); y++) {
            for (int x = 0; x < picture.width(); x++) {
                if (!horizontallyRemovedPixels[y][x] || !verticallyRemovedPixels[y][x]) {
                   newPicture.set(xx, yy, picture.get(x, y));
                }
                if (!verticallyRemovedPixels[y][x]) {
                    xx++;
                }
            }
        }

        picture = newPicture;
        pictureDirty = false;

        return picture;
    }

    public     int width()   { return currentWidth; }
    public     int height()  { return currentHeight; }

    public  double energy(int x, int y)               // energy of pixel at column x and row y
    {
        if (x == 0 || x == width() - 1)  { return BORDER_ENERGY; }
        if (y == 0 || y == height() - 1) { return BORDER_ENERGY; }

        return delta(x - 1, y, x + 1, y) + delta(x, y - 1, x, y + 1);
    }

    public   int[] findHorizontalSeam()               // sequence of indices for horizontal seam
    {
        double[][] dp = new double[height()][width()];
        int[][] p = new int[height()][width()];

        for (int y = 0; y < height(); y++) {
            dp[y][0] = energyArray[y][0];
        }

        for (int x = 1; x < width(); x++) {
            for (int y = 0; y < height(); y++) {
                int minY = Math.max(y - 1, 0);
                p[y][x] = minY;

                for (int yy = minY + 1; yy <= Math.min(y + 1, height() - 1); ++yy) {
                    if (dp[yy][x - 1] < dp[minY][x - 1]) {
                        minY = yy;
                        p[y][x] = minY;
                    }
                }
                dp[y][x] = energyArray[y][x] + dp[minY][x - 1];
            }
        }

        dumpArray(dp, width(), height());

        int minPathY = 0;
        for (int y = 0; y < height(); ++y) {
            if (dp[y][width() - 1] < dp[minPathY][width() - 1]) {
                minPathY = y;
            }
        }

        int[] path = new int[width()];
        int y = minPathY;
        for (int x = width() - 1; x >= 0; --x) {
            path[x] = y;
            y = p[y][x];
        }

        return path;
    }

    public   int[] findVerticalSeam() {                 // sequence of indices for vertical seam

        double[][] dp = new double[height()][width()];
        int[][] p = new int[height()][width()];

        for (int x = 0; x < width(); x++) {
            dp[0][x] = energyArray[0][x];
        }

        for (int y = 1; y < height(); y++) {
            for (int x = 0; x < width(); x++) {
                int minX = Math.max(x - 1, 0);
                p[y][x] = minX;

                for (int xx = Math.max(x - 1, 0); xx <= Math.min(x + 1, width() - 1); ++xx) {
                    if (dp[y - 1][xx] < dp[y - 1][minX]) {
                        minX = xx;
                        p[y][x] = minX;
                    }
                }
                dp[y][x] = energyArray[y][x] + dp[y-1][minX];
            }
        }

//        dumpArray(dp, width(), height());

        int minPathX = 0;
        for (int x = 0; x < width(); ++x) {
            if (dp[height() - 1][x] < dp[height() - 1][minPathX]) {
                minPathX = x;
            }
        }

        int[] path = new int[height()];
        int x = minPathX;
        for (int y = height() - 1; y >= 0; --y) {
            path[y] = x;
            x = p[y][x];
        }

        return path;
    }

    public    void removeHorizontalSeam(int[] seam)   // remove horizontal seam from current picture
    {
        pictureDirty = true;
    }

    public    void removeVerticalSeam(int[] seam)     // remove vertical seam from current picture
    {
        pictureDirty = true;
    }


    // implementation

    private char rgbComponent(int x, int y, int component) {
        return (char) ((picture.get(x, y).getRGB() >> 8 * component) & 0xFF);
    }

    private double delta(int x1, int y1, int x2, int y2) {
        double result = 0;
        for (int i = 0; i < 3; i++) {
            double componentDelta = rgbComponent(x1, y1, i) - rgbComponent(x2, y2, i);
            result += componentDelta * componentDelta;
        }
        return result;
    }

    private void dumpArray(double[][] array, int width, int height) {
        for (int j = 0; j < height; j++)
        {
            for (int i = 0; i < width; i++) {
                System.out.printf("%9.0f ", array[j][i]);
            }
            System.out.println();
        }
        System.out.println();
    }
}