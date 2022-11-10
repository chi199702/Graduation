#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif

#include <getopt.h>
#include <TArm.h>

#ifdef __cplusplus
}
#endif

using namespace std;

int main() {
    FILE *fp_dense_wrw = fopen("/home/cwm/Graduation/tensor/data/re.tns", "w");
    tnsDenseMatrix mtxA;
    tnsDenseMatrix mtxB;
    tnsNewDenseMatrix(&mtxA, 50, 50);
    tnsConstantDenseMatrix(&mtxA, 2);
    tnsNewDenseMatrix(&mtxB, 50, 50);
    tnsConstantDenseMatrix(&mtxB, 3);
    tnsHadamardDenmat_rw(&mtxA, &mtxB);
    tnsDumpDenseMatrix(&mtxA, fp_dense_wrw);
    cout << mtxA.nrows << " " << mtxA.ncols << endl;
    tnsFreeDenseMatrix(&mtxA);
    return 0;
}