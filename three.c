#include <stdio.h>
#include <math.h>
#include <mpi.h>
#define m1 1
#define m2 1
#define m3 1
#define fx1(x1, y1, x2, y2, x3, y3) (-(m2 * (x1 - x2) / pow(pow(x2 - x1, 2) + pow(y2 - y1, 2), 1.5) + m3 * (x1 - x3) / pow(pow(x3 - x1, 2) + pow(y3 - y1, 2), 1.5)))
#define fx2(x1, y1, x2, y2, x3, y3) (-(m3 * (x2 - x3) / pow(pow(x3 - x2, 2) + pow(y3 - y2, 2), 1.5) + m1 * (x2 - x1) / pow(pow(x1 - x2, 2) + pow(y1 - y2, 2), 1.5)))
#define fx3(x1, y1, x2, y2, x3, y3) (-(m1 * (x3 - x1) / pow(pow(x1 - x3, 2) + pow(y1 - y3, 2), 1.5) + m2 * (x3 - x2) / pow(pow(x2 - x3, 2) + pow(y2 - y3, 2), 1.5)))
#define fy1(x1, y1, x2, y2, x3, y3) (-(m2 * (y1 - y2) / pow(pow(x2 - x1, 2) + pow(y2 - y1, 2), 1.5) + m3 * (y1 - y3) / pow(pow(x3 - x1, 2) + pow(y3 - y1, 2), 1.5)))
#define fy2(x1, y1, x2, y2, x3, y3) (-(m3 * (y2 - y3) / pow(pow(x3 - x2, 2) + pow(y3 - y2, 2), 1.5) + m1 * (y2 - y1) / pow(pow(x1 - x2, 2) + pow(y1 - y2, 2), 1.5)))
#define fy3(x1, y1, x2, y2, x3, y3) (-(m1 * (y3 - y1) / pow(pow(x1 - x3, 2) + pow(y1 - y3, 2), 1.5) + m2 * (y3 - y2) / pow(pow(x2 - x3, 2) + pow(y2 - y3, 2), 1.5)))
void gx1(double x1, double y1, double x2, double y2, double x3, double y3, double xp1, double *xn1, double *xpn1, double h)
{
    double ph;
    ph = xp1 + (h * 0.5) * fx1(x1, y1, x2, y2, x3, y3);
    *xn1 = x1 + h * ph;
    *xpn1 = ph + (h * 0.5) * fx1(*xn1, y1, x2, y2, x3, y3);
}
void gy1(double x1, double y1, double x2, double y2, double x3, double y3, double xp1, double *xn1, double *xpn1, double h)
{
    double ph;
    ph = xp1 + (h * 0.5) * fy1(x1, y1, x2, y2, x3, y3);
    *xn1 = y1 + h * ph;
    *xpn1 = ph + (h * 0.5) * fy1(x1, *xn1, x2, y2, x3, y3);
}
void gx2(double x1, double y1, double x2, double y2, double x3, double y3, double xp1, double *xn1, double *xpn1, double h)
{
    double ph;
    ph = xp1 + (h * 0.5) * fx2(x1, y1, x2, y2, x3, y3);
    *xn1 = x2 + h * ph;
    *xpn1 = ph + (h * 0.5) * fx2(x1, y1, *xn1, y2, x3, y3);
}
void gy2(double x1, double y1, double x2, double y2, double x3, double y3, double xp1, double *xn1, double *xpn1, double h)
{
    double ph;
    ph = xp1 + (h * 0.5) * fy2(x1, y1, x2, y2, x3, y3);
    *xn1 = y2 + h * ph;
    *xpn1 = ph + (h * 0.5) * fy2(x1, y1, x2, *xn1, x3, y3);
}
void gx3(double x1, double y1, double x2, double y2, double x3, double y3, double xp1, double *xn1, double *xpn1, double h)
{
    double ph;
    ph = xp1 + (h * 0.5) * fx3(x1, y1, x2, y2, x3, y3);
    *xn1 = x3 + h * ph;
    *xpn1 = ph + (h * 0.5) * fx3(x1, y1, x2, y2, *xn1, y3);
}
void gy3(double x1, double y1, double x2, double y2, double x3, double y3, double xp1, double *xn1, double *xpn1, double h)
{
    double ph;
    ph = xp1 + (h * 0.5) * fy3(x1, y1, x2, y2, x3, y3);
    *xn1 = y3 + h * ph;
    *xpn1 = ph + (h * 0.5) * fy3(x1, y1, x2, y2, x3, *xn1);
}
int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double dt1, dt2;
    double dt = 0.000001;
    double x1, y1, x2, y2, x3, y3, xp1, yp1, xp2, yp2, xp3, yp3, xn1, yn1, xn2, yn2, xn3, yn3, xpn1, ypn1, xpn2, ypn2, xpn3, ypn3;
    double cx1, cy1, cx2, cy2, cx3, cy3;
    double d, d1, d2;
    int n;
    FILE *fp;

    d = pow(2, 1.0 / 3.0);
    d1 = 1 / (2 - d);
    d2 = -d / (2 - d);
    dt1 = dt * d1;
    dt2 = dt * d2;
    /* initial condition */
    x1 = 0;
    y1 = 2;
    x2 = 0;
    y2 = -2;
    x3 = 2;
    y3 = 0;
    xp1 = 0.633333;
    yp1 = 0.4;
    xp2 = -0.166666;
    yp2 = -0.4;
    xp3 = -0.4666666;
    yp3 = 0;
    cx1 = x1;
    cy1 = y1;
    cx2 = x2;
    cy2 = y2;
    cx3 = x3;
    cy3 = y3;
    /* file open */
    fp = fopen("three.txt", "w");
    setvbuf(fp, NULL, _IOFBF, 1024 * 1024);
    /* time development */
    for (n = 1; n < 50000000; n++)
    {
        if (rank == 0)
        {
            gx1(x1, cy1, cx2, cy2, cx3, cy3, xp1, &xn1, &xpn1, dt1);
            x1 = xn1;
            xp1 = xpn1;
            gx1(x1, cy1, cx2, cy2, cx3, cy3, xp1, &xn1, &xpn1, dt2);
            x1 = xn1;
            xp1 = xpn1;
            gx1(x1, cy1, cx2, cy2, cx3, cy3, xp1, &xn1, &xpn1, dt1);
            x1 = xn1;
            xp1 = xpn1;
        }
        if (rank == 1)
        {
            gx2(cx1, cy1, x2, cy2, cx3, cy3, xp2, &xn2, &xpn2, dt1);
            x2 = xn2;
            xp2 = xpn2;
            gx2(cx1, cy1, x2, cy2, cx3, cy3, xp2, &xn2, &xpn2, dt2);
            x2 = xn2;
            xp2 = xpn2;
            gx2(cx1, cy1, x2, cy2, cx3, cy3, xp2, &xn2, &xpn2, dt1);
            x2 = xn2;
            xp2 = xpn2;
        }
        if (rank == 2)
        {
            gx3(cx1, cy1, cx2, cy2, x3, cy3, xp3, &xn3, &xpn3, dt1);
            x3 = xn3;
            xp3 = xpn3;
            gx3(cx1, cy1, cx2, cy2, x3, cy3, xp3, &xn3, &xpn3, dt2);
            x3 = xn3;
            xp3 = xpn3;
            gx3(cx1, cy1, cx2, cy2, x3, cy3, xp3, &xn3, &xpn3, dt1);
            x3 = xn3;
            xp3 = xpn3;
        }
        if (rank == 3)
        {
            gy1(cx1, y1, cx2, cy2, cx3, cy3, yp1, &yn1, &ypn1, dt1);
            y1 = yn1;
            yp1 = ypn1;
            gy1(cx1, y1, cx2, cy2, cx3, cy3, yp1, &yn1, &ypn1, dt2);
            y1 = yn1;
            yp1 = ypn1;
            gy1(cx1, y1, cx2, cy2, cx3, cy3, yp1, &yn1, &ypn1, dt1);
            y1 = yn1;
            yp1 = ypn1;
        }
        if (rank == 4)
        {
            gy2(cx1, cy1, cx2, y2, cx3, cy3, yp2, &yn2, &ypn2, dt1);
            y2 = yn2;
            yp2 = ypn2;
            gy2(cx1, cy1, cx2, y2, cx3, cy3, yp2, &yn2, &ypn2, dt2);
            y2 = yn2;
            yp2 = ypn2;
            gy2(cx1, cy1, cx2, y2, cx3, cy3, yp2, &yn2, &ypn2, dt1);
            y2 = yn2;
            yp2 = ypn2;
        }
        if (rank == 5)
        {
            gy3(cx1, cy1, cx2, cy2, cx3, y3, yp3, &yn3, &ypn3, dt1);
            y3 = yn3;
            yp3 = ypn3;
            gy3(cx1, cy1, cx2, cy2, cx3, y3, yp3, &yn3, &ypn3, dt2);
            y3 = yn3;
            yp3 = ypn3;
            gy3(cx1, cy1, cx2, cy2, cx3, y3, yp3, &yn3, &ypn3, dt1);
            y3 = yn3;
            yp3 = ypn3;
        }
        MPI_Bcast(&x1, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Bcast(&x2, 1, MPI_DOUBLE, 1, MPI_COMM_WORLD);
        MPI_Bcast(&x3, 1, MPI_DOUBLE, 2, MPI_COMM_WORLD);
        MPI_Bcast(&y1, 1, MPI_DOUBLE, 3, MPI_COMM_WORLD);
        MPI_Bcast(&y2, 1, MPI_DOUBLE, 4, MPI_COMM_WORLD);
        MPI_Bcast(&y3, 1, MPI_DOUBLE, 5, MPI_COMM_WORLD);
        cx1 = x1;
        cy1 = y1;
        cx2 = x2;
        cy2 = y2;
        cx3 = x3;
        cy3 = y3;
        if (rank == 0 && n % 5000 == 0)
        {
            fprintf(fp, "%6.2f  %6.2f  %6.2f  %6.2f  %6.2f  %6.2f\n", cx1, cy1, cx2, cy2, cx3, cy3);
        }
    }
    /* end of time development */
    MPI_Finalize();
    fclose(fp);
    return 0;
}
