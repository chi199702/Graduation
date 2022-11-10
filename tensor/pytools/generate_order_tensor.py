
import math
import random
import sys
import numpy as np


if sys.version_info < (3,):
    range = xrange
    

def human_size(nbytes):
    if nbytes < 1024000:
        if nbytes < 1000:
            return '%d bytes' % nbytes
        else:
            return '%.1f KiB' % (nbytes / 1024.0)
    else:
        if nbytes < 1048576000:
            return '%.1f MiB' % (nbytes / 1048576.0)
        else:
            return '%.1f GiB' % (nbytes / 1073741824.0)

def main(argv):
    if len(argv) < 3:
        print('Usage:   %s output.tns [nonzero_rate%%]mode_dimension ...' % argv[0])
        print()
        print('Example: %s output.tns 10000 50%%1024 2%%4096' % argv[0])
        print()
        print('Each non-zero element will be a gaussian random number (mu=0, sigma=1).')
        print()
        return 1
        

    output = argv[1]
    nnz = int(argv[2])
    rates = []
    dims = []
    for i in argv[3:]:
        if '%' in i:
            rate, dim = i.split('%', 1)
            rates.append(float(rate) * 0.01)
            dims.append(int(dim))
        else:
            rates.append(1)
            dims.append(int(i))
    ndims = len(dims)


    tensor = []
    coo_array_list = []
    for i in range(ndims):
        # 二项分布
        # inds = np.random.binomial(n=dims[i], p=0.1, size=(nnz), dtype=np.int64)
        # 泊松分布（只考虑了nnz的数量，没有dim的约束）
        # inds = np.random.poisson(lamp=100, size=(nnz), dtype=np.int64)
        # 指数分布
        inds = np.random.exponential(scale=0.1, size=(nnz))
        inds = inds * dims[i]
        np.minimum(inds, dims[i]-1, inds)
        # inds 
        # 平均分布
        # inds = np.random.randint(low=0, high=dims[i], size=(nnz), dtype=np.int64)
        inds = inds.tolist()
        # inds.sort()
        coo_array_list.append(inds)
        print("mode %d generated succcess!" % (i))
    coo_array_list = list(zip(*coo_array_list))
    coo_array_finally = list(set(coo_array_list))
    # coo_array_finally = sorted(set(coo_array_list), key=coo_array_list.index)
    print("mode %d generated succcess!" % (i))
    nnz_finally = nnz - (len(coo_array_list) - len(coo_array_finally))
    # 产生对应的值
    vals = np.random.randn(nnz_finally).tolist()
    
    # 输出到文件
    print('goal is %d, actually is %d non-zero elements estimated.' % (nnz, nnz_finally))
    written = 0
    percent = 0
    f = open(output, 'w')
    f.write('%d\n' % ndims)
    f.write('\t'.join(map(str, dims)))
    f.write('\n')

    # 写入所有非零元的值
    for nnz_i in range(nnz_finally):
        for dim_i in range(ndims):
            f.write('%d\t' % (coo_array_finally[nnz_i][dim_i]))
        f.write('% .3f\n' % vals[nnz_i])

        written += 1
        if nnz_finally != 0:
            new_percent = int(written * 100.0 / nnz_finally)
            if new_percent < 100 and new_percent != percent:
                percent = new_percent
                print('%3d%% completed, %d generated, %s written.' % (percent, written, human_size(f.tell())), end='\r', flush=True)
    print('100%% completed, %d generated, %s written.' % (written, human_size(f.tell())))
    f.close()
    print('Successfully written into %s.' % output)
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv))


       # 所有都是0-1的随机数
    # tensor = np.random.rand(size=(dims))
    # for i in range(ndims):
    #     tensor[:, i] = 
    
    # 根据不同维度缩放
    # 生成每阶的概率数组，并根据概率选取值
    # for i in range(ndims):
    #     coo_list = []
    #     proba_list = []
    #     proba_list = np.random.random(dims[i])
    #     proba_list /= proba_list.sum()



        
        







