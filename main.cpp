/*interpolating Polynomials
  Solving the Matrix formed from the entered points
  to get the polynomial equation whose curve passes
  through these points
  FCAI-CU 2019
  */

#include <bits/stdc++.h>
using namespace std;

void printmatrix(double **arr,int n);

int GaussElimination(double **mat,int n);

void swap_row(double **mat, int i, int j, int n);

void backSub(double **mat,int n);

double fastPower(int n, int p);

int main()
{
    cout<<"Enter no. of Points: ";
    int numOfPoints;
Valid:
    cin>>numOfPoints;
    if (numOfPoints<2)
    {
        cout<<"Please Enter Valid number of points:"<<endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto Valid;
    }
    vector<pair<int,int>> points(numOfPoints);

    cout<<"Enter the points X Co-ordinate then Y Co-ordinate: "<<endl;
    for (int i=0; i<numOfPoints; i++)
    {
        int x,y;
        cin>>x>>y;
        points[i].first = x;
        points[i].second = y;
    }
    int n = numOfPoints;
    double **Matrix = new double*[n];

    for (int i=0; i<n; i++)
        Matrix[i] = new double[n+1];


    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n+1; j++)
        {
            if (j==n)
                Matrix[i][j] = points[i].second;
            else
            {
                Matrix[i][j] = fastPower(points[i].first,n-j-1);
            }
        }
    }

    /* cout<<"Enter the Matrix row by row:"<<endl;

     for (int i=0; i<n; i++)
         for (int j=0; j<n+1; j++)
             cin>>Matrix[i][j];*/

    cout<<"\n\n";
    cout<<"Formed Matrix:\n"<<endl;
    printmatrix(Matrix,n);

    GaussElimination(Matrix,n);
    cout<<"Matrix after Gaussian Elimination:\n"<<endl;
    printmatrix(Matrix,n);

    backSub(Matrix,n);
}

int GaussElimination(double **mat,int n)
{
    for (int k=0; k<n; k++)
    {
        int i_max = k;
        int v_max = mat[i_max][k];

        for (int i = k+1; i < n; i++)
            if (abs(mat[i][k]) > v_max)
                v_max = mat[i][k], i_max = i;

        if (!mat[k][i_max])
            return k;

        if (i_max != k)
            swap_row(mat, k, i_max,n);


        for (int i=k+1; i<n; i++)
        {
            double f = mat[i][k]/mat[k][k];

            for (int j=k+1; j<=n; j++)
                mat[i][j] -= mat[k][j]*f;

            mat[i][k] = 0;
        }
    }
    return -1;
}

void backSub(double **mat,int n)
{
    double x[n];
    for (int i = n-1; i >= 0; i--)
    {
        x[i] = mat[i][n];
        for (int j=i+1; j<n; j++)
        {
            x[i] -= mat[i][j]*x[j];
        }
        x[i] = x[i]/mat[i][i];
    }

    cout<<"The Polynomial is: ";
    for (int i=0; i<n; i++)
    {
        if (x[i]>0 && i!=0)
            cout<<"+";
        else if (x[i] == 0)
        {
            continue;
        }
        if ((n-i-1)==0) cout<<x[i];
        else if ((n-i-1)==1)
        {
            x[i]!=1?cout<<x[i]:cout<<"";
            cout<<"X";
        }
        else
        {
             x[i]!=1?cout<<x[i]:cout<<"";
             cout<<"X^"<<n-i-1;
        }

    }
}
double fastPower(int n, int p)
{
    int res = 1;

    while (p > 0)
    {
        if (p & 1)
            res = res*n;
        p = p>>1;
        n = n*n;
    }
    return res;
}
void swap_row(double **mat, int i, int j,int n)
{
    for (int k=0; k<=n; k++)
    {
        double temp = mat[i][k];
        mat[i][k] = mat[j][k];
        mat[j][k] = temp;
    }
}
void printmatrix(double **arr,int n)
{
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n+1; j++)
        {
            cout << setw(7) << setprecision(4) << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
