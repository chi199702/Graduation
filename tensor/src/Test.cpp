#ifdef __cplusplus
extern "C" {
#endif

#include <getopt.h>
#include <TArm.h>

#ifdef __cplusplus
}
#endif

int main() {
    FILE* fp_w = fopen("/home/cwm/Graduation/tensor/data/re.tns", "w");
    //测试张量排序
    tnsSparseTensor tsr;
    FILE* fp_r = fopen("/home/cwm/Graduation/tensor/data/art.tns", "r");
    printf("从文件中读取稀疏张量\n");
    tnsLoadSparseTensor(&tsr, fp_r, 1);
    printf("从文件中读取稀疏张量完毕\n");
    tnsDumpSparseTensor(&tsr, fp_w);
    printf("打印稀疏张量完毕\n");
    tnsSparseTensor tsr_2;
    tnsNewSparseTensor(&tsr_2, tsr.ndims, tsr.nmodes, tsr.nnz);
    tnsIndex order[3]={2,0,1};
    tnsPermuteSpatsr(&tsr_2, &tsr, order);
    tnsDumpSparseTensor(&tsr_2, fp_w);

    tnsFreeSparseTensor(&tsr);
    tnsFreeSparseTensor(&tsr_2);
    fclose(fp_r);
    fclose(fp_w);

    return 0;
}
