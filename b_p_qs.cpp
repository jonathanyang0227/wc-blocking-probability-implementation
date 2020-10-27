#include <bits/stdc++.h>

using namespace std;
int ramdom(double percent)
{
    double n = (double) rand() / (RAND_MAX + 1.0);
    // cout<<n<<endl;
    if (n < percent) {
        return 1;
    } else {
        return 0;
    }
}
int main()
{
    int S[3] = {1, 5, 10};
    srand(time(NULL));
    int Q, i, j, service_num;
    double arrival, service, lamda, mu,erlange;
    FILE *out = fopen("blocking probability_QS.csv", "w");
    i = 0;
    for (i = 0; i < 3; i++) {
        service_num = S[i];
        Q=service_num;
        double delta = 0.001;
        fprintf(out, "sever =%d\nQ=%d\n", service_num,Q);
        fprintf(out,"Erlang\t\tBlocking probability\n");
        int order = 1;
        for (lamda = 0.01; lamda <= 10; lamda *= 10) {
            arrival = (1 - exp((-lamda) * delta));
            for (mu = 0.01; mu <= 10.24; mu *= 4) {
                //fprintf(out,"")
                int cb = 0;     // counts of block num
                int carri = 0;  // counts of arrival time
                int num_in_service = 0;
                int num_in_Q = 0;
                double sum = 0, bp;
                for (j = 0; j < 10; j++) {  // runtime
                    for (int k = 0; k < 10000000;
                         k++) {  // time unit=system time/delta
                        if (ramdom(arrival)) {
                            carri += 1;
                            if (num_in_service <
                                service_num) {  // if service not full
                                num_in_service += 1;
                            } else {  // if service is full
                                if (num_in_service == service_num &&
                                    Q > num_in_Q) {
                                    num_in_Q += 1;
                                } else if (num_in_service == service_num &&
                                           Q == num_in_Q) {
                                    cb += 1;
                                }
                            }
                        }
                        // if (num_in_service > 0) {  // if service is occupied
                        service = (1 - exp((-mu) * delta * num_in_service));
                        if (ramdom(service)) {
                            if (num_in_Q > 0 && Q > 0) {
                                num_in_Q--;
                            } else if (num_in_Q == 0) {
                                num_in_service--;
                            }
                        }
                    }
                    bp = (double) cb / (double) carri;
                    sum = bp + sum;
                }
                erlange=lamda/mu;
                fprintf(out, "%7f", erlange);
                double ans = sum / 10;
                fprintf(out, "\tbp_ %d =  %7f\n", order, ans);
                order++;
            }
        }
        fprintf(out, "%s\n",
                "============================================================");
    }
    fclose(out);
    return 0;
}
