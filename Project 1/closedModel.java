// a Java program for solving M/M/l/N/N
// closed queuing model recursively

   public class closedModel {
    public static void main (String[] args) {
    double[] Qi = new double [500];
    double[] Rprime = new double [500];
    double[] X = new double [500];

    int m = 1;              // # of queuing node
    int N = 500;              // # of customers

    double Di = 0.25;       // service demand
    double Z = 2.0;                  // think time
    if (args.length ==2) {
       Di = Double.valueOf(args[0]).doubleValue();
       Z = Double.valueOf(args[1]).doubleValue();

    }

    Qi[0]=0.0;

    // iterate over the # of customers
    for (int n = 1; n < N; n++) {
       Rprime [n] = Di*(1.0 + Qi[n - 1]);
       X[n] = n/(Z + Rprime[n]);
       Qi[n] = X[n]*Rprime[n];

       // open model
       double Ui = X[n]* Di  *100;
       double Ri = Di/(1.0 - Ui*0.01);

       System.out.println("n =," + n + ",Ui=,"
              + Ui+ ",Rprime[n]=,"+
              Rprime[n]+"," + Ri+",X[n]=,"
              + X[n]+",Q[n]=,"+Qi[n]);
    }
    }
}